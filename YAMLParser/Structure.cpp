#include "pch.h"
#include "Structure.h"
#include <iostream>
#include <exception>

Structure::Structure(int structureID) {
	//Create default objects to assign when fields are omitted
	FECoordSys* defCoordSys = new FECoordSys(-1, 1, 0, 0, 0, 1, 0, 0, 0, 1);
	this->addCoordSys(defCoordSys);

	FEEccentricity* defEcc = new FEEccentricity(-1, 0.0, 0.0, 0.0);
	this->addElement(defEcc);

	FEVector* defVec = new FEVector(-1, 1.0, 0.0, 0.0);
	this->addElement(defVec);

	FEIsoMaterial* defMaterial = new FEIsoMaterial(-1, "elastic", 1.0, 1.0, 1.0, 1.0);
	this->addMaterial(defMaterial);

	GenericCrossSection* defCrossSection = new CrossSectionDummy();
	this->addCrossSection(defCrossSection);
}

Structure::~Structure() {
}

//------------ Check data object existence ------------
/*These functions return true if the data object with the requested ID 
* exists in Structure. Otherwise, they return false.
*/

bool Structure::checkCoordSysExistence(int id) {
	if (coordSysMap.find(id) != coordSysMap.end()) {
		return true;
	}
	return false;
}

bool Structure::checkElementExistence(int id, std::string type) {
	std::vector<GenericFE*>::iterator it;
	for (it = elementList.begin(); it != elementList.end(); ++it) {
		if ((*it)->getID() == id && (*it)->getTypeAsString() == type) {
			return true;
		}
	}
	return false;

	/* ---------------------------------------------------------
	*The following code has better performance as it traverses a map instead of a list.
	* However, it produces the wrong output due to key uniqueness.
	*/
	
	/*if (elementMap.find(id) != elementMap.end()
		&& elementMap[id]->getTypeAsString() == type) {
		return true;
	}
	return false;*/
}

bool Structure::checkCrossSectionExistence(int id, std::string& type) {
	if (crossSectionMap.find(id) != crossSectionMap.end()
		&& crossSectionMap[id]->getTypeAsString() == type) {
		return true;
	}
	return false;
}

bool Structure::checkMaterialExistence(int id) {
	if (materialMap.find(id) != materialMap.end()) {
		return true;
	}
	return false;
}

bool Structure::checkNodeExistence(int id) {
	if (nodeMap.find(id) != nodeMap.end()) {
		return true;
	}
	return false;
}

bool Structure::checkNodeLoadExistence(int id) {
	if (nodeLoadMap.find(id) != nodeLoadMap.end()) {
		return true;
	}
	return false;
}

bool Structure::checkLoadCombExistence(int id) {
	if (loadCombMap.find(id) != loadCombMap.end()) {
		return true;
	}
	return false;
}

// ------------ Fetch data objects ------------

/*These functions return the requested data object if it exists
* in Structure. Otherwise, they throw an error.
*/

FECoordSys* Structure::fetchCoordSys(int id) {
	if (coordSysMap.find(id) != coordSysMap.end()) {
		return coordSysMap[id];
	}
	throw std::runtime_error("Error: A coordinate system with id "
		+ std::to_string(id) + " does not exist in Structure.\n");
}

GenericFE* Structure::fetchObject(int id, std::string type) {
	for (int i = 0; i < elementList.size(); i++) {
		if (elementList[i]->getID() == id && elementList[i]->getTypeAsString() == type) {
			return elementList[i];
		}
	}

	/*The following code has better performance as it traverses a map instead of a list.
	* However, it produces the wrong output due to key uniqueness.
	*/
	/*if (elementMap.find(id) != elementMap.end() 
		&& elementMap[id]->getTypeAsString() == type) {
		return elementMap[id];
	}*/
	throw std::runtime_error("Error: A " + type + " element with id " 
		+ std::to_string(id) + " does not exist in Structure.\n");
}

GenericCrossSection* Structure::fetchCrossSection(int id) {
	if (crossSectionMap.find(id) != crossSectionMap.end()) {
		return crossSectionMap[id];
	}
	throw std::runtime_error("Error: A cross section with id " + 
		std::to_string(id) + " does not exist in Structure.\n");
}

GenericMaterial* Structure::fetchMaterial(int id) {
	if (materialMap.find(id) != materialMap.end()) {
		return materialMap[id];
	}
	throw std::runtime_error("Error: A material with id " 
		+ std::to_string(id) + " does not exist in Structure.\n");
}

FENode* Structure::fetchNode(int id) {
	if (nodeMap.find(id) != nodeMap.end()) {
		return nodeMap[id];
	}
	throw std::runtime_error("Error: A NODE with id " 
		+ std::to_string(id) + " does not exist in Structure.\n");
}

FENodeLoad* Structure::fetchNodeLoad(int id) {
	if (nodeLoadMap.find(id) != nodeLoadMap.end()) {
		return nodeLoadMap[id];
	}
	throw std::runtime_error("Error: A NODELOAD with id "
		+ std::to_string(id) + " does not exist in Structure.\n");
}

FELoadComb * Structure::fetchLoadComb(int id)
{
	if (loadCombMap.find(id) != loadCombMap.end()) {
		return loadCombMap[id];
	}
	throw std::runtime_error("Error: A LOADCOMB with id "
		+ std::to_string(id) + " does not exist in Structure.\n");
}

//------------ Add data objects ------------

/*These functions add the data object specified in the input 
* argument to the corresponding list and map of data objects.
*/

bool Structure::addCoordSys(FECoordSys* coordSys) {
	this->coordSysList.push_back(coordSys);
	this->coordSysMap[coordSys->getID()] = coordSys;
	return true;
}

bool Structure::addCrossSection(GenericCrossSection* crossSection) {
	this->crossSectionList.push_back(crossSection);
	this->crossSectionMap[crossSection->getID()] = crossSection;
	return true;
}

bool Structure::addMaterial(GenericMaterial* material) {
	this->materialList.push_back(material);
	this->materialMap[material->getID()] = material;
	return true;
}

bool Structure::addNode(FENode* node) {
	this->nodeList.push_back(node);
	this->nodeMap[node->getID()] = node;
	return true;
}

bool Structure::addElement(GenericFE* element) {
	this->elementList.push_back(element);
	this->elementMap[element->getID()] = element;
	return true;
}

bool Structure::addNodeLoad(FENodeLoad * nodeLoad) {
	this->nodeLoadList.push_back(nodeLoad);
	this->nodeLoadMap[nodeLoad->getID()] = nodeLoad;
	return true;
}

bool Structure::addLoadComb(FELoadComb * loadComb)
{
	this->loadCombList.push_back(loadComb);
	this->loadCombMap[loadComb->getID()] = loadComb;
	return false;
}

void Structure::printData() {
	for (FECoordSys* coordSys : coordSysList){
		coordSys->printAttributes();
	}
	for (GenericCrossSection* crossSection : crossSectionList) {
		crossSection->printAttributes();
	}
	for (GenericMaterial* mat : materialList) {
		mat->printAttributes();
	}
	for (FENode* node : nodeList) {
		node->printAttributes();
	}
	for (GenericFE* element : elementList) {
		element->printAttributes();
	}
	for (FENodeLoad* nl : nodeLoadList) {
		nl->printAttributes();
	}
	for (FELoadComb* lc : loadCombList) {
		lc->printAttributes();
	}
}
