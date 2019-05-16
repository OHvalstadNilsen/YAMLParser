#include "pch.h"
#include "Parser.h"
#include "yaml-cpp\yaml.h"
#include "FEAFormat.h"

#include <iostream>
#include <fstream>

FEAFormat feaformat;

Parser::Parser(std::string filename)
{
	this->root = YAML::LoadFile(filename);

	if (!root["CONSTRUCTION"]) {
		throw std::runtime_error("Parser error: Could not find \"CONSTRUCTION\" node.");
	}
	else {
		this->constructionNode = root["CONSTRUCTION"];
	}
	
	this->construction = new Construction();
	FEAFormat *feaformat = new FEAFormat();
}

Parser::~Parser()
{
}

//TODO: Can this be removed?
YAML::Node Parser::extractConstructionNode(YAML::Node rootNode) {
	if (!rootNode["CONSTRUCTION"]) {
		throw std::runtime_error("Parser error: Could not find \"CONSTRUCTION\" node.");
	}
	return rootNode["CONSTRUCTION"];
}

void Parser::logErrorMsg(std::runtime_error e) {
	std::ofstream ofs("ErrorLog.txt", std::fstream::app);
	ofs << e.what() << std::endl;
	ofs.close();
}

void Parser::parseCoordSys(YAML::Node& yamlNode, std::string type) {
	try {
		bool exists = construction->checkCoordSysExistence(yamlNode["rotID"].as<int>());
		if (exists) {
			throw std::runtime_error("Error: A coordinate system with id "
				+ yamlNode["id"].as<std::string>() + " already exists.");
		}
		else {
			//Initialize coordinate system from the YAML::Node
			FECoordSys *feCoordSys = new FECoordSys(yamlNode);
			construction->addCoordSys(feCoordSys);
			feCoordSys->printAttributes();
		}
	}
	catch(std::runtime_error &e){
		std::cout << e.what() << std::endl;
		logErrorMsg(e);
	}
}

void Parser::parseNode(YAML::Node& yamlNode, std::string type) {
	try {
		//Check if there already exists a node with this ID in the construction.
		bool exists = construction->checkNodeExistence(yamlNode["id"].as<int>());
		if (exists) {
			throw std::runtime_error("Error: A " + type + " element with id " 
				+ yamlNode["id"].as<std::string>() + " already exists.");
		}
		else {
			//Initialize a FEBeam from the YAML::Node
			FENode *feNode = new FENode(yamlNode);
			construction->addNode(feNode);
			feNode->printAttributes();
		}
	}
	catch(std::runtime_error &e){
		std::cout << e.what() << std::endl;
		logErrorMsg(e);
	}
}

void Parser::parseBeam(YAML::Node& yamlNode, std::string type) {
	try {
		bool exists = construction->checkElementExistence(yamlNode["elemID"].as<int>(), type);
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
			requiredElems["node1"] = (construction->fetchNode(yamlNode["nodes"][0].as<int>()));
			requiredElems["node2"] = (construction->fetchNode(yamlNode["nodes"][1].as<int>()));
		}
		else if (yamlNode["node1"] && yamlNode["node2"]) {
			//If the nodes are given on the form
			//node1: ID for node1
			//node2: ID for node2
			requiredElems["node1"] = (construction->fetchNode(yamlNode["node1"].as<int>()));
			requiredElems["node2"] = (construction->fetchNode(yamlNode["node2"].as<int>()));
		}
		
		//Set material:
		requiredElems["material"] = (construction->fetchMaterial(yamlNode["material"].as<int>()));
		//Set cross section:
		requiredElems["crossSection"] = (construction->fetchCrossSection(yamlNode["geoID"].as<int>()));
		//Set eccentricites:
		if (yamlNode["eccentricities"]) {
			//If the eccentricities are given on the form
			//eccentricities: [ID for ecc1, ID for ecc2]
			requiredElems["ecc1"] = (construction->fetchObject(yamlNode["eccentricities"][0].as<int>(), "ECCENT"));
			requiredElems["ecc2"] = (construction->fetchObject(yamlNode["eccentricities"][1].as<int>(), "ECCENT"));
		}
		else {
			requiredElems["ecc1"] = yamlNode["ecc1"] ? (construction->fetchObject(yamlNode["ecc1"].as<int>(), "ECCENT")) 
														: construction->fetchObject(-1, "ECCENT");
			requiredElems["ecc2"] = yamlNode["ecc2"] ? (construction->fetchObject(yamlNode["ecc2"].as<int>(), "ECCENT")) 
														: construction->fetchObject(-1, "ECCENT");
		}
		requiredElems["rotID"] = yamlNode["rotID"] ? construction->fetchCoordSys(yamlNode["rotID"].as<int>())
														: construction->fetchCoordSys(-1);
		
		FEBeam *feBeam = new FEBeam(
			yamlNode["elemID"].as<int>(), 
			(FENode*)requiredElems["node1"], 
			(FENode*)requiredElems["node2"], 
			(FEIsoMaterial*)requiredElems["material"], 
			(GenericCrossSection*)requiredElems["crossSection"],
			(FEEccentricity*)requiredElems["ecc1"],
			(FEEccentricity*)requiredElems["ecc2"],
			(FECoordSys*)requiredElems["rotID"]);
		
		construction->addElement(feBeam);
		feBeam->printAttributes();
	}
	catch (std::runtime_error &e) {
		std::cout << e.what() << std::endl;
		logErrorMsg(e);
	}
} 

