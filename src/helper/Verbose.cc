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


#include "src/helper/Verbose.hh"




/*****************************************************************************
******************************************************************************
** CLASS MEMBERS FOR RUNNING THE CODE                                       **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
Verbose::Verbose(DileptonsVerbose verbose, std::string error_file_path, std::string system_file_path){
    /*
    constructs the Verbose Class
    parameters: verbose (verbose level), error_file_path (path to the info 
	            file of error messages), system_file_path (path to the info
	            file of system messages)
    return: none
    */

	// Since we want to use predefined error messages, we need to make sure the error messages file exists.
	if(access(Tools::ConvertStdStringToCString(error_file_path), F_OK && R_OK) != 0){
		std::cerr << "The info file containing error messages cannot be found or reading is not permitted." << std::endl;
		std::cerr << "Please provide this info file with correct name, location and permission in order to run Dileptons." << std::endl;
		std::cerr << "Execution terminated!" << std::endl;
		exit(1);
	}

	Initialize(verbose, error_file_path, system_file_path);

}


//____________________________________________________________________________
Verbose::~Verbose(){
    /*
    destructs the Verbose Class
    parameters: none
    return: none
    */

}


//____________________________________________________________________________
void Verbose::Initialize(DileptonsVerbose verbose, std::string error_file_path, std::string system_file_path){
	/*
	initializes the Verbose class
    parameters: verbose (verbose level), error_file_path (path to the info 
	            file of error messages), system_file_path (path to the info
	            file of system messages)
	return: none
	*/

	SetVerbose(verbose);
	SetErrorMessages(error_file_path);
	SetSystemMessages(system_file_path);
	
	kStartTime = time(0);
	kWrittenOutput = "STARTING DIlEPTONS\n";

	Talk(GetSystemMessageByID(0).ReplaceAll("__TIMESTAMP__", Tools::ConvertStdStringToTString(Tools::GetTimestamp())), 1);

}





/*****************************************************************************
******************************************************************************
** CLASS MEMBERS FOR SETTING PARAMETERS                                     **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
void Verbose::SetErrorMessages(std::string error_file_path){
	/*
	sets the vector of error messages by reading them from the corresponding info file
	parameters: error_file_path (path to the info file)
	return: none
	*/

	kErrorMessages = OtherInput::ReadColumnFromListFile(error_file_path, 1);

}


//____________________________________________________________________________
void Verbose::SetLogFilePath(std::string new_value){
	/*
	sets the file path of the log file
	parameters: new_value
	return: none
	*/

	kLogFilePath = Tools::ConvertStdStringToTString(new_value);

}


//____________________________________________________________________________
void Verbose::SetNumberOfModules(int number_of_modules_left){
	/*
	sets the number of modules left
	parameters: number_of_modules_left
	return: none
	*/

	std::cout << "setting number of modules " << number_of_modules_left << std::endl;
	kNumberOfModulesLeft = number_of_modules_left;
	kNumberOfAllModules  = number_of_modules_left;

}


//____________________________________________________________________________
void Verbose::SetSystemMessages(std::string system_file_path){
	/*
	sets the vector of system messages by reading them from the corresponding info file
	parameters: system_file_path (path to the info file)
	return: none
	*/

	kSystemMessages = OtherInput::ReadColumnFromListFile(system_file_path, 1);

}


//____________________________________________________________________________
void Verbose::SetVerbose(DileptonsVerbose verbose){
	/*
	sets the verbose of the class to given value
	parameters: verbose (level to be set)
	return: none
	*/

	kVerbose = verbose;

}


//____________________________________________________________________________
void Verbose::SetVerboseFromInt(int verbose){
	/*
	sets the verbose of the class to given value
	parameters: verbose (level to be set)
	return: none
	*/

	kVerbose = (DileptonsVerbose) verbose;

}





/*****************************************************************************
******************************************************************************
** CLASS MEMBERS FOR GETTING PARAMETERS                                     **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
TString Verbose::GetErrorMessageByID(int error_id){
	/*
	returns the message at a given error ID
	parameters: error_id
	return: message at that ID
	*/

	return kErrorMessages[error_id];

}


//____________________________________________________________________________
std::vector<TString> Verbose::GetErrorMessages(){
	/*
	returns the vector of all error messages
	parameters: none
	return: kErrorMessages
	*/

	return kErrorMessages;

}


//____________________________________________________________________________
int Verbose::GetNumberOfModulesLeft(){
	/*
	returns the number of modules left
	parameters: none
	return: kNumberOfModulesLeft
	*/

	return kNumberOfModulesLeft;

}

//____________________________________________________________________________
TString Verbose::GetSystemMessageByID(int message_id){
	/*
	returns the message at a given message ID
	parameters: message_id
	return: message at that ID
	*/

	return kSystemMessages[message_id];

}


//____________________________________________________________________________
std::vector<TString> Verbose::GetSystemMessages(){
	/*
	returns the vector of all system messages
	parameters: none
	return: kSystemMessages
	*/

	return kSystemMessages;

}


