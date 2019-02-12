#include "pch.h"
#include "Parser.h"
#include "yaml-cpp\yaml.h"
#include "FEAFormat.h"
#include <iostream>
#include "FETypes.h"

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

YAML::Node Parser::extractConstructionNode(YAML::Node rootNode) {
	if (!rootNode["CONSTRUCTION"]) {
		throw std::runtime_error("Parser error: Could not find \"CONSTRUCTION\" node.");
	}
	return rootNode["CONTRUCTION"];
}

void Parser::parseNode(YAML::Node yamlNode) {
	try {
		//Initialize a FENode from the YAML::Node
		FENode *feNode = new FENode(yamlNode);
		feNode->PrintNode();
	}
	catch(std::runtime_error &e){
		std::cout << e.what() << std::endl;
	}
}

void Parser::parseBeam(YAML::Node yamlNode) {
	try {
		//Initialize a FENode from the YAML::Node
		FEBeam *feBeam = new FEBeam(yamlNode);
		feBeam->PrintBeam();
	}
	catch (std::runtime_error &e) {
		std::cout << e.what() << std::endl;
	}
}

void Parser::parseTrishell(YAML::Node yamlNode) {
	try {
		//Initialize a FENode from the YAML::Node
		FETrishell *feTrishell = new FETrishell(yamlNode);
		feTrishell->PrintTrishell();
	}
	catch (std::runtime_error &e) {
		std::cout << e.what() << std::endl;
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
	}
}