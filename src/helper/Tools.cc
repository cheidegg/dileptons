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

#ifndef Tools_hh
#define Tools_hh

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include "boost/filesystem.hpp"


namespace Tools {


	//____________________________________________________________________________
	inline double ComputeAngleAddition(double angle1, double angle2){
		/*
		computes the addition between two angles taking the pi correction into account
		*/

		double result = angle1 + angle2;
		while(result >   TMath::Pi()) result -= TMath::TwoPi();
		while(result <= -TMath::Pi()) result += TMath::TwoPi();
		return result;

	}


	//____________________________________________________________________________
	inline double ComputeAngleSubtraction(double angle1, double angle2){
		/*
		computes the subtraction between two angles taking the pi correction into account
		*/

		double result = angle1 - angle2;
		while(result >   TMath::Pi()) result -= TMath::TwoPi();
		while(result <= -TMath::Pi()) result += TMath::TwoPi();
		return result;

	}


	//____________________________________________________________________________
	inline double ComputeDeltaPhi(double phi1, double phi2){

		return TMath::Abs(Tools::ComputeAngleSubtraction(phi1, phi2));

	}


	//__________________________________________________________________________
	inline double ComputeDeltaR(double eta1, double eta2, double phi1, double phi2){
		/* 
		computes delta R between two particles
		*/

		double deta = eta1 - eta2;
		double dphi = Tools::ComputeDeltaPhi(phi1, phi2);
		return sqrt( deta*deta + dphi*dphi );

	}


	//____________________________________________________________________________
	inline int CountTStringOccurrence(TString haystack, TString needle, Ssiz_t position = 0){
		/*
		counts the total number of occurences of a TString needle in a TString haystack
		parameters: haystack (the underlying string), needle (the string whose occurrence
		            in haystack needs to be counted), position (the char at which we start
		            to count)
		return: number of occurences
		*/

		if(haystack.Index(needle, position) > 0)
			return 1 + Tools::CountTStringOccurrence(haystack, needle, haystack.Index(needle, position)+1);
		else
			return 0;

	}


	//____________________________________________________________________________
	inline std::vector<TString> ExplodeTString(TString string, TString delimiter){
		/*
		explodes a TString into a vector of TStrings by breaking the string at
		every delimiter
		parameters: string (the string to explode), delimiter (the string at whose
		            occurrence the string will be broken)
		return: vector
		*/

		std::vector<TString> vector;
		std::istringstream iss(s);
		
		for(std::string token; std::getline(iss, token, delim); ){
		    vector.push_back(std::move(token));
		}
		
		return vector;
	}


	//____________________________________________________________________________
	inline std::vector<int> ConvertTStringVectorToIntVector(std::vector<TString> vector){
		/*
		converts a vector of TString into a vector of integers
		parameters: vector (vector of TStrings)
		return: new_vector (vector of ints)
		*/

		std::vector<int> new_vector;

		for(int i = 0; i < vector.size(); ++i)
			new_vector.push_back(Atoi(vector[i]));

		return new_vector;

	}


	//____________________________________________________________________________
	inline TString GetErrorMessageByID(int error_id){
		/*
		takes out the predefined error message from the respective error file
		parameters: error_id (unique error number)
		return: error message
		*/

		char buffer[1000];
		char symbol[2], type[20], name[100], value[500], comment[300];

		ifstream IN(configfile);
		if(!IN.is_open()) Tools::PrintErrorMessageAndExit(10);

		while(IN.getline(buffer, 1000, '\n')){

			if(strlen(buffer) == 0) continue;
			if(buffer[0] == '#') continue;


		}
	}


	//____________________________________________________________________________
	inline TString GetSystemMessageByID(int message_id){
		/*
		takes out the predefined system message from the respective info file
		parameters: message_id (unique message number)
		return: message
		*/
		


	}


	//____________________________________________________________________________
	inline TString GetUserName(){
		/*
		returns the user name which is read out of the absolute path of the 
		executable by assuming that the system runs on a Tier-3 environment, i.e. in
		a directory structure that starts with /shome/...
		parameters: none
		return: user name 
		*/


		

	}


	//____________________________________________________________________________
	inline void PrintError(int errorid){
		/*
		prints out a predefined error message according to the given unique error 
		number
		parameters: error_id (unique error number)
		return: none
		*/

		cerr << Tools::GetErrorMessageByID(error_id) << endl;

	}


	//____________________________________________________________________________
	inline void PrintErrorMessageAndExit(int error_id){
		/*
		prints out a predefined error message according to the given unique error 
		number and exits the execution of the code
		parameters: error_id (unique error number)
		return: none
		*/

		Tools::PrintErrorMessageByID(1);
		Tools::PrintErrorMessageByID(error_id);
		exit(1);

	}


	//____________________________________________________________________________
	inline void PrintSystemMessageByID(int message_id){
		/* 
		prints out a predefined system message according to the given unique
		message number
		parameters: message_id (unique message number)
		return: none
		*/

		cout << Tools::GetSystemMessageByID(message_id) << endl;

	}


	//____________________________________________________________________________
	inline void PrintUsage(){
		/* 
		prints out a the predefined usage system message, i.e. system message 1
		and terminates the execution (usually, system messages are not printed 
		and they do not appear in combination with an termination of the code)
		parameters: none
		return: none
		*/

		Tools::PrintErrorMessageByID(1);
		Tools::PrintSystemMessageByID(1);
		exit(1);

	}


	//____________________________________________________________________________
	inline std::vector<std::vector<TString> > ReadFromInfoFile(TString info_file, TString delimiter = "\t"){
		/*
		opens a txt file in the info/ directory and 


		// analyse for number of delimiters per row
		ifstream IN(info_file);
		if(!IN.is_open()) Tools::PrintErrorAndExit(11);

		while(IN.getline(buffer, 600))




		// read into matrix form and return

		std::vector< std::vector<TString> > matrix;
		matrix.resize( num_of_col , vector<double>( num_of_row , init_value ) );
// and we are good to go ... 



	}

	
	//____________________________________________________________________________
	inline TString ReadFromTextFile(TString text_file){


	}


	//____________________________________________________________________________
	inline void WriteErrorToLogFile(int error_id){

		Tools::WriteToLogFile(Tools::GetErrorMessageByID(error_id));
	}


	//____________________________________________________________________________
	inline void WriteSystemMessageToLogFile(int message_id){

		Tools::WriteToLogFile(Tools::GetSystemMessageByID(message_id));

	}


	//____________________________________________________________________________
	inline void WriteToLogFile(TString message){

		

	}


}

#endif
