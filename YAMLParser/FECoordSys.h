/** \brief
* This class represents a coordinate system.
*/

#pragma once
#include "yaml-cpp/yaml.h"
#include "Identifiable.h"
#include "GenericFE.h"
#include <array>
#include <vector>

class FECoordSys :
	public Identifiable,
	public GenericFE
{
public:
	/**YAML-independent constructor
	*
	* id: identification number for the coordinate system object.		<br>
	* Xx, Xy, and Xz represent the vector components for the X-vector.	<br>
	* Yx, Yy, and Yz represent the vector components for the Y-vector.	<br>
	* Zx, Zy, and Zz represent the vector components for the Z-vector.	<br>
	*/
	FECoordSys(int id, double Xx, double Xy, double Xz,
			   double Yx, double Yy, double Yz,
			   double Zx, double Zy, double Zz);

	/**Constructor based on information from a YAML::Node*/
	FECoordSys(YAML::Node& yamlNode);
	virtual ~FECoordSys();

	//---------- Functions ----------
	// Inherited via GenericFE
	virtual bool assignIndependentAttributes(YAML::Node & yamlNode) override;
	virtual void printAttributes() override;

	/**Builds a coordinate system from three points, specified by the PCOORDSYS record*/
	void BuildFromPoints(YAML::Node yamlNode);

	/**Computes an orthogonal vector from two three-dimensional vectors.
	* 
	* Input: <br>
	*	XYZ components for vec1 <br>
	*	XYZ components for vec2
	*
	* Output:<br>
	*	Three-dimensional vector orthogonal to vec1 and vec2.
	*/
	std::vector<double> computeOrthogonalVector(double Xx, double Xy, double Xz, 
												double Zx, double Zy, double Zz);

	/**Normalizes the matrix defined in this class.*/
	void normalizeMatrix();
	
	//---------- Data fields ----------
	
	double M[3][3]; ///< Matrix containing the direction vectors (X, Y, Z) constituting the coordinate system.
};

