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
	public Identifiable, 
	public GenericFE
{
public:
	FETrishell(int id, FECoordSys* coord, FENode* n1, FENode* n2, FENode* n3, 
		FEIsoMaterial* mat, GenericCrossSection* crossSection,
		FEEccentricity* ecc1, FEEccentricity* ecc2, FEEccentricity* ecc3);
	~FETrishell();
	
	virtual std::string getTypeAsString() override;

	//Inherited from GenericFE
	bool assignIndependentAttributes(YAML::Node& yamlNode) override;
	void printAttributes();
	
	//Data fields
	FENode *pNode1, *pNode2, *pNode3;
	FECoordSys *pCoordSys;
	GenericCrossSection *pCrossSection;
	FEIsoMaterial* pMaterial;
	//TODO: Implement geoID attribute
	//-->
	FEEccentricity *pEcc1, *pEcc2, *pEcc3;
};

