/*
Author: Nikolai Alexander-Himlan
Class: EPG-301 <Section 01>
Assignment: Midterm
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#pragma once

#include <string>
#include <vector>
#include <forward_list>
//#include <Trackable.h>

#include "CountedArray.h"

using namespace std;

namespace nah
{
	///Parse strings to:
	class IntCoord;
	class GridCoord;
	class Rectangle;

	static const char whitespaceList[] = {' '};
	static const int whitespaceCount = 1;

	//static
	//CONSIDER: move inline functions to separate header files, which are structured like source files, then other files can include only the ones they need and reduce compile time
	//CONSIDER: remove StringTools class and just have global(namespace) functions
	//TODO: implementations have been moved to source file for development and should be moved back to header and inlined once they are completely working
	class StringTools
		// : public Trackable//for compliance with GameArchitecture
	{
	private:
		inline static int getSkipIndex(const string &source, char skipChar, int numSkips, int startIndex = 0)
		{
			string skipString;
			skipString.push_back(skipChar);
			return getSkipIndex(source, skipString, numSkips, startIndex);
		}
		static int getSkipIndex(const string& source, const string& skipString, int numSkips, int startIndex = 0);
	public:
		//StringTools(void);
		//~StringTools(void);

		//ToUpper function source: http://stackoverflow.com/a/5222874
		/*Visual Studio complains it isn't valid
		static string StringToUpper(string strToConvert)**
		{
		for (std::string::iterator p = strToConvert.begin(); strToConvert.end() != p; ++p)
		*p = toupper(*p);

		return p;
		}//*/
		/*don't fully understand transform
		static string StringToUpper(string strToConvert)
		{
		std::transform(strToConvert.begin(), strToConvert.end(), strToConvert.begin(), ::toupper);

		return strToConvert;
		}//*/
		inline static string StringToUpper(string strToConvert)
		{
			for (int i = 0; i < (int)strToConvert.size(); i++){
				strToConvert[i] = toupper(strToConvert[i]);
			}
			return strToConvert;
		}
		inline static string StringToLower(string strToConvert)
		{
			for (int i = 0; i < (int)strToConvert.size(); i++){
				strToConvert[i] = tolower(strToConvert[i]);
			}
			return strToConvert;
		}

		inline static string replace(const string& forString, const string& replaceThis, const string& withThis)
		{
			string extraString = forString;
			extraString.replace(forString.find(replaceThis), replaceThis.length(), withThis);
			return extraString;
		}
#pragma region Substrings and Trimming
		//parse a section of a string
		//a negative number for endChar denotes getting the entire rest of the string after the start
		//if endChar is not found, the entire rest of the line is returned
		static string substring( const string& source, int startIndex, int endIndex = -1, bool includeStartIndex = true, bool includeEndIndex = true );
