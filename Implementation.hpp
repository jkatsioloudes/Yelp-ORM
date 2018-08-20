#ifndef IMPLEMENTATION_H
#define IMPLEMENTATION_H

#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

class Reviews {
public:
	std::vector<std::string> business_ids;
	std::vector<int> stars;
};

class Businesses {
public:
	// The following vectors all have the same size

	std::vector<std::string> ids;
	std::vector<double> latitudes;
	std::vector<double> longitudes;
};

// select all businesses in the given coordinate square (latMin, laxMax, ...)
// return an unordered set (i.e., a hashtable) containing their ids
std::unordered_set<std::string> getQualifyingBusinessesIDs(Businesses const& b, float latMin, float latMax, float longMin, float longMax);

// check for every review if its business id is present in the set of qualifying business ids (which
// you generated in the method above)
// if it is, increase the counter in the appropriate bucket
std::vector<unsigned long>
aggregateStarsOfQualifyingBusinesses(Reviews const& r, std::unordered_set<std::string> const& qualifyingBusinesses);

std::vector<std::string> getQualifyingBusinessesIDsVector(Businesses const& b, float latMin, float latMax, float longMin, float longMax);

std::vector<unsigned long>
performNestedLoopJoinAndAggregation(Reviews const& r, std::vector<std::string> const& qualies);

#endif /* IMPLEMENTATION_H */
