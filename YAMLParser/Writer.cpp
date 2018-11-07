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
	switch (yamlStyleFlag) {
		case 0:
			YAML_STYLE = BLOCK;
			break;
		case 1:
			YAML_STYLE = FLOW;
	}
	data = dh;
	FEAFormat *format = new FEAFormat(); //FIXME: Is this correct?
}

//Determine whether an array contains a certain elemt.
bool contains(std::vector<std::string> vec, std::string el) {
	auto it = std::find(begin(vec), end(vec), el); //Fetch the iterator of element with value equal to el
	//If it fetches the last element, then el is not in vec:
	return it != end(vec);
}

std::string Writer::parseElementData(std::vector<std::string> v_t, std::vector<std::string> templ) {
	//Writes the input nodal data on the YAML block style.
	YAML::Emitter emitter;

	// Set emitter format according to the value of yamlStyle (given as user input)
	YAML_STYLE == BLOCK ? emitter.SetSeqFormat(YAML::Block) : emitter.SetSeqFormat(YAML::Flow);

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

//Alternative parse methods
//___1___
std::string Writer::parseElementData_idInElementKey(std::vector<std::string> v_t, std::vector<std::string> templ) {
	/*
	Problem: Not all elements can be treated this way, as not all elements have a natural ID.
	*/

	YAML::Emitter emitter;

	// Set emitter format according to the value of yamlStyle (given as user input)
	YAML_STYLE == BLOCK ? emitter.SetSeqFormat(YAML::Block) : emitter.SetSeqFormat(YAML::Flow);

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

//___2___
std::string Writer::parseElementData_asDatatypeLists(std::vector<std::string> v_t, std::vector<std::string> templ) {
	/*
	Problem: Comments within lists are illegal in YAML.
	*/
	YAML::Emitter emitter;

	// Set emitter format according to the value of yamlStyle (given as user input)
	YAML_STYLE == BLOCK ? emitter.SetSeqFormat(YAML::Block) : emitter.SetSeqFormat(YAML::Flow);

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

void Writer::writeToYamlFile2(std::string filename) {
	std::ofstream ofs(filename);
	if (!ofs.is_open()) {
		std::cout << "Error: Unable to access \'" << filename << "\' for output writing" << std::endl;
	}
	if (data.tokens2D.size() == 0) {
		std::cout << data.tokens2D.size() << std::endl;
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
		
		YAML::Emitter emitter;
		emitter << "Construction" << YAML::BeginSeq; 
		// Set emitter format according to the value of yamlStyle (given as user input)
		YAML_STYLE == BLOCK ? emitter.SetSeqFormat(YAML::Block) : emitter.SetSeqFormat(YAML::Flow);

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
			else if (contains(format_data_types, data.tokens2D[i].front())) {
				data_type = data.tokens2D[i].front(); //The line's data type

				//If the data type of the input line exists in FEAFormat, set the current template to the template corresponding to that data type:
				for (int k = 0; k < format_data_types.size(); k++) {
					if (data_type == format_data_types[k]) {
						currentTemplate = format.data_types_m[format_data_types[k]];
						break;
					}
				}
				//Translate to FEAFormat
				emitter << YAML::BeginMap << YAML::Key << data_type;
				emitter << YAML::Value << YAML::BeginSeq;
				for (int l = 0; l < data.tokens2D[i].size() - 1; l++) {
					emitter << YAML::BeginMap << YAML::Key << currentTemplate[l];
					emitter << YAML::Value << data.tokens2D[i][l + 1] << YAML::EndMap;
				}
				emitter << YAML::EndSeq;
				emitter << YAML::EndMap;
				
			}
		}
		emitter << YAML::EndSeq;
		ofs << emitter.c_str();
	}
	ofs.close();
}

//void Writer::writeToYamlFile(std::string filename) {
//	//TODO: Change this to use a macro on enum values (data types) in order to avoid if cluster.
//
//	std::ofstream ofs(filename);
//	if (!ofs.is_open()) {
//		std::cout << "Error: Unable to access \'" << filename << "\' for output writing" << std::endl;
//	}
//	if (data.tokens2D.size() == 0) {
//		std::cout << data.tokens2D.size() << std::endl;
//		std::cout << "No data to write to file." << std::endl;
//	}
//	else {
//		/*
//		For each token:
//			If the token is in comment_signs --> Print the successing tokens on the same line, separated
//			by spaces (' ').
//			If the token is in data_types --> Send the corresponding write subfunction.
//		*/
//		std::cout << "Writing data to \'" << filename << "\' ..." << std::endl;
//
//		for (int i = 0; i < data.tokens2D.size(); i++) {
//			// Build a comment string from the tokens (separated by space), then write the comment to file.
//			if (contains(data.comment_signs, data.tokens2D[i].front())) {
//				YAML::Emitter emitter;
//				std::string comment; //FIXME: MOVE OUTSIDE OF IF STATEMENT. AS-IS, A NEW STRING IS CREATED FOR EACH i.
//
//				//Starting at j = 1 means omitting the comment sign (first element). YAML::comment provides the necessary comment sign.
//				for (int j = 1; j < data.tokens2D[i].size(); j++) {
//					comment.append(data.tokens2D[i][j]);
//					comment.append(" ");
//				}
//
//				emitter << YAML::Comment(comment);
//				ofs << emitter.c_str() << std::endl;
//			}
//			else if (contains(format.data_types, data.tokens2D[i].front())) {
//				std::string data_type = data.tokens2D[i].front();
//
//				//TODO: MAKE THIS MORE DYNAMIC AND AVOID AN IF-CLUSTER
//				if (data_type == "NODE") {
//					ofs << parseElementData_asDatatypeLists(data.tokens2D[i], format.node_template) << std::endl;
//				}
//				else if (data_type == "NODTRANS") {
//					ofs << parseElementData(data.tokens2D[i], format.nodtrans_template) << std::endl;
//				}
//				else if (data_type == "BEAM") {
//					ofs << parseElementData(data.tokens2D[i], format.beam_template) << std::endl;
//				}
//				else if (data_type == "TRISHELL") {
//					ofs << parseElementData(data.tokens2D[i], format.trishell_template) << std::endl;
//				}
//				else if (data_type == "PIPE") {
//					ofs << parseElementData(data.tokens2D[i], format.pipe_template) << std::endl;
//				}
//				else if (data_type == "IHPROFIL") {
//					ofs << parseElementData(data.tokens2D[i], format.ihprofile_template) << std::endl;
//				}
//				else if (data_type == "PLTHICK") {
//					ofs << parseElementData(data.tokens2D[i], format.plthick_template) << std::endl;
//				}
//				else if (data_type == "UNITVEC" || data_type == "YVECTOR" || data_type == "ZVECTOR") {
//					ofs << parseElementData(data.tokens2D[i], format.cfemvector_template) << std::endl;
//				}
//				else if (data_type == "ECCENT") {
//					ofs << parseElementData(data.tokens2D[i], format.eccent_template) << std::endl;
//				}
//				else if (data_type == "MISOIEP") {
//					ofs << parseElementData(data.tokens2D[i], format.misoiep_template) << std::endl;
//				}
//				else if (data_type == "NODELOAD") {
//					ofs << parseElementData(data.tokens2D[i], format.nodeload_template) << std::endl;
//				}
//				else if (data_type == "GRAVITY") {
//					ofs << parseElementData(data.tokens2D[i], format.gravity_template) << std::endl;
//				}
//			}
//		}
//		data.tokens2D.erase(begin(data.tokens2D)); //Erase the token after it has been written to the new file.
//		std::cout << "YAMLParser has written data to \'" << filename << "\'" << std::endl;
//	}
//	ofs.close();
//}

Writer::~Writer()
{
}