#pragma region Substring - char Index
		//TODO: figure out if the char Index substring functions should be changed to refer to the string Index substring functions to reduce duplicate funcitonality?
		inline static string substring( const string& source, char startChar, char endChar, bool includeStartChar = true, bool includeEndChar = true )
		{ return substring(source, (int)source.find_first_of(startChar), endChar, includeStartChar, includeEndChar);	}
		inline static string substring( const string& source, int startChar, char endChar, bool includeStartChar = true, bool includeEndChar = true )
		{ return substring(source, startChar, (int)source.find_first_of(endChar, startChar+1), includeStartChar, includeEndChar);	}
		inline static string substring( const string& source, char startChar, int endChar = -1, bool includeStartChar = true, bool includeEndChar = true )
		{ return substring(source, (int)source.find_first_of(startChar), endChar, includeStartChar, includeEndChar);	}
		//************************************
		// Method:    substring
		// FullName:  nah::StringTools::substring
		// Access:    public static 
		// Returns:   std::string
		// Parameter: const string(ref) source
		// Parameter: char startChar
		// Parameter: char endChar
		// Parameter: unsigned int skipStartChars
		// Parameter: unsigned int skipEndChars
		// Parameter: bool includeStartChar
		// Parameter: bool includeEndChar
		//************************************
		/// <summary> Returns part of a string </summary>
		/// <remarks> Making skip characters a separate function will reduce inline size by inlining the smaller function when able. </remarks>
		/// <param name="source"> The string to create a substring from. </param>
		/// <param name="startChar"> The character to start the substring on. </param>
		/// <param name="skipStartChars"> 
		/// The number of times to skip the given start character before starting the substring.
		/// <para> If there are fewer instances of the given character than specified by skip, the last one will be used. </para>
		/// </param>
		/// <param name="endChar"> The character to stop the substring on. </param>
		/// <param name="skipEndChars"> number of times to skip the given end character, starting from startChar, before ending the substring.
		/// <para> If there are fewer instances of the given character than specified by skip, the last one will be used. </para>
		/// </param>
		/// <param name="includeStartChar"> should the starting character be included in the returned string? </param>
		/// <param name="includeEndChar"> should the ending character be included in the returned string? </param>
		/// <returns> A string containing the specified section of source. </returns>
		inline static string substring( const string& source, char startChar, char endChar, unsigned int skipStartChars, unsigned int skipEndChars, bool includeStartChar = true, bool includeEndChar = true )
		{
			int startIndex = getSkipIndex(source, startChar, skipStartChars);
			int endIndex = getSkipIndex(source, endChar, skipEndChars, startIndex);
			return substring(source, startIndex, endIndex, includeStartChar, includeEndChar);
		}
		//************************************
		// Method:    substring
		// FullName:  nah::StringTools::substring
		// Access:    public static 
		// Returns:   std::string
		// Parameter: const string(ref) source
		// Parameter: char startChar
		// Parameter: unsigned int skipStartChars
		// Parameter: int endChar
		// Parameter: bool includeStartChar
		// Parameter: bool includeEndChar
		//************************************
		/// <summary> Returns part of a string </summary>
		/// <remarks> while this function could be done with optional parameters, this way will help the inline be smaller. </remarks>
		/// <param name="source"> The string to create a substring from. </param>
		/// <param name="startChar"> The character to start the substring on. </param>
		/// <param name="endChar"> Position in the source where the substring should end. 
		/// <para> If this value is negative or goes over the length of the source, the remainder of the string after the start will be used. </para>
		/// <remarks> This version of the function cannot have a default value for endChar in order to prevent ambiguity. </remarks>
		/// </param>
		/// <param name="skipStartChars"> The number of times to skip the given start character before starting the substring.
		/// <para> If there are fewer instances of the given character than specified by skip, the last one will be used. </para>
		/// </param>
		/// <param name="includeStartChar"> should the starting character be included in the returned string? </param>
		/// <param name="includeEndChar"> should the ending character be included in the returned string? </param>
		inline static string substring( const string& source, char startChar, int endIndex, unsigned int skipStartChars, bool includeStartChar = true, bool includeEndChar = true )
		{
			int startIndex = getSkipIndex(source, startChar, skipStartChars);
			return substring(source, startIndex, endIndex, includeStartChar, includeEndChar);
		}
		inline static string substring( const string& source, int startIndex, char endChar, unsigned int skipEndChars, bool includeStartChar = true, bool includeEndChar = true )
		{
			int endIndex = getSkipIndex(source, endChar, skipEndChars, startIndex);
			string tempString = substring(source, startIndex, endIndex, includeStartChar, includeEndChar);
			return tempString;
		}