void Parser::parseTrishell(YAML::Node& yamlNode, std::string type) {
	try {
		bool exists = construction->checkElementExistence(yamlNode["elemID"].as<int>(), type);
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
				requiredElems["node1"] = (construction->fetchNode(yamlNode["nodes"][0].as<int>()));
				requiredElems["node2"] = (construction->fetchNode(yamlNode["nodes"][1].as<int>()));
				requiredElems["node3"] = (construction->fetchNode(yamlNode["nodes"][2].as<int>()));
			}
			else if (yamlNode["node1"] && yamlNode["node2"] && yamlNode["node3"]) {
				//if the nodes are given on the form
				//node1: id for node1
				//node2: id for node2
				//node3: id for node 3
				requiredElems["node1"] = (construction->fetchNode(yamlNode["node1"].as<int>()));
				requiredElems["node2"] = (construction->fetchNode(yamlNode["node2"].as<int>()));
				requiredElems["node3"] = (construction->fetchNode(yamlNode["node3"].as<int>()));
			}
			requiredElems["coordSys"] = yamlNode["coordID"] ? (construction->fetchCoordSys(yamlNode["coordID"].as<int>()))
				: construction->fetchCoordSys(-1);

			requiredElems["material"] = construction->fetchMaterial(yamlNode["material"].as<int>());
			
			requiredElems["crossSection"] = yamlNode["secID"] ? (construction->fetchCrossSection(yamlNode["secID"].as<int>()))
				: construction->fetchCrossSection(-1);

			if (yamlNode["eccentricities"].size() == 3) {
				requiredElems["ecc1"] = (construction->fetchObject(yamlNode["eccentricities"][0].as<int>(), "ECCENT"));
				requiredElems["ecc2"] = (construction->fetchObject(yamlNode["eccentricities"][1].as<int>(), "ECCENT"));
				requiredElems["ecc3"] = (construction->fetchObject(yamlNode["eccentricities"][2].as<int>(), "ECCENT"));
			}
			else {
				requiredElems["ecc1"] = yamlNode["ecc1"] ? (construction->fetchObject(yamlNode["ecc1"].as<int>(), "ECCENT"))
					: construction->fetchObject(-1, "ECCENT");
				requiredElems["ecc2"] = yamlNode["ecc2"] ? (construction->fetchObject(yamlNode["ecc2"].as<int>(), "ECCENT"))
					: construction->fetchObject(-1, "ECCENT");
				requiredElems["ecc3"] = yamlNode["ecc3"] ? (construction->fetchObject(yamlNode["ecc3"].as<int>(), "ECCENT"))
					: construction->fetchObject(-1, "ECCENT");
			}

			FETrishell *feTrishell = new FETrishell(
				yamlNode["elemID"].as<int>(),
				(FECoordSys*)requiredElems["coordSys"],
				(FENode*)requiredElems["node1"],
				(FENode*)requiredElems["node2"],
				(FENode*)requiredElems["node3"],
				(FEIsoMaterial*)requiredElems["material"],
				(GenericCrossSection*)requiredElems["crossSection"],
				(FEEccentricity*)requiredElems["ecc1"],
				(FEEccentricity*)requiredElems["ecc2"],
				(FEEccentricity*)requiredElems["ecc3"]
			);

			construction->addElement(feTrishell);
			feTrishell->printAttributes();
		}
	}
	catch (std::runtime_error &e) {
		std::cout << e.what() << std::endl;
		logErrorMsg(e);
	}
}

