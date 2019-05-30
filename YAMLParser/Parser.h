/** \brief This is the top-level parser class. 
*
* This class traverses the YAML representation (graph of YAML::Nodes) once per dependency level
* and calls calls the parse function (e.g. parseNode) corresponding to the FE type for each YAML::Node.
*/

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

	YAML::Node root;			///< YAML root node.
	YAML::Node structureNode;	///< FEA format structure node.
	YAML::Node nextNode;		///< Next node to parse.
	Structure* structure;		///< Ptr to Structure object to which the data types are added.

	//---------- Functions -----------
	/**Error logger. Writes error message to console and to log file*/
	void logErrorMsg(std::runtime_error e);

	/*The following functions are parse functions for the FEM 
	* data types supported by the parser.
	*/
	//----- Nodal data -----
	void parseCoordSys(YAML::Node & yamlNode, std::string type);	 ///< Instantiate a FECoordSys object from the YAML::Node
	void parseNode(YAML::Node& yamlNode, std::string type);			 ///< Instantiate a FENode object from the YAML::Node

	//----- Element data -----
	void parseVector(YAML::Node & yamlNode, std::string type);		///< Instantiate a FEVector object from the YAML::Node
	void parseBeam(YAML::Node& yamlNode, std::string type);			///< Instantiate a FEBeam object from the YAML::Node
	void parseTrishell(YAML::Node& yamlNode, std::string type);		///< Instantiate a FETrishell object from the YAML::Node
	void parseQuadshell(YAML::Node & yamlNode, std::string type);	///< Instantiate a FEQuadshell object from the YAML::Node
	void ParseGenericFEMElement(YAML::Node& yamlNode);				///< A classifier. Parses a generic FEM element, identified by the literal string FEMElement in the YAML::Node
	void parseEccentricity(YAML::Node & yamlNode, std::string type);///< Instantiate a FEEccentricity object from the YAML::Node
	
	//----- Material data -----
	void ParseIsoMaterial(YAML::Node & yamlNode, std::string type); ///< Instantiate a FEIsoMaterial object from the YAML::Node

	//----- Cross-sectional data -----
	void ParsePipe(YAML::Node & yamlNode, std::string type);		///< Instantiate a cross-sectional FEPipe object from the YAML::Node
	void parsePLThick(YAML::Node & yamlNode, std::string type);						///< Instantiate a PLThick object from the YAML::Node

	//----- Load data -----
	void parseNodeLoad(YAML::Node & yamlNode);						///< Instantiate a FENodeLoad object from the YAML::Node
	void parseLoadComb(YAML::Node & yamlNode);						///< Instantiate a FELoadComb object from the YAML::Node

	/*Execute the data type parsing methods in order
	* according to their level of dependency.
	*/
	/**Traverses the entire graph of YAML::Nodes and parses all FE types of dependency level null*/
	void parseDepenencyLevelNull();
	/**Traverses the entire graph of YAML::Nodes and parses all FE types of dependency level one*/
	void parseDepenencyLevelOne();
	/**Traverses the entire graph of YAML::Nodes and parses all FE types of dependency level two*/
	void parseDepenencyLevelTwo();

	/**parse() is the parser main method which iterates over the input YAML::Node list. 
	* This method checks the YAML::Node's element type and passes the 
	* node to the corresponding parse function for FEM types.
	*/
	void parse();
};

