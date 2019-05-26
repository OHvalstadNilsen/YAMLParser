#include "pch.h"
#include "FEIsoMaterial.h"
#include <iostream>

FEIsoMaterial::FEIsoMaterial(YAML::Node& yamlNode) {
	if (!assignIndependentAttributes(yamlNode)) {
		throw std::runtime_error("IsoMaterial error: Mandatory attributes missing.");
	}
	this->type = ISOMATERIAL;
}

FEIsoMaterial::FEIsoMaterial(int id, std::string type, double Emod, double poiss, double density, double thermX) {
	//Constructor non-dependent on a YAML::Node
	setID(id);
	this->type = type;
	this->Emod = Emod;
	this->poisson = poiss;
	this->density = density;
	this->thermX = thermX;
}

FEIsoMaterial::~FEIsoMaterial() {}

std::string FEIsoMaterial::getTypeAsString() {
	return "ISOMATERIAL";
}

bool FEIsoMaterial::assignIndependentAttributes(YAML::Node& yamlNode) {
	/* Assign the mandatory values (id, type, Emod, poisson, yield).
	 * If the values are defined in the node, assign them and return true.
	 * Else, return false.
	*/
	if (yamlNode["id"] && yamlNode["type"] && yamlNode["Emod"]
		&& yamlNode["poisson"]) {
		int id = yamlNode["id"].as<int>();
		setID(id);

		this->type = yamlNode["type"].as<std::string>();
		this->Emod = yamlNode["Emod"].as<double>();
		this->poisson = yamlNode["poisson"].as<double>();
		
		/*The yield attribute is only defined for plastic materials.
		  For elastic materials, the yield attribute holds a dummy variable.*/
		if (type == "plastic" && !yamlNode["yield"]) {
			return false;
		}
		this->yield = (type == "plastic") ? yamlNode["yield"].as<double>() : -1;
		
		//Assign optional values
		//TODO: Decide which value to assign when the density is not defined
		this->density = (yamlNode["density"]) ? yamlNode["density"].as<double>() : -1;
		this->thermX = (yamlNode["thermX"]) ? yamlNode["thermX"].as<double>() : 0;

		return true;
	}
	return false;
}

void FEIsoMaterial::printAttributes() {
	std::cout << "IsoMaterial:   id: " << getID() 
		<< ", type: " << type 
		<< ", Emod: " << Emod
		<< ", poisson: " << poisson 
		<< ", yield: " << yield 
		<< ", density: " << density
		<< ", thermX: " << thermX << std::endl;
}
