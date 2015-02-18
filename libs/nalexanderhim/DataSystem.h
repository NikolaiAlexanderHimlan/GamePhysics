/*
Author: Nikolai Alexander-Himlan
Class: EPG-310 <Section 02>
Assignment: midterm
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#pragma once
//#include <Trackable.h>

///System Tools
#include <map>

namespace nah
{
	///Global Instance
	class DataSystem;//used so global pointer has a type
	//singular instance, this is so it is initialized while still having only 1 global instance
	extern DataSystem* gpDataReader;

	//TODO: rename DataReader
	//TODO: CONSIDER: static class
	class DataSystem
		//: public Trackable
	{
	private:
		//2 keys, first key is ini section, second key is the ini key, and the second map value is the ini key value
		std::map<std::string, std::map<std::string, std::string>> mIniFileMap;
		std::map<std::string, std::map<std::string, std::string>> mIniWriteQueue;//stores data to be written to .ini file

		DataSystem(void) { mIniFileMap = std::map<std::string, std::map<std::string, std::string>>(); }
		~DataSystem(void){ clearFileData(); }

		bool checkFileExtension(std::string& filenameReference)
		{
			//TODO: if filename does not end with an extension, append ".ini" to it

		}

	public:
		//TODO: able to specify the data file formats you would like to read and only instantiate the system for those
		static inline void instantiateGlobal(void){ gpDataReader = new DataSystem(); }
		static inline bool clearGlobal(void)
		{
			delete gpDataReader;
			gpDataReader = nullptr;
			return gpDataReader == nullptr;
		}

		bool readFileContents(const std::string& filename);
		bool printFileConents(const std::string& filename);
		bool readIniFile(const std::string& filename);
		const std::string& getIniKeyValue(const std::string& section, const std::string& key);
		//{ return mIniFileMap.find(section)->second.find(key)->second;	}

		inline bool clearFileData(void){
			bool dataCleared = true;
			dataCleared = dataCleared && clearIniData();
			dataCleared = dataCleared && clearIniWriteQueue();
			return dataCleared;
		}
		inline bool clearIniData(void){
			mIniFileMap.clear();//I am unsure if this will clear the inner map successfully?
			return mIniFileMap.empty();
		}

		///Same map is used for both reading and writing files
		//TODO: decide if file should be created if it doesn't exist
		bool writeQueueToIniFile(const std::string& filename);
		//stores data to write to a .ini file
		bool queueIniFileWrite(const std::string& section, const std::string& key, const std::string& value);
		//clears data that is to be written to a .ini file
		inline bool clearIniWriteQueue(void)
		{
			mIniWriteQueue.clear();//I am unsure if this will clear the inner map successfully?
			return mIniWriteQueue.empty();
		}
	};
}

