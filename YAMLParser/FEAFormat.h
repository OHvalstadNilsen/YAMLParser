/*
The YAML-based FEAFormat is defined here.
*/

#pragma once
#include <string>
#include <vector>

class FEAFormat
{
public:
	FEAFormat();
	~FEAFormat();

	//Data types defined in the format
	const std::vector<std::string> data_types = { "NODE", "BEAM", "TRISHELL", "PIPE", "IHPROFILE", "PLTHICK",
		"UNITVEC", "ECCENT", "MISOIEP", "NODELOAD", "GRAVITY", "NODTRANS" };

	//Format definitions, i.e. templates defining the attrubutes comprised in each data type
	std::vector<std::string> node_template = { "id", "x", "y", "z", "ix", "iy", "iz", "irx", "iry", "irz", "rotID" };
	std::vector<std::string> nodtrans_template = { "rotID", "Xx", "Yy", "Zz", "Yx", "Yy", "Yz", "Zx", "Zy", "Zz" };
	std::vector<std::string> beam_template = { "elemID", "node1", "node2", "material", "geoID", "vecID", "ecc1", "ecc2" };
	std::vector<std::string> trishell_template = { "elemID", "node1", "node2", "node3", "material", "geoID", "vecID", "ecc1", "ecc2" };
	std::vector<std::string> pipe_template = { "geoID", "d_outer", "thickness", "shearY", "shearZ" };
	std::vector<std::string> ihprofile_template = { "geoID", "height", "T_web", "W_top", "T_top", "W_bot", "T_bot", "shearY", "shearZ" };
	std::vector<std::string> plthick_template = { "geoID", "thickness" };
	std::vector<std::string> cfemvector_template = { "vecID", "x", "y", "z" }; //template for UNITVEC, ZVECTOR and YVECTOR in CFEM.
	std::vector<std::string> eccent_template = { "eccID", "eX", "eY", "eZ" };
	std::vector<std::string> misoiep_template = { "matID", "E-module", "poisson", "yield", "density", "thermalExpansion" };
	std::vector<std::string> nodeload_template = { "loadCaseID", "nodeID", "fx", "fy", "fz", "mx", "my", "mz", "ecc" };
	std::vector<std::string> gravity_template = { "loadCaseID", "aX", "aY", "aZ" };
	//TODO: ADD THE REMAINING DATA TYPES (Remember also adding to data_types).

	//const std::string node_template[11] = { "id", "x", "y", "z", "ix", "iy", "iz", "irx", "iry", "irz", "rotID" };
	//const std::string nodtrans_template[10] = { "rotID", "Xx", "Yy", "Zz", "Yx", "Yy", "Yz", "Zx", "Zy", "Zz" };
	//const std::string beam_template[8] = { "elemID", "node1", "node2", "material", "geoID", "vecID", "ecc1", "ecc2" };
	//const std::string trishell_template[9] = { "elemID", "node1", "node2", "node3", "material", "geoID", "vecID", "ecc1", "ecc2" };
	//const std::string pipe_template[5] = { "geoID", "d_outer", "thickness", "shearY", "shearZ" };
	//const std::string ihprofile_template[9] = { "geoID", "height", "T_web", "W_top", "T_top", "W_bot", "T_bot", "shearY", "shearZ" };
	//const std::string plthick_template[2] = { "geoID", "thickness" };
	//const std::string cfemvector_template[4] = { "vecID", "x", "y", "z" }; //template for UNITVEC, ZVECTOR and YVECTOR in CFEM.
	//const std::string eccent_template[4] = { "eccID", "eX", "eY", "eZ" };
	//const std::string misoiep_template[6] = { "matID", "E-module", "poisson", "yield", "density", "thermalExpansion" };
	//const std::string nodeload_template[9] = { "loadCaseID", "nodeID", "fx", "fy", "fz", "mx", "my", "mz", "ecc" };
	//const std::string gravity_template[4] = { "loadCaseID", "aX", "aY", "aZ" };
};

