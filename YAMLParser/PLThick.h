//#pragma once
//#include "yaml-cpp/yaml.h"
//#include "Identifiable.h"
//#include "GenericFE.h"
//
///* This class defines the thickness for plate/shell elements.
//* PLThick = plate thickness
//*/
//class PLThick :
//	public Identifiable,
//	public GenericFE,
//	public GenericCrossSection
//{
//public:
//	PLThick(YAML::Node& yamlNode);
//	~PLThick();
//	//Functions
//	//Inherited via GenericFE
//	virtual void printAttributes() override;
//	virtual bool setMandatoryValues(YAML::Node & yamlNode) override;
//	virtual void setOptionalValues(YAML::Node & yamlNode) override;
//
//	//Variables:
//	//ID inherited from Identifiable.
//	double T;
//
//};
//
