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


namespace Tools {


	//____________________________________________________________________________
	inline double ComputeAngleAddition(double angle1, double angle2){
		double result = angle1 + angle2;
		while(result >   TMath::Pi()) result -= TMath::TwoPi();
		while(result <= -TMath::Pi()) result += TMath::TwoPi();
		return result;
	}


	//____________________________________________________________________________
	inline double ComputeAngleSubtraction(double angle1, double angle2){
		double result = angle1 - angle2;
		while(result >   TMath::Pi()) result -= TMath::TwoPi();
		while(result <= -TMath::Pi()) result += TMath::TwoPi();
		return result;
	}


	//____________________________________________________________________________
	inline double ComputeDeltaPhi(double phi1, double phi2){

		return TMath::Abs(ComputeAngleSubtraction(phi1, phi2));

		// From cmssw reco::deltaPhi()
		double result = phi1 - phi2;
		while( result >   TMath::Pi() ) result -= TMath::TwoPi();
		while( result <= -TMath::Pi() ) result += TMath::TwoPi();
		return result);
	}

	//__________________________________________________________________________
	inline double ComputeDeltaR(double eta1, double eta2, double phi1, double phi2){
		double deta = eta1 - eta2;
		double dphi = Util::DeltaPhi(phi1, phi2);
		return sqrt( deta*deta + dphi*dphi );
	}


	//____________________________________________________________________________
	inline TString FindAndReplace(TString string, TString find, TString replace){
		/*
		prints a predefined error message according to the given unique error 
		number
		parameters: error (unique error number)
		return: none
		*/

		for(int i = 0; (i = string.find(find, i)) != std::string::npos;) {
			source.replace(i, find.length(), replace);
			i += replace.length() - find.length() + 1;
		}

		return string;

	}


	//____________________________________________________________________________
	inline void PrintError(int error){
		/*
		prints a predefined error message according to the given unique error 
		number
		parameters: error (unique error number)
		return: none
		*/

		char buffer[1000];
		char symbol[2], type[20], name[100], value[500], comment[300];

		ifstream IN(configfile);
		if(!IN.is_open()) Dileptons_Tools::PrintErrorAndExit(10);

		while(IN.getline(buffer, 1000, '\n')){

			if(strlen(buffer) == 0) continue;
			if(buffer[0] == '#') continue;


		}

	}


	//____________________________________________________________________________
	inline void PrintErrorAndExit(int error){
		/*
		returns a predefined error message according to the given unique error 
		number and exits the execution of the code
		parameters: error (unique error number)
		return: none
		*/

		PrintError(error);
		exit(1);

	}


	//____________________________________________________________________________
	inline bool SampleIsData(TString sampletype){
		/*
		converts TString value of sample type into bool, i.e. "data" is converted
		to true, everythinge else to false
		parameters: sampletype (value to be converted to bool)
		return: true (if sample is data) or false (else)
		*/

		if(sampletype == "data") return true;

		return false;

	}



}

#endif
