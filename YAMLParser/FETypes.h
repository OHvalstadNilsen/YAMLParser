#pragma once
/*This is a collective header file for all
* FEM element types defined in the parser.
* 
* Including this file in other .h or .cpp 
* files will include all the defined FEM
* element types.
*/

#include <array>
#include <string>

#include "FENode.h"
#include "FEBeam.h"
#include "FETrishell.h"
#include "FEQuadshell.h"
#include "FEIsoMaterial.h"
#include "FEPipe.h"

/*
class FETypes {
public:
	std::string types[] = {
		"node",
		"beam",
		"trishell",
		"quadshell",
		"isomaterial"
	};
	
};

*/