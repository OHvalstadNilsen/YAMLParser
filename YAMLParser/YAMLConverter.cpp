//TODO: Delete this script. This main function is deprecated. New main function is defined in YAMLParser.cpp.

#include "pch.h"
#include "yaml-cpp\yaml.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "DataHolder.h"
#include "Writer.h"
/*
int main() {
	
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
	
	return 0;
}
*/