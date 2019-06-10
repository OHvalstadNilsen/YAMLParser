/** \brief
*	Template definitions for the FEM data records in
*	the YAML based input file format for FEA.
*/

#pragma once
#include <string>
#include <vector>
#include <map>

class FEAFormat
{
public:
	FEAFormat();
	~FEAFormat();

	//Data types defined in the format
	//const std::vector<std::string> data_types = { "NODE", "BEAM", "TRISHELL", "PIPE", "IHPROFILE", "PLTHICK",
	//	"UNITVEC", "ECCENT", "MISOIEP", "NODELOAD", "GRAVITY", "NODTRANS" };

	//Format definitions, i.e. templates defining the attrubutes comprised in each data type
	// Nodal data:
	std::vector<std::string> node_template = { "id", "x", "y", "z", "ix", "iy", "iz", "irx", "iry", "irz", "rotID" };
	std::vector<std::string> nodtrans_template = { "rotID", "Xx", "Yy", "Zz", "Yx", "Yy", "Yz", "Zx", "Zy", "Zz" };
	std::vector<std::string> coordsys_template = { "rotID", "Xx", "Xy", "Xz", "Yx", "Yy", "Yz", "Zx", "Zy", "Zz" };
	std::vector<std::string> pcoordsys_template = { "rotID", "Ox", "Oy", "Oz", "Zx", "Zy", "Zz", "Xx", "Xy", "Xz" };
	//std::vector<std::string> trannodes_template = { "rotID", "nod1", "nod2", ...};
	// Element data:
	std::vector<std::string> beam_template = { "elemID", "node1", "node2", "material", "geoID", "vecID", "ecc1", "ecc2" };
	std::vector<std::string> trishell_template = { "elemID", "node1", "node2", "node3", "material", "geoID", "vecID", "ecc1", "ecc2" };
	std::vector<std::string> quadshell_template = { "elemID", "node1", "node2", "node3", "node4", "material", "geoID", "coordID", "ecc1", "ecc2", "ecc3", "ecc4" };
	// Cross-sectinal data
	std::vector<std::string> pipe_template = { "geoID", "d_outer", "thickness", "shearY", "shearZ" };
	std::vector<std::string> ihprofile_template = { "geoID", "height", "T_web", "W_top", "T_top", "W_bot", "T_bot", "shearY", "shearZ" };
	std::vector<std::string> plthick_template = { "geoID", "thickness" };
	// Misc data
	std::vector<std::string> cfemvector_template = { "vecID", "x", "y", "z" }; //template for UNITVEC, ZVECTOR and YVECTOR in CFEM.
	std::vector<std::string> eccent_template = { "eccID", "eX", "eY", "eZ" };
	std::vector<std::string> misoiep_template = { "matID", "E-module", "poisson", "yield", "density", "thermalExpansion" };
	std::vector<std::string> nodeload_template = { "loadCaseID", "nodeID", "fx", "fy", "fz", "mx", "my", "mz", "ecc" };
	std::vector<std::string> gravity_template = { "loadCaseID", "aX", "aY", "aZ" };

	//Mapping the templates to its corresponding data type:
	std::map<std::string, std::vector<std::string>> data_types_m; // map<data_type, data_type_template>.

	/**Extract all keys from map<std::string, std::vector<std::string>>*/
	std::vector<std::string> extract_keys();
};

