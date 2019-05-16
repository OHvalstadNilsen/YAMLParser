#include "pch.h"
#include "Construction.h"
#include <iostream>
#include <exception>

Construction::Construction() {
	//Create default objects to assign when fields are omitted
	FECoordSys* defCoordSys = new FECoordSys(-1, 1, 0, 0, 0, 1, 0, 0, 0, 1);
	this->addCoordSys(defCoordSys);

	FEEccentricity* defEcc = new FEEccentricity(-1, 0.0, 0.0, 0.0);
	this->addElement(defEcc);

	FEIsoMaterial* defMaterial = new FEIsoMaterial(-1, "elastic", 1.0, 1.0, 1.0, 1.0);
	this->addMaterial(defMaterial);

	GenericCrossSection* defCrossSection = new GenericCrossSection(-1);
	this->addCrossSection(defCrossSection);
}

Construction::~Construction()
{
}

bool Construction::checkExistence2(Identifiable element) {
	//works!
	//for (std::vector<Identifiable>::iterator it = elementList.begin(); it != elementList.end(); ++it) {
	//	if ((*it).getID() == element.getID() && (*it).getType() == element.getType()) {
	//		/*fixme:
	//		* problem with this error message:
	//		* element.gettypeasstring() is called on an identifiable, hence it will do a function
	//		* call to that method instead of the (correct) child method.
	//		*/
	//		throw std::runtime_error("error: a " + element.getTypeAsString() + " element with id " + std::to_string(element.getID()) + " already exists.");
	//	}
	//}
	return false; //doesn't exist!
}

bool Construction::checkCoordSysExistence(int id) {
	if (coordSysMap.find(id) != coordSysMap.end()) {
		return true;
	}
	return false;
}

bool Construction::checkElementExistence(int id, std::string& type) {
	/*for (std::vector<Identifiable*>::iterator it = elementList.begin(); it != elementList.end(); ++it) {
		if ((*it)->getID() == id && (*it)->getTypeAsString() == type) {
			return true;
		}
	}*/
	if (elementMap.find(id) != elementMap.end()
		&& elementMap[id]->getTypeAsString() == type) {
		return true;
	}
	return false;
}

bool Construction::checkCrossSectionExistence(int id, std::string& type) {
	for (std::vector<GenericCrossSection*>::iterator it = crossSectionList.begin(); it != crossSectionList.end(); ++it) {
		if ((*it)->getID() == id && (*it)->getTypeAsString() == type) {
			return true;
		}
	}
	return false;
}

bool Construction::checkMaterialExistence(int id) {
	for (std::vector<FEIsoMaterial*>::iterator it = materialList.begin(); it != materialList.end(); ++it) {
		if ((*it)->getID() == id) {
			return true;
		}
	}
	return false;
}

bool Construction::checkNodeExistence(int id) {
	for (std::vector<FENode*>::iterator it = nodeList.begin(); it != nodeList.end(); ++it) {
		if((*it)->getID() == id){
			return true;
		}
	}
	return false;
}


//Fetch data objects
template <typename T>
T* fetchObject(int id, std::vector<T*> li) {
	for (int i = 0; i < li.size(); i++) {
		if (li[i]->getID() == id) {
			return li[i];
		}
	}
	return nullptr;
}

FECoordSys* Construction::fetchCoordSys(int id) {
	if (coordSysMap.find(id) != coordSysMap.end()) {
		return coordSysMap[id];
	}
	throw std::runtime_error("Error: A coordinate system with id "
		+ std::to_string(id) + " does not exist in construction.\n");
}

Identifiable* Construction::fetchObject(int id, std::string type) {
	for (int i = 0; i < elementList.size(); i++) {
		if (elementList[i]->getID() == id && elementList[i]->getTypeAsString() == type) {
			return elementList[i];
		}
	}
	//If no corresponding element exists, this error is thrown 
	throw std::runtime_error("Error: A " + type + " element with id " 
		+ std::to_string(id) + " does not exist in construction.\n");
}

GenericCrossSection* Construction::fetchCrossSection(int id) {
	if (crossSectionMap.find(id) != crossSectionMap.end()) {
		return crossSectionMap[id];
	}
	throw std::runtime_error("Error: A cross section with id " + 
		std::to_string(id) + " does not exist in construction.\n");
}

FEIsoMaterial* Construction::fetchMaterial(int id) {
	if (materialMap.find(id) != materialMap.end()) {
		return materialMap[id];
	}
	throw std::runtime_error("Error: A material with id " 
		+ std::to_string(id) + " does not exist in construction.\n");
}

FENode* Construction::fetchNode(int id) {
	if (nodeMap.find(id) != nodeMap.end()) {
		return nodeMap[id];
	}
	throw std::runtime_error("Error: A NODE with id " 
		+ std::to_string(id) + " does not exist in construction.\n");
}

//Add data objects
bool Construction::addCoordSys(FECoordSys* coordSys) {
	this->coordSysList.push_back(coordSys);
	this->coordSysMap[coordSys->getID()] = coordSys;
	return true;
}

bool Construction::addCrossSection(GenericCrossSection* crossSection) {
	this->crossSectionList.push_back(crossSection);
	this->crossSectionMap[crossSection->getID()] = crossSection;
	return true;
}

bool Construction::addMaterial(FEIsoMaterial* material) {
	this->materialList.push_back(material);
	this->materialMap[material->getID()] = material;
	return true;
}

bool Construction::addNode(FENode* node) {
	this->nodeList.push_back(node);
	this->nodeMap[node->getID()] = node;
	return true;
}

bool Construction::addElement(Identifiable* element) {
	this->elementList.push_back(element);
	this->elementMap[element->getID()] = element;
	return true;
}
