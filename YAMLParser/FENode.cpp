#include "pch.h"
#include "FENode.h"
#include <iostream>


FENode::FENode(int id, double x, double y, double z, int ix, int iy, int iz, int irx, int iry, int irz, int rotID) 
{
	this->id = id;
	this->x = x;
	this->y = y;
	this->z = z;
	this->ix = ix;
	this->iy = iy;
	this->iz = iz;
	this->irx = irx;
	this->iry = iry;
	this->irz = irz;
	this->rotID = rotID;
}


FENode::~FENode()
{
}

void FENode::PrintNode() {
	std::cout << "FENode:   id: " << id << ", x: " << x << ", y: " << y 
			  << ", z: " << z << ", ix: " << ix << ", iy: " << iy <<", iz: " << iz 
			  << ", irx: " << irx << ", iry: " << iry << ", irz: " << irz << ", rotID: " << rotID << std::endl;
}
