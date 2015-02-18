#ifndef PlanetaryDataKey_h__
#define PlanetaryDataKey_h__
/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 2
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include <string>

struct PlanetDataKey
{
private:
	static const std::string PLANET_NAME_STRINGS[];
public:
	enum PlanetName {
		INVALID_PLANET = -1, 

		SUN, 
		MERCURY, 
		VENUS, 
		EARTH, 
		MARS, 
		JUPITER, 
		SATURN, 
		URANUS, 
		NEPTUNE, 
		PLUTO, 

		NUM_PLANETS
	};
	inline static std::string getPlanetNameString(PlanetName getNameString) { return PLANET_NAME_STRINGS[getNameString];	};

	//Datafile Name
	static const std::string DATAFILE_NAME;

	//Section Names
	static const std::string SEC_SIM;

	//Value Names
	static const std::string VAL_SCALEFACT;
	static const std::string VAL_MASS;
	static const std::string VAL_SIZE;
	static const std::string VAL_DIST;
	static const std::string VAL_VEL;
	static const std::string VAL_MOON_COUNT;
};

__declspec(selectany) const std::string PlanetDataKey::PLANET_NAME_STRINGS[] = {
	"Sun",
	"Mercury",
	"Venus",
	"Earth",
	"Mars",
	"Jupiter",
	"Saturn",
	"Uranus",
	"Neptune",
	"Pluto"
};

__declspec(selectany) const std::string PlanetDataKey::DATAFILE_NAME = "PlanetaryData.ini";
__declspec(selectany) const std::string PlanetDataKey::SEC_SIM = "simulation";

__declspec(selectany) const std::string PlanetDataKey::VAL_SCALEFACT = "scale factor";
__declspec(selectany) const std::string PlanetDataKey::VAL_MASS = "mass";
__declspec(selectany) const std::string PlanetDataKey::VAL_SIZE = "diameter";
__declspec(selectany) const std::string PlanetDataKey::VAL_DIST = "distance from sun";
__declspec(selectany) const std::string PlanetDataKey::VAL_VEL = "orbital velocity";
__declspec(selectany) const std::string PlanetDataKey::VAL_MOON_COUNT = "num moons";

#endif // PlanetaryDataKey_h__
