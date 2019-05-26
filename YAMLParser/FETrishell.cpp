#include "pch.h"
#include "FETrishell.h"
#include <iostream>

//TODO: Add vectorID as an input argument. Needed to properly construct a Trishell element.
FETrishell::FETrishell(int id, FECoordSys* coord, FENode* n1, FENode* n2, FENode* n3, FEIsoMaterial* mat, GenericCrossSection* crossSection,
	FEEccentricity* ecc1, FEEccentricity* ecc2, FEEccentricity* ecc3) {
	setID(id); //Inherited from Identifiable
	this->type = TRISHELL;

	this->pCoordSys = coord;
	this->pNode1 = n1;
	this->pNode2 = n2;
	this->pNode3 = n3;
	this->pMaterial = mat;
	this->pCrossSection = crossSection;
	this->pEcc1 = ecc1;
	this->pEcc2 = ecc2;
	this->pEcc3 = ecc3;
}

FETrishell::~FETrishell() {
}

std::string FETrishell::getTypeAsString() {	return "TRISHELL"; }

bool FETrishell::assignIndependentAttributes(YAML::Node& yamlNode) {
	//Only ID
	return true;
}

void FETrishell::printAttributes() {
	std::cout << "FETrishell:   "
		<< "id: " << getID()
		<< ", coordSys: " << std::to_string(pCoordSys->getID())
		<< ", node1: " << std::to_string(pNode1->getID())
		<< ", node2: " << std::to_string(pNode2->getID())
		<< ", node3: " << std::to_string(pNode3->getID())
		<< ", material: " << std::to_string(pMaterial->getID())
		<< ", ecc1: " << std::to_string(pEcc1->getID())
		<< ", ecc2: " << std::to_string(pEcc2->getID())
		<< ", ecc3: " << std::to_string(pEcc3->getID())
		<< std::endl;
}
