#pragma once

#include <map>
#include "yaml-cpp/yaml.h"
#include "FETypes.h"
#include "GenericFE.h"
#include "Identifiable.h"
#include "GenericCrossSection.h"

//Forward declarations
class FEIsoMaterial;
class FEEccentricity;

class FEBeam : 
	public Identifiable, 
	public GenericFE
{
public:
	//Constructors
	FEBeam(int id, FENode* node1, FENode* node2, FEIsoMaterial* mat, 
		GenericCrossSection* crossSection, FEEccentricity* ecc1, FEEccentricity* ecc2, FECoordSys* rotID);
	~FEBeam();

	//Functions
	Identifiable::Type getType();
	virtual std::string getTypeAsString() override;
	bool assignIndependentAttributes(YAML::Node& yamlNode) override;
	void printAttributes();
	
	//Data fields
	const FENode *pNode1, *pNode2;
	const FEIsoMaterial *pMaterial;
	const GenericCrossSection *pCrossSection;
	const FEEccentricity *pEcc1, *pEcc2;
	const FECoordSys *pCoordSys;
};

