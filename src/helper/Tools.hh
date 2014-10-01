/*****************************************************************************
******************************************************************************
******************************************************************************
**                                                                          **
** The Dileptons Analysis Framework                                         **
**                                                                          **
** Constantin Heidegger, CERN, Summer 2014                                  **
**                                                                          **
******************************************************************************
******************************************************************************
*****************************************************************************/


#ifndef TOOLS_HH
#define TOOLS_HH

#include <TROOT.h>
#include <TString.h>
#include <TMath.h>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <map>
#include <time.h>
#include <sstream>

#include "src/helper/CustomTypes.hh"


namespace Tools {

	// Non-template members

	bool CheckDirectoryWritePermission(TString);
	float ConvertBoolToFloatAlternatively(bool);
	std::string ConvertBoolToStdString(bool);
	TString ConvertBoolToTString(bool);
	bool ConvertFloatToBoolAlternatively(float);
	std::string ConvertIntToStdString(int);
	TString ConvertIntToTString(int);
	std::string ConvertOutputTypeToStdString(OutputType);
	const char* ConvertStdStringToCString(std::string);
	Label ConvertStdStringToLabel(std::string);
	TString ConvertStdStringToTString(std::string);
	const char* ConvertTStringToCString(TString);
	DileptonsMode ConvertTStringToDileptonsMode(TString);
	DileptonsRunOn ConvertTStringToDileptonsRunOn(TString);
	DileptonsVerbose ConvertTStringToDileptonsVerbose(TString);
	OutputType ConvertTStringToOutputType(TString);
	SampleType ConvertTStringToSampleType(TString);
	std::string ConvertTStringToStdString(TString);
	std::vector<int> ConvertTStringVectorToIntVector(std::vector<TString>);
	int CountTStringOccurrence(TString, TString, Ssiz_t = 0, Ssiz_t = -1);
	int ExecuteBashCommand(std::string);
	TString ExecuteShellScript(TString);
	std::vector<TString> ExplodeTString(TString, TString);
	std::vector<TString> GetColumnFromTStringMatrix(std::vector<std::vector<TString> >, int = 0);
	std::vector<TString> GetRowFromTStringMatrix(std::vector<std::vector<TString> >, int = 0);
	std::string GetTimestamp();
	TString GetUserName();
	std::string JoinStdString(std::vector<std::string>, std::string);
	TString JoinTString(std::vector<TString>, TString);
	void ReplaceAll(std::string&, const std::string, const std::string);
	int ScanTStringFormat(TString, TString, std::vector<TString>&);

	// Template members


	//____________________________________________________________________________
	template<typename ValueType, size_t n> std::vector<ValueType> ConvertArrayToVector(const ValueType (&array)[n]){
		/*
		converts an array to a vector, or in other words, initializes a vector with
		an array
		parameters: array
		return: vector
		*/
	
		return std::vector<ValueType>(array, array + n);
	
	}


	//____________________________________________________________________________
	template<typename KeyType, typename VectorType> bool FindElementInMapByKey(std::map<KeyType, VectorType> map, KeyType element){

		if(map.find(element) != map.end()) return true;
	
		return false;

	}


	//____________________________________________________________________________
	template<typename VectorType> bool FindElementInVector(std::vector<VectorType> vector, VectorType element){
		/*
		searches through the elements of a vector and returns true if it finds a given one
		parameters: vector (the vector), element (the element we are looking for)
		return: true (if element is in vector), false (else)
		*/
		
		if(std::find(vector.begin(), vector.end(), element) != vector.end()) return true;
		
		return false;
	
	}


	//____________________________________________________________________________
	template<typename ValueType> int GetElementIndexInVector(std::vector<ValueType> vector, ValueType element){
		/*
		returns the index of an element in a vector, if it is part of the vector, 
		otherwise it returns the length of the vector
		parameters: vector (the vector), element (the element we are looking for)	
		return: position of element in vector
		*/

		return std::distance(vector.begin(), std::find(vector.begin(), vector.end(), element));

	}


	//____________________________________________________________________________
	template<typename ValueType> int GetElementIndexByObjectName(std::vector<ValueType> vector, TString name){
		/*
		searches through a vector of more complex elements, i.e. elements that may be
		of custom type which has a method called "GetName()", and returns the index
		of the element whose name matches a given one
		parameters: vector (the vector), name (the name)
		return: index of the element in vector, whose name matches name
		*/
		
		for(int i = 0; i < vector.size(); ++i)
			if(vector[i] -> GetName() = name)
				return i;
		
		return -1;
	
	}


	//____________________________________________________________________________
	template<typename ValueType> Label GetElementKeyByObjectName(const std::map<Label, ValueType> map, TString name){
		/*
		searches through a map of more complex elements, i.e. elements that may be
		of custom type which has a method called "GetName()", and returns the key
		of the element whose name matches a given one
		parameters: map (the map), name (the name)
		return: key of the element in map, whose name matches name
		*/
		
		typename std::map<Label, ValueType>::const_iterator i;
		
		for(i = map.begin(); i != map.end(); ++i)
			if(i -> second -> GetName() == name)
				return i->first;
		
		return "";
	
	}