#pragma endregion
#pragma region Substring - string Index
		inline static string substring( const string& source, const string& startString, const string& endString, bool includeStartString = true, bool includeEndString = true )
		{ return substring(source, (int)(source.find(startString)+startString.length())-1, endString, includeStartString, includeEndString);	}
		inline static string substring( const string& source, int startString, const string& endString, bool includeStartString = true, bool includeEndString = true )
		{ return substring(source, startString, (int)source.find(endString, startString+1), includeStartString, includeEndString);	}
		inline static string substring( const string& source, const string& startString, int endString = -1, bool includeStartString = true, bool includeEndString = true )
		{ return substring(source, (int)(source.find(startString)+startString.length())-1, endString, includeStartString, includeEndString);	}
		//************************************
		// Method:    substring
		// FullName:  nah::StringTools::substring
		// Access:    public static 
		// Returns:   std::string
		// Parameter: const string(ref) source
		// Parameter: const string(ref) startString
		// Parameter: const string(ref) endString
		// Parameter: unsigned int skipStartStrings
		// Parameter: unsigned int skipEndStrings
		// Parameter: bool includeStartString
		// Parameter: bool includeEndString
		//************************************
		/// <summary> Returns part of a string </summary>
		/// <remarks> Making skip strings a separate function will reduce inline size by inlining the smaller function when able. </remarks>
		/// <param name="source"> The string to create a substring from. </param>
		/// <param name="startString"> The string to start the substring on. </param>
		/// <param name="skipStartStrings"> 
		/// The number of times to skip the given start string before starting the substring.
		/// <para> If there are fewer instances of the given string than specified by skip, the last one will be used. </para>
		/// </param>
		/// <param name="endString"> The string to stop the substring on. </param>
		/// <param name="skipEndStrings"> number of times to skip the given end string, starting from startString, before ending the substring.
		/// <para> If there are fewer instances of the given string than specified by skip, the last one will be used. </para>
		/// </param>
		/// <param name="includeStartString"> should the starting string be included in the returned string? </param>
		/// <param name="includeEndString"> should the ending string be included in the returned string? </param>
		/// <returns> A string containing the specified section of source. </returns>
		inline static string substring( const string& source, const string& startString, const string& endString, unsigned int skipStartStrings, unsigned int skipEndStrings, bool includeStartString = true, bool includeEndString = true )
		{
			int startIndex = getSkipIndex(source, startString, skipStartStrings);
			int endIndex = getSkipIndex(source, endString, skipEndStrings, startIndex);
			return substring(source, startIndex, endIndex, includeStartString, includeEndString);
		}
		//************************************
		// Method:    substring
		// FullName:  nah::StringTools::substring
		// Access:    public static 
		// Returns:   std::string
		// Parameter: const string(ref) source
		// Parameter: const string(ref) startString
		// Parameter: int endIndex
		// Parameter: unsigned int skipStartStrings
		// Parameter: bool includeStartString
		// Parameter: bool includeEndString
		//************************************
		/// <summary> Returns part of a string </summary>
		/// <remarks> while this function could be done with optional parameters, this way will help the inline be smaller. </remarks>
		/// <param name="source"> The string to create a substring from. </param>
		/// <param name="startString"> The string to start the substring on. </param>
		/// <param name="endString"> Position in the source where the substring should end. 
		/// <para> If this value is negative or goes over the length of the source, the remainder of the string after the start will be used. </para>
		/// <remarks> This version of the function cannot have a default value for endString in order to prevent ambiguity. </remarks>
		/// </param>
		/// <param name="skipStartStrings"> The number of times to skip the given start string before starting the substring.
		/// <para> If there are fewer instances of the given string than specified by skip, the last one will be used. </para>
		/// </param>
		/// <param name="includeStartString"> should the starting string be included in the returned string? </param>
		/// <param name="includeEndString"> should the ending string be included in the returned string? </param>
		inline static string substring( const string& source, const string& startString, int endIndex, unsigned int skipStartStrings, bool includeStartString = true, bool includeEndString = true )
		{
			int startIndex = getSkipIndex(source, startString, skipStartStrings);
			return substring(source, startIndex, endIndex, includeStartString, includeEndString);
		}
		inline static string substring( const string& source, int startIndex, const string& endString, unsigned int skipEndStrings, bool includeStartString = true, bool includeEndString = true )
		{
			int endIndex = getSkipIndex(source, endString, skipEndStrings, startIndex);
			return substring(source, startIndex, endIndex, includeStartString, includeEndString);
		}
