#include "Implementation.hpp"
#include <iostream>

using namespace std;
//////////////////// Nested Loop Joins ////////////////////

std::vector<std::string> getQualifyingBusinessesIDsVector(Businesses const& b, float latMin, float latMax, float longMin, float longMax) {

	std::vector<std::string> result;

	// iterating using ids.size() exploiting the functional dependency between ids -> latitudes, longitudes
	for (size_t i = 0; i < b.ids.size(); i++) {
		if (b.longitudes[i] >= longMin && b.longitudes[i] <= longMax && b.latitudes[i] >= latMin && b.latitudes[i] <= latMax) {
			result.push_back(b.ids[i]);
		}
	}
	return result;
}

std::vector<unsigned long>
performNestedLoopJoinAndAggregation(Reviews const& r, std::vector<std::string> const& qualifyingBusinessesIDs) {

	// holds the resulting vector of the form (1, 2, 3, 4, 5) where each number holds the corresponding count of stars.
	// for example: (11, 22, 33, 44, 55) means that 1 start was given 11 times, and so on.
	const int STARS_MAX = 6;
	std::vector<unsigned long> result(STARS_MAX);

	for (size_t i = 0; i < r.business_ids.size(); i++) {
		for(size_t j = 0; j < qualifyingBusinessesIDs.size(); j++) {
			// natural join occurs here
			if (r.business_ids[i] == qualifyingBusinessesIDs[j]) {
				// grouping occurs here
				int r_stars = r.stars[i];
				if (r_stars == 0) {
					result[0]++;
				} else if (r_stars == 1) {
					result[1]++;
				} else if (r_stars == 2) {
					result[2]++;
				} else if (r_stars == 3) {
					result[3]++;
				} else if (r_stars == 4) {
					result[4]++;
				} else if (r_stars == 5) {
					result[5]++;
				}
			}
		}
	}
	return result;
}

//////////////////// Hash Join ////////////////////

std::unordered_set<std::string> getQualifyingBusinessesIDs(Businesses const& b, float latMin, float latMax, float longMin, float longMax) {

	std::unordered_set<std::string> result;

	for (size_t i = 0; i < b.ids.size(); i++) {
		if (b.longitudes[i] >= longMin && b.longitudes[i] <= longMax && b.latitudes[i] >= latMin && b.latitudes[i] <= latMax) {
			result.insert(b.ids[i]);
		}
	}
	return result;
}

std::vector<unsigned long>
aggregateStarsOfQualifyingBusinesses(Reviews const& r, std::unordered_set<std::string> const& qualifyingBusinesses) {

	const int STARS_MAX = 6;
	std::vector<unsigned long> result(STARS_MAX);

	for (size_t i = 0; i < r.business_ids.size(); i++) {
		// natural join occurs here
		if (qualifyingBusinesses.count(r.business_ids[i])) {
			// grouping occurs here
			int r_stars = r.stars[i];
			if (r_stars == 0) {
				result[0]++;
			} else if (r_stars == 1) {
				result[1]++;
			} else if (r_stars == 2) {
				result[2]++;
			} else if (r_stars == 3) {
				result[3]++;
			} else if (r_stars == 4) {
				result[4]++;
			} else if (r_stars == 5) {
				result[5]++;
			}
		}
	}
	return result;
}
