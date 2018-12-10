#pragma once
#include <vector>
#include <string>
class DataHolder
{
public:
	DataHolder();
	~DataHolder();
	DataHolder(std::string);
	
	//Define comment signs. This is, for now, hard-coded to be the comment signs in USFOS.
	std::vector<std::string> comment_signs;

	std::vector<std::string> tokens; //contains the tokens generated from the input file
	std::vector<std::vector<std::string>> tokens2D; //Two-dimensional vector containing lines from the input with their respective sub-tokens.
	
	void readInput(std::string filename);
	void printTokens2D();

private:
	void tokenizeString(std::string s);
	void tokenizeString2D(std::string s);
	void printTokens();
};

