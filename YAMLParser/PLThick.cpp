#include "pch.h"
//#include "PLThick.h"
//#include <iostream>
//
//
//PLThick::PLThick(YAML::Node& yamlNode) {
//	if (!setMandatoryValues(yamlNode)) {
//		throw std::runtime_error("PLThick error: Mandatory attributes missing.");
//	}
//	setOptionalValues(yamlNode);
//}
//
//PLThick::~PLThick() {}
//
//bool PLThick::setMandatoryValues(YAML::Node & yamlNode) {
//	if (yamlNode["id"] && yamlNode["T"]) {
//		setID(yamlNode["id"].as<int>());
//		this->T = yamlNode["T"].as<int>();
//		return true;
//	}
//	return false;
//}
//
//void PLThick::setOptionalValues(YAML::Node & yamlNode) {
//	//This record has no optional values.
//}
//
//void PLThick::printAttributes() {
//	std::cout << "PLThick:    "
//		<< "id: " << getID()
//		<< ", T: " << this->T;
//}
