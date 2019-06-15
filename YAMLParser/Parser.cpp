#include "pch.h"
#include "Parser.h"
#include "yaml-cpp\yaml.h"
#include "FEAFormat.h"
#include <iostream>
#include <fstream>

//Forward declaration
FEAFormat feaformat;

Parser::Parser(std::string filename)
{
	this->root = YAML::LoadFile(filename);

	if (!root["STRUCTURE"]) {
		throw std::runtime_error("Parser error: Could not find \"STRUCTURE\" node.");
	}
	else {
		this->structureNode = root["STRUCTURE"];
	}
	
	this->structure = new Structure(1);
	FEAFormat *feaformat = new FEAFormat();
}

Parser::~Parser() {
}

void Parser::logErrorMsg(std::runtime_error e) {
	std::ofstream ofs("ErrorLog.txt", std::fstream::app);
	ofs << e.what() << std::endl;
	ofs.close();
}

void Parser::parseCoordSys(YAML::Node& yamlNode, std::string type) {
	try {
		bool exists = structure->checkCoordSysExistence(yamlNode["rotID"].as<int>());
		if (exists) {
			throw std::runtime_error("Error: A coordinate system with id "
				+ yamlNode["id"].as<std::string>() + " already exists.");
		}
		else {
			//Instantiate coordinate system from the YAML::Node
			FECoordSys *feCoordSys = new FECoordSys(yamlNode);
			structure->addCoordSys(feCoordSys);
		}
	}
	catch(std::runtime_error &e){
		std::cout << e.what() << std::endl;
		logErrorMsg(e);
	}
}

void Parser::parseNode(YAML::Node& yamlNode, std::string type) {
	try {
		//Check if there already exists a node with this ID in the structure.
		bool exists = structure->checkNodeExistence(yamlNode["id"].as<int>());
		if (exists) {
			throw std::runtime_error("Error: A " + type + " element with id " 
				+ yamlNode["id"].as<std::string>() + " already exists.");
		}
		else {
			FECoordSys* rot;
			//Check if rotID is specified and, if so, if the corresponding coordinate system exists.
			if (yamlNode["rotID"]) {
				bool rotExists = structure->checkCoordSysExistence(yamlNode["rotID"].as<int>());
				if (!rotExists) {
					throw std::runtime_error("Error: A coordinate system with id "
						+ yamlNode["rotID"].as<std::string>() + "does not exist in structure.");
				}
				//Assign ptr to coordinate system
				rot = structure->fetchCoordSys(yamlNode["rotID"].as<int>());
			}
			else {
				//Assign default coordinate system if rotID is not specified.
				rot = structure->fetchCoordSys(0);
			}
			//Instantiate FENode
			FENode *feNode = new FENode(yamlNode, rot);
			structure->addNode(feNode);	
		}
	}
	catch(std::runtime_error &e){
		std::cout << e.what() << std::endl;
		logErrorMsg(e);
	}
}

void Parser::parseVector(YAML::Node& yamlNode, std::string type) {
	try {
		bool exists = structure->checkElementExistence(yamlNode["vecID"].as<int>(), "VECTOR");
		if (exists) {
			throw std::runtime_error("Error: A vector with id "
				+ yamlNode["vecID"].as<std::string>() + " already exists.");
		}
		else {
			FEVector* feVector = new FEVector(
			yamlNode,
			type
			);
			structure->addElement(feVector);
		}
	}
	catch (std::runtime_error &e) {
		std::cout << e.what() << std::endl;
		logErrorMsg(e);
	}
}

