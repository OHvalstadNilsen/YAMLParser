/** \brief
* This class represents a triangular shell element.
*/


#pragma once

#include "yaml-cpp/yaml.h"
#include "GenericFE.h"
#include "Identifiable.h"
#include "FETypes.h"

//Forward declarations
class FECoordSys;
class FEIsoMaterial;
class GenericCrossSection;
class FEEccentricity;

class FETrishell : 
	public GenericFE
{
public:
	FETrishell(int id, FECoordSys* coord, FENode* n1, FENode* n2, FENode* n3, 
		FEIsoMaterial* mat, GenericCrossSection* crossSection,
		FEEccentricity* ecc1, FEEccentricity* ecc2, FEEccentricity* ecc3);
	~FETrishell();
	
	//---------- Functions -----------
	virtual std::string getTypeAsString() override;
	//Inherited from GenericFE
	bool assignIndependentAttributes(YAML::Node& yamlNode) override;
	void printAttributes();
	
	//----------- Data fields -----------
	FENode *pNode1;							///< Ptr to node defining first corner
	FENode *pNode2;							///< Ptr to node defining second corner
	FENode *pNode3;							///< Ptr to node defining third corner
	//TODO: Remove coordSys
	FECoordSys *pCoordSys;
	GenericCrossSection *pCrossSection;		///< Ptr to object containing cross-sectional data
	FEIsoMaterial* pMaterial;				///< Ptr to object containing material information
	//TODO: Implement geoID attribute
	//-->
	FEEccentricity *pEcc1;					///< Ptr to eccentricity information for node1
	FEEccentricity *pEcc2;					///< Ptr to eccentricity information for node2
	FEEccentricity *pEcc3;					///< Ptr to eccentricity information for node3
};

