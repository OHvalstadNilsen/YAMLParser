/** \brief
* This class represents an isotropic material
*/

#pragma once
#include <string>
#include "yaml-cpp/yaml.h"
#include "GenericFE.h"
#include "Identifiable.h"

class FEIsoMaterial : 
	public Identifiable, 
	public GenericFE
{
public:
	/**Constructor based on information from a YAML::Node*/
	FEIsoMaterial(YAML::Node& yamlNode);
	/**YAML-independent constructor*/
	FEIsoMaterial(int id, std::string type, double Emod, double poiss, double density, double thermX);
	~FEIsoMaterial();

	//---------- Functions ----------
	virtual std::string getTypeAsString() override;
	bool assignIndependentAttributes(YAML::Node& yamlNode) override;
	void printAttributes();

	//---------- Data fields ----------
	std::string type;	///< Literal string identifying whether the material is elastic or plastic
	double Emod;		///< Young's modulus
	double poisson;		///< Poissons' ratio
	double yield;		///< Yield stress when plastic (for elastic materials, yield = 0.0)
	double density;		///< Material density
	double thermX;		///< Thermal exapansion coeffiecient
};

