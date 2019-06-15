/** \brief
*	This class represents a triangular shell element.
*/
#pragma once
#include "yaml-cpp/yaml.h"
#include "GenericFE.h"
#include "Identifiable.h"
#include "FETypes.h"

//Forward declarations
class FECoordSys;
class FEIsoMaterial;
class GenericCompSection;
class FEEccentricity;

class FETrishell : 
	public GenericFE
{
public:
	FETrishell(int id, FENode* n1, FENode* n2, FENode* n3, 
		FEIsoMaterial* mat, GenericCompSection* section, FEVector* vec,
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
	GenericCompSection *pCompSection;		///< Ptr to object containing composite sectional data
	FEIsoMaterial* pMaterial;				///< Ptr to object containing material information
	FEVector *pVec;							///< Ptr to vector defining local X-direction
	FEEccentricity *pEcc1;					///< Ptr to eccentricity information for node1
	FEEccentricity *pEcc2;					///< Ptr to eccentricity information for node2
	FEEccentricity *pEcc3;					///< Ptr to eccentricity information for node3
};

