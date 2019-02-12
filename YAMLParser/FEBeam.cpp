#include "pch.h"
#include "FEBeam.h"
#include <iostream>


FEBeam::FEBeam(YAML::Node yamlNode) {
	if (!setMandatoryValues(yamlNode)) {
		throw std::runtime_error("Error: Mandatory attributes missing.");
	}
	setOptionalValues(yamlNode);
}


FEBeam::~FEBeam()
{
}

bool FEBeam::setMandatoryValues(YAML::Node yamlNode) {
	/* Assign the mandatory values (elemID, node1, node2, material and geoID).
	 * If the values are defined in the node, assign them and return true.
	 * Else, return false.
	*/
	if (yamlNode["elemID"] && yamlNode["node1"] && yamlNode["node2"] &&
							yamlNode["material"] && yamlNode["geoID"]) {
		
		this->id = yamlNode["elemID"].as<int>();
		this->node1 = yamlNode["node1"].as<int>();
		this->node2 = yamlNode["node2"].as<int>();
		this->material = yamlNode["material"].as<int>();
		this->geoID = yamlNode["geoID"].as<int>();
		return true;
	}
	return false;
}

void FEBeam::setOptionalValues(YAML::Node yamlNode) {
	/* Assign the optional values (vecID, eccentricity1 and eccentricity2).
	 * If the value is defined in the YAML node, assign that value.
	 * Else, assign the default value.
	 */
	this->vecID = (yamlNode["vecID"]) ? yamlNode["vecID"].as<int>() : 0;
	this->eccentricity1 = (yamlNode["ecc1"]) ? yamlNode["ecc1"].as<int>() : 0;
	this->eccentricity2 = (yamlNode["ecc2"]) ? yamlNode["ecc2"].as<int>() : 0;
}

void FEBeam::PrintBeam() {
	std::cout << "FEBeam:   id: " << id << ", node1: " << node1 << ", node2: " << node2
		<< ", material: " << material << ", geoID: " << geoID << ", vecID: " << vecID
		<< ", ecc1: " << eccentricity1 << ", ecc2: " << eccentricity2 << std::endl;
}
