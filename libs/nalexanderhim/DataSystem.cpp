/*
Author: Nikolai Alexander-Himlan
Class: EPG-310 <Section 02>
Assignment: midterm
Certification of Authenticity:
I certify that this assignment is almost entirely my own work.
Basic file parsing taken from here: http://cs.dvc.edu/HowTo_Cparse.html
							& here: http://www.cs.uregina.ca/Links/class-info/330/ParsingLine/parsingline.html
*/
#include "DataSystem.h"

///System Tools
#include <iostream>
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;

#include <cstring>

///NikolaiA-H Tools
#include "StringTools.h"

///Definitions
const int MAXLINE=256;
const int MAX_CHARS_PER_LINE = 512;
const int MAX_TOKENS_PER_LINE = 20;
const char* const DELIMITER = " ";

using namespace nah;

extern DataSystem* nah::gpDataReader = nullptr;

bool nah::DataSystem::printFileConents(const std::string& filename)
{
	ifstream inFile (filename);
	if (!inFile.good()) return false; // exit if file not found
	char oneline[MAXLINE];

	while (inFile.getline(oneline, MAXLINE))
		cout<<oneline<<endl;

	inFile.close();
	return true;
}

//TODO: replace #define with const

//start a new section if this line is found
#define INI_SECTION_START	'['
//trim this from the section name
#define INI_SECTION_END		']'
//ignore everything on the line after this
#define INI_COMMENT_LINE	';'
//everything before this is a key, everything after is a key value
#define INI_KEY_VAL_START	'='
//use this value when filling space
#define FILLER_VALUE	"NONE"
/*first source
bool nah::DataSystem::readIniFile(const std::string& filename)
{
	// create a file-reading object
	ifstream fin;
	fin.open(filename); // open a file
	if (!fin.good()) 
		return false; // exit if file not found

	while (!fin.eof())
	{
		// read an entire line into memory
		char buf[MAX_CHARS_PER_LINE];
		fin.getline(buf, MAX_CHARS_PER_LINE);

		// parse the line into blank-delimited tokens
		int n = 0; // a for-loop index

		// array to store memory addresses of the tokens in buf
		const char* token[MAX_TOKENS_PER_LINE] = {}; // initialize to 0
		std::string currentSection = "";//store the current section of the ini file
		// parse the line
		token[0] = strtok(buf, DELIMITER); // first token
		if (token[0]) // zero if line is blank
		{
			for (n = 1; n < MAX_TOKENS_PER_LINE; n++)
			{
				token[n] = strtok(0, DELIMITER); // subsequent tokens
				if (!token[n]) break; // no more tokens
			}
		}

		// process (print) the tokens
		for (int i = 0; i < n; i++) // n = #of tokens
			cout << "Token[" << i << "] = " << token[i] << endl;
		cout << endl;
}
*/
//*second source
bool nah::DataSystem::readIniFile(const std::string& filename)
{
	//checkFileExtension(filename);

	clearIniData();

	//TODO: if filename does not end in ".ini", append it
	ifstream inFile (filename);
	if (!inFile.good()) return false; // exit if file not found
	//char oneline[MAXLINE];
	string oneline;

	//have default values to prevent serious problems
	//WHAT: what kind of "serious" problems?
	std::string currentSection = FILLER_VALUE;
	std::string storeKey = FILLER_VALUE;
	std::string storeVal = FILLER_VALUE;
	while (getline(inFile, oneline))
	{
		//inFile.getline(oneline, MAXLINE);
		//cout << oneline << endl;
		//if ( oneline.find_first_not_of(" \t\v\r\n") )
		if(oneline.empty()) continue;//empty line, skip
		if(oneline[0] != INI_COMMENT_LINE)//not a comment
			//TODO: error check to make sure the first key is part of a section
			if(oneline[0] == INI_SECTION_START)//is a section
			{
					if(currentSection != FILLER_VALUE) mIniFileMap.find(currentSection)->second.insert(std::pair<std::string, std::string>(storeKey, storeVal));//old key and value into section before setting new section
					storeKey = FILLER_VALUE; storeVal = FILLER_VALUE;//empty out key and value containers

				currentSection = StringTools::substring(oneline, INI_SECTION_START, INI_SECTION_END, false, false);//get section name
				mIniFileMap.insert(std::pair<std::string, std::map<std::string, std::string>>(currentSection, std::map<std::string, std::string>()));//create a map for the current section
				//NOTE: do not need to do error checking on this, as it is a good thing if this new map is not created because the section already exists
			}
				//else if(currentSection == "NONE") throw std::logic_error("Did not get to a section first!");
			else//not a comment or section
				if(oneline.find_first_of('=') != string::npos)//check if it is a continuation or new key
				{
					mIniFileMap.find(currentSection)->second.insert(std::pair<std::string, std::string>(storeKey, storeVal));//new key, put the old key and value into the map

					storeKey = StringTools::substring(oneline, 0, INI_KEY_VAL_START, true, false);//gets the key
					storeVal = StringTools::substring(oneline, INI_KEY_VAL_START, INI_COMMENT_LINE, false, false);//get the value
					storeKey = StringTools::trimWhitespace(storeKey);//trim whitespace
					storeVal = StringTools::trimWhitespace(storeVal);//trim whitespace
			}
				else//is continuation of previous value
					storeVal = StringTools::substring(oneline, INI_KEY_VAL_START, INI_COMMENT_LINE, false, false);//add additional lines to value
	}
	mIniFileMap.find(currentSection)->second.insert(std::pair<std::string, std::string>(storeKey, storeVal));//put the last key and value into the map
	inFile.close();
	return true;
}
//*/

