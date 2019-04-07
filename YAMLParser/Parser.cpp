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

void Parser::parseNode(YAML::Node& yamlNode, std::string type) {
	try {
		//Check if there already exists a node with this ID in the construction.
		bool exists = construction->checkExistence(yamlNode["id"].as<int>(), type);
		if (exists) {
			throw std::runtime_error("Error: A " + type + " element with id " + yamlNode["id"].as<std::string>() + " already exists.");
		}
		else {
			//Initialize a FEBeam from the YAML::Node
			FENode *feNode = new FENode(yamlNode);
			construction->addElement(feNode);
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
		//TODO: Check if the material and nodes exist in construction.

		bool exists = construction->checkExistence(yamlNode["elemID"].as<int>(), type);
		if (exists) {
			throw std::runtime_error("Error: A " + type + " element with id "
				+ yamlNode["elemID"].as<std::string>() + " already exists.");
		}
		else {
			//Initialize a FEBeam from the YAML::Node
			std::vector<Identifiable*> requiredElems;
			
			//Set nodes:
			if (yamlNode["nodes"].size() == 2) {
				//If the nodes are given on the form
				//nodes: [ID for node1, ID for node2]
				requiredElems.push_back(construction->fetchObject(yamlNode["nodes"][0].as<int>(), "NODE"));
				requiredElems.push_back(construction->fetchObject(yamlNode["nodes"][1].as<int>(), "NODE"));
			}
			else if (yamlNode["node1"] && yamlNode["node2"]) {
				//If the nodes are given on the form
				//node1: ID for node1
				//node2: ID for node2
				requiredElems.push_back(construction->fetchObject(yamlNode["node1"].as<int>(), "NODE"));
				requiredElems.push_back(construction->fetchObject(yamlNode["node2"].as<int>(), "NODE"));
			}
			
			//Set material:
			requiredElems.push_back(construction->fetchObject(yamlNode["material"].as<int>(), "ISOMATERIAL"));
			//Set cross section:
			requiredElems.push_back(construction->fetchObject(yamlNode["geoID"].as<int>(), "PIPE"));
			
			//TODO: Add fetch logic for geoID and eccentricities
			

			//FEBeam *feBeam = new FEBeam(yamlNode);
			FEBeam *feBeam = new FEBeam(yamlNode["elemID"].as<int>(), (FENode*)requiredElems[0], 
				(FENode*)requiredElems[1], (FEIsoMaterial*)requiredElems[2], (GenericCrossSection*)requiredElems[3]);
			
			construction->addElement(feBeam);
			//feBeam->printAttributes();
			feBeam->printAttributes2();
		}
	}
	catch (std::runtime_error &e) {
		std::cout << e.what() << std::endl;
		logErrorMsg(e);
	}
} 

void Parser::parseTrishell(YAML::Node& yamlNode, std::string type) {
	try {
		bool exists = construction->checkExistence(yamlNode["elemID"].as<int>(), type);
		if (exists) {
			throw std::runtime_error("Error: A " + type + " element with id " + yamlNode["elemID"].as<std::string>() + " already exists.");
		}
		else {
			//Initialize a FETrishell from the YAML::Node
			FETrishell *feTrishell = new FETrishell(yamlNode);
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
		bool exists = construction->checkExistence(yamlNode["elemID"].as<int>(), type);
		if (exists) {
			throw std::runtime_error("Error: A " + type + " element with id " + yamlNode["elemID"].as<std::string>() + " already exists.");
		}
		else {
			//Initialize a FETrishell from the YAML::Node
			FEQuadshell *feQuadshell = new FEQuadshell(yamlNode);
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
	
	//Extract 'type' string and tranform it to lower case:
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

void Parser::ParseIsoMaterial(YAML::Node& yamlNode, std::string type) {
	try {
		bool exists = construction->checkExistence(yamlNode["id"].as<int>(), type);
		if (exists) {
			throw std::runtime_error("Error: A " + type + " element with id " + yamlNode["id"].as<std::string>() + " already exists.");
		}
		else {
			//Initialize a IsoMaterial from the YAML::Node
			FEIsoMaterial *feIsoMaterial = new FEIsoMaterial(yamlNode);
			construction->addElement(feIsoMaterial);
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
		bool exists = construction->checkExistence(yamlNode["geoID"].as<int>(), type);
		if (exists) {
			throw std::runtime_error("Error: A " + type + " element with id " + yamlNode["geoID"].as<std::string>() + " already exists.");
		}
		else {
			FEPipe *fePipe = new FEPipe(yamlNode);
			construction->addElement(fePipe);
			fePipe->printAttributes();
		}
	}
	catch (std::runtime_error &e) {
		std::cout << e.what() << std::endl;
		logErrorMsg(e);
	}
}

void Parser::parse() {
	for (int iterator = 0; iterator < constructionNode.size(); ++iterator) {
		nextNode = constructionNode[iterator];
		std::string key;

		YAML::const_iterator it = nextNode.begin(); //Used to access the key using it.first. TODO: Better way to do this?
		key = it->first.as<std::string>();
		if (key == "NODE") {
			nextNode = constructionNode[iterator][key];
			parseNode(nextNode, key);
		}
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
		if (key == "ISOMATERIAL") {
			nextNode = constructionNode[iterator][key];
			ParseIsoMaterial(nextNode, key);
		}
		if (key == "PIPE") {
			nextNode = constructionNode[iterator][key];
			ParsePipe(nextNode, key);
		}
	}
	std::cout << "Size of elementList: " << construction->elementList.size() << std::endl;
}