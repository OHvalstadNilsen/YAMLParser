#pragma once
#include <string>
#include "yaml-cpp/yaml.h" //Is this correct/wise?

class Parser
{
public:
	Parser(std::string filename);
	~Parser();

	void parseNode(YAML::Node node);
	bool validateNode();
};

