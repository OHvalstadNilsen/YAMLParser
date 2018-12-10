#pragma once

#include <string>
#include <vector>
#include "yaml-cpp/yaml.h"

class DataHolder; //Forward declaration to pass a DataHolder object to the constructor.
class Writer
{
public:
	Writer(DataHolder data, std::string filename, int yamlStyleFlag);
	~Writer();

	void writeToYamlFile(std::string filename);

	enum YamlStyle { BLOCK, FLOW };

private:
	std::string parseElementData(std::vector<std::string> v_t, std::vector<std::string> templ);
};

