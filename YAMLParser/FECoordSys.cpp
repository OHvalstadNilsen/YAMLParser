#include "pch.h"
#include "FECoordSys.h"
#include <iostream>

FECoordSys::FECoordSys(YAML::Node& yamlNode) {
	if (!assignIndependentAttributes(yamlNode)) {
		throw std::runtime_error("CoordSys error: Mandatory attributes missing.");
	}
	normalizeMatrix();
	this->type = COORDSYS;
}

FECoordSys::FECoordSys(int id, double Xx, double Xy, double Xz,
					   double Yx, double Yy, double Yz,
					   double Zx, double Zy, double Zz) {
	setID(id);
	M[0][0] = Xx;
	M[0][1] = Xy;
	M[0][2] = Xz;

	M[1][0] = Yx;
	M[1][1] = Yy;
	M[1][2] = Yz;
	
	M[2][0] = Zx;
	M[2][1] = Zy;
	M[2][2] = Zz;
}

FECoordSys::~FECoordSys() {}

bool FECoordSys::assignIndependentAttributes(YAML::Node & yamlNode) {
	if (!yamlNode["rotID"]) return false;
	setID(yamlNode["rotID"].as<int>());

	if (yamlNode["X"] && yamlNode["Y"] && yamlNode["Z"]) {
		for (int j = 0; j < yamlNode["X"].size(); j++) {
			this->M[0][j] = yamlNode["X"][j].as<double>();
			this->M[1][j] = yamlNode["Y"][j].as<double>();
			this->M[2][j] = yamlNode["Z"][j].as<double>();
		}
		return true;
	}
	else if (yamlNode["Xx"] && yamlNode["Xy"] && yamlNode["Xz"]
		&& yamlNode["Yx"] && yamlNode["Yy"] && yamlNode["Yz"]
		&& yamlNode["Zx"] && yamlNode["Xy"] && yamlNode["Zz"]) {
		M[0][0] = yamlNode["Xx"].as<double>();
		M[0][1] = yamlNode["Xy"].as<double>();
		M[0][2] = yamlNode["Xz"].as<double>();

		M[1][0] = yamlNode["Yx"].as<double>();
		M[1][1] = yamlNode["Yy"].as<double>();
		M[1][2] = yamlNode["Yz"].as<double>();

		M[2][0] = yamlNode["Zx"].as<double>();
		M[2][1] = yamlNode["Zy"].as<double>();
		M[2][2] = yamlNode["Zz"].as<double>();
		return true;
	}
	//If the coordinates system is defined by points 
	//with respect to the global origin (PCOORDSYS)
	else if (yamlNode["Ox"] && yamlNode["Zx"] && yamlNode["Xx"]
		&& yamlNode["Oy"] && yamlNode["Zy"] && yamlNode["Xy"]
		&& yamlNode["Oz"] && yamlNode["Zz"] && yamlNode["Xz"]) {
		BuildFromPoints(yamlNode);
		return true;
	}
	return false;
}

void FECoordSys::BuildFromPoints(YAML::Node yamlNode) {
	M[0][0] = yamlNode["Xx"].as<double>() - yamlNode["Ox"].as<double>();
	M[0][1] = yamlNode["Xy"].as<double>() - yamlNode["Oy"].as<double>();
	M[0][2] = yamlNode["Xz"].as<double>() - yamlNode["Oz"].as<double>();

	M[2][0] = yamlNode["Zx"].as<double>() - yamlNode["Ox"].as<double>();
	M[2][1] = yamlNode["Zy"].as<double>() - yamlNode["Oy"].as<double>();
	M[2][2] = yamlNode["Zz"].as<double>() - yamlNode["Oz"].as<double>();

	//Compute orthogonal vector
	std::vector<double> orthoVec = computeOrthogonalVector(M[0][0], M[0][1], M[0][2], M[2][0], M[2][1], M[2][2]);
	//Insert values into Y vector in the matrix
	M[1][0] = orthoVec[0];
	M[1][1] = orthoVec[1];
	M[1][2] = orthoVec[2];
}

std::vector<double> FECoordSys::computeOrthogonalVector(double Xx, double Xy, double Xz, 
														double Zx, double Zy, double Zz) {
	//Compute the vector cross product of the two input vectors
	std::vector<double> orthoVec;
	orthoVec.push_back(-((Xy * Zz) - (Xz * Zy)));
	orthoVec.push_back(-((Xz * Zx) - (Xx * Zz)));
	orthoVec.push_back(-((Xx * Zy) - (Xy * Zx)));
	return orthoVec;
}

void FECoordSys::normalizeMatrix() {
	for (int i = 0; i < 3; i++) {
		double length = sqrt((M[i][0] * M[i][0]) + (M[i][1] * M[i][1]) + (M[i][2] * M[i][2]));

		if (length == 0) {
			throw std::runtime_error("CoordSys error: Cannot normalize null vector");
		}
		else {
			//Update the vector to unit length
			for (int j = 0; j < 3; j++) {
				M[i][j] = M[i][j] / length;
			}
		}
	}
}

void FECoordSys::printAttributes() {
	std::cout << "CoordSys:    "
		<< "id: " << getID()
		<< std::endl;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			std::cout << M[i][j] << "\t";
		}
		std::cout << "\n";
	}
}
