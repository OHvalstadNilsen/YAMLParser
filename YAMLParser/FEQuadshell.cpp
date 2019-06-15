#include "pch.h"
#include "FEQuadshell.h"
#include <iostream>

FEQuadshell::FEQuadshell(int id, FENode* n1, FENode* n2, FENode* n3, FENode* n4,
	FEIsoMaterial* mat, GenericCompSection* compSection, FEVector* vec,
	FEEccentricity* ecc1, FEEccentricity* ecc2, FEEccentricity* ecc3, FEEccentricity* ecc4){
	
	setID(id);
	this->type = QUADSHEL;
	this->pNode1 = n1;
	this->pNode2 = n2;
	this->pNode3 = n3;
	this->pNode4 = n4;
	this->pMaterial = mat;
	this->pCompSection = compSection;
	this->pVec = vec;
	this->pEcc1 = ecc1;
	this->pEcc2 = ecc2;
	this->pEcc3 = ecc3;
	this->pEcc4 = ecc4;
}

FEQuadshell::~FEQuadshell(){
}

std::string FEQuadshell::getTypeAsString() { return "QUADSHEL"; }

bool FEQuadshell::assignIndependentAttributes (YAML::Node & yamlNode) {
	//Only ID
	return true;
}


void FEQuadshell::printAttributes() {
	if (pMaterial != nullptr) {
		std::cout << "FEQuadshell:   "
			<< "id: " << getID()
			<< ", node1: " << std::to_string(pNode1->getID())
			<< ", node2: " << std::to_string(pNode2->getID())
			<< ", node3: " << std::to_string(pNode3->getID())
			<< ", node4: " << std::to_string(pNode4->getID())
			<< ", material: " << std::to_string(pMaterial->getID())
			<< ", vecID: " << std::to_string(pVec->getID())
			<< ", ecc1: " << std::to_string(pEcc1->getID())
			<< ", ecc2: " << std::to_string(pEcc2->getID())
			<< ", ecc3: " << std::to_string(pEcc3->getID())
			<< ", ecc4: " << std::to_string(pEcc4->getID())
			<< std::endl;
	}
	else if (pCompSection != nullptr) {
		std::cout << "FEQuadshell:   "
			<< "id: " << getID()
			<< ", node1: " << std::to_string(pNode1->getID())
			<< ", node2: " << std::to_string(pNode2->getID())
			<< ", node3: " << std::to_string(pNode3->getID())
			<< ", node4: " << std::to_string(pNode4->getID())
			<< ", secID: " << std::to_string(pCompSection->getID())
			<< ", vecID: " << std::to_string(pVec->getID())
			<< ", ecc1: " << std::to_string(pEcc1->getID())
			<< ", ecc2: " << std::to_string(pEcc2->getID())
			<< ", ecc3: " << std::to_string(pEcc3->getID())
			<< ", ecc4: " << std::to_string(pEcc4->getID())
			<< std::endl;
	}
	
}

