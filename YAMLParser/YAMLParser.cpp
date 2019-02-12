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
	try {
		Parser *parser = new Parser(filename);
		parser->parse();
	}
	catch(std::runtime_error &e){
		std::cout << e.what() << std::endl;
	}
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
