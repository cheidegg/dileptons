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


#include "src/helper/OtherOutput.hh"



//____________________________________________________________________________
bool OtherOutput::CloseTreeAndWrite(){

}


//____________________________________________________________________________
bool OtherOutput::OpenTreeToWrite(TString configplot, int module, TString output_name){

	//TFile * root_file = new TFile(root_file_path);
	//if(root_file.IsZombie()) return root_file;
	//
	//
	//f.IsZombie()


}


//____________________________________________________________________________
void OtherOutput::PrintUsage(){


}


//____________________________________________________________________________
bool OtherOutput::WriteToTextFile(TString output_folder, TString file_name, TString content){

	std::string file_path = Tools::ConvertTStringToStdString(output_folder) + Tools::ConvertTStringToStdString(file_name);

	ofstream out_stream;
	out_stream.open(Tools::ConvertStdStringToCString(file_path + ".txt"));
	out_stream << content;
	out_stream.close();

}





