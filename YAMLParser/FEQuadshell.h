/** \brief
*	This class represents a quadrilateral shell element.
*/

#pragma once
#include "GenericFE.h"
#include "yaml-cpp/yaml.h"
#include "Identifiable.h"
#include "FETypes.h"

//Forward declarations
class FECoordSys;
class FENode;
class FEIsoMaterial;
class GenericCompSection;
class FEEccentricity;

class FEQuadshell : 
	public GenericFE
{
public:
	FEQuadshell(int id, FENode* n1, FENode* n2, FENode* n3, FENode* n4,
		FEIsoMaterial* mat, GenericCompSection* compSection,
		FEEccentricity* ecc1, FEEccentricity* ecc2, FEEccentricity* ecc3, FEEccentricity* ecc4);
	~FEQuadshell();

	//---------- Functions -----------
	//Inherited from GenericFE
	virtual std::string getTypeAsString() override;

	bool assignIndependentAttributes(YAML::Node& yamlNode) override;
	void printAttributes();

	//---------- Data fields ----------
	FENode *pNode1;							///< Ptr to node defining first corner
	FENode *pNode2;							///< Ptr to node defining second corner
	FENode *pNode3;							///< Ptr to node defining third corner
	FENode *pNode4;							///< Ptr to node defining fourth corner
	GenericCompSection* pCompSection;		///< Ptr to object containing composite sectional data
	FEIsoMaterial *pMaterial;				///< Ptr to object containing material information
	FEEccentricity *pEcc1;					///< Ptr to eccentricity information for node1
	FEEccentricity *pEcc2;					///< Ptr to eccentricity information for node2
	FEEccentricity *pEcc3;					///< Ptr to eccentricity information for node3
	FEEccentricity *pEcc4;					///< Ptr to eccentricity information for node4
};

