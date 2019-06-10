/** \brief
*	Main part of emitter module. Responsible for 
*	writing the data on the YAML based input file 
*	format for FEA to file.
*/

#pragma once
#include <string>
#include <vector>
#include "yaml-cpp/yaml.h"

//Forward declaration to pass a DataHolder object to the constructor.
class DataHolder;
class Writer
{
public:
	Writer(DataHolder data, std::string filename, int yamlStyleFlag);
	~Writer();

	/**Writes the contents of tokens2D as YAML data to file.*/
	void writeToYamlFile(std::string filename);

	/**Enum identifying whether to write output in YAML block style or YAML flow style.*/
	enum YamlStyle { BLOCK, FLOW };

};

