/**This is a collective header file for all
* FEM element types defined in the parser.
* 
* Including this file in other .h or .cpp 
* files will include all the defined FEM
* element types.
*/

#pragma once
#include <array>
#include <string>

#include "FECoordSys.h"
#include "PLThick.h"
#include "FENode.h"
#include "FEVector.h"
#include "FEBeam.h"
#include "FETrishell.h"
#include "FEQuadshell.h"
#include "FEEccentricity.h"
#include "FEIsoMaterial.h"
#include "GenericCrossSection.h"
#include "CrossSectionDummy.h"
#include "FEPipe.h"
#include "PLComp.h"
#include "FENodeLoad.h"
#include "FELoadComb.h"