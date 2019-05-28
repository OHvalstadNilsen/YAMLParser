/** \brief
* This is the base class for all types with an external identifier attribute.
* Used when reference to an arbitrary identifiable type is required.
*/
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
	int id; ///< Externally defined identification number

public:
	virtual ~Identifiable();
	
	/**The FEM element type.
	* Used to avoid problems with elements of different
	* types having the same id number.
	* E.g. both a BEAM and a NODE can have id = 1.
	*/
	enum Type {
		NULLTYPE,
		//Nodal data
		NODE, COORDSYS,
		//Element data
		BEAM, TRISHELL, QUADSHEL, UNITVEC, ECCENT,
		//Material data
		ISOMATERIAL,
		//Cross-sectional data
		PIPE, BOX, IHPROFIL, LSECTION, TSECTION,
		//Load data
		NODELOAD, LOADCOMB
	};
	
	//---------- Functions ----------
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

	/**Function returning the type of the element. <br>
	* Used to specify element types for operatins such as comparison.
	*/
	virtual Identifiable::Type getType();
	/**Function returning the type as a string. <br>
	* Used to throw informative error messages*/
	virtual std::string getTypeAsString();
	
	//---------- Data fields ----------
	Type type;				///< The FEM element type (see enum definition)
	int getID() const;		///< Getter for the externally defined identification number
	void setID(int id);		///< Setter for the externally defined identification number
};
