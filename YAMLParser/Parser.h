#pragma once
#include <string>
#include "yaml-cpp/yaml.h"
#include "Structure.h"
#include "FETypes.h"

class Parser
{
public:
	Parser(std::string filename);
	~Parser();

	YAML::Node root;			//YAML root node.
	YAML::Node structureNode;	//FEA format structure node.
	YAML::Node nextNode;		//Next node to parse.
	Structure* structure;		//Structure to which the data types	
								//are added.

	//Error logger
	void logErrorMsg(std::runtime_error e);

	/*The following functions are parse functions for the FEM 
	* data types supported by the parser.
	*/
	//Nodal data:
	void parseCoordSys(YAML::Node & yamlNode, std::string type);
	void parseNode(YAML::Node& yamlNode, std::string type);
	
	//Element data:
	void parseBeam(YAML::Node& yamlNode, std::string type);
	void parseTrishell(YAML::Node& yamlNode, std::string type);
	void parseQuadshell(YAML::Node & yamlNode, std::string type);
	void ParseGenericFEMElement(YAML::Node& yamlNode);
	void parseEccentricity(YAML::Node & yamlNode, std::string type);
	
	//Material data:
	void ParseIsoMaterial(YAML::Node & yamlNode, std::string type);

	//Cross-sectional data:
	void ParsePipe(YAML::Node & yamlNode, std::string type);
	void parsePLThick(YAML::Node & yamlNode);

	//Load data
	void parseNodeLoad(YAML::Node & yamlNode);

	/*Execute the data type parsing methods in order
	* according to their level of dependency.
	*/
	void parseDepenencyLevelNull();
	void parseDepenencyLevelOne();
	void parseDepenencyLevelTwo();

	/* parse() is the parser main method which iterates over the input YAML::Node list. 
	* This method checks the YAML::Node's element type and passes the 
	* node to the corresponding parse function for FEM element types.
	*/
	void parse();
};