void Parser::parseBeam(YAML::Node& yamlNode, std::string type) {
	try {
		bool exists = structure->checkElementExistence(yamlNode["elemID"].as<int>(), type);
		if (exists) {
			throw std::runtime_error("Error: A " + type + " element with id "
				+ yamlNode["elemID"].as<std::string>() + " already exists.");
		}
		//Initialize a FEBeam from the YAML::Node
		std::map<std::string, Identifiable*> requiredElems;
		
		//Set nodes:
		if (yamlNode["nodes"].size() == 2) {
			//If the nodes are given on the form
			//nodes: [ID for node1, ID for node2]
			requiredElems["node1"] = (structure->fetchNode(yamlNode["nodes"][0].as<int>()));
			requiredElems["node2"] = (structure->fetchNode(yamlNode["nodes"][1].as<int>()));
		}
		else if (yamlNode["node1"] && yamlNode["node2"]) {
			//If the nodes are given on the form
			//node1: ID for node1
			//node2: ID for node2
			requiredElems["node1"] = (structure->fetchNode(yamlNode["node1"].as<int>()));
			requiredElems["node2"] = (structure->fetchNode(yamlNode["node2"].as<int>()));
		}
		
		//Set material:
		requiredElems["material"] = (structure->fetchMaterial(yamlNode["material"].as<int>()));
		//Set cross section:
		requiredElems["crossSection"] = (structure->fetchCrossSection(yamlNode["geoID"].as<int>()));
		//Set eccentricites:
		if (yamlNode["eccentricities"]) {
			//If the eccentricities are given on the form
			//eccentricities: [ID for ecc1, ID for ecc2]
			requiredElems["ecc1"] = (structure->fetchObject(yamlNode["eccentricities"][0].as<int>(), "ECCENT"));
			requiredElems["ecc2"] = (structure->fetchObject(yamlNode["eccentricities"][1].as<int>(), "ECCENT"));
		}
		else {
			requiredElems["ecc1"] = yamlNode["ecc1"] ? (structure->fetchObject(yamlNode["ecc1"].as<int>(), "ECCENT")) 
														: structure->fetchObject(0, "ECCENT");
			requiredElems["ecc2"] = yamlNode["ecc2"] ? (structure->fetchObject(yamlNode["ecc2"].as<int>(), "ECCENT")) 
														: structure->fetchObject(0, "ECCENT");
		}
		requiredElems["vecID"] = yamlNode["vecID"] ? structure->fetchObject(yamlNode["vecID"].as<int>(), "VECTOR")
														: structure->fetchObject(0, "VECTOR");
		
		//Instantiate FEBeam
		FEBeam *feBeam = new FEBeam(
			yamlNode["elemID"].as<int>(), 
			(FENode*)requiredElems["node1"], 
			(FENode*)requiredElems["node2"], 
			(FEIsoMaterial*)requiredElems["material"], 
			(GenericCrossSection*)requiredElems["crossSection"],
			(FEEccentricity*)requiredElems["ecc1"],
			(FEEccentricity*)requiredElems["ecc2"],
			(FEVector*)requiredElems["vecID"]);
		
		structure->addElement(feBeam);
	}
	catch (std::runtime_error &e) {
		std::cout << e.what() << std::endl;
		logErrorMsg(e);
	}
} 

