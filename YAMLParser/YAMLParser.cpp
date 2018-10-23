#include "pch.h"
#include "yaml-cpp\yaml.h"
#include <iostream>
#include <fstream>
#include <string>

/*
---------- Constants ----------
*/
std::vector<std::string> data_types = { "NODE", "BEAM", "TRISHELL", "PIPE", "IHPROFILE", "PLTHICK", "UNITVEC", "ECCENT", "MISOIEP", "NODELOAD", "GRAVITY" }; //contains all data types defined in the cfem language
std::vector<std::string> comment_signs = { "'", "#", "*", "%", "!" }; //from USFOS: Lines with these characters in the first column are interpreted as comments.

enum InputFlag { NONE, COMMENT, NODE }; //Flag used to denote the last read input type. FIXME: NOT IN USE?

//Format definitions (templates)
std::vector<std::string> node_template = {"id", "x", "y", "z", "ix", "iy", "iz", "irx", "iry", "irz", "rotID"};
std::vector<std::string> beam_template = {"elemID", "node1", "node2", "material", "geoID", "vecID", "ecc1", "ecc2"};
std::vector<std::string> trishell_template = { "elemID", "node1", "node2", "node3", "material", "geoID", "vecID", "ecc1", "ecc2" };
std::vector<std::string> pipe_template = { "geoID", "d_outer", "thickness", "shearY", "shearZ"};
std::vector<std::string> ihprofile_template = { "geoID", "height", "T_web", "W_top", "T_top", "W_bot", "T_bot", "shearY", "shearZ" };
std::vector<std::string> plthick_template = { "geoID", "thickness" };
std::vector<std::string> cfemvector_template = { "vecID", "x", "y", "z" }; //template for UNITVEC, ZVECTOR and YVECTOR in CFEM.
std::vector<std::string> eccent_template = { "eccID", "eX", "eY", "eZ" };
std::vector<std::string> misoiep_template = { "matID", "E-module", "poisson", "yield", "density", "thermalExpansion" };
std::vector<std::string> nodeload_template = { "loadCaseID", "nodeID", "fx", "fy", "fz", "mx", "my", "mz", "ecc" };
std::vector<std::string> gravity_template = { "loadCaseID", "aX", "aY", "aZ" };

/*
---------- Variables ----------
*/
std::vector<std::string> tokens; //contains the tokens generated from the input file
std::vector<std::vector<std::string>> tokens2D; //Two-dimensional vector containing significant tokens with their respective sub-tokens.

InputFlag inputFlag = NONE;

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


std::string writeDataBlock(std::vector<std::string> v_t, std::vector<std::string> templ) {
	//Writes the input nodal data on the YAML block style.
	YAML::Emitter emitter;

	emitter << YAML::BeginMap << YAML::Key << v_t[0];
	emitter << YAML::Value << YAML::BeginSeq;
	for (int i = 0; i < v_t.size() - 1; i++) {
		emitter << YAML::BeginMap << YAML::Key << templ[i];
		emitter << YAML::Value << v_t[i + 1] << YAML::EndMap;
	}
	emitter << YAML::EndSeq;
	emitter << YAML::EndMap;

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

		}
		ifs.close();

		//Prints used for debugging:
		//printTokens();
		//printTokens2D();

	}
	else std::cout << "Error: Unable to open \'" << filename << "\'" << std::endl;
}

void writeToYamlFile(std::string filename) {
	//TODO: IMPLEMENT ME!

	std::ofstream ofs(filename);
	if (!ofs.is_open()){
		std::cout << "Error: Unable to access \'" << filename << "\' for output writing" << std::endl;
	}
	else {		
		/*
		For each token:	
			If the token is in comment_signs --> Print the successing tokens on the same line, separated
			by spaces (' ').
			If the token is in data_types --> Send the corresponding write subfunction.
		*/
		std::cout << "Writing data to \'" << filename << "\' ..." << std::endl;

		for (int i = 0; i < tokens2D.size(); i++) {
			// Build a comment string from the tokens (separated by space), then write the comment to file.
			if (contains(comment_signs, tokens2D[i].front())) {
				//FIXME: USE THE "COMMENT" METHOD IN THE EMITTER. THAT SHOULD BE MORE CONSISTENT WITH THE YAML SYNTAX.
				std::string comment; //FIXME: MOVE OUTSIDE OF IF STATEMENT. AS-IS, A NEW STRING IS CREATED FOR EACH i.
				if (tokens2D[i].front() != "#") {
					comment.append("# "); //Adds the YAML comment indicator, as not all USFOS indicators are valid in the YAML syntax.
				}
				for (int j = 0; j < tokens2D[i].size(); j++) {
					comment.append(tokens2D[i][j]);
					comment.append(" ");
				}
				ofs << comment << std::endl;
			}
			else if (contains(data_types, tokens2D[i].front())) {
				std::string data_type = tokens2D[i].front();

				//TODO: MAKE THIS MORE DYNAMIC AND AVOID AN IF-CLUSTER
				if (data_type == "NODE") {
					ofs << writeDataBlock(tokens2D[i], node_template) << std::endl;
				}
				else if (data_type == "BEAM") {
					ofs << writeDataBlock(tokens2D[i], beam_template) << std::endl;
				}
				else if (data_type == "TRISHELL") {
					ofs << writeDataBlock(tokens2D[i], trishell_template) << std::endl;
				}
				else if (data_type == "PIPE") {
					ofs << writeDataBlock(tokens2D[i], pipe_template) << std::endl;
				}
				else if (data_type == "IHPROFIL") {
					ofs << writeDataBlock(tokens2D[i], ihprofile_template) << std::endl;
				}
				else if (data_type == "PLTHICK") {
					ofs << writeDataBlock(tokens2D[i], plthick_template) << std::endl;
				}
				else if (data_type == "UNITVEC" || data_type == "YVECTOR" || data_type == "ZVECTOR") {
					ofs << writeDataBlock(tokens2D[i], cfemvector_template) << std::endl;
				}
				else if (data_type == "ECCENT") {
					ofs << writeDataBlock(tokens2D[i], eccent_template) << std::endl;
				}
				else if (data_type == "MISOIEP") {
					ofs << writeDataBlock(tokens2D[i], misoiep_template) << std::endl;
				}
				else if (data_type == "NODELOAD") {
					ofs << writeDataBlock(tokens2D[i], nodeload_template) << std::endl;
				}
				else if (data_type == "GRAVITY") {
					ofs << writeDataBlock(tokens2D[i], gravity_template) << std::endl;
				}
			}
		}
		tokens2D.erase(begin(tokens2D)); //Erase the token after it has been written to the new file.
	
	}
	ofs.close();
	std::cout << "YAMLParser has written data to \'" << filename << "\'" << std::endl;
}

void readYamlTestInput(std::string filename) {
	// NB! THIS FUNCTION IS NOT PART OF THE FINAL PROGRAM!

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

int main() {
	
	std::string userInput;
	
	std::cout << "Enter name of input file: ";
	std::cin >> userInput;
	
	readInput(userInput);

	writeToYamlFile("output.yaml");
	
	//readYamlTestInput("example.yml");
	/*
	YAML::Emitter out;
	out << "Hello World!";

	std::cout << "Here's the output YAML:\n" << out.c_str();  // prints "Hello, World!"
	*/

	return 0;

}
