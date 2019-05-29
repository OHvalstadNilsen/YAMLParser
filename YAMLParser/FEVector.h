/** \brief
*	This class represents a (normalized) vector used to define element orientation.
*/
#pragma once
#include "yaml-cpp/yaml.h"
#include "GenericFE.h"

class FEVector :
	public GenericFE
{
public:
	FEVector(YAML::Node& yamlNode, std::string vecType);
	~FEVector();


	//---------- Functions ----------
	Identifiable::Type getType();
	std::string getTypeAsString();
	// Inherited via GenericFE
	virtual void printAttributes() override;
	virtual bool assignIndependentAttributes(YAML::Node & yamlNode) override;

	void normalizeVector(); ///< Normalize the vector (named vec)
	
	//---------- Data fields ----------
	double vec[3]; ///< The vector data. Contents: x-, y-, and z-components of the vector.
	
};

