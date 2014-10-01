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

#ifndef VERBOSE_HH
#define VERBOSE_HH

#include "TROOT.h"
#include "TString.h"

#include <time.h>

#include "src/helper/CustomTypes.hh"
#include "src/helper/OtherInput.hh"
#include "src/helper/Tools.hh"



class Verbose{

public:

	// Member Functions

	Verbose(DileptonsVerbose, std::string, std::string);
	~Verbose();
	virtual void Initialize(DileptonsVerbose, std::string, std::string);

	void SetErrorMessages(std::string);
	void SetLogFilePath(std::string);
	void SetNumberOfModules(int);
	void SetSystemMessages(std::string);
	void SetVerbose(DileptonsVerbose);
	void SetVerboseFromInt(int);

	TString GetErrorMessageByID(int = 0);
	std::vector<TString> GetErrorMessages();
	int GetNumberOfModulesLeft();
	TString GetSystemMessageByID(int = 0);
	std::vector<TString> GetSystemMessages();
	int GetVerboseAsInt();

	void Class(TString);
	void Control();
	void Error(int = 0);
	void ErrorAndExit(int = 0);
	void ExecutionTime();
	void Function(TString);
	void JobControl();
	void Message(int = 0);
	void Module();
	void Print(TString, bool = false);
	void Sample(Label);
	void Talk(TString, int = 0, bool = false);
	void Write(TString);
	void WriteLogFile();
	

private:
	
	bool kJobControl;
	TString kLogFilePath;
	int kNumberOfModulesLeft;
	int kNumberOfAllModules;
	time_t kStartTime;
	DileptonsVerbose kVerbose;
	TString kWrittenOutput;

	std::vector<TString> kErrorMessages;
	std::vector<TString> kSystemMessages;

	
};


#endif