//____________________________________________________________________________
int Verbose::GetVerboseAsInt(){
	/*
	returns the verbose of the class as int
	parameters: none
	return: kVerbose as int
	*/

	return (int) kVerbose;

}






/*****************************************************************************
******************************************************************************
** CLASS MEMBERS FOR USING THE VERBOSE                                      **
******************************************************************************
*****************************************************************************/


//____________________________________________________________________________
void Verbose::Class(TString class_name){
	/*
  	talks about initializing a new class
  	parameters: class_name
  	return: none
  	*/

	Talk(GetSystemMessageByID(1).ReplaceAll("__CLASS_NAME__", class_name), 2);

}


//____________________________________________________________________________
void Verbose::Error(int error_id){
	/*
  	talks about an error that occurred
  	parameters: error_id
  	return: none
  	*/

	Talk(GetErrorMessageByID(error_id), 0, true);

}


//____________________________________________________________________________
void Verbose::ErrorAndExit(int error_id){
	/*
  	talks about a severe error that occurred and exists the execution
  	parametres: error_id
  	return: none
  	*/

	Error(error_id);
	exit(1);

}


//____________________________________________________________________________
void Verbose::ExecutionTime(){
	/*
  	talks about the execution time, i.e. the time difference between kStartTime
  	(which is set when this class is initialized, which happens when Dileptons
  	is initialized) and now
  	parameters: none
  	return: none
  	*/

	time_t now = time(0);
	double seconds = difftime(now, kStartTime);
	int hours = (int) seconds / 3600;
	int rest_minutes = (int) seconds / 60 - hours * 60;
	int rest_seconds = (int) seconds - hours * 3600 - rest_minutes * 60;

	std::string execution_time = Tools::ConvertIntToStdString(hours) + "h " + Tools::ConvertIntToStdString(rest_minutes) + "m " + Tools::ConvertIntToStdString(rest_seconds) + "s"; 

	Talk(GetSystemMessageByID(5).ReplaceAll("__TIMESTAMP__", Tools::ConvertStdStringToTString(Tools::GetTimestamp())).ReplaceAll("__EXECUTION_TIME__", Tools::ConvertStdStringToTString(execution_time)), 1);


}


//____________________________________________________________________________
void Verbose::Function(TString function_name){
	/*
  	talks about a (member) function being called
  	parameters: function_name
  	return: none
  	*/

	Talk(GetSystemMessageByID(2).ReplaceAll("__FUNCTION_NAME__", function_name), 2);

}


//____________________________________________________________________________
void Verbose::JobControl(){
	/*
  	this will be job control at some point
  	*/


}


//____________________________________________________________________________
void Verbose::Message(int message_id){
	/*
  	talks about system stuff, regular system messages that are not errors
  	parameters: message_id
  	return: none
  	*/

	Talk(GetSystemMessageByID(message_id), 1);

}


//____________________________________________________________________________
void Verbose::Module(){
	/*
  	talks about the number of modules left to process, since this method is called
  	immediately before the calling of another module, we decrease the number of
  	modules left by 1 right afterwards
  	parameters: none
  	return: none
  	*/

	Talk(GetSystemMessageByID(3).ReplaceAll("__NUMBER_OF_MODULES_LEFT__", Tools::ConvertIntToTString(kNumberOfModulesLeft)).ReplaceAll("__NUMBER_OF_MODULES__", Tools::ConvertIntToTString(kNumberOfAllModules)), 1);
	--kNumberOfModulesLeft;

}


//____________________________________________________________________________
void Verbose::Print(TString message, bool print_error){
	/*
  	do the printing, i.e. printing out a message in bash
  	parameters: message, print_error (true if we are printing an error, false otherwise)
  	return: none
  	*/

	if(print_error) std::cerr << ">> " << message << std::endl;
	else            std::cout << ">> " << message << std::endl;

}


//____________________________________________________________________________
void Verbose::Sample(Label sample_name){
	/*
  	talks about a samples being processed
  	parameters: sample_name
  	return: none
  	*/

	Talk(GetSystemMessageByID(4).ReplaceAll("__SAMPLE_NAME__", sample_name), 1);

}

//____________________________________________________________________________
void Verbose::Talk(TString message, int required_verbose, bool talk_error){
	/*
  	does the talking, i.e. prints and writes a message
  	parameters: message, required_verbose (minimum verbosity level required for printing
  	            the message in the prompt as integer), talk_error (true if the message
  	            is an error message, false otherwise)
  	return: none
  	*/

	if(kVerbose == (DileptonsVerbose) required_verbose) Print(message, talk_error);

	Write(message);

}


//____________________________________________________________________________
void Verbose::Write(TString message){
	/*
  	writes a message to the log file cache
  	parameters: message
  	return: none
  	*/

	kWrittenOutput += message;
	kWrittenOutput += "\n";

}


//____________________________________________________________________________
void Verbose::WriteLogFile(){
	/*
  	writes the log file cache to the log file
  	parameters: none
  	return: none
  	*/

	std::ofstream log_file;
	log_file.open(kLogFilePath);
	log_file << kWrittenOutput;
	log_file << "CLOSING DILEPTONS\n";
	log_file.close();

}




