#pragma once
#include "yaml-cpp/yaml.h"
#include "GenericFE.h"
#include "Identifiable.h"
#include "FETypes.h"

class FENodeLoad :
	public Identifiable,
	public GenericFE
{
public:
	FENodeLoad(int nodeLoadId, YAML::Node& yamlNode, FENode *n, FEEccentricity *ecc);
	~FENodeLoad();

	Identifiable::Type getType();

	std::string getTypeAsString();

	// Inherited via GenericFE
	virtual bool assignIndependentAttributes(YAML::Node & yamlNode) override;
	virtual void printAttributes() override;

	//Data fields
	int loadCaseId;
	FENode *pNode;
	double fx, fy, fz;
	double mx, my, mz;
	FEEccentricity *pEcc;
};

