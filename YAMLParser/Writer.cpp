#include "pch.h"
#include "Writer.h"
#include <iostream>
#include <fstream>
#include "FEAFormat.h"
#include "DataHolder.h"

Writer::YamlStyle YAML_STYLE;
DataHolder data; //Forward declaration
FEAFormat format;

Writer::Writer(DataHolder dh, std::string filename, int yamlStyleFlag) {
	/*
	Constructor setting the format to write to, indicates the YAML style to write in, and which data to write.
	*/
	switch (yamlStyleFlag) {
		case 0:
			YAML_STYLE = BLOCK;
			break;
		case 1:
			YAML_STYLE = FLOW;
	}
	data = dh;
	FEAFormat *format = new FEAFormat();
}

//Determine whether an array contains a certain elemt.
bool contains(std::vector<std::string> vec, std::string el) {
	/*
	Helper function determining wheter the vector vec contains the string element el.
	*/
	auto it = std::find(begin(vec), end(vec), el); //Fetch the iterator of element with value equal to el
	//If it fetches the last element, then el is not in vec:
	return it != end(vec);
}

void Writer::writeToYamlFile(std::string filename) {
	/*
	Writes output to the file defined by filename, according to parameters set in constructor.
	*/
	//If there is no data to write, break out of the loop
	if (data.tokens2D.size() == 0) {
		std::cout << data.tokens2D.size() << std::endl;
		std::cout << "No data to write to file." << std::endl;
		return;
	}
	//Set up output file stream
	std::ofstream ofs(filename);
	if (!ofs.is_open()) {
		std::cout << "Error: Unable to access \'" << filename << "\' for output writing" << std::endl;
		return;
	}
	else {
		/*
		Send data from the dataHolder to output stream, on the form defined in constructor.
		For each token:
			If the token is in comment_signs --> Print the successing tokens on the same line, separated
			by spaces (' ').
			If the token is in data_types --> Send the corresponding write subfunction.
		*/
		std::cout << "Writing data to \'" << filename << "\' ..." << std::endl;
		
		YAML::Emitter emitter;
		emitter << YAML::BeginMap << YAML::Key << "CONSTRUCTION" << YAML::Value;
		emitter << YAML::BeginSeq;
		// Set emitter format according to the value of yamlStyle (given as user input to the constructor)
		YAML_STYLE == BLOCK ? emitter.SetMapFormat(YAML::Block) : emitter.SetMapFormat(YAML::Flow);

		std::string data_type;
		std::vector<std::string> currentTemplate;
		std::vector<std::string> format_data_types = format.extract_keys();

		for (int i = 0; i < data.tokens2D.size(); i++) {
			// Build a comment string from the tokens (separated by space), then write the comment to file.
			if (contains(data.comment_signs, data.tokens2D[i].front())) {
				std::string comment; //FIXME: MOVE OUTSIDE OF IF STATEMENT. AS-IS, A NEW STRING IS CREATED FOR EACH i.

				//Starting at j = 1 means omitting the comment sign (first element). YAML::comment provides the necessary comment sign.
				for (int j = 1; j < data.tokens2D[i].size(); j++) {
					comment.append(data.tokens2D[i][j]);
					comment.append(" ");
				}
				emitter << YAML::Comment(comment);
			}
			//Formulate the content of tokens2D in the desired format (for now, FEAformat)
			else if (contains(format_data_types, data.tokens2D[i].front())) {
				data_type = data.tokens2D[i].front();

				//If the data type of the input line exists in FEAFormat, set the current template to the template corresponding to that data type:
				for (int k = 0; k < format_data_types.size(); k++) {
					if (data_type == format_data_types[k]) {
						currentTemplate = format.data_types_m[format_data_types[k]];
						break;
					}
				}
				//Translate to FEAFormat
				emitter << YAML::BeginMap << YAML::Key << data_type; //Data type map
				emitter << YAML::Value << YAML::BeginMap; //AttributeMap
				for (int l = 0; l < data.tokens2D[i].size() - 1; l++) {
					emitter << YAML::Key << currentTemplate[l];
					emitter << YAML::Value << data.tokens2D[i][l + 1];
				}
				emitter << YAML::EndMap; //Attribute map
				emitter << YAML::EndMap; //Data type map
				
			}
		}
		emitter << YAML::EndSeq;
		emitter << YAML::EndMap;
		//Dump the emitter data into the output file stream:
		ofs << emitter.c_str();
	}
	ofs.close();
}


Writer::~Writer()
{
}