//*used for debugging getIniKeyValue
const std::string& nah::DataSystem::getIniKeyValue(const std::string& section, const std::string& key)
{
	std::map<std::string, std::string>* sectionMap = &mIniFileMap.find(section)->second;
	std::string keyVal = sectionMap->find(key)->second;
	return mIniFileMap.find(section)->second.find(key)->second;
}

bool nah::DataSystem::writeQueueToIniFile(const std::string& filename)
{
	//checkFileExtension(filename);

	//HACK: don't worry about preserving comments for now
	//TODO: read .ini file data, use writeQueue to modify data in the read map and create new keys as necessary, then write the entire read map to the file section-by-section
	readIniFile(filename);//read in .ini data from file

	//modify data read from the file
	while (!mIniWriteQueue.empty())
	{
		//TODO: get reference to mIniWriteQueue.begin() and mIniFileMap.begin() to save time by not calling functions
		while (!mIniWriteQueue.begin()->second.empty())
		{
			//[] on a map will create the key if it doesn't exist
			mIniFileMap[mIniWriteQueue.begin()->first][mIniWriteQueue.begin()->second.begin()->first] = mIniWriteQueue.begin()->second.begin()->second;
			mIniWriteQueue.begin()->second.erase(mIniWriteQueue.begin()->second.begin());//remove used key/value pair
		}
		mIniWriteQueue.erase(mIniWriteQueue.begin());//remove used section
	}

	//re-open file for writing
	fstream outFile(filename);
	if (!outFile.good()) return false; // exit if file not opened (supposedly ofstream creates the file)

	//write file map to file section-by-section
	std::string tempString = "";
	while (!mIniFileMap.empty())
	{
		/*Try to preserve .ini comments
		//skip any lines which starts with the .ini comment marker
		while (outFile.peek() == INI_COMMENT_LINE)
			//outFile << "demoman is spy!\n";
			getline(outFile, tempString);//skip line
			*/

		//write section title to file
		//TODO: get reference to mIniFileMap.begin() to save time by not calling functions
		outFile << INI_SECTION_START << mIniFileMap.begin()->first << INI_SECTION_END <<"\n";
		while (!mIniFileMap.begin()->second.empty())
		{
			//don't write key if filler value
			if (mIniFileMap.begin()->second.begin()->first != FILLER_VALUE)
				outFile << mIniFileMap.begin()->second.begin()->first << ' ' << INI_KEY_VAL_START << ' '<< mIniFileMap.begin()->second.begin()->second << "\n";//write key/value combinations to file
			mIniFileMap.begin()->second.erase(mIniFileMap.begin()->second.begin());//remove used key/value pair
		}
		mIniFileMap.erase(mIniFileMap.begin());//remove used section
		outFile << "\n";//append empty line after section
	}

	outFile.close();
	clearIniWriteQueue();//clear data that was written
	clearIniData();//clear data that was read
	return true;
}
bool nah::DataSystem::queueIniFileWrite(const std::string& section, const std::string& key, const std::string& keyValue)
{
	//create section, will not be created if already exists
	mIniWriteQueue.insert(std::pair<std::string, std::map<std::string, std::string>>(section, std::map<std::string, std::string>()));
	//create key+keyValue pair in section
	if (mIniWriteQueue.count(key))//if key exists already, change the value
		mIniWriteQueue.find(section)->second.find(key)->second = keyValue;
	else// if it doesn't exist, put the key/value pair into the map
	mIniWriteQueue.find(section)->second.insert(std::pair<std::string, std::string>(key, keyValue));
	return true;
}

//*/

