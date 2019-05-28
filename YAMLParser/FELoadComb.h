#pragma once
#include "Identifiable.h"
#include "GenericFE.h"
#include "FETypes.h"
#include <vector>
#include <map>

class FELoadComb :
	public Identifiable,
	public GenericFE
{
public:
	FELoadComb(int loadCombId, std::map<int, double> lcFactors);
	~FELoadComb();
	
	// Inherited via GenericFE
	virtual bool assignIndependentAttributes(YAML::Node & yamlNode) override;
	virtual void printAttributes() override;
	
	//Data fields
	std::map<int, double> loadCombFactors; //map<ilc, f>
};