#pragma endregion

		/// <summary> Splits a string into 2 parts and assigns them to the outputs. </summary>
		/// <param name="outLeft"> Output of the left side of the split. </param>
		/// <param name="outRight"> Output of the right side of the split. </param>
		/// <param name="source"></param>
		/// <param name="splitIndex"></param>
		/// <param name="dropSplit"> bool is valid.
		/// <para> 0(false) = split character is put out on the right output. </para>
		/// <para> 1(true) = split character is not included in either output. </para>
		/// <para> -1 = split character is put on the left output. </para>
		/// </param>
		inline static void splitString(string* outLeft, string* outRight, const string& source, int splitIndex, int dropSplit = true)
		{
			//TODO: more efficient method than substring?
			*outLeft = substring(source, 0, (int)splitIndex, true, dropSplit <= -1);//include the split character in outLeft if dropSplit is -1
			*outRight = substring(source, (int)splitIndex, (int)source.length(), (dropSplit <= -1) ? false : !dropSplit, true);//don't include the split character if dropSplit is -1 or 1
		}
		/// <summary> Splits a string into 2 parts and assigns them to the outputs. </summary>
		/// <param name="outLeft"> Output of the left side of the split. </param>
		/// <param name="outRight"> Output of the right side of the split. </param>
		/// <param name="source"></param>
		/// <param name="splitAt"></param>
		/// <param name="dropSplit"> bool is valid.
		/// <para> 0(false) = split character is put out on the right output. </para>
		/// <para> 1(true) = split character is not included in either output. </para>
		/// <para> -1 = split character is put on the left output. </para>
		/// </param>
		inline static void splitString(string* outLeft, string* outRight, const string& source, char splitAt, int dropSplit = true)
		{
			int splitIndex = (int)source.find_first_of(splitAt);
			if (splitIndex > 0)//valid split
				splitString(outLeft, outRight, source, splitIndex, dropSplit);
			else if (splitIndex < 0) //split char doesn't exist, put source into left
				*outLeft = source;
			else //split index is the first character, put source into right
				*outRight = source;
		};

		//************************************
		// Method:    trim
		// FullName:  nah::StringTools::trim
		// Access:    public static 
		// Returns:   std::string
		// Qualifier:
		// Parameter: const string(ref) source
		// Parameter: int numChars
		// Parameter: bool trimEnd
		//************************************
		/// <summary> Trims the specified number of characters off the given string. </summary>
		/// <param name="source"></param>
		/// <param name="numChars"></param>
		/// <param name="trimEnd">should the end of the string or the start of the string be trimmed?</param>
		/// <returns></returns>
		inline static string trim(const string& source, int numChars, bool trimEnd = true)
		{
			if(trimEnd) return substring(source, -1, int(source.length() - numChars), false, true);
			else 		return substring(source, numChars);
		}
		//************************************
		// Method:    trimWhitespace
		// FullName:  nah::StringTools::trimWhitespace
		// Access:    public static 
		// Returns:   std::string
		// Parameter: string source
		// Parameter: bool trimStart
		// Parameter: bool trimEnd
		//************************************
		/// <summary> Removes whitespace from the start and end of a string. </summary>
		/// <remarks> Currently only trims spaces. </remarks>
		//TODO: rename source to trimThis
		/// <param name="source"> The string value to be trimmed. </param>
		/// <remarks> The copy of source is modified to create the returned value. It is NOT supposed to be a const reference.</remarks>
		/// <param name="trimStart"> Should the start of the string have whitespace removed? </param>
		/// <param name="trimEnd"> Should the end of the string have whitespace removed? </param>
		/// <returns></returns>
		static string trimWhitespace( const string& source, bool trimStart = true, bool trimEnd = true)
		{
			if(!trimStart && !trimEnd)//stop here if there isn't any trimming to do
				return source;

			//TODO: use whitespaceList
			int startIndex=-1, endIndex=-1;
			if(trimStart) if(source.front() == ' ') //make sure there is whitespace at the start first
					startIndex= source.find_first_not_of(' ');
			if(trimEnd) if(source.back() == ' ') //make sure there is whitespace on the end first
					endIndex= source.find_last_not_of(' ');

			std::string trimmed = substring( source, startIndex, endIndex, true, true );

			/*alternate way, would have a problem if there isn't a space at the start/end
			if(trimStart || trimEnd)
				trimmed = substring(source,
					trimStart ?(int)source.find_first_not_of(' '):-1, 
					trimEnd ?(int)source.find_last_not_of(' '):-1, true,true);
			*/
			return trimmed;
		}
		//************************************
		// Method:    compressWhitespace
		// FullName:  nah::StringTools::compressWhitespace
		// Access:    public static 
		// Returns:   std::string
		// Parameter: const string(ref) source
		//************************************
		/// <summary>
		/// Compress repeated whitespace characters (ex. spaces) into 1
		/// <para> NOTE: Currently only compresses spaces. </para>
		/// <para> WARNING: Current method is very inefficient! </para>
		/// </summary>
		/// <param name="source"></param>
		/// <returns>The compressed string</returns>
		inline static string compressWhitespace(string source)
		{
			for (int i=0; i<whitespaceCount; i++)
			{
				size_t whitePos = source.find(whitespaceList[i]+whitespaceList[i]);
				while (whitePos != string::npos)
				{
					//HACK: this is probably very inefficient!
					source.erase(whitePos+1,1);
					whitePos = source.find("  ");
				}
			}
			return source;
		}
		//TODO: documentation
		static CountedArray<std::string> parseNewlines(const std::string& parseThis)
		{
			//TODO: multiple types of endline characters
			char nl = '\n';
			int numLines = std::count(parseThis.begin(),parseThis.end(), nl)+1;//number of lines
			if(numLines == 1) return CountedArray<std::string>(parseThis);
			CountedArray<std::string> parsedLines = CountedArray<std::string>(numLines);
			unsigned int i = 0;
			for (i=0; i < parsedLines.size()-1; i++)
				parsedLines[i] = substring(parseThis, 0,nl, i, true, false);
			parsedLines[i] = substring(parseThis,nl,-1,i+1,false,true);
			return parsedLines;
		}
