/** \brief
*		This class represents a quadrilateral shell element.
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
class GenericCrossSection;
class FEEccentricity;

class FEQuadshell : 
	public Identifiable, 
	public GenericFE
{
public:
	FEQuadshell(int id, FECoordSys* coordSys, FENode* n1, FENode* n2, FENode* n3, FENode* n4,
		FEIsoMaterial* mat, GenericCrossSection* crossSection,
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
	GenericCrossSection* pCrossSection;		///< Ptr to object containing cross-sectional data
	FEIsoMaterial *pMaterial;				///< Ptr to object containing material information
	//TODO: Implement geoID reference
	//-->
	//TODO: Remove coordsys
	FECoordSys *pCoordSys;					///< Ptr to local coordinate system
	FEEccentricity *pEcc1;					///< Ptr to eccentricity information for node1
	FEEccentricity *pEcc2;					///< Ptr to eccentricity information for node2
	FEEccentricity *pEcc3;					///< Ptr to eccentricity information for node3
	FEEccentricity *pEcc4;					///< Ptr to eccentricity information for node4
};

