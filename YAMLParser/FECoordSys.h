#pragma once
#include "yaml-cpp/yaml.h"
#include "Identifiable.h"
#include "GenericFE.h"
#include <array>
#include <vector>

class FECoordSys :
	public Identifiable,
	public GenericFE
{
public:
	FECoordSys(int id, double Xx, double Xy, double Xz,
			   double Yx, double Yy, double Yz,
			   double Zx, double Zy, double Zz);

	FECoordSys(YAML::Node& yamlNode);
	
	virtual ~FECoordSys();

	// Inherited via GenericFE
	virtual bool assignIndependentAttributes(YAML::Node & yamlNode) override;
	virtual void printAttributes() override;

	void BuildFromPoints(YAML::Node yamlNode);

	std::vector<double> computeOrthogonalVector(double Xx, double Xy, double Xz, 
												double Zx, double Zy, double Zz);

	void normalizeMatrix();
	
	//Data fields
	double M[3][3]; //Matrix containing the direction vectors (X, Y, Z)
};

