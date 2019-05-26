#include "pch.h"
#include "FENodeLoad.h"
#include <iostream>


FENodeLoad::FENodeLoad(int nodeLoadId, YAML::Node& yamlNode, FENode *n, FEEccentricity *ecc) {
	if (!assignIndependentAttributes(yamlNode)) {
		throw std::runtime_error("NodeLoad error: Mandatory attributes missing.");
	}
	setID(nodeLoadId);
	this->pNode = n;
	this->pEcc = ecc;
	this->type = NODELOAD;
}


FENodeLoad::~FENodeLoad()
{
}

//Getters for type
Identifiable::Type FENodeLoad::getType() { return this->type; }
std::string FENodeLoad::getTypeAsString() { return "NODELOAD"; }


bool FENodeLoad::assignIndependentAttributes(YAML::Node& yamlNode) {
	//Check presence of mandatory attributes
	if (yamlNode["loadCaseID"]) {
		this->loadCaseId = yamlNode["loadCaseID"].as<int>();
				
		//These values may be omitted. In that case they are assigned to zero.
		this->fx = yamlNode["fx"] ? yamlNode["fx"].as<double>() : 0.0;
		this->fy = yamlNode["fy"] ? yamlNode["fy"].as<double>() : 0.0;
		this->fz = yamlNode["fz"] ? yamlNode["fz"].as<double>() : 0.0;
		this->mx = yamlNode["mx"] ? yamlNode["mx"].as<double>() : 0.0;
		this->my = yamlNode["my"] ? yamlNode["my"].as<double>() : 0.0;
		this->mz = yamlNode["mz"] ? yamlNode["mz"].as<double>() : 0.0;
		return true;
	}
	return false;
}

void FENodeLoad::printAttributes() {
	std::cout << "FENodeLoad:    id: " << getID()
		<< ", loadCaseId: " << loadCaseId
		<< ", node: " << std::to_string(pNode->getID())
		<< ", fx: " << fx
		<< ", fy: " << fy
		<< ", fz: " << fz
		<< ", mx: " << mx
		<< ", my: " << my
		<< ", mz: " << mz
		<< ", ecc: " << std::to_string(pEcc->getID())
		<< std::endl;
}
