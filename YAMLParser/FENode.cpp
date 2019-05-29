#include "pch.h"
#include "FENode.h"
#include <iostream>
#include <exception>

FENode::FENode(int ID, double x, double y, double z, int ix, int iy, int iz, int irx, int iry, int irz, int rotID) 
{
	int id = ID;
	setID(id);
	this->x = x;
	this->y = y;
	this->z = z;
	this->ix = ix;
	this->iy = iy;
	this->iz = iz;
	this->irx = irx;
	this->iry = iry;
	this->irz = irz;
	//this->rotID = rotID;
}

FENode::FENode(YAML::Node& yamlNode, FECoordSys * rot) {
	if (!assignIndependentAttributes(yamlNode)) {
		throw std::runtime_error("Node error: Mandatory attributes missing.");
	}
	this->type = NODE;
	this-> pRotID = rot;
}

//Getters for type
Identifiable::Type FENode::getType() { return this->type; }
std::string FENode::getTypeAsString() {	return "NODE"; }


FENode::~FENode()
{
}

bool FENode::assignIndependentAttributes(YAML::Node& yamlNode) {
	/* Assign the mandatory values (id, x, y, and z).
	 * If the values are defined in the node, assign them and return true.
	 * Else, return false.
	*/
	if (yamlNode["id"]) {
		//Mandatory attributes
		int id = yamlNode["id"].as<int>();
		setID(id); //Sets the ID attribute in the base class 'Identifiable'
		return setCoordinates(yamlNode);
	
		//Optional attributes
		this->ix = (yamlNode["ix"]) ? yamlNode["ix"].as<int>() : 0;
		this->iy = (yamlNode["iy"]) ? yamlNode["iy"].as<int>() : 0;
		this->iz = (yamlNode["iz"]) ? yamlNode["iz"].as<int>() : 0;
		this->irx = (yamlNode["irx"]) ? yamlNode["irx"].as<int>() : 0;
		this->iry = (yamlNode["iry"]) ? yamlNode["iry"].as<int>() : 0;
		this->irz = (yamlNode["irz"]) ? yamlNode["irz"].as<int>() : 0;
	}
	return false;
}

bool FENode::setCoordinates(YAML::Node& yamlNode) {
	//For coordinate data on the form "xyz: [x, y, z]"
	if (yamlNode["xyz"]) {
		this->x = yamlNode["xyz"][0].as<double>();
		this->y = yamlNode["xyz"][1].as<double>();
		this->z = yamlNode["xyz"][2].as<double>();
		return true;
	}
	/*For coordinate data on the form
	 x: x
	 y: y 
	 z: z
	*/
	else if (yamlNode["x"] && yamlNode["y"] && yamlNode["z"]) {
		this->x = yamlNode["x"].as<double>();
		this->y = yamlNode["y"].as<double>();
		this->z = yamlNode["z"].as<double>();
		return true;
	}
	return false;
}

//Extract keys of a YAML mapping, in a container on the form std::vector<std::string>.
std::vector<std::string> FENode::extractYamlKeys(YAML::Node yamlNode) {
	std::vector<std::string> retval;
	for (YAML::const_iterator it = yamlNode.begin(); it != yamlNode.end(); ++it) {
		retval.push_back(it->first.as<std::string>());
	}

	return retval;
}

void FENode::printAttributes() {
	std::cout << "FENode:   id: " << getID()
		<< ", x: " << x
		<< ", y: " << y
		<< ", z: " << z
		<< ", ix: " << ix
		<< ", iy: " << iy
		<< ", iz: " << iz
		<< ", irx: " << irx
		<< ", iry: " << iry
		<< ", irz: " << irz
		<< ", rotID: " << std::to_string(pRotID->getID()) << std::endl;
}
