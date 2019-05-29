/** \brief
* This class represents a FE node load element.
*/

#pragma once
#include "yaml-cpp/yaml.h"
#include "GenericFE.h"
#include "Identifiable.h"
#include "FETypes.h"

class FENodeLoad :
	public GenericFE
{
public:
	FENodeLoad(int nodeLoadId, YAML::Node& yamlNode, FENode *node, FEEccentricity *ecc);
	~FENodeLoad();

	//---------- Functions ----------
	Identifiable::Type getType();
	std::string getTypeAsString();

	// Inherited via GenericFE
	virtual bool assignIndependentAttributes(YAML::Node & yamlNode) override;
	virtual void printAttributes() override;

	//---------- Data fields ----------
	int loadCaseId;			///< Reference number for load case (NB: Not unique!)
	FENode *pNode;			///< Ptr to node in which the node load is acting.
	double fx;				///< Translational force in X-direction
	double fy;				///< Translational force in Y-direction
	double fz;				///< Translational force in Z-direction
	double mx;				///< Concentrated moment aboud X-axis
	double my;				///< Concentrated moment aboud Y-axis
	double mz;				///< Concentrated moment aboud Z-axis
	FEEccentricity *pEcc;	///< Ptr to eccentricity location vector
};

