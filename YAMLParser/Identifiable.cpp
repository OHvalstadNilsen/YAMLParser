#include "pch.h"
#include "Identifiable.h"

int Identifiable::getID() const {
	return id;
}

void Identifiable::setID(int id) {
	this->id = id;
}

Identifiable::~Identifiable()
{
}

Identifiable::Type Identifiable::getType() {
	return NULLTYPE;
}

std::string Identifiable::getTypeAsString()
{
	/*This method is supposed to be overridden for each child
	* class of Identifiable.
	*/
	return "Identifiable";
}

