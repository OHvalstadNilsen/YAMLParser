#include "pch.h"
#include "Construction.h"
#include <iostream>
#include <exception>

Construction::Construction()
{
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
	//		* element.gettypeasstring() is called on an identifiable, hence it will do a funciton
	//		* call to that method instead of the (correct) child method.
	//		*/
	//		throw std::runtime_error("error: a " + element.getTypeAsString() + " element with id " + std::to_string(element.getID()) + " already exists.");
	//	}
	//}
	return false; //doesn't exist!
}

Identifiable* Construction::fetchObject(int id, std::string type) {
	for (int i = 0; i < elementList.size(); i++) {
		if (elementList[i]->getID() == id && elementList[i]->getTypeAsString() == type) {
			return elementList[i];
		}
	}
	//If no corresponding element exists, this error is thrown 
	throw std::runtime_error("Error: A " + type + " element with id " + std::to_string(id) + " does not exists in construction. \n");
}

bool Construction::checkExistence(int id, std::string type) {
	for (std::vector<Identifiable*>::iterator it = elementList.begin(); it != elementList.end(); ++it) {
		if ((*it)->getID() == id && (*it)->getTypeAsString() == type) {
			//throw std::runtime_error("Error: A " + (*it)->getTypeAsString() + " element with id " + std::to_string((*it)->getID()) + " already exists.");
			return true;
		}
	}
	return false;
}

bool Construction::addNode(FENode& node) {
	std::vector<FENode>::iterator result = std::find_if(nodeList.begin(), nodeList.end(), check_id(node.getID()));
	if (result != nodeList.end()) {
		return false;
	}
	this->nodeList.push_back(node);
	return true;
}

bool Construction::addBeam(FEBeam& beam) {
	std::vector<FEBeam>::iterator result = std::find_if(beamList.begin(), beamList.end(), check_id(beam.getID()));
	if (result == beamList.end()) {
		return false;
	}
	this->beamList.push_back(beam);
	return true;
}


bool Construction::addElement(Identifiable* element)
{
	this->elementList.push_back(element);
	return true;
}
