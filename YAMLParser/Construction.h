#pragma once

#include "yaml-cpp/yaml.h"
#include "FETypes.h"
#include <vector>
#include <map>
#include <iostream>

class Construction
{
public:
	Construction();
	~Construction();

	bool checkExistence(int id, std::string type);
	
	bool checkExistence2(Identifiable element); //Possibly superfluous

	Identifiable* fetchObject(int id, std::string type);

	bool addNode(FENode& node);
	bool addBeam(FEBeam& beam);
	bool addElement(Identifiable* element);

	std::vector<Identifiable*> elementList;
	std::vector<FENode> nodeList;
	std::vector<FEBeam> beamList;
	std::vector<FEIsoMaterial> isoMaterialList;
	// and so on ...
};

//FIXME: Probably unnecessary code. Not in use in checkExistence.
struct check_id {
	check_id(const int& id) {}
	bool operator()(Identifiable el) { //FIXME: bool operator()(const Identifiable& el){ ?
		return el.getID() == id;
	}
private:
	int id;
};

struct check_type {
	check_type(const Identifiable::Type& t) {}
	bool operator()(Identifiable el) {
		return el.getType() == t;
	}
private:
	Identifiable::Type t;
};

struct check_existence {
	check_existence(const int& id, const Identifiable::Type& t) {}
	bool operator() (Identifiable el) const {
		//FIXME: id has wrong value!
		std::cout << el.getID() << " should be equal to " << id << std::endl;
		return (el.getID() == id) && (el.getType() == t);
	}
private:
	int id;
	Identifiable::Type t;
};
