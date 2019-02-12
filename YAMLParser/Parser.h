#pragma once
#include <string>
#include "yaml-cpp/yaml.h"

class Parser
{
public:
	Parser(std::string filename);
	~Parser();

	YAML::Node root;
	YAML::Node construction;
	YAML::Node nextNode;

	YAML::Node extractConstructionNode(YAML::Node rootNode);
	void parseNode(YAML::Node yamlNode);
	void parseBeam(YAML::Node yamlNode);
	void parseTrishell(YAML::Node yamlNode);
	void parse();
};