void Parser::parseTrishell(YAML::Node& yamlNode, std::string type) {
	try {
		bool exists = structure->checkElementExistence(yamlNode["elemID"].as<int>(), type);
		if (exists) {
			throw std::runtime_error("Error: A " + type + " element with id " 
				+ yamlNode["elemID"].as<std::string>() + " already exists.");
		}
		else {
			//Initialize a FETrishell from the YAML::Node
			std::map<std::string, Identifiable*> requiredElems;

			//set nodes:
			if (yamlNode["nodes"].size() == 3) {
				//if the nodes are given on the form
				//nodes: [id for node1, id for node2, id for node3]
				requiredElems["node1"] = (structure->fetchNode(yamlNode["nodes"][0].as<int>()));
				requiredElems["node2"] = (structure->fetchNode(yamlNode["nodes"][1].as<int>()));
				requiredElems["node3"] = (structure->fetchNode(yamlNode["nodes"][2].as<int>()));
			}
			else if (yamlNode["node1"] && yamlNode["node2"] && yamlNode["node3"]) {
				//if the nodes are given on the form
				//node1: id for node1
				//node2: id for node2
				//node3: id for node 3
				requiredElems["node1"] = (structure->fetchNode(yamlNode["node1"].as<int>()));
				requiredElems["node2"] = (structure->fetchNode(yamlNode["node2"].as<int>()));
				requiredElems["node3"] = (structure->fetchNode(yamlNode["node3"].as<int>()));
			}
			requiredElems["coordSys"] = yamlNode["coordID"] ? (structure->fetchCoordSys(yamlNode["coordID"].as<int>()))
				: structure->fetchCoordSys(0);
			
			//Assign composite section or material:
			if ((yamlNode["material"].as<int>() == -1) && yamlNode["secID"]) {
				requiredElems["section"] = structure->fetchCompSection(yamlNode["secID"].as<int>());
				requiredElems["material"] = nullptr;
			}
			else if ((yamlNode["secID"].as<int>() == -1) && yamlNode["material"]) {
				requiredElems["material"] = structure->fetchMaterial(yamlNode["material"].as<int>());
				requiredElems["section"] = nullptr;
			}
			else {
				throw std::runtime_error("Trishell error: No material or section specified");
			}

			if (yamlNode["eccentricities"].size() == 3) {
				requiredElems["ecc1"] = (structure->fetchObject(yamlNode["eccentricities"][0].as<int>(), "ECCENT"));
				requiredElems["ecc2"] = (structure->fetchObject(yamlNode["eccentricities"][1].as<int>(), "ECCENT"));
				requiredElems["ecc3"] = (structure->fetchObject(yamlNode["eccentricities"][2].as<int>(), "ECCENT"));
			}
			else {
				requiredElems["ecc1"] = yamlNode["ecc1"] ? (structure->fetchObject(yamlNode["ecc1"].as<int>(), "ECCENT"))
					: structure->fetchObject(0, "ECCENT");
				requiredElems["ecc2"] = yamlNode["ecc2"] ? (structure->fetchObject(yamlNode["ecc2"].as<int>(), "ECCENT"))
					: structure->fetchObject(0, "ECCENT");
				requiredElems["ecc3"] = yamlNode["ecc3"] ? (structure->fetchObject(yamlNode["ecc3"].as<int>(), "ECCENT"))
					: structure->fetchObject(0, "ECCENT");
			}

			//Instantiate FETrishell
			FETrishell *feTrishell = new FETrishell(
				yamlNode["elemID"].as<int>(),
				(FECoordSys*)requiredElems["coordSys"],
				(FENode*)requiredElems["node1"],
				(FENode*)requiredElems["node2"],
				(FENode*)requiredElems["node3"],
				(FEIsoMaterial*)requiredElems["material"],
				(GenericCompSection*)requiredElems["section"],
				(FEEccentricity*)requiredElems["ecc1"],
				(FEEccentricity*)requiredElems["ecc2"],
				(FEEccentricity*)requiredElems["ecc3"]
			);
			structure->addElement(feTrishell);
		}
	}
	catch (std::runtime_error &e) {
		std::cout << e.what() << std::endl;
		logErrorMsg(e);
	}
}

