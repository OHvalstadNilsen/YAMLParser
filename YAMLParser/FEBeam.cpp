#include "pch.h"
#include "FEBeam.h"
#include <iostream>

FEBeam::FEBeam(int id, FENode* n1, FENode* n2, FEIsoMaterial* mat,
	GenericCrossSection* crossSection, FEEccentricity* ecc1, FEEccentricity* ecc2, FECoordSys* rotID) {
	setID(id);
	this->pNode1 = n1;
	this->pNode2 = n2;
	this->pMaterial = mat;
	this->pCrossSection = crossSection;
	this->pEcc1 = ecc1;
	this->pEcc2 = ecc2;
	this->pCoordSys = rotID;
	this->type = BEAM;
}

FEBeam::~FEBeam() {
}

//Getters for FEType
Identifiable::Type FEBeam::getType() { return this->type; }
std::string FEBeam::getTypeAsString(){ return "BEAM"; }

bool FEBeam::assignIndependentAttributes(YAML::Node& yamlNode) {
	//Only ID is an independent attribute.
	return true;
}

void FEBeam::printAttributes() {
	std::cout << "FEBeam:    id: " << getID() 
		<< ", node1: " << std::to_string(pNode1->getID()) 
		<< ", node2: " << std::to_string(pNode2->getID()) 
		<< ", material: " << std::to_string(pMaterial->getID()) 
		<< ", geoID: " << pCrossSection->getID()
		<< ", ecc1: " << pEcc1->getID()
		<< ", ecc2: " << pEcc2->getID()
		<< std::endl;
}