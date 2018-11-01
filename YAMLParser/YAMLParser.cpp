#include "pch.h"
#include "yaml-cpp\yaml.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>

/*
---------- Constants ----------
*/
std::vector<std::string> data_types = { "NODE", "BEAM", "TRISHELL", "PIPE", "IHPROFILE", "PLTHICK", "UNITVEC", "ECCENT", "MISOIEP", "NODELOAD", "GRAVITY", "NODTRANS"}; //contains all data types defined in the cfem language
std::vector<std::string> comment_signs = { "'", "#", "*", "%", "!" }; //from USFOS: Lines with these characters in the first column are interpreted as comments.

enum InputFlag { NONE, COMMENT, NODE }; //Flag used to denote the last read input type. FIXME: NOT IN USE?
enum YamlStyle { BLOCK, FLOW };

YamlStyle yamlStyle; //flag denoting wheteher to print the yaml file in block or flow style

//Format definitions (templates)
std::vector<std::string> node_template = {"id", "x", "y", "z", "ix", "iy", "iz", "irx", "iry", "irz", "rotID" };
std::vector<std::string> nodtrans_template = { "rotID", "Xx", "Yy", "Zz", "Yx", "Yy", "Yz", "Zx", "Zy", "Zz" };
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

void printMap(std::map<std::string, std::string> m) {
	std::map<std::string, std::string>::const_iterator it;
	for (it = m.begin(); it != m.end(); it++) {
		std::cout << it->first << " => " << it->second << std::endl;
	}
	std::cout << std::endl;
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

		if (token != "") {
			lineTokens.push_back(token);
		}

	}

	if (lineTokens.size() > 0) {
		tokens2D.push_back(lineTokens);
	}
}


std::string parseElementData(std::vector<std::string> v_t, std::vector<std::string> templ) {
	//Writes the input nodal data on the YAML block style.
	YAML::Emitter emitter;
	
	// Set emitter format according to the value of yamlStyle (given as user input)
	yamlStyle == BLOCK ? emitter.SetSeqFormat(YAML::Block) : emitter.SetSeqFormat(YAML::Flow);

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

std::string parseElementData_idInElementKey(std::vector<std::string> v_t, std::vector<std::string> templ) {
	/*
	Problem: Not all elements can be treated this way, as not all elements have a natural ID.
	*/
	
	YAML::Emitter emitter;

	// Set emitter format according to the value of yamlStyle (given as user input)
	yamlStyle == BLOCK ? emitter.SetSeqFormat(YAML::Block) : emitter.SetSeqFormat(YAML::Flow);

	emitter << YAML::BeginMap << YAML::Key << v_t[0] + "_" + v_t[1];
	emitter << YAML::Value << YAML::BeginSeq;
	for (int i = 1; i < v_t.size() - 1; i++) {
		emitter << YAML::BeginMap << YAML::Key << templ[i];
		emitter << YAML::Value << v_t[i + 1] << YAML::EndMap;
	}
	emitter << YAML::EndSeq;
	emitter << YAML::EndMap;

	return emitter.c_str();
}

std::string parseElementData_asDatatypeLists(std::vector<std::string> v_t, std::vector<std::string> templ) {
	/*
	Problem: Comments within lists are illegal in YAML.
	*/
	YAML::Emitter emitter;

	// Set emitter format according to the value of yamlStyle (given as user input)
	yamlStyle == BLOCK ? emitter.SetSeqFormat(YAML::Block) : emitter.SetSeqFormat(YAML::Flow);

	emitter << YAML::BeginSeq << YAML::BeginMap << YAML::Key << v_t[0] + "List";
	emitter << YAML::Value << YAML::BeginSeq;
	for (int i = 0; i < v_t.size() - 1; i++) {
		emitter << YAML::BeginMap << YAML::Key << templ[i];
		emitter << YAML::Value << v_t[i + 1] << YAML::EndMap;
	}
	emitter << YAML::EndSeq;
	emitter << YAML::EndMap;
	emitter << YAML::EndSeq;

	return emitter.c_str();
}

std::string writeDataFlowStyleFromMap(std::vector<std::string> v_t, std::vector<std::string> templ) {
	// NOT IN USE!
	//A MAP IS SORTED ALPHABETICALLY BY KEY. WE WANT TO PRESERVE THE ORDER OF INSERTION, SO THIS MAY NOT BE A GOOD METHOD.
	
	std::map<std::string, std::string> m;
	for (int i = 1; i < v_t.size(); i++) {
		m[templ[i - 1]] = v_t[i]; //problem: the map is sorted alphabetically by key.
	}

	YAML::Emitter emitter;	
	emitter << YAML::BeginMap << YAML::Key << v_t[0];
	emitter << YAML::Value << YAML::Flow << m << YAML::EndMap;

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

		//Prints used for debugging:
		//printTokens();
		//printTokens2D();

	}
	else std::cout << "Error: Unable to open \'" << filename << "\'" << std::endl;
	ifs.close();
	
}

