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


#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <TROOT.h>
#include "TString.h"

#include "src/head/AnalysisModules.hh"
#include "src/head/Sketches.hh"

using namespace std;


//_____________________________________________________________________________________
TString GetRunOnFromConfigurationFile(TString configuration_file);
	/*
	opens and reads the configuration file, analyzes the file content for the variable
	runon and returns its value
	parameters: configuration_file (the file path of the config file)
	return: RunOn
	*/

	char buffer[1000];
	char symbol[2], type[20], name[100], value[500], comment[300];
	
	ifstream IN(configfile);
	if(!IN.is_open()) Tools::PrintErrorAndExit(10);
	
	while(IN.getline(buffer, 1000, '\n')){
	
		if(strlen(buffer) == 0) continue;
		if(buffer[0] == '#') continue;	
		if(sscanf(buffer, "%s\t%s\t\t%s\t\t%s\t\t%s", symbol, type, name, value, comment) <= 3) continue;
				
		if(symbol == 'n' && type == "TString" && name == "RunOn") return value;

	}
}


//_____________________________________________________________________________________
int main(int argc, char* argv[]) {
	/*
	main function, does the whole job
	parameters:
	return: none
	*/



	// Starting Dileptons

	cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	cout << "=======================================================================================" << endl;
	cout << "=======================================================================================" << endl;
	cout << " Starting Dileptons ...                                                                " << endl;
	cout << "=======================================================================================" << endl;
	cout << "=======================================================================================" << endl;
	cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;



	// Getting Configuration File Path

	TString configfile = "";
	char ch;

	while ((ch = getopt(argc, argv, "c:h:?")) != -1 ) {
		switch (ch) {
			case 'c': configfile = TString(optarg); break;
			case '?':
			case 'h': Tools::PrintUsage(); ; break;
			default : Tools::PrintErrorAndExit(2);
		}
	}

	// Checking Arguments

	if(argc < 1) Tools::PrintErrorAndExit(3);



	// Reading the Mode to Run on

	TString runon = GetRunOnFromConfigurationFile(configfile);



	// Running on Analysis or Modules

	if(runon == "analysis" or runon == "modules") {

		AnalysisModules *AM = new AnalysisModules(configfile);
		if(runon == "analysis") AM->RunAnalysis();
		else                    AM->RunModules();
		AM->CopyOutputOnAFSWebspace();
		AM->TagCode(AM->GetVersion(), AM->GetConfigplot());
	
	}



	// Running on Sketches

	else {

		Sketches *SK = new Sketches(configfile);
		SK->RunSketches();
		SK->CopyOutputOnAFSWebspace();
		SK->TagCode(SK->GetVersion(), SK->GetConfigplot());

	}



	// Closing Dileptons

	cout << "......................................................................................." << endl;	
	cout << "=======================================================================================" << endl;
	cout << "=======================================================================================" << endl;
	cout << " Closing Dileptons ...                                                                 " << endl;
	cout << "=======================================================================================" << endl;
	cout << "=======================================================================================" << endl;
	cout << "......................................................................................." << endl;


	// Return

	return 0;
}

