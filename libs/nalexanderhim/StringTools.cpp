/*
Author: Nikolai Alexander-Himlan
Class: EPG-301 <Section 01>
Assignment: Midterm
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "StringTools.h"
#include "MathDefines.h"

using namespace std;

using namespace nah;

int StringTools::getSkipIndex(const string& source, const string& skipString, int numSkips, int startIndex /*= 0*/)
{
	int tempIndex = 0;
	int skipIndex = startIndex;
	do
	{
		tempIndex = source.find(skipString, skipIndex+1);//don't include startIndex in skip check
		if(tempIndex == string::npos) break;//make sure a valid position was found, if not cut loop
		skipIndex = tempIndex;
		numSkips--;
	} while (numSkips>0);
	return skipIndex;
}

std::string StringTools::substring(const string& source, int startIndex, int endIndex /*= -1*/, bool includeStartIndex /*= true*/, bool includeEndIndex /*= true */)
{
	if(source == "") { __debugbreak(); throw std::logic_error("empty string!"); }

	if(startIndex < 0) startIndex = 0;//if startIndex is negative, return the string up until endIndex
	else if(!includeStartIndex) startIndex++;//cut the startIndex

	if(endIndex <= startIndex) return source.substr(startIndex, string::npos);//if endIndex is negative, return the entire string after the startIndex
	else if(includeEndIndex) endIndex++;//push end position back 1 so it is included in length

	string tempString = source.substr(startIndex, endIndex - startIndex);//second parameter is length not position
	return tempString;
}

//parse datatypes
double nah::StringTools::parseSciNotation(const string& source)
{
	const char SCI = 'e';
	double number;
	int exponent = 1;//in case 'e' is not found
	bool found_e = false;
	std::string numberString, exponentString;

	//TODO: handle if e does not exist in string
	splitString(&numberString, &exponentString, trimWhitespace(source), SCI, true);

	number = std::atof(numberString.c_str());//don't need to check if numberString is valid, because that would be the user's fault
	if (!exponentString.empty())//no exponent, keep 1
		exponent = std::atoi(exponentString.c_str());

	return number * exp10(exponent);
}

//TODO: move functionality to separate cpp file(s) so StringTools isn't dependent
//#include "Rectangle.h"//TODO: move functionality to separate cpp file so StringTools isn't dependent
#include "IntCoord.h"//TODO: move functionality to separate cpp file so StringTools isn't dependent
//#include "GridCoord.h"//TODO: move functionality to separate cpp file so StringTools isn't dependent
