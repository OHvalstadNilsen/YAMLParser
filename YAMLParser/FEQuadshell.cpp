#include "pch.h"
#include "FEQuadshell.h"
#include <iostream>

FEQuadshell::FEQuadshell(YAML::Node& yamlNode) {
	if (!setMandatoryValues(yamlNode)) {
		throw std::runtime_error("Quadshell error: Mandatory attributes missing.");
	}
	setOptionalValues(yamlNode);
}

FEQuadshell::FEQuadshell(int id, FECoordSys* coordSys, FENode* n1, FENode* n2, FENode* n3, FENode* n4,
	FEIsoMaterial* mat, GenericCrossSection* crossSection,
	FEEccentricity* ecc1, FEEccentricity* ecc2, FEEccentricity* ecc3, FEEccentricity* ecc4){
	//Set fields inherited from Identifiable
	setID(id);
	this->type = QUADSHEL;
	
	this->pCoordSys = coordSys;
	this->pNode1 = n1;
	this->pNode2 = n2;
	this->pNode3 = n3;
	this->pNode4 = n4;
	this->pMaterial = mat;
	this->pCrossSection = crossSection;
	this->pEcc1 = ecc1;
	this->pEcc2 = ecc2;
	this->pEcc3 = ecc3;
	this->pEcc4 = ecc4;
}


FEQuadshell::~FEQuadshell()
{
}

std::string FEQuadshell::getTypeAsString() { return "QUADSHEL"; }

bool FEQuadshell::setMandatoryValues(YAML::Node & yamlNode) {
	/* Assign the mandatory values (elemID, node1, node2, node3, node4, 
	* material and geoID).
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
	std::cout << "FEQuadshell:   "
		<< "id: " << getID()
		<< ", coordSys: " << std::to_string(pCoordSys->getID())
		<< ", node1: " << std::to_string(pNode1->getID())
		<< ", node2: " << std::to_string(pNode2->getID())
		<< ", node3: " << std::to_string(pNode3->getID())
		<< ", node4: " << std::to_string(pNode4->getID())
		<< ", material: " << std::to_string(pMaterial->getID())
		<< ", ecc1: " << std::to_string(pEcc1->getID())
		<< ", ecc2: " << std::to_string(pEcc2->getID())
		<< ", ecc3: " << std::to_string(pEcc3->getID())
		<< ", ecc4: " << std::to_string(pEcc4->getID())
		<< std::endl;
}

