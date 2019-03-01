#include "pch.h"
#include "FEQuadshell.h"
#include <iostream>

FEQuadshell::FEQuadshell(YAML::Node& yamlNode) {
	if (!setMandatoryValues(yamlNode)) {
		throw std::runtime_error("Quadshell error: Mandatory attributes missing.");
	}
	setOptionalValues(yamlNode);
}


FEQuadshell::~FEQuadshell()
{
}

bool FEQuadshell::setMandatoryValues(YAML::Node & yamlNode) {
	/* Assign the mandatory values (elemID, node1, node2, node3, node4, 
	* material and geoID).
	* If the values are defined in the node, assign them and return true.
	* Else, return false.
	*/
	bool isValid = false;
	if (yamlNode["elemID"] && yamlNode["material"] && yamlNode["geoID"]) {
		this->id = yamlNode["elemID"].as<int>();
		this->material = yamlNode["material"].as<int>();
		this->geoID = yamlNode["geoID"].as<int>();
		isValid = setNodes(yamlNode);
		return isValid;
	}
	return false;
}

void FEQuadshell::setOptionalValues(YAML::Node & yamlNode) {
	/* Assign the optional values (vecID, eccentricity1, eccentricity2,
	* eccentricity3, and eccentricity4).
	* If the value is defined in the YAML node, assign that value.
	* Else, assign the default value.
	*/
	this->coordID = (yamlNode["coordID"]) ? yamlNode["coordID"].as<int>() : 0;
	this->ecc1 = (yamlNode["ecc1"]) ? yamlNode["ecc1"].as<int>() : 0;
	this->ecc2 = (yamlNode["ecc2"]) ? yamlNode["ecc2"].as<int>() : 0;
	this->ecc3 = (yamlNode["ecc3"]) ? yamlNode["ecc3"].as<int>() : 0;
	this->ecc4 = (yamlNode["ecc4"]) ? yamlNode["ecc4"].as<int>() : 0;
}

bool FEQuadshell::setNodes(YAML::Node& yamlNode) {
	/*
	 * If the nodes are given on the form
	 * nodes: [ID for node1, ID for node2, ...]
	 */
	if (yamlNode["nodes"].size() == 4) {
		this->node1 = yamlNode["nodes"][0].as<int>();
		this->node2 = yamlNode["nodes"][1].as<int>();
		this->node3 = yamlNode["nodes"][2].as<int>();
		this->node4 = yamlNode["nodes"][3].as<int>();
		return true;
	}
	/*
	 * If the nodes are given on the form
	 * node1: Id for node1
	 * node2: Id for node2
	 * ...
	 */
	else if (yamlNode["node1"] && yamlNode["node2"]
		&& yamlNode["node3"] && yamlNode["node4"]) {
		this->node1 = yamlNode["node1"].as<int>();
		this->node2 = yamlNode["node2"].as<int>();
		this->node3 = yamlNode["node3"].as<int>();
		this->node4 = yamlNode["node4"].as<int>();
		return true;
	}
	return false;
}

void FEQuadshell::printAttributes() {
	std::cout << "FEQuadshell:   id: " << id << ", node1: " << node1 << ", node2: " << node2
		<< ", node3: " << node3 << ", node4: " << node4 << ", material: " << material 
		<< ", geoID: " << geoID << ", coordID: " << coordID << ", ecc1: " << ecc1
		<< ", ecc2: " << ecc2 << ", ecc3: " << ecc3 << ", ecc4: " << ecc4 << std::endl;
}

