#include "pch.h"
#include "Parser.h"
#include "yaml-cpp\yaml.h"
#include "FEAFormat.h"
#include "FETypes.h"

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
		this->construction = root["CONSTRUCTION"];
	}

	FEAFormat *feaformat = new FEAFormat(); //TODO: Move to YAMLParser.cpp. This way, it is not defined a humongous number of times
}

Parser::~Parser()
{
}

//TODO: Can this be removed?
YAML::Node Parser::extractConstructionNode(YAML::Node rootNode) {
	if (!rootNode["CONSTRUCTION"]) {
		throw std::runtime_error("Parser error: Could not find \"CONSTRUCTION\" node.");
	}
	return rootNode["CONTRUCTION"];
}

void Parser::logErrorMsg(std::runtime_error e) {
	std::ofstream ofs("ErrorLog.txt", std::fstream::app);
	ofs << e.what() << std::endl;
	ofs.close();
}

void Parser::parseNode(YAML::Node& yamlNode) {
	try {
		//Initialize a FENode from the YAML::Node
		FENode *feNode = new FENode(yamlNode);
		feNode->printAttributes();
	}
	catch(std::runtime_error &e){
		std::cout << e.what() << std::endl;
		logErrorMsg(e);
	}
}

void Parser::parseBeam(YAML::Node& yamlNode) {
	try {
		//Initialize a FEBeam from the YAML::Node
		FEBeam *feBeam = new FEBeam(yamlNode);
		feBeam->printAttributes();
	}
	catch (std::runtime_error &e) {
		std::cout << e.what() << std::endl;
		logErrorMsg(e);
	}
}

void Parser::parseTrishell(YAML::Node& yamlNode) {
	try {
		//Initialize a FETrishell from the YAML::Node
		FETrishell *feTrishell = new FETrishell(yamlNode);
		feTrishell->printAttributes();
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
	std::transform(type.begin(), type.end(), type.begin(), ::tolower);
	
	//Pass the YAML node on to the correct parser method:
	if (type == "beam" && yamlNode["nodes"].size() == 2) {
		parseBeam(yamlNode);
	}
	
	else if (type == "trishell" && yamlNode["nodes"].size() == 3) {
		parseTrishell(yamlNode);
	}
	
}

void Parser::ParserIsoMaterial(YAML::Node& yamlNode) {
	try {
		//Initialize a IsoMaterial from the YAML::Node
		FEIsoMaterial *feIsoMaterial = new FEIsoMaterial(yamlNode);
		feIsoMaterial->printAttributes();
	}
	catch (std::runtime_error &e) {
		std::cout << e.what() << std::endl;
		logErrorMsg(e);
	}
}

void Parser::parse() {
	for (int iterator = 0; iterator < construction.size(); ++iterator) {
		nextNode = construction[iterator];
		std::string key;

		YAML::const_iterator it = nextNode.begin(); //Used to access the key using it.first. TODO: Better way to do this?
		key = it->first.as<std::string>();
		if (key == "NODE") {
			nextNode = construction[iterator][key];
			parseNode(nextNode);
		}
		if (key == "BEAM") {
			nextNode = construction[iterator][key];
			parseBeam(nextNode);
		}
		if (key == "TRISHELL") {
			nextNode = construction[iterator][key];
			parseTrishell(nextNode);
		}
		if (key == "FEMELEMENT") {
			nextNode = construction[iterator][key];
			ParseGenericFEMElement(nextNode);
		}
		if (key == "ISOMATERIAL") {
			nextNode = construction[iterator][key];
			ParserIsoMaterial(nextNode);
		}
	}
}