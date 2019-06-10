#include "pch.h"
#include "FEEccentricity.h"
#include <iostream>


FEEccentricity::FEEccentricity(YAML::Node& yamlNode) {
	if (!assignIndependentAttributes(yamlNode)) {
		throw std::runtime_error("Eccentricity error: Mandatory attributes missing.");
	}
	this->type = ECCENT;
}

FEEccentricity::FEEccentricity(int id, double eX, double eY, double eZ) {
	//Constructor independent on a YAML::Node.
	setID(id);
	this->eX = eX;
	this->eY = eY;
	this->eZ = eZ;
	this->type = ECCENT;
}

FEEccentricity::~FEEccentricity()
{
}

Identifiable::Type FEEccentricity::getType() { return this->type; }
std::string FEEccentricity::getTypeAsString() { return "ECCENT"; }


bool FEEccentricity::assignIndependentAttributes(YAML::Node & yamlNode)
{
	/* Assign the mandatory values (eccID, eX, eY, eZ).
	* If the values are defined in the node, assign them and return true.
	* Else, return false.
	*/
	if (yamlNode["eccID"] && yamlNode["eX"]
		&& yamlNode["eY"] && yamlNode["eZ"]) {
		setID(yamlNode["eccID"].as<int>());
		this->eX = yamlNode["eX"].as<double>();
		this->eY = yamlNode["eY"].as<double>();
		this->eZ = yamlNode["eZ"].as<double>();
		return true;
	}
	return false;
}

void FEEccentricity::printAttributes()	{
	std::cout << "Eccentricity:    id: " << getID() 
		<< ", eX: " << eX
		<< ", eY: " << eY 
		<< ", eZ: " << eZ << std::endl;
}
