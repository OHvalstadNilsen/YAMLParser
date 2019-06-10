#include "pch.h"
#include "FELoadComb.h"
#include <iostream>

FELoadComb::FELoadComb(int loadCombId, std::map<int, double> lcFactors) {
	setID(loadCombId);
	this->loadCombFactors = lcFactors;
	this->type = LOADCOMB;
}

FELoadComb::~FELoadComb() {
}

bool FELoadComb::assignIndependentAttributes(YAML::Node & yamlNode) {
	//Only loadCombId, which is set in constructor.
	return true;
}

void FELoadComb::printAttributes() {
	std::string factorsString;
	std::map<int, double>::iterator it;
	for (it = loadCombFactors.begin(); it != loadCombFactors.end(); ++it) {
		factorsString.append(std::to_string(it->first));
		factorsString.append(": " + std::to_string(it->second));
		factorsString.append(", ");
	}

	std::cout << "LoadComb:    " << "id: " << getID()
		<< " factors: " << factorsString << std::endl;
}
