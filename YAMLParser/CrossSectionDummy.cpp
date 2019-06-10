#include "pch.h"
#include "CrossSectionDummy.h"
#include <iostream>


CrossSectionDummy::CrossSectionDummy() {
	setID(-1);
	this->type = CROSS_SECTION_DUMMY;
}

CrossSectionDummy::~CrossSectionDummy(){
}

//Getters for FEType
Identifiable::Type CrossSectionDummy::getType() { return this->type; }
std::string CrossSectionDummy::getTypeAsString() { return "CROSS_SECTION_DUMMY"; }

bool CrossSectionDummy::assignIndependentAttributes(YAML::Node & yamlNode)
{
	//Nothing to assign. This function is present only to ensure consistency with the base class.
	return false;
}

void CrossSectionDummy::printAttributes() {
	std::cout << "CrossSection:		id: " << getID()
		<< "type: " << getTypeAsString() << std::endl;
}