void Parser::parseQuadshell(YAML::Node& yamlNode, std::string type) {
	try {
		bool exists = construction->checkElementExistence(yamlNode["elemID"].as<int>(), type);
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
				requiredElems["node1"] = (construction->fetchNode(yamlNode["nodes"][0].as<int>()));
				requiredElems["node2"] = (construction->fetchNode(yamlNode["nodes"][1].as<int>()));
				requiredElems["node3"] = (construction->fetchNode(yamlNode["nodes"][2].as<int>()));
				requiredElems["node4"] = (construction->fetchNode(yamlNode["nodes"][3].as<int>()));
			}
			else if (yamlNode["node1"] && yamlNode["node2"] && yamlNode["node3"] && yamlNode["node4"]) {
				//if the nodes are given on the form
				//node1: id for node1
				//node2: id for node2
				// ...
				requiredElems["node1"] = (construction->fetchNode(yamlNode["node1"].as<int>()));
				requiredElems["node2"] = (construction->fetchNode(yamlNode["node2"].as<int>()));
				requiredElems["node3"] = (construction->fetchNode(yamlNode["node3"].as<int>()));
				requiredElems["node4"] = (construction->fetchNode(yamlNode["node4"].as<int>()));
			}
			requiredElems["coordSys"] = yamlNode["coordID"] ? (construction->fetchCoordSys(yamlNode["coordID"].as<int>()))
				: construction->fetchCoordSys(-1);
			requiredElems["material"] = construction->fetchMaterial(yamlNode["material"].as<int>());

			//FIXME: Is this correct for the geoID? Is it supposed to be a cross section?
			//***********
			/*requiredElems["crossSection"] = yamlNode["geoID"] ? (construction->fetchCrossSection(yamlNode["geoID"].as<int>()))
				: construction->fetchCrossSection(-1);*/
			//***********

			if (yamlNode["eccentricities"].size() == 3) {
				requiredElems["ecc1"] = (construction->fetchObject(yamlNode["eccentricities"][0].as<int>(), "ECCENT"));
				requiredElems["ecc2"] = (construction->fetchObject(yamlNode["eccentricities"][1].as<int>(), "ECCENT"));
				requiredElems["ecc3"] = (construction->fetchObject(yamlNode["eccentricities"][2].as<int>(), "ECCENT"));
				requiredElems["ecc4"] = (construction->fetchObject(yamlNode["eccentricities"][3].as<int>(), "ECCENT"));
			}
			else {
				requiredElems["ecc1"] = yamlNode["ecc1"] ? (construction->fetchObject(yamlNode["ecc1"].as<int>(), "ECCENT"))
					: construction->fetchObject(-1, "ECCENT");
				requiredElems["ecc2"] = yamlNode["ecc2"] ? (construction->fetchObject(yamlNode["ecc2"].as<int>(), "ECCENT"))
					: construction->fetchObject(-1, "ECCENT");
				requiredElems["ecc3"] = yamlNode["ecc3"] ? (construction->fetchObject(yamlNode["ecc3"].as<int>(), "ECCENT"))
					: construction->fetchObject(-1, "ECCENT");
				requiredElems["ecc4"] = yamlNode["ecc4"] ? (construction->fetchObject(yamlNode["ecc4"].as<int>(), "ECCENT"))
					: construction->fetchObject(-1, "ECCENT");
			}

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

			construction->addElement(feQuadshell);
			feQuadshell->printAttributes();
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
		bool exists = construction->checkElementExistence(yamlNode["eccID"].as<int>(), type);
		if (exists) {
			throw std::runtime_error("Error: A " + type + " element with id "
				+ yamlNode["eccID"].as<std::string>() + " already exists.");
		}
		else {
			//Initialize an Eccentricity object from the YAML::Node
			FEEccentricity *feEccentricity = new FEEccentricity(yamlNode);
			construction->addElement(feEccentricity);
			feEccentricity->printAttributes();
		}
	}
	catch (std::runtime_error &e) {
		std::cout << e.what() << std::endl;
		logErrorMsg(e);
	}
}

