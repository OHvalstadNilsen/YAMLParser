/** \brief
* This class represents a pipe-shaped cross-section.
*/

#pragma once
#include "GenericCrossSection.h"
#include "GenericFE.h"
#include "yaml-cpp/yaml.h"
class FEPipe :
	public GenericCrossSection,
	public GenericFE
{
public:
	FEPipe(YAML::Node yamlNode);
	virtual ~FEPipe();

	//---------- Functions -----------
	//Inherited via Identifiable
	virtual Identifiable::Type getType() override;
	virtual std::string getTypeAsString() override;

	// Inherited via GenericFE
	virtual void printAttributes() override;
	virtual bool assignIndependentAttributes(YAML::Node & yamlNode) override;
	
	//---------- Data types ----------
	double outerDiameter;	///< Outer diameter of the pipe
	double thickness;		///< Thickness of the pipe wall
	double shearY;			///< Shear area factor of Y-axia
	double shearZ;			///< Shear area factor of Z-axia
};