#pragma endregion

#pragma region Datatype parsing
		static double parseSciNotation(const string& source);

		//Custom Types
		//TODO: move to relevant classes, better for them to depend on a system class (std::string) than for my StringTools to depend on my custom datatypes
		//TODO: turn each of these into a string operator function/constructor (make sure it has to be an explicit conversion)
		static Rectangle parseRectangle( string source, char separator = ',' );//TODO: multi-char separator (ex. ", ")
		static IntCoord parseIntCoord( string source, char separator = ',' );//TODO: multi-char separator (ex. ", ")
		static GridCoord parseGridCoord( string source, char separator = ',' );//TODO: multi-char separator (ex. ", ")
		///<returns> The number of Rectangles in the array. </returns>
		static int parseRectangleArray( string source, Rectangle* arrayOut, char valueSeparator = ',', char rectSeparator = ' ' );//TODO: multi-char separator (ex. ", ")
		static vector<Rectangle> parseRectangleVector(string source, char valueSeparator = ',', char rectSeparator = ' ' );//TODO: multi-char separator (ex. ", ")
		//************************************
		// Method:    parseIntCoordArray
		// FullName:  nah::StringTools::parseIntCoordArray
		// Access:    public static 
		// Returns:   int
		// Parameter: string source
		// Parameter: IntCoord* arrayOut
		// Parameter: char valueSeparator
		// Parameter: char coordSeparator
		//************************************
		/// <summary> Parses a string into an array of IntCoords 
		/// <para> NOT IMPLEMENTED! </para></summary>
		/// <param name="source">The string to parse</param>
		/// <param name="arrayOut"> The array that the IntCoords will be put into. </param>
		/// <remarks> (arrays are always passed by reference) </remarks>
		/// <param name="valueSeparator">what character is between each IntCoord value</param>
		/// <param name="coordSeparator">what character is between each IntCoord</param>
		/// <returns>the number of elements in the output array. Needed because c++ does not support array sizes. </returns>
		static int parseIntCoordArray( string source, IntCoord* arrayOut, char valueSeparator = ',', char coordSeparator = ' ');//TODO: multi-char separator (ex. ", ")
		//************************************
		// Method:    parseIntCoordVector
		// FullName:  nah::StringTools::parseIntCoordList
		// Access:    public static 
		// Returns:   std::vector(nah::IntCoord)
		// Parameter: string source
		// Parameter: char valueSeparator
		// Parameter: char coordSeparator
		//************************************
		/// <summary> Parses an std::string into an std::vector of IntCoords. </summary>
		/// <param name="source">The string to parse</param>
		/// <param name="valueSeparator">what character is between each IntCoord value</param>
		/// <param name="coordSeparator">what character is between each IntCoord</param>
		/// <returns> an std::vector of IntCoords parsed from the string </returns>
		static vector<IntCoord> parseIntCoordVector( string source, char valueSeparator = ',', char coordSeparator = ' ');//TODO: multi-char separator (ex. ", ")
		static forward_list<IntCoord> parseIntCoordList( string source, char valueSeparator = ',', char coordSeparator = ' ');//TODO: multi-char separator (ex. ", ")
		//************************************
		// Method:    parseGridCoordVector
		// FullName:  nah::StringTools::parseGridCoordVector
		// Access:    public static 
		// Returns:   std::vector(nah::GridCoord)
		// Parameter: string source
		// Parameter: char valueSeparator
		// Parameter: char coordSeparator
		//************************************
		/// <summary> Parses an std::string into an std::vector of GridCoords. </summary>
		/// <param name="source"> The string to parse. </param>
		/// <param name="valueSeparator"> What character is between each GridCoord value. </param>
		/// <param name="coordSeparator"> What character is between each GridCoord. </param>
		/// <returns> an std::vector of GridCoords parsed from the string. </returns>
		static vector<GridCoord> parseGridCoordVector( string source, char valueSeparator = ',', char coordSeparator = ' ');//TODO: multi-char separator (ex. ", ")
#pragma endregion for parsing different data types out of strings
	};
}