void Parser::parseQuadshell(YAML::Node& yamlNode, std::string type) {
	try {
		bool exists = structure->checkElementExistence(yamlNode["elemID"].as<int>(), type);
		if (exists) {
			throw std::runtime_error("Error: A " + type + " element with id " 
				+ yamlNode["elemID"].as<std::string>() + " already exists.");
		}
		else {
			//Initialize a FETrishell from the YAML::Node
			std::map<std::string, Identifiable*> requiredElems;

			//set nodes:
			if (yamlNode["nodes"].size() == 4) {
				//if the nodes are given on the form
				//nodes: [id for node1, id for node2, ...]
				requiredElems["node1"] = (structure->fetchNode(yamlNode["nodes"][0].as<int>()));
				requiredElems["node2"] = (structure->fetchNode(yamlNode["nodes"][1].as<int>()));
				requiredElems["node3"] = (structure->fetchNode(yamlNode["nodes"][2].as<int>()));
				requiredElems["node4"] = (structure->fetchNode(yamlNode["nodes"][3].as<int>()));
			}
			else if (yamlNode["node1"] && yamlNode["node2"] && yamlNode["node3"] && yamlNode["node4"]) {
				//if the nodes are given on the form
				//node1: id for node1
				//node2: id for node2
				// ...
				requiredElems["node1"] = (structure->fetchNode(yamlNode["node1"].as<int>()));
				requiredElems["node2"] = (structure->fetchNode(yamlNode["node2"].as<int>()));
				requiredElems["node3"] = (structure->fetchNode(yamlNode["node3"].as<int>()));
				requiredElems["node4"] = (structure->fetchNode(yamlNode["node4"].as<int>()));
			}
			requiredElems["coordSys"] = yamlNode["coordID"] ? (structure->fetchCoordSys(yamlNode["coordID"].as<int>()))
				: structure->fetchCoordSys(0);
			requiredElems["material"] = structure->fetchMaterial(yamlNode["material"].as<int>());

			//FIXME: Is this correct for the geoID? Is it supposed to be a cross section?
			//***********
			/*requiredElems["crossSection"] = yamlNode["geoID"] ? (structure->fetchCrossSection(yamlNode["geoID"].as<int>()))
				: structure->fetchCrossSection(0);*/
			//***********

			if (yamlNode["eccentricities"].size() == 3) {
				requiredElems["ecc1"] = (structure->fetchObject(yamlNode["eccentricities"][0].as<int>(), "ECCENT"));
				requiredElems["ecc2"] = (structure->fetchObject(yamlNode["eccentricities"][1].as<int>(), "ECCENT"));
				requiredElems["ecc3"] = (structure->fetchObject(yamlNode["eccentricities"][2].as<int>(), "ECCENT"));
				requiredElems["ecc4"] = (structure->fetchObject(yamlNode["eccentricities"][3].as<int>(), "ECCENT"));
			}
			else {
				requiredElems["ecc1"] = yamlNode["ecc1"] ? (structure->fetchObject(yamlNode["ecc1"].as<int>(), "ECCENT"))
					: structure->fetchObject(0, "ECCENT");
				requiredElems["ecc2"] = yamlNode["ecc2"] ? (structure->fetchObject(yamlNode["ecc2"].as<int>(), "ECCENT"))
					: structure->fetchObject(0, "ECCENT");
				requiredElems["ecc3"] = yamlNode["ecc3"] ? (structure->fetchObject(yamlNode["ecc3"].as<int>(), "ECCENT"))
					: structure->fetchObject(0, "ECCENT");
				requiredElems["ecc4"] = yamlNode["ecc4"] ? (structure->fetchObject(yamlNode["ecc4"].as<int>(), "ECCENT"))
					: structure->fetchObject(0, "ECCENT");
			}

			//Instantiate FEQuadhell
			FEQuadshell *feQuadshell = new FEQuadshell(
				yamlNode["elemID"].as<int>(),
				(FECoordSys*)requiredElems["coordSys"],
				(FENode*)requiredElems["node1"],
				(FENode*)requiredElems["node2"],
				(FENode*)requiredElems["node3"],
				(FENode*)requiredElems["node4"],
				(FEIsoMaterial*)requiredElems["material"],
				(GenericCrossSection*)requiredElems["crossSection"],
				(FEEccentricity*)requiredElems["ecc1"],
				(FEEccentricity*)requiredElems["ecc2"],
				(FEEccentricity*)requiredElems["ecc3"],
				(FEEccentricity*)requiredElems["ecc4"]
			);
			structure->addElement(feQuadshell);
		}
	}
	catch (std::runtime_error &e) {
		std::cout << e.what() << std::endl;
		logErrorMsg(e);
	}
}

