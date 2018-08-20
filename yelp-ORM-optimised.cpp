#include <cstdlib>
#include <fstream>
#include <future>
#include <iostream>
#ifdef __APPLE__
#include <libproc.h>
#endif
#include <numeric>
#include <set>
#include <unistd.h>

#include "Implementation.hpp"

std::string getExecutablePath() {
	using namespace std;
	char processPath[4096]{};
#ifdef __APPLE__
	auto ret = proc_pidpath(getpid(), processPath, sizeof(processPath));
	if(ret == 0)
		cout << "program is stored to deep in the filesystem" << endl;
#else
	char szTmp[32];
	sprintf(szTmp, "/proc/%d/exe", getpid());
	int bytes = readlink(szTmp, processPath, 4095);
	if(bytes == 4095)
		cout << "program is stored to deep in the filesystem" << endl;
#endif
	return string(processPath).substr(0, string(processPath).find_last_of("/"));
}

std::shared_ptr<Reviews const> getReviews() {
	using namespace std;
	ifstream reviewStream;
	reviewStream.open(getExecutablePath() + "/review.csv");
	if(!reviewStream.is_open()) {
		std::cout << "could not open review.csv, was expecting it in directory " << getExecutablePath()
							<< std::endl;
		exit(1);
	}
	auto r = make_unique<Reviews>();
	while(reviewStream.good()) {
		string businessID, stars;
		getline(reviewStream, businessID, '\t');
		getline(reviewStream, stars, '\n');
		r->business_ids.push_back(businessID);
		r->stars.push_back(atoi(stars.c_str()));
	}
	return std::shared_ptr<Reviews const>(const_cast<Reviews const*>(r.release()));
}

std::shared_ptr<Businesses const> getBusinesses() {
	using namespace std;
	ifstream businessStream;
	businessStream.open(getExecutablePath() + "/business.csv");
	if(!businessStream.is_open()) {
		std::cout << "could not open business.csv, was expecting it in directory "
							<< getExecutablePath() << std::endl;
		exit(1);
	}
	auto r = make_unique<Businesses>();
	while(businessStream.good()) {
		string businessID, latitude, longitude;
		getline(businessStream, businessID, '\t');
		getline(businessStream, latitude, '\t');
		getline(businessStream, longitude, '\n');
		r->ids.emplace_back(businessID);
		r->latitudes.push_back(::atof(latitude.c_str()));
		r->longitudes.push_back(::atof(longitude.c_str()));
	}
	return std::shared_ptr<Businesses const>(const_cast<Businesses const*>(r.release()));
}

std::vector<size_t> performQueryUsingHashJoin(std::shared_ptr<Reviews const> r,
																							std::shared_ptr<Businesses const> b, float latMin,
																							float latMax, float longMin, float longMax) {
	using namespace std;
	//////////////////// Build Side ////////////////////

	auto buildStart = chrono::high_resolution_clock::now();
	auto qualifyingBusinesses = getQualifyingBusinessesIDs(*b, latMin, latMax, longMin, longMax);
	std::cout << "build: " << (chrono::duration_cast<chrono::milliseconds>(
																 chrono::high_resolution_clock::now() - buildStart)
																 .count())
						<< std::endl;

	//////////////////// Probe Side ///////////////////
	//
	// This side is parallelized
	//
	///////////////////////////////////////////////////

	auto probeStart = chrono::high_resolution_clock::now();

	std::vector<future<vector<size_t>>> futures;
	// auto const threads = 4;
	// for(size_t i = 0; i < threads; i++)
	// 	futures.push_back(std::async(std::launch::async, aggregateStarsOfQualifyingBusinesses, *r,
	// 															 i * r->stars.size() / threads, (i + 1) * r->stars.size() /
	// threads,
	// 															 qualifyingBusinesses));
	futures.push_back(std::async(std::launch::async, aggregateStarsOfQualifyingBusinesses, *r,
															 qualifyingBusinesses));

	vector<size_t> groups;
	for(auto& it : futures) {
		auto groups1 = it.get();
		if(groups.size() < groups1.size())
			groups.resize(groups1.size());
		for(size_t i = 0; i < groups1.size(); i++)
			groups[i] += groups1[i];
	}

	std::cout << "probe: " << (chrono::duration_cast<chrono::milliseconds>(
																 chrono::high_resolution_clock::now() - probeStart)
																 .count())
						<< std::endl;

	//////////////////// Output ////////////////////
	return groups;
}

////////////////////////////////////////

std::vector<size_t> performQueryUsingNestedLoopJoin(std::shared_ptr<Reviews const> r,
																										std::shared_ptr<Businesses const> b,
																										float latMin, float latMax, float longMin,
																										float longMax) {

	using namespace std;
	auto selectStart = chrono::high_resolution_clock::now();
	auto qualies = getQualifyingBusinessesIDsVector(*b, latMin, latMax, longMin, longMax);
	std::cout << "select: " << (chrono::duration_cast<chrono::milliseconds>(
																	chrono::high_resolution_clock::now() - selectStart)
																	.count())
						<< std::endl;

	auto joinStart = chrono::high_resolution_clock::now();

	auto groups = performNestedLoopJoinAndAggregation(*r, qualies);

	std::cout << "nested loops join: " << (chrono::duration_cast<chrono::milliseconds>(
																						 chrono::high_resolution_clock::now() - joinStart)
																						 .count())
						<< std::endl;

	return groups;
}

std::vector<size_t> printGroups(std::vector<size_t> groups) {
	using namespace std;
	auto outputCount = 0;
	for(size_t i = 0; i < groups.size(); i++)
		if(groups[i])
			cout << (outputCount++ ? ", " : "") << i << ": " << groups[i];
	return groups;
}

void checkResults(std::vector<size_t> groups, int queryNumber) {
	auto failure = false;
	std::vector<unsigned long> fixture = std::vector<std::vector<unsigned long>>{
			{0, 137039, 111817, 174317, 337639, 410518},
			{0, 28781, 19532, 27541, 56435, 83655},
			{0, 95, 38, 59, 124, 236},
			{0, 122, 84, 108, 244, 551},
	}[queryNumber];
	for(size_t i = 0; i < 6; i++) {
		failure |= (groups[i] != fixture[i]);
	}
	std::cout << "...: " << (failure ? "failed" : "passed") << std::endl;
}

int main(int, char**) {
	using namespace std;

	auto r = getReviews();
	auto b = getBusinesses();

	checkResults(printGroups(performQueryUsingHashJoin(r, b, 30.0, 45.7, -100.0, -1.0)), 0);
	checkResults(printGroups(performQueryUsingHashJoin(r, b, 4.0, 40., -90.0, -40.0)), 1);
	checkResults(printGroups(performQueryUsingHashJoin(r, b, 42.0, 43.0, -89.45, -89.25)), 2);
	checkResults(printGroups(performQueryUsingHashJoin(r, b, 42.0, 43.0, -89.65, -89.45)), 3);
	checkResults(printGroups(performQueryUsingNestedLoopJoin(r, b, 42.0, 43.0, -89.45, -89.25)), 2);
	checkResults(printGroups(performQueryUsingNestedLoopJoin(r, b, 42.0, 43.0, -89.65, -89.45)), 3);
	return 0;
}
