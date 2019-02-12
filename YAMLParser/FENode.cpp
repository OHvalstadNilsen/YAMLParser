#include "pch.h"
#include "FENode.h"
#include <iostream>
#include <exception>


FENode::FENode(int id, double x, double y, double z, int ix, int iy, int iz, int irx, int iry, int irz, int rotID) 
{
	this->id = id;
	this->x = x;
	this->y = y;
	this->z = z;
	this->ix = ix;
	this->iy = iy;
	this->iz = iz;
	this->irx = irx;
	this->iry = iry;
	this->irz = irz;
	this->rotID = rotID;
}

FENode::FENode(YAML::Node yamlNode) {
	if (!setMandatoryValues(yamlNode)) {
		throw std::runtime_error("Error: Mandatory attributes missing.");
	}
	setOptionalValues(yamlNode);
}


FENode::~FENode()
{
}

bool FENode::setMandatoryValues(YAML::Node yamlNode) {
	/* Assign the mandatory values (id, x, y, and z).
	 * If the values are defined in the node, assign them and return true.
	 * Else, return false.
	*/
	if (yamlNode["id"] && yamlNode["x"] && yamlNode["y"] && yamlNode["z"]) {
		this->id = yamlNode["id"].as<int>();
		this->x = yamlNode["x"].as<double>();
		this->y = yamlNode["y"].as<double>();
		this->z = yamlNode["z"].as<double>();
		return true;
	}
	return false;
}

void FENode::setOptionalValues(YAML::Node yamlNode) {
	/* Assign the optional values (boundary conditions and rotID).
	 * If the value is defined in the YAML node, assign that value.
	 * Else, assign the default value.
	 */
	this->ix = (yamlNode["ix"]) ? yamlNode["ix"].as<int>() : 0;
	this->iy = (yamlNode["iy"]) ? yamlNode["iy"].as<int>() : 0;
	this->iz = (yamlNode["iz"]) ? yamlNode["iz"].as<int>() : 0;
	this->irx = (yamlNode["irx"]) ? yamlNode["irx"].as<int>() : 0;
	this->iry = (yamlNode["iry"]) ? yamlNode["iry"].as<int>() : 0;
	this->irz = (yamlNode["irz"]) ? yamlNode["irz"].as<int>() : 0;
	this->rotID = (yamlNode["rotID"]) ? yamlNode["rotID"].as<int>() : 0;
}

//Extract keys of a YAML mapping, in a container on the form std::vector<std::string>.
std::vector<std::string> FENode::extractYamlKeys(YAML::Node yamlNode) {
	std::vector<std::string> retval;
	for (YAML::const_iterator it = yamlNode.begin(); it != yamlNode.end(); ++it) {
		retval.push_back(it->first.as<std::string>());
	}

	return retval;
}

void FENode::PrintNode() {
	std::cout << "FENode:   id: " << id << ", x: " << x << ", y: " << y 
			  << ", z: " << z << ", ix: " << ix << ", iy: " << iy <<", iz: " << iz 
			  << ", irx: " << irx << ", iry: " << iry << ", irz: " << irz << ", rotID: " << rotID << std::endl;
}