void Parser::ParseGenericFEMElement(YAML::Node& yamlNode) {
	/* This method is a classifier.
	 * Parses a generic FEM element, identified by the literal string FEMElement
	 */
	
	//Extract 'type' string and tranform it to upper case:
	std::string type = yamlNode["type"].as<std::string>();
	std::transform(type.begin(), type.end(), type.begin(), ::toupper);
	
	//Pass the YAML node on to the correct parser method:
	if (type == "beam" && yamlNode["nodes"].size() == 2) {
		parseBeam(yamlNode, type);
	}
	
	else if (type == "trishell") {
		parseTrishell(yamlNode, type);
	}
	else if (type == "quadshel") {
		parseQuadshell(yamlNode, type);
	}
	
}

void Parser::parseEccentricity(YAML::Node& yamlNode, std::string type) {
	try {
		bool exists = structure->checkElementExistence(yamlNode["eccID"].as<int>(), type);
		if (exists) {
			throw std::runtime_error("Error: A " + type + " element with id "
				+ yamlNode["eccID"].as<std::string>() + " already exists.");
		}
		else {
			//Instantiate FEEccentricity
			FEEccentricity *feEccentricity = new FEEccentricity(yamlNode);
			structure->addElement(feEccentricity);
		}
	}
	catch (std::runtime_error &e) {
		std::cout << e.what() << std::endl;
		logErrorMsg(e);
	}
}

void Parser::ParseIsoMaterial(YAML::Node& yamlNode, std::string type) {
	try {
		bool exists = structure->checkMaterialExistence(yamlNode["matID"].as<int>());
		if (exists) {
			throw std::runtime_error("Error: A " + type + " element with id " 
				+ yamlNode["matID"].as<std::string>() + " already exists.");
		}
		else {
			//Instantiate IsoMaterial
			FEIsoMaterial *feIsoMaterial = new FEIsoMaterial(yamlNode);
			structure->addMaterial(feIsoMaterial);
		}
	}
	catch (std::runtime_error &e) {
		std::cout << e.what() << std::endl;
		logErrorMsg(e);
	}
}

void Parser::ParsePipe(YAML::Node& yamlNode, std::string type) {
	try {
		bool exists = structure->checkCrossSectionExistence(yamlNode["geoID"].as<int>(), type);
		if (exists) {
			throw std::runtime_error("Error: A " + type + " element with id " 
				+ yamlNode["geoID"].as<std::string>() + " already exists.");
		}
		else {
			//Instantiate FEPipe
			FEPipe *fePipe = new FEPipe(yamlNode);
			structure->addCrossSection(fePipe);
		}
	}
	catch (std::runtime_error &e) {
		std::cout << e.what() << std::endl;
		logErrorMsg(e);
	}
}

void Parser::parseTsection(YAML::Node& yamlNode, std::string type) {
	try	{
		bool exists = structure->checkCrossSectionExistence(yamlNode["geoID"].as<int>(), type);
		if (exists) {
			throw std::runtime_error("Error: A " + type + " element with id "
				+ yamlNode["geoID"].as<std::string>() + " already exists.");
		}
		else {
			//Instantiate FETsection
			FETsection* feTsection = new FETsection(yamlNode);
			structure->addCrossSection(feTsection);
		}
	}
	catch (std::runtime_error &e) {
		std::cout << e.what() << std::endl;
		logErrorMsg(e);
	}
}

void Parser::parsePLThick(YAML::Node& yamlNode, std::string type) {
	try {
		bool exists = structure->checkCrossSectionExistence(yamlNode["geoID"].as<int>(), type);
		if (exists) {
			throw std::runtime_error("Error: A cross section object with id "
				+ yamlNode["geoID"].as<std::string>() + " already exists.");
		}
		else {
			PLThick* plThick = new PLThick(yamlNode);
			structure->addCrossSection(plThick);
		}
	}
	catch (const std::runtime_error &e) {
		std::cout << e.what() << std::endl;
		logErrorMsg(e);
	}
}

