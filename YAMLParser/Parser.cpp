#include "pch.h"
#include "Parser.h"
#include "yaml-cpp\yaml.h"
#include "FEAFormat.h"
#include <iostream>
#include "FENode.h" //For more classes, the fact that this include is needed is unfortunate.

FEAFormat feaformat;

Parser::Parser(std::string filename)
{
	YAML::Node inputFile = YAML::LoadFile(filename);
	FEAFormat *feaformat = new FEAFormat(); //TODO: Move to YAMLParser.cpp. This way, it is not defined a humongous number of times
}

Parser::~Parser()
{
}

void Parser::parseNode(YAML::Node node) {
	//This methods takes as input a FEAFormat NODE. Hence, node is a list of attribute maps.

	int id = node[0]["id"].as<int>();
	double x = node[1]["x"].as<double>();
	double y = node[2]["y"].as<double>();
	double z = node[3]["z"].as<double>();

	//TODO: Expand this to all omittable fields. Can we use a for loop?
	if (!node[4]["ix"].Type() == YAML::NodeType::Undefined) {
		int ix = node[4]["ix"].as<int>(); // bool on lhs is legal, but requires that the int value is 0 or 1.
		FENode *feNode = new FENode(id, x, y, z, ix);
		feNode->PrintNode();
	}
	else {
		FENode *feNode = new FENode(id, x, y, z);
		feNode->PrintNode();
	}

}

bool Parser::validateNode() {
	//TODO: Implement me!
	return true;
}
