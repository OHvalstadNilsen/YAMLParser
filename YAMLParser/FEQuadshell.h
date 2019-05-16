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
	FEQuadshell(YAML::Node& yamlNode);
	FEQuadshell(int id, FECoordSys* coordSys, FENode* n1, FENode* n2, FENode* n3, FENode* n4,
		FEIsoMaterial* mat, GenericCrossSection* crossSection,
		FEEccentricity* ecc1, FEEccentricity* ecc2, FEEccentricity* ecc3, FEEccentricity* ecc4);

	~FEQuadshell();
	virtual std::string getTypeAsString() override;

	bool setMandatoryValues(YAML::Node& yamlNode);
	void setOptionalValues(YAML::Node& yamlNode);
	bool setNodes(YAML::Node & yamlNode);
	void printAttributes();

	int node1, node2, node3, node4, material, geoID;
	int coordID, ecc1, ecc2, ecc3, ecc4;

	//Attributes
	FENode *pNode1, *pNode2, *pNode3, *pNode4;
	GenericCrossSection* pCrossSection;
	FEIsoMaterial *pMaterial;
	//TODO: Implement geoID reference
	//-->
	FECoordSys *pCoordSys;
	FEEccentricity *pEcc1, *pEcc2, *pEcc3, *pEcc4;
};