void Parser::parsePLComp(YAML::Node& yamlNode, std::string type) {
	try {
		bool exists = structure->checkCompSectionExistence(yamlNode["secID"].as<int>());
		if (exists) {
			throw std::runtime_error("Error: A section object with id "
				+ yamlNode["secID"].as<std::string>() + " already exists.");
		}
		else {
			std::vector<GenericMaterial*> matList;
			for (YAML::Node ply : yamlNode["plies"]) {
				matList.push_back(structure->fetchMaterial(ply["matID"].as<int>()));
			}
			PLComp* plComp = new PLComp(yamlNode, matList);
			structure->addCompSection(plComp);
		}
	}
	catch (const std::runtime_error &e) {
		std::cout << e.what() << std::endl;
		logErrorMsg(e);
	}
}

void Parser::parseNodeLoad(YAML::Node& yamlNode) {
	try {
		static int nodeLoadId = 1; //Autogenerated identifier

		//Initialize a FENodeLoad from the YAML::Node
		std::map<std::string, Identifiable*> depElements;

		//Set node in which the load is acting
		bool nodeExists = structure->checkNodeExistence(yamlNode["nodeID"].as<int>());
		if (nodeExists) {
			depElements["node"] = structure->fetchNode(yamlNode["nodeID"].as<int>());
		}
		else {
			throw std::runtime_error("NodeLoad error: A NODE with id "
				+ yamlNode["nodeID"].as<std::string>() + " does not exist in Structure.");
		}
		// Set eccentricity
		depElements["ecc"] = yamlNode["eccID"] ? structure->fetchObject(yamlNode["eccID"].as<int>(), "ECCENT")
			: structure->fetchObject(0, "ECCENT");
		
		//Instantiate FENodeLoad
		FENodeLoad *feNodeLoad = new FENodeLoad(
			nodeLoadId,
			yamlNode, 
			(FENode*) depElements["node"], 
			(FEEccentricity*) depElements["ecc"]);
		
		structure->addNodeLoad(feNodeLoad);
		nodeLoadId++;
	}
	catch (std::runtime_error &e){
		std::cout << e.what() << std::endl;
		logErrorMsg(e);
	}
}

void Parser::parseLoadComb(YAML::Node& yamlNode) {
	try {
		bool exists = structure->checkLoadCombExistence(yamlNode["loadCombID"].as<int>());
		if (exists) {
			throw std::runtime_error("LoadComb error: A LoadComb object with id "
				+ yamlNode["loadCombID"].as<std::string>() + " does not exist in Structure.");
		}
		else if (!(yamlNode["loadCombID"] && yamlNode["factors"].size() > 0)) {
				throw std::runtime_error("LoadComb error: Mandatory attributes missing");
			}
		else {
			int loadCombId = yamlNode["loadCombID"].as<int>();
			std::map<int, double> loadCaseId_to_factor; //map<loadCaseId, scaling factor>
			for (YAML::const_iterator it = yamlNode["factors"].begin(); it != yamlNode["factors"].end(); it++) {
				loadCaseId_to_factor[it->first.as<int>()] = it->second.as<double>();
			}
			
			//Instantiate FELoadComb
			FELoadComb *feLoadComb = new FELoadComb(
				loadCombId,
				loadCaseId_to_factor
			);

			structure->addLoadComb(feLoadComb);
		}
	}
	catch (std::runtime_error &e){
		std::cout << e.what() << std::endl;
		logErrorMsg(e);
	}
}