void writeToYamlFile(std::string filename) {
	//TODO: IMPLEMENT ME!

	std::ofstream ofs(filename);
	if (!ofs.is_open()){
		std::cout << "Error: Unable to access \'" << filename << "\' for output writing" << std::endl;
	}
	if (tokens2D.size() == 0) {
		std::cout << "No data to write to file." << std::endl;
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
				YAML::Emitter emitter;
				std::string comment; //FIXME: MOVE OUTSIDE OF IF STATEMENT. AS-IS, A NEW STRING IS CREATED FOR EACH i.
				
				//Starting at j = 1 means omitting the comment sign (first element). YAML::comment provides the necessary comment sign.
				for (int j = 1; j < tokens2D[i].size(); j++) {
					comment.append(tokens2D[i][j]);
					comment.append(" ");
				}

				emitter << YAML::Comment(comment);
				ofs << emitter.c_str() << std::endl;
			}
			else if (contains(data_types, tokens2D[i].front())) {
				std::string data_type = tokens2D[i].front();

				//TODO: MAKE THIS MORE DYNAMIC AND AVOID AN IF-CLUSTER
				if (data_type == "NODE") {
					ofs << parseElementData_asDatatypeLists(tokens2D[i], node_template) << std::endl;
				}
				else if (data_type == "NODTRANS") {
					ofs << parseElementData(tokens2D[i], nodtrans_template) << std::endl;
				}
				else if (data_type == "BEAM") {
					ofs << parseElementData(tokens2D[i], beam_template) << std::endl;
				}
				else if (data_type == "TRISHELL") {
					ofs << parseElementData(tokens2D[i], trishell_template) << std::endl;
				}
				else if (data_type == "PIPE") {
					ofs << parseElementData(tokens2D[i], pipe_template) << std::endl;
				}
				else if (data_type == "IHPROFIL") {
					ofs << parseElementData(tokens2D[i], ihprofile_template) << std::endl;
				}
				else if (data_type == "PLTHICK") {
					ofs << parseElementData(tokens2D[i], plthick_template) << std::endl;
				}
				else if (data_type == "UNITVEC" || data_type == "YVECTOR" || data_type == "ZVECTOR") {
					ofs << parseElementData(tokens2D[i], cfemvector_template) << std::endl;
				}
				else if (data_type == "ECCENT") {
					ofs << parseElementData(tokens2D[i], eccent_template) << std::endl;
				}
				else if (data_type == "MISOIEP") {
					ofs << parseElementData(tokens2D[i], misoiep_template) << std::endl;
				}
				else if (data_type == "NODELOAD") {
					ofs << parseElementData(tokens2D[i], nodeload_template) << std::endl;
				}
				else if (data_type == "GRAVITY") {
					ofs << parseElementData(tokens2D[i], gravity_template) << std::endl;
				}
			}
		}
		tokens2D.erase(begin(tokens2D)); //Erase the token after it has been written to the new file.
		std::cout << "YAMLParser has written data to \'" << filename << "\'" << std::endl;
	}
	ofs.close();
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
	int style;

	std::cout << "Enter name of input file: ";
	std::cin >> userInput;
	std::cin.clear();
	std::cout << "Choose Yaml format style (block = 0 | flow = 1): ";
	std::cin >> style;
	
	switch (style) {
		case 0: 
			yamlStyle = BLOCK;
			std::cout << "Block style chosen" << std::endl;
			break;
		case 1:
			yamlStyle = FLOW;
			std::cout << "Flow style chosen" << std::endl;
			break;
	}

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