void Parser::ParseIsoMaterial(YAML::Node& yamlNode, std::string type) {
	try {
		bool exists = construction->checkMaterialExistence(yamlNode["id"].as<int>());
		if (exists) {
			throw std::runtime_error("Error: A " + type + " element with id " 
				+ yamlNode["id"].as<std::string>() + " already exists.");
		}
		else {
			//Initialize a IsoMaterial from the YAML::Node
			FEIsoMaterial *feIsoMaterial = new FEIsoMaterial(yamlNode);
			construction->addMaterial(feIsoMaterial);
			feIsoMaterial->printAttributes();
		}
	}
	catch (std::runtime_error &e) {
		std::cout << e.what() << std::endl;
		logErrorMsg(e);
	}
}

void Parser::ParsePipe(YAML::Node& yamlNode, std::string type) {
	try {
		bool exists = construction->checkCrossSectionExistence(yamlNode["geoID"].as<int>(), type);
		if (exists) {
			throw std::runtime_error("Error: A " + type + " element with id " 
				+ yamlNode["geoID"].as<std::string>() + " already exists.");
		}
		else {
			FEPipe *fePipe = new FEPipe(yamlNode);
			construction->addCrossSection(fePipe);
			fePipe->printAttributes();
		}
	}
	catch (std::runtime_error &e) {
		std::cout << e.what() << std::endl;
		logErrorMsg(e);
	}
}

void Parser::parsePLThick(YAML::Node& yamlNode) {
	try {
		//TODO:
	}
	catch (const std::runtime_error &e) {
		std::cout << e.what() << std::endl;
		logErrorMsg(e);
	}
}

void Parser::parseDepenencyLevelNull() {
	for (int iterator = 0; iterator < constructionNode.size(); ++iterator) {
		YAML::const_iterator it = constructionNode[iterator].begin();
		std::string key = it->first.as<std::string>();
		
		if (key == "COORDSYS" || key == "NODTRANS" || key == "PCOORDSYS") {
			nextNode = constructionNode[iterator][key];
			parseCoordSys(nextNode, key);
		}
		if (key == "ECCENT") {
			nextNode = constructionNode[iterator][key];
			parseEccentricity(nextNode, key);
		}
		if (key == "ISOMATERIAL") {
			nextNode = constructionNode[iterator][key];
			ParseIsoMaterial(nextNode, key);
		}
		if (key == "PIPE") {
			nextNode = constructionNode[iterator][key];
			ParsePipe(nextNode, key);
		}
	}
}

void Parser::parseDepenencyLevelOne() {
	for (int iterator = 0; iterator < constructionNode.size(); ++iterator) {
		YAML::const_iterator it = constructionNode[iterator].begin();
		std::string key = it->first.as<std::string>();

		if (key == "NODE") {
			nextNode = constructionNode[iterator][key];
			parseNode(nextNode, key);
		}
	}
}

void Parser::parseDepenencyLevelTwo() {
	for (int iterator = 0; iterator < constructionNode.size(); ++iterator) {
		YAML::const_iterator it = constructionNode[iterator].begin();
		std::string key = it->first.as<std::string>();

		if (key == "BEAM") {
			nextNode = constructionNode[iterator][key];
			parseBeam(nextNode, key);
		}
		if (key == "TRISHELL") {
			nextNode = constructionNode[iterator][key];
			parseTrishell(nextNode, key);
		}
		if (key == "QUADSHEL") {
			nextNode = constructionNode[iterator][key];
			parseQuadshell(nextNode, key);
		}
		if (key == "FEMELEMENT") {
			nextNode = constructionNode[iterator][key];
			ParseGenericFEMElement(nextNode);
		}
	}
}

void Parser::parse() {
	parseDepenencyLevelNull();
	parseDepenencyLevelOne();
	parseDepenencyLevelTwo();
	
	//Print used while debugging:
	std::cout << "\nSome numbers:" << std::endl;
	std::cout << "Size of materials list: " << construction->materialList.size() << std::endl;
	std::cout << "Size of cross sections list: " << construction->crossSectionList.size() << std::endl;
	std::cout << "Size of nodes list: " << construction->nodeList.size() << std::endl;
	std::cout << "Size of elements list: " << construction->elementList.size() << std::endl;
	std::cout << "Total number of objects: "
		<< construction->elementList.size() + construction->nodeList.size()
		+ construction->materialList.size() + construction->crossSectionList.size() << std::endl;
}