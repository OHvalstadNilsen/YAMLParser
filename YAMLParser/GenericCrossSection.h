/**This is the base class for all cross-sections.
* This is the least common multiple for cross-section classes, used when
* reference to a arbitrary cross-section element is required.
*/
#pragma once
#include "Identifiable.h"
class GenericCrossSection :
	public Identifiable
{
public:
	GenericCrossSection();
	GenericCrossSection(int id);
	~GenericCrossSection();
};

