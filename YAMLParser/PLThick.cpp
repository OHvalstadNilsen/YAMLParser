#include "pch.h"
#include "PLThick.h"
#include <iostream>

PLThick::PLThick(YAML::Node& yamlNode) {
	if (!assignIndependentAttributes(yamlNode)) {
		throw std::runtime_error("PLThick error: Mandatory attributes missing.");
	}
}

PLThick::~PLThick() {}

bool PLThick::assignIndependentAttributes(YAML::Node & yamlNode)
{
	if (yamlNode["geoID"] && yamlNode["T"]) {
		setID(yamlNode["geoID"].as<int>());
		this->T = yamlNode["T"].as<double>();
		return true;
	}
	return false;
}

void PLThick::printAttributes() {
	std::cout << "PLThick:    "
		<< "id: " << getID()
		<< ", T: " << this->T
		<< std::endl;
}