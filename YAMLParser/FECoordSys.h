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
	virtual void printAttributes() override;
	virtual bool setMandatoryValues(YAML::Node & yamlNode) override;
	virtual void setOptionalValues(YAML::Node & yamlNode) override;
	void BuildFromPoints(YAML::Node yamlNode);

	void normalizeMatrix();

	std::vector<double> computeOrthogonalVector(double Xx, double Xy, double Xz, 
												double Zx, double Zy, double Zz);

	//Matrix containing the direction vectors (X, Y, Z)
	double M[3][3];
};

