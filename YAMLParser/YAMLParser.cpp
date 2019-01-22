#include "pch.h"
#include "yaml-cpp\yaml.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "DataHolder.h"
#include "Writer.h"
#include "Parser.h"

void runParser() {
	std::string filename;
	std::cout << "Enter file path: ";
	std::cin >> filename;
	Parser *parser = new Parser(filename);
	
	YAML::Node root = YAML::LoadFile(filename);
	YAML::Node construction = root["CONSTRUCTION"];
	YAML::Node node;

	for (int iterator = 0; iterator < construction.size(); ++iterator) {
		node = construction[iterator];
		std::string key;

		YAML::const_iterator it = node.begin(); //Used to access the key using it.first. //TODO: Better way to do this?
		key = it->first.as<std::string>();
		if (key == "NODE") {
			node = construction[iterator][key];
			parser->parseNode(node);
		}
	}

	//------------------------------------
	/*
	if (!node.IsDefined()) {
		std::cout << "node is undefined" << std::endl;
	}
	else if (node.IsMap()) {
		std::cout << "node is a map" << std::endl;
		for (auto it = node.begin(); it != node.end(); ++it) {
			YAML::Node key = it->first;
			YAML::Node value = it->second;
			if (key.Type() == YAML::NodeType::Scalar) {
				std::cout << "Key is a scalar" << std::endl;
				std::cout << "Key: " << key.as<std::string>() << std::endl;
			}
			if (value.Type() == YAML::NodeType::Sequence) {
				std::cout << "Value is a seq" << std::endl;
			}
		}
	}
	else if (node.IsNull()) {
		std::cout << "node is Null";
	}
	else if (node.IsScalar()) {
		std::cout << "node is a scalar";
	}
	else if (node.IsSequence()) {
		std::cout << "node is a sequence" << std::endl;
		YAML::Node childnode = node[0];
		if (childnode.IsMap()) {
			 std::cout << "node[0] is a map" << std::endl;
			 std::cout << node[1]["x"].as<std::string>() << std::endl;
			}
	}
	// For testing purposes
	std::string id = node[0]["id"].as<std::string>();
	double x = node[1]["x"].as<double>();
	double y = node[2]["y"].as<double>();
	double z = node[3]["z"].as<double>();
	
	std::cout << "Parameters: " << id <<", "<< x << ", " << y << ", " << z << std::endl;
	*/
}

void runConverter() {
	std::string inputFileName;
	std::string outputFileName;
	int style;

	std::cout << "Enter name of input file: ";
	std::cin >> inputFileName;
	std::cin.clear();
	std::cout << "Choose Yaml format style (block = 0 | flow = 1): ";
	std::cin >> style;
	std::cout << "Enter name of output file: ";
	std::cin >> outputFileName;

	DataHolder *dh = new DataHolder();
	std::cout << "DataHolder instantiated." << std::endl;
	dh->readInput(inputFileName);
	std::cout << "DataHolder: Data read from '" << inputFileName << "'" << std::endl;
	Writer *writer = new Writer(*dh, outputFileName, style);
	std::cout << "Writer instantiated." << std::endl;
	writer->writeToYamlFile(outputFileName);
}

int main() {
	int runParam;
	std::cout << "Please choose which part of the program to run (Parser = 0 | Converter = 1): ";
	std::cin >> runParam;

	switch (runParam) {
	case 0:
		std::cout << "Parser chosen." << std::endl;
		runParser();
		break;
	case 1:
		std::cout << "Converter chosen." << std::endl;
		runConverter();
		break;
	}

	return 0;
}
