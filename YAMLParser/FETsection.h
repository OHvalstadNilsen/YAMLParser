/** \brief  This class represents a T-profile cross-sections, 
*			used by for instance BEAM elements
*/

#pragma once
#include "yaml-cpp/yaml.h"
#include "GenericCrossSection.h"
class FETsection :
	public GenericCrossSection
{
public:
	FETsection(YAML::Node& yamlNode);
	~FETsection();

	//---------- Functions -----------
	//Inherited via Identifiable
	virtual Identifiable::Type getType() override;
	virtual std::string getTypeAsString() override;

	// Inherited via GenericCrossSection
	virtual void printAttributes() override;
	virtual bool assignIndependentAttributes(YAML::Node & yamlNode) override;

	//---------- Data fields ----------
	double H;		///< Height of profile
	double T_web;	///< Thickness of the vertical part
	double Width;	///< Width of the top flange
	double T_top;	///< Thickness of the top flange
};

