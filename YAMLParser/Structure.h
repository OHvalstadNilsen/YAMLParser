/** \brief  This class represents the entire FE structure
*			in which the FE data instances are members.
*			The FE data types are grouped and stored in a list 
*			and a map for each data instance.
*
*  \todo	checkElementExistence traverses a list. The check should be performed wrt. a map ( list search = O(n) / map search = (Olog(n)) )
*  \todo	fetchObject traveses a list. It should rather obtain the value from the corresponding map (list search = O(n) / map search = (O(log(n)) ).
*/
#pragma once
#include "yaml-cpp/yaml.h"
#include "FETypes.h"
#include <vector>
#include <map>
#include <iostream>

class Structure
{
public:
	Structure(int structureID);
	~Structure();


	//---------- Functions -----------
	//---- Check object existence ----
	/**Check if a specific FE element instance exists in the structure*/
	bool checkElementExistence(int id, std::string type);
	/**Check if a specific coordinate system instance exists in the structure*/
	bool checkCoordSysExistence(int id);
	/**Check if a specific cross-section instance exists in the structure*/
	bool checkCrossSectionExistence(int id, std::string& type);
	/**Check if a specific section instance exists in the structure*/
	bool checkCompSectionExistence(int id);
	/**Check if a specific material instance exists in the structure*/
	bool checkMaterialExistence(int id);
	/**Check if a specific node instance exists in the structure*/
	bool checkNodeExistence(int id);
	/**Check if a specific node load instance exists in the structure*/
	bool checkNodeLoadExistence(int id);
	/**Check if a specific load combination instance exists in the structure*/
	bool checkLoadCombExistence(int id);


	//----- Fetch data objects -----
	/**Fetch a specific coordinate system instance*/
	FECoordSys * fetchCoordSys(int id);
	/**Fetch a specific FE element instance instance*/
	GenericFE* fetchObject(int id, std::string type);
	/**Fetch a specific cross-section instance*/
	GenericCrossSection* fetchCrossSection(int id);
	/**Fetch a specific section instance*/
	GenericCompSection* fetchCompSection(int id);
	/**Fetch a specific material instance*/
	GenericMaterial* fetchMaterial(int id);
	/**Fetch a specific node instance*/
	FENode* fetchNode(int id);
	/**Fetch a specific node load instance*/
	FENodeLoad* fetchNodeLoad(int id);
	/**Fetch a specific load combination instance*/
	FELoadComb* fetchLoadComb(int id);

	//------ Add data objects ------
	/**Add a new node instance to the corresponding map and vector containers*/
	bool addNode(FENode* node);
	/**Add a new FE element instance to the corresponding map and vector containers*/
	bool addElement(GenericFE* element);
	/**Add a new coordinate system instance to the corresponding map and vector containers*/
	bool addCoordSys(FECoordSys * coordSys);
	/**Add a new cross-section instance to the corresponding map and vector containers*/
	bool addCrossSection(GenericCrossSection * crossSection);
	/**Add a new section instance to the corresponding map and vector containers*/
	bool addCompSection(GenericCompSection * section);
	/**Add a new material instance to the corresponding map and vector containers*/
	bool addMaterial(GenericMaterial * material);
	/**Add a new node load instance to the corresponding map and vector containers*/
	bool addNodeLoad(FENodeLoad * nodeLoad);
	/**Add a new load combination instance to the corresponding map and vector containers*/
	bool addLoadComb(FELoadComb* loadComb);


	//---------- Data fields ----------
	int structureID; ///< Identifier for the structure

	//-- Containers for instantiated data objects --
	std::vector<FECoordSys*> coordSysList;					///< List of ptrs to coordSys instances
	std::map<int, FECoordSys*> coordSysMap;					///< Map from ID to corresponding coordSys instance ptr

	std::vector<GenericCrossSection*> crossSectionList;		///< List of ptrs to cross-section instances
	std::map<int, GenericCrossSection*> crossSectionMap;	///< Map from ID to corresponding cross-section instance

	std::vector<GenericCompSection*> compSectionList;		///< List of ptrs to composite section instances
	std::map<int, GenericCompSection*> compSectionMap;		///< Map from ID to corresponding composite section instance
	
	std::vector<GenericMaterial*> materialList;				///< List of ptrs to material instances
	std::map<int, GenericMaterial*> materialMap;			///< Map from ID to corresponding material instance ptr

	std::vector<FENode*> nodeList;							///< List of ptrs to nodes
	std::map<int, FENode*> nodeMap;							///< Map from ID to corresponding node instance ptr

	std::vector<GenericFE*> elementList;					///< List of ptrs to Identifiables (used to generalize FE elements)
	std::map<int, GenericFE*> elementMap;					///< Map from ID to corresponding Identifiable ptr for a specific FE element

	std::vector<FENodeLoad*> nodeLoadList;					///< List of ptrs to node load instances
	std::map<int, FENodeLoad*> nodeLoadMap;					///< Map from ID to corresponding node load instance ptr

	std::vector<FELoadComb*> loadCombList;					///< List of ptrs to load combination instances
	std::map<int, FELoadComb*> loadCombMap;					///< Map from ID to corresponding load combination instance ptr

	//Print content data elements to console
	void printData();
};
