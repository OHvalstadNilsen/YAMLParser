/** \brief
* This class represents a load combination.
*/

#pragma once
#include "Identifiable.h"
#include "GenericFE.h"
#include "FETypes.h"
#include <vector>
#include <map>

class FELoadComb :
	public GenericFE
{
public:
	/**Constructor. 
	*
	*loadCombId: Identification number for the object.
	*
	* lcFactors: Map with load case ID as key, and scaling factor as value.
	*/
	FELoadComb(int loadCombId, std::map<int, double> lcFactors);
	~FELoadComb();
	
	//---------- Functions ----------
	// Inherited via GenericFE
	virtual bool assignIndependentAttributes(YAML::Node & yamlNode) override;
	virtual void printAttributes() override;
	
	//---------- Data fields ----------
	std::map<int, double> loadCombFactors; ///< Map associating load case IDs to scaling factors.
};

