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

#include "src/include/AnalysisModules.hh"
#include "src/include/Sketches.hh"

using namespace std;


//_____________________________________________________________________________________
int RunOn(Tstring ) {


}


//_____________________________________________________________________________________
TString FindVersion() {

}


//_____________________________________________________________________________________
TString FindConfigplot() {

}


//_____________________________________________________________________________________
void FindAndReplace(TString& source, TString const& find, TString const& replace)
{
    for(std::string::size_type i = 0; (i = source.find(find, i)) != std::string::npos;)
    {
        source.replace(i, find.length(), replace);
        i += replace.length() - find.length() + 1;
    }
}


//_____________________________________________________________________________________
void TagCode(TString version, TString cidpid) {

	TString templatetext;
	ifstream templatefile;
	templatefile.open("templates/tag.sh");

	if(templatefile.is_open())
		while(TString line = getline(templatefile, line)) 
			strcat(templatetext, line);

		templatefile.close();

		FindAndReplace(templatetext, "VERSION", version)
		FindAndReplace(templatetext, "CONFIGPLOT", configplot)
	
		ofstream executefile;
  		executefile.open ("tag.sh");
  		executefile << templatetext;
  		executefile.close();

		system("chmod 0755 tag.sh")
		system("bash tag.sh");	

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
			case 'h': exit(0)                     ; break;
			default : cerr << "*** Error: unknown option " << optarg << std::endl;
			exit(-1);
		}
	}

	// Checking Arguments

	if( argc < 1 )  exit(-1);


	// Initializing Dileptons Class and Reading the Configuration File

	Dileptons *DL = new Dileptons(configfile);
	int mode = DL->GetMode();


	// Running on Analysis


	// Running on Modules


	// Running on Sketches

	Sketches *SK = new Sketches();
	SK->


	// Output Management



	// Tagging the Code

	TagCode(FindVersion(), FindConfigplot());


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

