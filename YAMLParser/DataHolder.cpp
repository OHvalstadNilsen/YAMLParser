#include "pch.h"
#include "DataHolder.h"
#include <sstream>
#include <fstream>
#include <iostream>

const std::vector<std::string> comment_signs = { "'", "#", "*", "%", "!" }; //USFOS comment signs
DataHolder::DataHolder()
{
}

DataHolder::DataHolder(std::string filename) {
	readInput(filename);
}

void DataHolder::tokenizeString(std::string s) {
	// Splits the string on space (' ') and adds each token to the global vector tokens.
	std::stringstream s_stream(s);
	std::string token;

	while (getline(s_stream, token, ' ')) {
		if (token != "") {
			tokens.push_back(token);
		}
	}
}

void DataHolder::tokenizeString2D(std::string s) {
	std::stringstream s_stream(s);
	std::string token;
	std::vector<std::string> lineTokens;

	while (getline(s_stream, token, ' ')) {

		if (token != "") {
			lineTokens.push_back(token);
		}

	}

	if (lineTokens.size() > 0) {
		tokens2D.push_back(lineTokens);
	}
}

void DataHolder::readInput(std::string filename) {
	// Reads input file and prints its content.

	std::ifstream ifs(filename);
	if (ifs.is_open()) {
		std::string line = "";
		while (getline(ifs, line)) {

			// --- tokenizer method ---
			//tokenizeString(line);
			tokenizeString2D(line);

		}

		//Prints used for debugging:
		//printTokens();
		//printTokens2D();

	}
	else std::cout << "Error: Unable to open \'" << filename << "\'" << std::endl;
	ifs.close();
}

void DataHolder::printTokens() {
	std::cout << "Content of tokens: \n" << std::endl;
	for (int i = 0; i < tokens.size(); i++) {
		std::cout << '[' << tokens[i] << "]" << std::endl;
	}
}

void DataHolder::printTokens2D() {
	std::cout << "Content of tokens2D: \n" << std::endl;
	for (int i = 0; i < tokens2D.size(); i++) {
		std::cout << "Tokens2D index " << i << ":" << std::endl;
		for (int j = 0; j < tokens2D[i].size(); j++) {
			std::cout << '[' << tokens2D[i][j] << ']' << std::endl;

		}
	}
}


DataHolder::~DataHolder()
{
}
