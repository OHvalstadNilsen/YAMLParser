#pragma once
#include <string>
#include "yaml-cpp/yaml.h"
#include "Construction.h"
#include "FETypes.h"

class Parser
{
public:
	Parser(std::string filename);
	~Parser();

	YAML::Node root;
	YAML::Node constructionNode;
	YAML::Node nextNode;
	Construction* construction;

	YAML::Node extractConstructionNode(YAML::Node rootNode);
	void logErrorMsg(std::runtime_error e);

	/*The following functions are parse functions for the FEM 
	* element types supported by the parser.
	*/

	//Nodal data:
	void parseNode(YAML::Node& yamlNode, std::string type);
	
	//Element data:
	void parseBeam(YAML::Node& yamlNode, std::string type);
	void parseTrishell(YAML::Node& yamlNode, std::string type);
	void parseQuadshell(YAML::Node & yamlNode, std::string type);
	void ParseGenericFEMElement(YAML::Node& yamlNode);
	
	//Material data:
	void ParseIsoMaterial(YAML::Node & yamlNode, std::string type);

	//Cross-sectional data:
	void ParsePipe(YAML::Node & yamlNode, std::string type);

	void parseDepenencyLevelNull();

	void parseDepenencyLevelOne();

	void parseDepenencyLevelTwo();
	

	/* parse() is the parser main method which iterates over the input YAML::Node list. 
	* This method checks the YAML::Node's element type and passes the 
	* node to the corresponding parse function for FEM element types.
	*/
	void parse();
};

