#include "pch.h"
#include "FEBeam.h"
#include <iostream>

FEBeam::FEBeam(YAML::Node yamlNode) {
	if (!setMandatoryValues(yamlNode)) {
		throw std::runtime_error("Beam error: Mandatory attributes missing.");
	}
	setOptionalValues(yamlNode);
	this->type = BEAM;
}

FEBeam::FEBeam(int id, FENode* n1, FENode* n2, FEIsoMaterial* mat, GenericCrossSection* crossSection) {
	//Set fields inherited from Identifiable
	setID(id);
	this->type = BEAM;
	
	this->pNode1 = n1;
	this->pNode2 = n2;
	this->pMaterial = mat;
	this->pCrossSection = crossSection;
}


FEBeam::~FEBeam()
{
}

//Getters for FEType
Identifiable::Type FEBeam::getType() { return this->type; }
std::string FEBeam::getTypeAsString(){ return "BEAM"; }


bool FEBeam::setMandatoryValues(YAML::Node& yamlNode) {
	/* Assign the mandatory values (elemID, node1, node2, material and geoID).
	 * If the values are defined in the node, assign them and return true.
	 * Else, return false.
	*/
	bool isValid = false;
	if (yamlNode["elemID"] && yamlNode["material"] && yamlNode["geoID"]) {
		int id = yamlNode["elemID"].as<int>();
		setID(id); //Sets the ID attribute in the base class 'Identifiable'

		this->material = yamlNode["material"].as<int>();
		this->geoID = yamlNode["geoID"].as<int>();
		isValid = setNodes(yamlNode);
		return isValid;
	}
	return false;
}

void FEBeam::setOptionalValues(YAML::Node& yamlNode) {
	/* Assign the optional values (vecID, eccentricity1 and eccentricity2).
	 * If the value is defined in the YAML node, assign that value.
	 * Else, assign the default value.
	 */
	this->vecID = (yamlNode["vecID"]) ? yamlNode["vecID"].as<int>() : 0;
	this->eccentricity1 = (yamlNode["ecc1"]) ? yamlNode["ecc1"].as<int>() : 0;
	this->eccentricity2 = (yamlNode["ecc2"]) ? yamlNode["ecc2"].as<int>() : 0;
}

bool FEBeam::setNodes(YAML::Node& yamlNode) {
	/*
	 * If the nodes are given on the form
	 * nodes: [ID for node1, ID for node2]
	 */
	if (yamlNode["nodes"].size() == 2) {
		this->node1 = yamlNode["nodes"][0].as<int>();
		this->node2 = yamlNode["nodes"][1].as<int>();
		return true;
	}
	/*
	 * If the nodes are given on the form
	 * node1: Id for node1
	 * node2: Id for node2
	 */
	else if (yamlNode["node1"] && yamlNode["node2"]) {
		this->node1 = yamlNode["node1"].as<int>();
		this->node2 = yamlNode["node2"].as<int>();
		return true;
	}
	return false;
}

void FEBeam::printAttributes() {
	std::cout << "FEBeam:   id: " << getID() << ", node1: " << node1 << ", node2: " << node2
		<< ", material: " << material << ", geoID: " << geoID << ", vecID: " << vecID
		<< ", ecc1: " << eccentricity1 << ", ecc2: " << eccentricity2 << std::endl;
}

void FEBeam::printAttributes2() {
	std::cout << "FEBeam:    id: " << getID() 
		<< ", node1: " << std::to_string(pNode1->getID()) 
		<< ", node2: " << std::to_string(pNode2->getID()) 
		<< ", material: " << std::to_string(pMaterial->getID()) 
		<< ", geoID: " << pCrossSection->getID()
		<< std::endl;
}