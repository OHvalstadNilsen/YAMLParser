/** \brief
	This class represents a plate composite. That is, a composite 
	cross section for shell elements.
*/
#pragma once
#include "yaml-cpp/yaml.h"
#include "GenericSection.h"
#include "GenericMaterial.h"
class PLComp :
	public GenericSection
{
public:
	PLComp(YAML::Node& yamlNode, std::vector<GenericMaterial*> matList);
	~PLComp();

	//---------- Data fields ----------
	/**Struct holding information for one ply in the composite*/
	struct Ply {
		GenericMaterial* mat;		///< Ptr to the material of the ply
		double T;					///< Ply thickness
		double theta;				///< Ply orientation
	};
	
	double z0;					///< Starting coordinate for the first laminate layer
	std::vector<Ply> plies;		///< Ordered list of plies (bottom ply at index 0)
	
	//---------- Functions ----------
	//Inherited via Identifiable
	virtual Identifiable::Type getType() override;
	virtual std::string getTypeAsString() override;
	
	// Inherited via GenericMaterial
	virtual bool assignIndependentAttributes(YAML::Node & yamlNode) override;
	virtual void printAttributes() override;
	
	/**Initiate a ply from the lists of plies and materials
	 * and add it to the list of plies*/
	bool addPly(const YAML::Node & plyNode, GenericMaterial* mat);
};