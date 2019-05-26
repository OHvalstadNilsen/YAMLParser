#include "pch.h"
#include "FEPipe.h"
#include <exception>
#include <iostream>

FEPipe::FEPipe(YAML::Node yamlNode) {
	if (!assignIndependentAttributes(yamlNode)) {
		throw std::runtime_error("Pipe error: Mandatory attributes missing.");
	}
	this->type = PIPE;
}

FEPipe::~FEPipe()
{
}

Identifiable::Type FEPipe::getType() { return this->type; }
std::string FEPipe::getTypeAsString() { return "PIPE"; }

bool FEPipe::assignIndependentAttributes(YAML::Node & yamlNode) {
	/* Assign the mandatory values (geoID, D_o, T).
	* If the values are defined in the node, assign them and return true.
	* Else, return false.
	*/
	if (yamlNode["geoID"] && yamlNode["D_o"] && yamlNode["T"]) {
		//Mandatory values
		setID(yamlNode["geoID"].as<int>());
		this->outerDiameter = yamlNode["D_o"].as<double>();
		this->thickness = yamlNode["T"].as<double>();

		//Optional values
		this->shearY = (yamlNode["shearY"]) ? yamlNode["shearY"].as<double>() : 0.5;
		this->shearZ = (yamlNode["shearZ"]) ? yamlNode["shearZ"].as<double>() : 0.5;
		return true;
	}
	return false;
}

void FEPipe::printAttributes() {
	std::cout << "Pipe:    id: " << getID() 
		<< ", D_o: " << outerDiameter
		<< ", T: " << thickness 
		<< ", shearY: " << shearY
		<< ", shearZ: " << shearZ << std::endl;
}
