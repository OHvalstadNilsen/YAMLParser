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
	void logErrorMsg(std::runtime_error e);

	/*The following functions are parse functions for the FEM 
	* element types supported by the parser.
	*/

	//Nodal data:
	void parseNode(YAML::Node& yamlNode);
	
	//Element data:
	void parseBeam(YAML::Node& yamlNode);
	void parseTrishell(YAML::Node& yamlNode);
	void ParseGenericFEMElement(YAML::Node& yamlNode);
	
	//Material data:
	void ParserIsoMaterial(YAML::Node & yamlNode);
	

	/* parse() is the parser main method which iterates over the input YAML::Node list. 
	* This method checks the YAML::Node's element type and passes the 
	* node to the corresponding parse function for FEM element types.
	*/
	void parse();
};