	//____________________________________________________________________________
	template<typename ValueType> std::map<Label, ValueType> GetSubSetOfMapByKeys(std::map<Label, ValueType> map, Label keys_beginning){
		/*
		selects a subset of a map according to a list of given keys
		parameters: map (the parent map), keys (the vector of keys)
		return: subset of map containing only elements whose keys are in keys
		*/
	
		std::map<Label, ValueType> result;
		typename std::map<Label, ValueType>::iterator i;
		
		for(i = map.begin(); i != map.end(); ++i)
			if(i -> first(0, keys_beginning.Length()) == keys_beginning)
				result[i -> first] = map[i -> first];
	
		return result;
	
	}
	
	
	//____________________________________________________________________________
	template<typename ValueType> std::map<Label, ValueType> GetSubSetOfMapByKeys(std::map<Label, ValueType> map, std::vector<Label> keys){
		/*
		selects a subset of a map according to a list of given keys
		parameters: map (the parent map), keys (the vector of keys)
		return: subset of map containing only elements whose keys are in keys
		*/
		
		std::map<Label, ValueType> result;
		typename std::map<Label, ValueType>::iterator i;
		
		for(i = map.begin(); i != map.end(); ++i)
			if(std::find(keys.begin(), keys.end(), i->first) != keys.end())
				result[i -> first] = map[i -> first];
		
		return result;
	
	}


	//____________________________________________________________________________
	template<typename ValueType> std::map<Label, ValueType> GetSubSetOfMapByObjectNames(std::map<Label, ValueType> map, TString names_beginning){
		/*
		selects a subset of a map according to a list of given keys
		parameters: map (the parent map), keys (the vector of keys)
		return: subset of map containing only elements whose keys are in keys
		*/
		
		std::map<Label, ValueType> result;
		typename std::map<Label, ValueType>::iterator i;
		
		for(i = map.begin(); i != map.end(); ++i)
			if(i -> second -> GetName()(0, names_beginning.Length()) == names_beginning)
				result[i -> first] = map[i -> first];
		
		return result;
	
	}
	
	
	//____________________________________________________________________________
	template<typename ValueType> std::map<Label, ValueType> GetSubSetOfMapByObjectNames(std::map<Label, ValueType> map, std::vector<TString> names){
		/*
		selects a subset of a map according to a list of given keys
		parameters: map (the parent map), keys (the vector of keys)
		return: subset of map containing only elements whose keys are in keys
		*/
		
		std::map<Label, ValueType> result;
		typename std::map<Label, ValueType>::iterator i;
		
		for(i = map.begin(); i != map.end(); ++i)
			if(std::find(names.begin(), names.end(), (i -> second) -> GetName()) != names.end())
				result[i -> first] = map[i -> first];

		return result;
	
	}


	//____________________________________________________________________________
	template<typename ValueType> std::vector<ValueType> GetSubSetOfVectorByObjectNames(const std::vector<ValueType> vector, TString names_beginning){
		/*
		selects a subset of a map according to a list of given keys
		parameters: map (the parent map), keys (the vector of keys)
		return: subset of map containing only elements whose keys are in keys
		*/
		
		std::vector<ValueType> result;
		
		for(int i = 0; i < vector.size(); ++i)
			if(vector[i] -> GetName()(0, names_beginning.Length()) == names_beginning)
				result.push_back(vector[i]);
		
		return result;
	
	}
	
	
	//____________________________________________________________________________
	template<typename ValueType> std::vector<ValueType> GetSubSetOfVectorByObjectNames(const std::vector<ValueType> vector, std::vector<TString> names){
		/*
		selects a subset of a map according to a list of given keys
		parameters: map (the parent map), keys (the vector of keys)
		return: subset of map containing only elements whose keys are in keys
		*/
		
		std::vector<ValueType> result;
		
		for(int i = 0; i < vector.size(); ++i)
			if(std::find(names.begin(), names.end(), vector[i] -> GetName()) != names.end())
				result.push_back(vector[i]);
		
		return result;
	
	}


	//____________________________________________________________________________
	template<typename KeyType, typename ValueType> std::vector<KeyType> GetVectorFromMapKeys(const std::map<KeyType, ValueType> map){
		/*
		takes out all keys froma  map discarding all values, i.e. we end up with a vector
		parameters: map (the map)
		return: vector of only keys
		*/
		
		std::vector<KeyType> vector;
		typename std::map<KeyType, ValueType>::const_iterator i;
		
		for(i = map.begin(); i != map.end(); ++i)
			vector.push_back(i->first);
		
		return vector;
	}
	
	
	//____________________________________________________________________________
	template<typename KeyType, typename ValueType> std::vector<ValueType> GetVectorFromMapValues(const std::map<KeyType, ValueType> map){
		/*
		takes out all values from a map discarding all keys, i.e. we end up with a vector
		parameters: map (the map)
		return: vector of only values
		*/
		
		std::vector<ValueType> vector;
		typename std::map<KeyType, ValueType>::const_iterator i;
		
		for(i = map.begin(); i != map.end(); ++i)
			vector.push_back(i->second);
		
		return vector;
		
	}


	//____________________________________________________________________________
	template<typename KeyType, typename ValueType> TString PrintContentsOfMap(const std::map<KeyType, ValueType> map, TString delimiter = "\n"){

		TString content = "";
		typename std::map<KeyType, ValueType>::const_iterator i;
		
		for(i = map.begin(); i != map.end(); ++i){
			std::ostringstream stream;
			stream << i->first << ": " << i->second << delimiter;
			content += Tools::ConvertStdStringToTString(stream.str());
			
			//content += i->first;
			//content += ": ";
			//content += i->second;
			//content += delimiter;
		}
		
		return content;

	}


	//____________________________________________________________________________
	template<typename ValueType> std::vector<ValueType> RemoveElementFromVector(std::vector<ValueType> vector, ValueType element){
		/*
		remove every element in a vector that matches a given value
		parameters: vector (the vector), element (the given value)
		return: new_vector without element
		*/
		
		std::vector<ValueType> new_vector;
		for(int i = 0; i < vector.size(); ++i)
			if(vector[i] != element) new_vector.push_back(vector[i]);
		
		return new_vector;
	
	}






}

#endif
