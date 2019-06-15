/** \brief
* This class represents a FE beam element.
*/

#pragma once
#include <map>
#include "yaml-cpp/yaml.h"
#include "FETypes.h"
#include "GenericFE.h"
#include "Identifiable.h"
#include "GenericCrossSection.h"

//Forward declarations
class GenericMaterial;
class FEEccentricity;

class FEBeam :  
	public GenericFE
{
public:
	/**This is the class constructor. It simply populates the attributes with data from
	* the function argument list.
	*/
	FEBeam(int id, FENode* node1, FENode* node2, GenericMaterial* mat, GenericCrossSection* crossSection, 
		FEEccentricity* ecc1, FEEccentricity* ecc2, FEVector* vec);
	~FEBeam();

	//---------- Functions ----------
	Identifiable::Type getType();
	virtual std::string getTypeAsString() override;
	
	/**This function is inherited from GenericFE. This function does nothing.
	* The only independent attributes for the BEAM record is the id, but this attribute
	* is not assigned in this function. Rather, the id is passed as an integer in the constructor
	* because passing an integer is more effective than passing a YAML::Node.
	*
	*This method is implemented to ensure consistency with the base class.
	*/
	bool assignIndependentAttributes(YAML::Node& yamlNode) override;
	
	void printAttributes();
	
	//Data fields
	const FENode *pNode1;						///< Ptr to FENode object defining the start point of the beam
	const FENode *pNode2;						///< Ptr to FENode object defining the end point of the beam
	const GenericMaterial *pMaterial;			///< Ptr to material object
	const GenericCrossSection *pCrossSection;	///< Ptr to object holding the cross-sectional data
	const FEEccentricity *pEcc1;				///< Ptr to eccentricity information for node 1
	const FEEccentricity *pEcc2;				///< Ptr to eccentricity information for node 2
	const FEVector* pVec;						///< Ptr to FEVector object specifying the beam's orientation
};

