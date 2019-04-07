#include "pch.h"
#include "FETrishell.h"
#include <iostream>


FETrishell::FETrishell(YAML::Node yamlNode) {
	if (!setMandatoryValues(yamlNode)) {
		throw std::runtime_error("Trishell error: Mandatory attributes missing.");
	}
	setOptionalValues(yamlNode);
}


FETrishell::~FETrishell()
{
}

std::string FETrishell::getTypeAsString() {	return "TRISHELL"; }

bool FETrishell::setMandatoryValues(YAML::Node& yamlNode) {
	/* Assign the mandatory values (elemID, node1, node2, node3, material and geoID).
	* If the values are defined in the node, assign them and return true.
	* Else, return false.
	*/
	bool isValid = false;
	if (yamlNode["elemID"] && yamlNode["material"] && yamlNode["geoID"]) {
		int id = yamlNode["elemID"].as<int>();
		setID(id);

		this->material = yamlNode["material"].as<int>();
		this->geoID = yamlNode["geoID"].as<int>();
		isValid = setNodes(yamlNode);
		return isValid;
	}
	return false;
}

void FETrishell::setOptionalValues(YAML::Node& yamlNode) {
	/* Assign the optional values (vecID, eccentricity1, eccentricity2 and eccentricity3).
	 * If the value is defined in the YAML node, assign that value.
	 * Else, assign the default value.
	 */
	this->coordID = (yamlNode["coordID"]) ? yamlNode["coordID"].as<int>() : 0;
	this->eccentricity1 = (yamlNode["ecc1"]) ? yamlNode["ecc1"].as<int>() : 0;
	this->eccentricity2 = (yamlNode["ecc2"]) ? yamlNode["ecc2"].as<int>() : 0;
	this->eccentricity3 = (yamlNode["ecc3"]) ? yamlNode["ecc3"].as<int>() : 0;
}

bool FETrishell::setNodes(YAML::Node yamlNode) {
	/*
	 * If the nodes are given on the form
	 * nodes: [ID for node1, ID for node2, ...]
	 */
	if (yamlNode["nodes"].size() == 3) {
		this->node1 = yamlNode["nodes"][0].as<int>();
		this->node2 = yamlNode["nodes"][1].as<int>();
		this->node3 = yamlNode["nodes"][2].as<int>();
		return true;
	}
	/*
	 * If the nodes are given on the form
	 * node1: Id for node1
	 * node2: Id for node2
	 * ... 
	 */
	else if (yamlNode["node1"] && yamlNode["node2"] && yamlNode["node3"]) {
		this->node1 = yamlNode["node1"].as<int>();
		this->node2 = yamlNode["node2"].as<int>();
		this->node3 = yamlNode["node3"].as<int>();
		return true;
	}
	return false;
}

void FETrishell::printAttributes() {
	std::cout << "FETrishell:   id: " << getID() << ", node1: " << node1 << ", node2: " << node2
		<<", node3: " << node3 << ", material: " << material << ", geoID: " << geoID 
		<< ", coordID: " << coordID << ", ecc1: " << eccentricity1 
		<< ", ecc2: " << eccentricity2 << ", ecc3: " << eccentricity3 << std::endl;
}
