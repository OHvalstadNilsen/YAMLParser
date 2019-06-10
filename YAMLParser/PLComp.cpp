#include "pch.h"
#include "PLComp.h"
#include <iostream>


PLComp::PLComp(YAML::Node& yamlNode, std::vector<GenericMaterial*> matList) {
	if (!assignIndependentAttributes(yamlNode) || matList.size() < 1) {
		throw std::runtime_error("PLComp error: Mandatory attributes missing.");
	}
	
	for (int i = 0; i < matList.size(); i++) {
		addPly(yamlNode["plies"][i], matList[i]);
	}

	this->type = PLCOMP;
}

PLComp::~PLComp() {
}

Identifiable::Type PLComp::getType() {
	return this->type;
}

std::string PLComp::getTypeAsString() {
	return "PLCOMP";
}

bool PLComp::assignIndependentAttributes(YAML::Node & yamlNode) {
	if (yamlNode["secID"] && yamlNode["z0"] && yamlNode["plies"].size() > 0) {
		setID(yamlNode["secID"].as<int>());
		this->z0 = yamlNode["z0"].as<double>();
		return true;
	}
	return false;
}

bool PLComp::addPly(const YAML::Node& plyNode, GenericMaterial* mat) {
	if (plyNode["T"] && plyNode["theta"]) {
		PLComp::Ply ply;
		ply.mat = mat;
		ply.T = plyNode["T"].as<double>();
		ply.theta = plyNode["theta"].as<double>();
		plies.push_back(ply);
		return true;
	}
	return false;
}

void PLComp::printAttributes() {
	std::cout << "PLComp:	"
		<< "secID: " << getID()
		<< ", z0: " << z0
		<< ", plies:\n";

	for (Ply ply : plies) {
		std::cout
			<< "\t- {matID: " << ply.mat->getID()
			<< ", T: " << ply.T
			<< ", theta: " << ply.theta << "}" << std::endl;
	}
}
