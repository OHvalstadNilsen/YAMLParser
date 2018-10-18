#include "pch.h"
#include "yaml-cpp\yaml.h"
#include <iostream>
#include <fstream>
#include <string>

//using namespace std;

/*
---------- Variables ----------
*/
std::vector<std::string> tokens; //contains the tokens generated from the input file
std::vector<std::string> data_types = { "NODE" }; //contains all data types defined in the cfem language
std::vector<std::string> comment_signs = { "'", "#", "*", "%", "!" }; //from USFOS: Lines with these characters in the first column are interpreted as comments.
std::vector<std::vector<std::string>> tokens2D; //Two-dimensional vector containing significant tokens with their respective sub-tokens.

enum InputFlag { NONE, COMMENT, NODE }; //Flag used to denote the last read input type
InputFlag inputFlag = NONE;

enum InputFile { JOINTMODEL, TEST3, TEST3_SAMPLE, TESTLINES}; //Flag used for choosing input file used for testing

/*
---------- Helper functions ----------
*/

//determine whether an array contains a certain elemt.
bool contains(std::vector<std::string> vec, std::string el) {
	auto it = std::find(begin(vec), end(vec), el); //Fetch the iterator of element with value equal to el
	//If it fetches the last element, then el is not in vec:
	return it != end(vec);
}

void printTokens() {
	std::cout << "Content of tokens: \n" << std::endl;
	for (int i = 0; i < tokens.size(); i++) {
		std::cout << '[' << tokens[i] << "]" << std::endl;
	}
}

void printTokens2D() {
	std::cout << "Content of tokens2D: \n" << std::endl;
	for (int i = 0; i < tokens2D.size(); i++) {
		std::cout << "Tokens2D index " << i << ":" << std::endl;
		for (int j = 0; j < tokens2D[i].size(); j++) {
			std::cout << '[' << tokens2D[i][j] << ']' << std::endl;

		}
	}
}


void tokenizeString(std::string s) {
	// Splits the string on space (' ') and adds each token to the global vector tokens.
	std::stringstream s_stream(s);
	std::string token;

	while (getline(s_stream, token, ' ')) {
		if (token != "") {
			tokens.push_back(token);
		}
	}
}

void tokenizeString2D(std::string s) {
	std::stringstream s_stream(s);
	std::string token;
	std::vector<std::string> lineTokens;

	while (getline(s_stream, token, ' ')) {
		//FIXME: READ EMPTY LINES ("") AND WRITE THEM AS NEWLINES ("\N")?
		if (token != "") {
			lineTokens.push_back(token);
		}
	}

	if (lineTokens.size() > 0) {
		tokens2D.push_back(lineTokens); //Append the vector named data to the tokens2D vector
	}
}

//std::string writeNodalPoint(std::vector<std::string> v_t) {
//	// v_t is a vector of tokens from one line in the input file
//	YAML::Emitter emitter;
//	emitter << YAML::BeginSeq;
//	emitter << YAML::Flow << v_t;
//	emitter << YAML::EndSeq;
//	
//
//	return emitter.c_str();
//}

std::string writeNodalPoint (std::vector<std::string> v_t) {
	//FIXME: THIS CODE MUST BE MODIFIED TO MATCH THE DESIRED DATA STRUCTURE FOR NODE
	//Pri 1
	YAML::Emitter emitter;
	emitter << YAML::BeginMap << v_t << YAML::EndMap;
	return emitter.c_str();
}

void readInput(std::string filename) {
	// Reads input file and prints its content.

	std::ifstream ifs(filename);
	if (ifs.is_open()) {
		std::string line = "";
		while (getline(ifs, line)) {
			
			// --- tokenizer method ---
			//tokenizeString(line);
			tokenizeString2D(line);

			std::cout << "\n\n";

		}
		ifs.close();

		//Print used for debugging:
		//printTokens();
		printTokens2D();

	}
	else std::cout << "Error: Unable to open " << filename << std::endl;
}

void writeToYamlFile(std::string filename) {
	//TODO: IMPLEMENT ME!

	std::ofstream ofs(filename);
	if (!ofs.is_open()){
		std::cout << "Error: Unable to access " << filename << " for output writing" << std::endl;
	}
	else {

		/*
		For each token:	
			If the token is in comment_signs --> Print the successing tokens on the same line, separated
			by spaces (' ').
			If the token is in data_types --> Send the corresponding write subfunction.
		*/

		for (int i = 0; i < tokens2D.size(); i++) {
			// Build a comment string from the tokens (separated by space), then write the comment to file.
			if (contains(comment_signs, tokens2D[i].front())) {
				std::string comment; //FIXME: MOVE OUTSIDE OF IF STATEMENT. AS-IS, A NEW STRING IS CREATED FOR EACH i.
				if (tokens2D[i].front() != "#") {
					comment.append("# "); //Add the YAML comment indicator, as not all USFOS indicators are valid in the YAML syntax.
				}
				for (int j = 0; j < tokens2D[i].size(); j++) {
					comment.append(tokens2D[i][j]);
					comment.append(" ");
				}
				ofs << comment << std::endl;
			}
			else if (contains(data_types, tokens2D[i].front())) {
				//TODO: IMPLEMENT METHODS FOR HANDLING THE DIFFERENT DATA TYPES. THAT IS, NODE, TRISHELL, QUADSHELL, ...
				//Pri 1
				ofs << writeNodalPoint(tokens2D[i]);
			}
		}
		tokens2D.erase(begin(tokens2D)); //Erase the token after it has been written to the new file.
	}
	ofs.close();
}

void readYamlTestInput(std::string filename) {
	//THIS FUNCTION IS NOT PART OF THE FINAL PROGRAM!

	//Test function to verify that the yaml-cpp library is properly integrated.
	YAML::Node node;
	node = YAML::LoadFile(filename);
	std::string cloudName = "Cloud name not set";
	std::string cloudPassword = "Cloud password not set";

	if (node["cloud"]) {
		if (node["cloud"]["name"] && node["cloud"]["password"]) {

			cloudName = node["cloud"]["name"].as<std::string>();
			cloudPassword = node["cloud"]["password"].as<std::string>();

		}
	}

	std::cout << "Cloud name: " << cloudName << "\nPassword: " << cloudPassword;
}

//TODO: main() MUST BE A PARSE FUNCTION CALLING readInput AND writeToYamlFile IN A REASONABLE WAY
int main() {

	InputFile f = TEST3_SAMPLE;
	switch (f) {
		case(TEST3): readInput("test3.usf");
			break;
		case(TEST3_SAMPLE): readInput("test3_sample_20.usf");
			break;
		case(JOINTMODEL): 	readInput("Joint_model.usf");
			break;
		case(TESTLINES): 	readInput("testlines.txt");
			break;
	}

	writeToYamlFile("output.yaml");
	
	//readYamlTestInput("example.yml");
	/*
	YAML::Emitter out;
	out << "Hello World!";

	std::cout << "Here's the output YAML:\n" << out.c_str();  // prints "Hello, World!"
	*/

	return 0;

}
