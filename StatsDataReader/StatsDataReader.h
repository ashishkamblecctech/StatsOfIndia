#include "pch.h"
#include <vector>
#include <string>

struct RegionInfo1 {
	std::string filePath;
	float r, g, b;
	long statePopulation;
		float stateEducation, stateArea;
};

// This class is exported from the dll
class STATSDATAREADER_API StatsDataReader {
public:
	StatsDataReader();
	~StatsDataReader();
	// TODO: add your methods here.

public:
	void dataReader(std::vector <std::string>& stateNames, std::vector<long>& statePopulation,
						std::vector<float>& stateEducation, std::vector<float>& stateArea, std::vector<long>& stateActualPopulation,
							std::vector<float>& stateActualEducation, std::vector<float>& stateActualArea, std::vector <RegionInfo1>& reg);

};