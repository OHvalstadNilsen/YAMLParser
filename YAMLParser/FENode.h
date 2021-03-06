/** \brief
* This class represents a FE node.
*/

#pragma once
#include <vector>
#include <string>
#include "yaml-cpp/yaml.h"
#include "Identifiable.h"
#include "FECoordSys.h"

//Forward declarations
class FECoordSys;

class FENode : 
	public Identifiable
{
public:
	FENode(YAML::Node& yamlNode, FECoordSys* rot);
	~FENode();

	
	Identifiable::Type getType();
	virtual std::string getTypeAsString() override;

	/**Assigns NODE attributes with dependency level null, 
	* i.e. attributes which can be obtained directly from the YAML representation*/
	bool assignIndependentAttributes(YAML::Node& yamlNode);

	/**Sets the coordinates for the node, from the attribute fields in yamlNode*/
	bool setCoordinates(YAML::Node& yamlNode);

	/**Extracts keys of a YAML mapping, in a container on the form std::vector<std::string>.*/
	std::vector<std::string> extractYamlKeys(YAML::Node yamlNode);

	/**Prints the attributes and their values to console*/
	void printAttributes();

	//Data fields
	double x;			///< X-coordinate for the node
	double y;			///< Y-coordinate for the node
	double z;			///< Z-coordinate for the node
	int ix;				///< Boundary code for translation in x-direction
	int iy;				///< Boundary code for translation in y-direction
	int iz;				///< Boundary code for translation in z-direction
	int irx;			///< Boundary code for rotation about X-axis
	int iry;			///< Boundary code for rotation about Y-axis
	int irz;			///< Boundary code for rotation about Z-axis
	FECoordSys *pRotID;	///< Reference to local coordinate system for BCs
};

