#include "pch.h"
#include "Structure.h"
#include <iostream>
#include <exception>

Structure::Structure() {
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

Structure::~Structure()
{
}

bool Structure::checkExistence2(Identifiable element) {
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

bool Structure::checkCoordSysExistence(int id) {
	if (coordSysMap.find(id) != coordSysMap.end()) {
		return true;
	}
	return false;
}

bool Structure::checkElementExistence(int id, std::string& type) {
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

bool Structure::checkCrossSectionExistence(int id, std::string& type) {
	for (std::vector<GenericCrossSection*>::iterator it = crossSectionList.begin(); it != crossSectionList.end(); ++it) {
		if ((*it)->getID() == id && (*it)->getTypeAsString() == type) {
			return true;
		}
	}
	return false;
}

bool Structure::checkMaterialExistence(int id) {
	for (std::vector<FEIsoMaterial*>::iterator it = materialList.begin(); it != materialList.end(); ++it) {
		if ((*it)->getID() == id) {
			return true;
		}
	}
	return false;
}

bool Structure::checkNodeExistence(int id) {
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

FECoordSys* Structure::fetchCoordSys(int id) {
	if (coordSysMap.find(id) != coordSysMap.end()) {
		return coordSysMap[id];
	}
	throw std::runtime_error("Error: A coordinate system with id "
		+ std::to_string(id) + " does not exist in Structure.\n");
}

Identifiable* Structure::fetchObject(int id, std::string type) {
	for (int i = 0; i < elementList.size(); i++) {
		if (elementList[i]->getID() == id && elementList[i]->getTypeAsString() == type) {
			return elementList[i];
		}
	}
	//If no corresponding element exists, this error is thrown 
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

FEIsoMaterial* Structure::fetchMaterial(int id) {
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

//Add data objects
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

bool Structure::addMaterial(FEIsoMaterial* material) {
	this->materialList.push_back(material);
	this->materialMap[material->getID()] = material;
	return true;
}

bool Structure::addNode(FENode* node) {
	this->nodeList.push_back(node);
	this->nodeMap[node->getID()] = node;
	return true;
}

bool Structure::addElement(Identifiable* element) {
	this->elementList.push_back(element);
	this->elementMap[element->getID()] = element;
	return true;
}