void Parser::parseDepenencyLevelNull() {
	for (int iterator = 0; iterator < structureNode.size(); ++iterator) {
		YAML::const_iterator it = structureNode[iterator].begin();
		std::string key = it->first.as<std::string>();
		
		if (key == "COORDSYS" || key == "NODTRANS" || key == "PCOORDSYS") {
			nextNode = structureNode[iterator][key];
			parseCoordSys(nextNode, key);
		}
		if (key == "ECCENT") {
			nextNode = structureNode[iterator][key];
			parseEccentricity(nextNode, key);
		}
		if (key == "ISOMATERIAL") {
			nextNode = structureNode[iterator][key];
			ParseIsoMaterial(nextNode, key);
		}
		if (key == "PIPE") {
			nextNode = structureNode[iterator][key];
			ParsePipe(nextNode, key);
		}
		if (key == "TSECTION") {
			nextNode = structureNode[iterator][key];
			parseTsection(nextNode, key);
		}
		if (key == "PLTHICK") {
			nextNode = structureNode[iterator][key];
			parsePLThick(nextNode, key);
		}
		if (key == "UNITVEC" || key == "ZVECTOR" || key == "YVECTOR") {
			nextNode = structureNode[iterator][key];
			parseVector(nextNode, key);
		}
	}
}

void Parser::parseDepenencyLevelOne() {
	for (int iterator = 0; iterator < structureNode.size(); ++iterator) {
		YAML::const_iterator it = structureNode[iterator].begin();
		std::string key = it->first.as<std::string>();

		if (key == "NODE") {
			nextNode = structureNode[iterator][key];
			parseNode(nextNode, key);
		}
		if (key == "PLCOMP") {
			nextNode = structureNode[iterator][key];
			parsePLComp(nextNode, key);
		}
		if (key == "LOADCOMB") {
			nextNode = structureNode[iterator][key];
			parseLoadComb(nextNode);
		}
	}
}

void Parser::parseDepenencyLevelTwo() {
	for (int iterator = 0; iterator < structureNode.size(); ++iterator) {
		YAML::const_iterator it = structureNode[iterator].begin();
		std::string key = it->first.as<std::string>();

		if (key == "BEAM") {
			nextNode = structureNode[iterator][key];
			parseBeam(nextNode, key);
		}
		if (key == "TRISHELL") {
			nextNode = structureNode[iterator][key];
			parseTrishell(nextNode, key);
		}
		if (key == "QUADSHEL") {
			nextNode = structureNode[iterator][key];
			parseQuadshell(nextNode, key);
		}
		if (key == "FEMELEMENT") {
			nextNode = structureNode[iterator][key];
			ParseGenericFEMElement(nextNode);
		}
		if (key == "NODELOAD") {
			nextNode = structureNode[iterator][key];
			parseNodeLoad(nextNode);
		}
	}
}

void Parser::parse() {
	parseDepenencyLevelNull();
	parseDepenencyLevelOne();
	parseDepenencyLevelTwo();
	
	//Print data contents in structure
	structure->printData();
	//Print used while debugging:
	std::cout << "\nSome numbers:" << std::endl;
	std::cout << "Size of coordSysList: " << structure->coordSysList.size() << std::endl;
	std::cout << "Size of materials list: " << structure->materialList.size() << std::endl;
	std::cout << "Size of cross sections list: " << structure->crossSectionList.size() << std::endl;
	std::cout << "Size of nodes list: " << structure->nodeList.size() << std::endl;
	std::cout << "Size of elements list: " << structure->elementList.size() << std::endl;
	std::cout << "Size of NodeLoad list: " << structure->nodeLoadList.size() << std::endl;
	std::cout << "Size of loadCombList: " << structure->loadCombList.size() << std::endl;
	std::cout << "Total number of objects: "
		<< structure-> coordSysList.size()
		+ structure->elementList.size() 
		+ structure->nodeList.size()
		+ structure->materialList.size() 
		+ structure->crossSectionList.size() 
		+ structure->nodeLoadList.size() 
		+ structure->loadCombList.size() 
	<< std::endl;
}