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

#include "FECoordSys.h"
#include "PLThick.h"
#include "FENode.h"
#include "FEBeam.h"
#include "FETrishell.h"
#include "FEQuadshell.h"
#include "FEEccentricity.h"
#include "FEIsoMaterial.h"
#include "GenericCrossSection.h"
#include "FEPipe.h"
#include "FENodeLoad.h"