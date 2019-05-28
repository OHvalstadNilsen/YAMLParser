/** \brief
* This class represents a FE eccentricity element.
* 
* Used to define offset location of BEAM and SHELL elements relative to the global node.
*/

#pragma once
#include "Identifiable.h"
#include "yaml-cpp/yaml.h"
#include "GenericFE.h"

class FEEccentricity :
	public Identifiable,
	public GenericFE
{
public:
	/**Constructor based on information from a YAML::Node*/
	FEEccentricity(YAML::Node& yamlNode);
	/**YAML-independent constructor*/
	FEEccentricity(int id, double eX, double eY, double eZ);
	virtual ~FEEccentricity();

	//----------- Funtions ----------
	// Inherited via Identifiable
	Identifiable::Type getType();
	virtual std::string getTypeAsString() override;

	// Inherited via GenericFE
	virtual bool assignIndependentAttributes(YAML::Node & yamlNode) override;
	virtual void printAttributes() override;
	
	//---------- Data fields ----------
	double eX;	///<X-component of the eccentricity offset vector
	double eY;	///<Y-component of the eccentricity offset vector
	double eZ;	///<Z-component of the eccentricity offset vector
};

