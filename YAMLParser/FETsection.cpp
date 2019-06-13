#include "pch.h"
#include "FETsection.h"
#include <iostream>

FETsection::FETsection(YAML::Node& yamlNode) {
	if (!assignIndependentAttributes(yamlNode)) {
		throw std::runtime_error("Tsection error: Mandatory attributes missing.");
	}
	this->type = TSECTION;
}

FETsection::~FETsection() {
}

Identifiable::Type FETsection::getType() { return this->type; }
std::string FETsection::getTypeAsString() {	return "TSECTION"; }

bool FETsection::assignIndependentAttributes(YAML::Node & yamlNode) {
	/* Assign the mandatory values.
	* If the values are defined in the YAML::Node, assign them and return true.
	* Else, return false.
	*/
	if (yamlNode["geoID"] && yamlNode["H"] && yamlNode["T_web"]
		&& yamlNode["Width"] && yamlNode["T_top"]) {
		//Mandatory values
		setID(yamlNode["geoID"].as<int>());		
		this->H = yamlNode["H"].as<double>();
		this->T_web = yamlNode["T_web"].as<double>();
		this->Width = yamlNode["Width"].as<double>();
		this->T_top = yamlNode["T_top"].as<double>();
		return true;
	}	
	return false;
}

void FETsection::printAttributes() {
	std::cout << "Tsection:    id: " << getID()
		<< ", H: " << H
		<< ", T_web: " << T_web
		<< ", Width: " << Width
		<< ", T_top: " << T_top << std::endl;
}
