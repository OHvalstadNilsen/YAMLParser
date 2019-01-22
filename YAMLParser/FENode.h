#pragma once

#include <vector>
#include <string>

class FENode
{
public:
	FENode(int id, double x, double y, double z, int ix = 0, int iy = 0, int iz = 0, int irx = 0, int iry = 0, int irz = 0, int rotID = 0);
	~FENode();

	void PrintNode();

	int id, rotID;
	double x, y, z;
	int ix, iy, iz, irx, iry, irz;
};

