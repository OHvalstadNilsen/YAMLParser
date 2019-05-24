#pragma once

#include "yaml-cpp/yaml.h"
#include "FETypes.h"
#include <vector>
#include <map>
#include <iostream>

class Structure
{
public:
	Structure();
	~Structure();

	bool checkElementExistence(int id, std::string& type);

	//Check object existence
	bool checkCoordSysExistence(int id);
	bool checkCrossSectionExistence(int id, std::string& type);
	bool checkMaterialExistence(int id);
	bool checkNodeExistence(int id);
	bool checkNodeLoadExistence(int id);


	//Fetch data objects
	FECoordSys * fetchCoordSys(int id);
	Identifiable* fetchObject(int id, std::string type);
	GenericCrossSection* fetchCrossSection(int id);
	FEIsoMaterial* fetchMaterial(int id); //TODO: Change to generic material type
	FENode* fetchNode(int id);
	FENodeLoad* fetchNodeLoad(int id);

	//Add data objects
	bool addNode(FENode* node);
	bool addElement(Identifiable* element);
	bool addCoordSys(FECoordSys * coordSys);
	bool addCrossSection(GenericCrossSection * crossSection);
	bool addMaterial(FEIsoMaterial * material); //TODO: Change to generic material type
	bool addNodeLoad(FENodeLoad * nodeLoad);

	//Containers for instantiated data objects
	std::vector<FECoordSys*> coordSysList;
	std::map<int, FECoordSys*> coordSysMap;

	std::vector<GenericCrossSection*> crossSectionList;
	std::map<int, GenericCrossSection*> crossSectionMap;
	
	//TODO: Change to generic material type
	std::vector<FEIsoMaterial*> materialList;
	std::map<int, FEIsoMaterial*> materialMap;

	std::vector<FENode*> nodeList;
	std::map<int, FENode*> nodeMap;

	std::vector<Identifiable*> elementList;
	std::map<int, Identifiable*> elementMap;

	std::vector<FENodeLoad*> nodeLoadList;
	std::map<int, FENodeLoad*> nodeLoadMap;
};

//FIXME: Delete this (unnecessary code). Not in use in checkExistence.
//struct check_id {
//	check_id(const int& id) {}
//	bool operator()(Identifiable el) { //FIXME: bool operator()(const Identifiable& el){ ?
//		return el.getID() == id;
//	}
//private:
//	int id;
//};
//
//struct check_type {
//	check_type(const Identifiable::Type& t) {}
//	bool operator()(Identifiable el) {
//		return el.getType() == t;
//	}
//private:
//	Identifiable::Type t;
//};
//
//struct check_existence {
//	check_existence(const int& id, const Identifiable::Type& t) {}
//	bool operator() (Identifiable el) const {
//		//FIXME: id has wrong value!
//		std::cout << el.getID() << " should be equal to " << id << std::endl;
//		return (el.getID() == id) && (el.getType() == t);
//	}
//private:
//	int id;
//	Identifiable::Type t;
//};
