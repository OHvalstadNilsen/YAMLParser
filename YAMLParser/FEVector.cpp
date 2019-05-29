#include "pch.h"
#include "FEVector.h"
#include <iostream>


FEVector::FEVector(YAML::Node& yamlNode, std::string vecType) {
	if (!assignIndependentAttributes(yamlNode)) {
		throw std::runtime_error("CoordSys error: Mandatory attributes missing.");
	}
	normalizeVector();
	this->type = VECTOR;
}


FEVector::~FEVector() {
}

//Getters for FEType
Identifiable::Type FEVector::getType() { return this->type; }
std::string FEVector::getTypeAsString() { return "VECTOR"; }

bool FEVector::assignIndependentAttributes(YAML::Node & yamlNode) {
	if (yamlNode["vecID"] && yamlNode["x"] && yamlNode["y"] && yamlNode["z"]) {
		setID(yamlNode["vecID"].as<int>());
		vec[0] = yamlNode["x"].as<double>();
		vec[1] = yamlNode["y"].as<double>();
		vec[2] = yamlNode["z"].as<double>();
		return true;
	}
	return false;
}

void FEVector::normalizeVector() {
	double length = sqrt(vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2]);
	
	if (length == 0) {
		throw std::runtime_error("Vector error: Cannot normalize zero vector");
	}
	else {
		for (int i = 0; i < 3; i++) {
			vec[i] = vec[i] / length;
		}
	}
}

void FEVector::printAttributes() {
	std::cout << "Vector:	id: " << getID()
		<< ", components (xyz): ";

	for (int i = 0; i < 3; i++) {
		std::cout << vec[i] << "\t";
	}
	std::cout << std::endl;
}
