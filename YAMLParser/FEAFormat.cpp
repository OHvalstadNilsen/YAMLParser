#include "pch.h"
#include "FEAFormat.h"

//Constructor populating the mapping of data types with their corresponding template.
FEAFormat::FEAFormat()
{
	/*
	data_types_m is a map with
		Key: data_type
		Value: data_type_template.
	*/
	//Nodal data
	data_types_m["NODE"] = node_template;
	data_types_m["NODTRANS"] = nodtrans_template;
	data_types_m["COORDSYS"] = coordsys_template;
	data_types_m["PCOORDSYS"] = pcoordsys_template;
	//data_types_m["TRANNODES"] = trannodes_template;
	data_types_m["BEAM"] = beam_template;
	data_types_m["TRISHELL"] = trishell_template;
	data_types_m["QUADSHEL"] = quadshell_template;
	data_types_m["PIPE"] = pipe_template;
	data_types_m["IHPROFILE"] = ihprofile_template;
	data_types_m["PLTHICK"] = plthick_template;
	data_types_m["UNITVEC"] = cfemvector_template;
	data_types_m["ECCENT"] = eccent_template;
	data_types_m["MISOIEP"] = misoiep_template;
	data_types_m["NODELOAD"] = nodeload_template;
	data_types_m["GRAVITY"] = gravity_template;
}

//Extract all keys in a map on the form <std::string, std::vector<std::string>>
std::vector<std::string> FEAFormat::extract_keys() {
	std::vector<std::string> retval;
	for (auto const& element : data_types_m) {
		retval.push_back(element.first);
	}
	return retval;
}

//Destructor
FEAFormat::~FEAFormat()
{
}
