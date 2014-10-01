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


#include "src/helper/OtherInput.hh"




//____________________________________________________________________________
std::vector<TString> OtherInput::ReadColumnFromListFile(std::string file_path, int column_index){
	/*
	reads a single column from a list file
	parameters: file_path (path to the text file), column_index (number of the column to be read)
	return: vector of elements matching the column
	*/

	return Tools::GetColumnFromTStringMatrix(OtherInput::ReadMatrixFromListFile(file_path), column_index);

}

	
//____________________________________________________________________________
TString OtherInput::ReadFromTextFile(std::string file_path){



}


//____________________________________________________________________________
std::vector<std::vector<TString> > OtherInput::ReadMatrixFromListFile(std::string file_path, TString delimiter, int number_of_columns){
	/*
	opens a text file with list structure and reads is content into a matrix or TStrings
	parameters: file_path (path to the info file), delimiter (delimiter between the columns), number_of_columns (the number of columns if known)
	return: matrix of TStrings	
	*/


	std::vector<std::vector<TString> > matrix;


	// we first analyse the structure of the list file, i.e. we search for
	// the maximal number of occurrences of the delimiter in each row
	// this defines us the number of columns we have to look for
	// we search for the maximal number since maybe not all columns are filled out in every row


	if(number_of_columns == 0){

		char buffer[1000];
		int occurrences = 0;
		FILE * list_file;

		list_file = fopen(Tools::ConvertStdStringToCString(file_path), "r");
		if(list_file == NULL) return matrix;

		while(fgets(buffer, 1000, list_file) != NULL){
			if(strlen(buffer) == 0) continue;
			if(buffer[0] == '#') continue;

			if(occurrences < Tools::CountTStringOccurrence(Tools::ConvertStdStringToTString(buffer), delimiter)) 
				occurrences = Tools::CountTStringOccurrence(Tools::ConvertStdStringToTString(buffer), delimiter);
		}
		fclose(list_file);
		number_of_columns = occurrences + 1;
	}


	// we define a matrix with 1 row but occurrences+1 number of columns
	// we need to add +1 to occurences as occurrences just counts the maximal 
	// number of occurences of the delimiter per row, however, the number of
	// all columns is +1


	char buffer[1000];
	char format[1000];
	std::string format_s;
	std::vector<TString> column;
	std::vector<std::string> format_elements;

	column.resize( number_of_columns, "");
	format_elements.resize( number_of_columns, "%s");
	matrix.resize( 0, std::vector<TString>( number_of_columns , "" ) );

	format_s = Tools::JoinStdString(format_elements, Tools::ConvertTStringToStdString(delimiter));
	strcpy(format, Tools::ConvertStdStringToCString(format_s));

	ifstream IN(Tools::ConvertStdStringToCString(file_path));

	int line = -1;
	while(IN.getline(buffer,1000)){
		++line;

		if(strlen(buffer) == 0) continue;
		if(buffer[0] == '#') continue;

		if(Tools::ScanTStringFormat(buffer, format, column) == 0) continue;

		matrix.push_back(column);

	}


	return matrix;

}


//____________________________________________________________________________
std::vector<TString> OtherInput::ReadRowFromListFile(std::string file_path, int row_index ){

	return Tools::GetRowFromTStringMatrix(OtherInput::ReadMatrixFromListFile(file_path), row_index);

}


//____________________________________________________________________________
TH1F * OtherInput::ReadTH1FFromROOTFile(TString file_path, TString canvas_name, TString histogram_name){


}


//____________________________________________________________________________
TH2F * OtherInput::ReadTH2FFromROOTFile(TString file_path, TString canvas_name, TString histogram_name){

}






