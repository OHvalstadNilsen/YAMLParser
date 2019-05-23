#pragma once
#include <string>
#include <vector>

/*This class is a base class for all FEM element types
* that has an externally user defined identification number
* (an 'id' attribute).
*/
class Identifiable
{
protected:
	//The externally defined identification number
	int id;

public:
	virtual ~Identifiable();
	/*The FEM element type.
	* Used to avoid problems with elements of different
	* types having the same id number.
	* E.g. both a BEAM and a NODE can have id = 1.
	*/
	enum Type {
		NULLTYPE,
		//Nodal data
		NODE,
		//Element data
		BEAM, TRISHELL, QUADSHEL, UNITVEC, ECCENT,
		//Cross-sectional data
		PIPE, BOX, IHPROFIL, LSECTION, TSECTION,
		//Load data
		NODELOAD
	};
	
	//Vector containing string values that correspond to the enums in Type:
	std::vector<std::string> s_Types = {
	"NULLTYPE",
	//Nodal data
	"NODE",
	//Element data
	"BEAM", "TRISHELL", "QUADSHEL", "UNITVEC", "ECCENT",
	//Cross-sectional data
	"PIPE", "BOX", "LSECTION", "TSECTION"
	};

	Type type;
	virtual Identifiable::Type getType();
	//Function used to throw informative error messages:
	virtual std::string getTypeAsString();
	
	int getID() const;
	void setID(int id);
};
