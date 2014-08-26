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

#ifndef AKROSD_cc
#define AKROSD_cc

#include <TString.h>

#include "src/helper/Tools.cc";

typedef TString AKROSD;


namespace AKROSD {

	
	
	//____________________________________________________________________________
	inline bool CheckStringForDefinedVariables(AKROSD string, std::vector<AKROSD> osdefinitions){
		/*
		checks the AKROSD string according to the rules of defined event variables
		parameters: string (AKROSD string to be checked), osdefinitions (vector of AKROSD
		            strings for object selection definitions)
		return: true (if everything is ok), false (else)
		*/
	
	}


	//____________________________________________________________________________
	inline bool CheckStringForEventSelection(AKROSD string, std::vector<AKROSD> osdefinitions){
		/*
		checks the AKROSD string according to the rules of event selection definitions
		parameters: string (AKROSD string to be checked), osdefinitions (vector of AKROSD
		            strings for object selection definitions)
		return: true (if everything is ok), false (else)
		*/
	
	}
	
	
	//____________________________________________________________________________
	inline bool CheckStringForObjectSelection(AKROSD string){
		/*
		checks the AKROSD string according to the rules of object selection definitions
		parameters: string (AKROSD string to be checked)
		return: true (if everything is ok), false (else)
		*/
	
	}
	
	
	//____________________________________________________________________________
	inline AKROSD RemoveStatements(AKROSD string, AKROSD needle){
		/*
		removes statements containing needle from a AKROSD string
		parameters: string (AKROSD string to be edited), needle (AKROSD substring to 
		            identify statements that need to be removed)
		return: new_string (edited string)
		*/
	
	}
	
	
	//____________________________________________________________________________
	inline AKROSD SortStatements(AKROSD string){
		/*
		sorts the statements of the AKROSD string alphabetically
		parameters: string (AKROSD string to be edited)
		return: new_string (edited string)
		*/
	
	}
	
	
	//____________________________________________________________________________
	inline AKROSD NegateStatement(AKROSD statement){
		/*
		negates a single regular statement of the AKROSD string
		parameters: statement (single AKROSD statement)
		return: newstatement (negated statement)
		*/
	
		AKROSD newstatement = statement;
		
		TString searchfor[6] = {"++", "--", "=" , "!=", "+" , "-" }; // order of arguments is important!
		TString replaceby[6] = {"-" , "+" , "!=", "=" , "--", "++"}; // order of arguments is important!
	
		for(int i = 0; i<6; ++i){
			newstatement = newstatement.ReplaceAll(searchfor[i], replaceby[i]);
	
		return newstatement;	
	
	}
	
	
	//____________________________________________________________________________
	inline AKROSD NegateStatements(AKROSD string, AKROSD needle){
		/*
		negates statements containing needle in a AKROSD string
		parameters: string (AKROSD string to be edited), needle (AKROSD substring to
		            identify statements that need to negated)
		return: new_string (edited string)
		*/
	
	
	}
	
	
	//____________________________________________________________________________
	AKROSD InterpretRangeStatements(AKROSD string){
		/*
		performs the interpretation of ALL range statements (e.g. NJ+2-3) used 
		in an AKROSD string
		parameters: string (AKROSD string)
		return: newstring (interpreted AKROSD string)
		*/
	
		AKROSD newstring;
		AKROSD statement;
		AKROSD lastdelimiter;
	
		for(Ssiz_t position = 0; position < string.Length(); ++position){
	
			// search through every char of the AKROSD string
			AKROSD delimiter = string(position,1);
	
			// if the char is no , or | we attach it to the statement
			if(delimiter != "," && delimiter != "|") {
				statement += delimiter;
			}
	
			// if the char is indeed , or | or if we have reached the end of the string
			// the statement is complete
			else if(delimiter == "," || delimiter == "|" || position + 1 == string.Length()) {
	
				// looking for a range statement which (1) is no if-th-el statement and (2) contains
				// + and - operators at the same time
				if(Tools::CountTStringOccurrence(statement, "%if") == 0 && Tools::CountTStringOccurrence(statement, "+") > 0 && Tools::CountTStringOccurrence(statement, "-") > 0) {
	
					// define which operator oomes first in the statement
					AKROSD first  = "-";
					AKDOSD second = "+";
					if(statement.Index("+") > 0 && statement.Index("+") < statement.Index("-")){ 
						first  = "+";
						second = "-";
					}
	
					// we explode the statement twice at every operator in order to get the information between them
					// i.e. the statement looks like AAA+BBB-CCC (or AAA-CCC+BBB) and we want to interpret this as
					// AAA+BBB,AAA-CCC (or alternatively AAA-CCC,AAA+BBB) so we need to get AAA, BBB and CCC individually	
					std::vector<AKROSD> explode1 = Tools::ExplodeTString(statement, first);
					std::vector<AKROSD> explode2 = Tools::ExplodeTString(explode1[1], second);
	
					statement = "(" + explode1[0] + first + explode2[0] + "," + explode1[0] + second + explode2[1] + ")";
	
				}
	
				// add the interpreted statement to the new string
				newstring = newstring + lastdelimiter + statement;
	
				// reset everything and be prepared for the next statement
				lastdelimiter = delimiter;
				statement = "";
	
			}
		}
	
		return newstring;
	}
	
	
	//____________________________________________________________________________
	inline AKROSD InterpretIfThElStatements(AKROSD string){
		/*
		performs the interpretation of ALL if-th-el statements used in an AKROSD string
		parameters: string (AKROSD string)
		return: newstring (interpreted AKROSD string)
		*/
	
	
		// we first add a whitespace because Index will return 0 if we find '%if' at the first 
		// position in the string and 0 is interpreted as false in the subsequent if-clause
	
		string = " " + string;
		Ssiz_t first = string.Index("%if");
	
		if(first > 0){
	
			// if the next separator is | instead of an , we separate by |, otherwise we separate by ,
			TString lookfor = ",";
			if(string.Index("|", first) > 0 && string.Index("|", first) < string.Index(",", first)) lookfor = "|"; 
	
			if(string.Index(lookfor, first) > 0) Ssiz_t separate = string.Index(lookfor, first);
			else Ssiz_t separate = string.Length();
	
			// we take out the first if-th-el statement from left
			AKROSD statement = string(first, separate - first);
			statement = statement.Strip(kBoth, " ");
	
			// we take out the three regular statements between the if, th and el keywords
			// i.e. the statement looks like ifAAAthBBBelCCC and we want to get AAA, BBB, CCC individually
			std::vector<AKROSD> explode1 = Tools::ExplodeTString(statement, "th");
			std::vector<AKROSD> explode2 = Tools::ExplodeTString(explode1[1], "el");
	
			AKROSD ifstatement = explode1[0](3, explode1[0].Length()-3);
			AKROSD thstatement = explode2[0];
			AKROSD elstatement = explode2[1];
	
			ifstatement.Strip(kBoth, " ");
			thstatement.Strip(kBoth, " ");
			elstatement.Strip(kBoth, " ");
	
			// interpreting the if-th-el statement
			statement = "((" + ifstatement + "," + thstatement + ")|(" + AKROSD::NegateStatement(ifstatement) + "," + elstatement + "))";
	
			// remaining if-th-el statements are interpreted one after another recursively
			return string(0,first).Strip(kBoth, " ") + statement + AKROSD::InterpretIfThElStatements(string(separate, string.Length()-separate));
	
		}
		else {
			return string;
		}
	}
	
	
	//____________________________________________________________________________
	inline AKROSD InterpretAbbreviations(AKROSD string){
		/*
		performs the interpretation of the abbreviations used in an AKROSD string
		parameters: string (AKROSD string)
		return: newstring (interpreted AKROSD string)
		*/

		AKROSD new_string;

		// 
	
		$newstring="";
	
		$searchforlist[0] = array('CH'     , 'PT'   , 'ETA'   , 'PHI');
		$replacebylist[0] = array('ElCharge', 'ElPt', 'ElEta', 'ElPhi');
		$searchforlist[1] = array('LE'     , 'VM');
		$replacebylist[1] = array('Loose-Electron-', 'Veto-Muon-');
		$searchforlist[2] = array('M', 'E');
		$replacebylist[2] = array('Muon-', 'Electron-');
	
		for($k=0;$k<3;$k++) {
			$done = false;
			echo "k: ". $k.", ";
			for($i=1;$i<=strlen($string);$i++){
				echo "i: ". $i.", ";
				for($j=0;$j<sizeof($searchforlist[$k]);$j++) {
					echo "j: ". $j.", substr: ".substr($string,-$i).", searchfor: ".$searchforlist[$k][$j].", ";
					if(substr($string,-$i) == $searchforlist[$k][$j]) {
						$string=substr($string,0,strlen($string)-$i);
						$newstring=$replacebylist[$k][$j].$newstring;
						$done = true;
					}
					echo "replaceby: ".$replacebylist[$k][$j].", newstring: ".$newstring.", string: ".$string.", done: ".$done."<br />";
					if($done) break 2;
				}
			}
		}
	
	
		for($i=0;$i<sizeof($searchfor);$i++)
			$string = str_replace($searchfor[$i], $replaceby[$i], $string);
	
		return $newstring;
	
	
	
	}
	
	
	//____________________________________________________________________________
	inline AKROSD InterpretOperators(AKROSD string){
		/*
		performs the interpretation of the operators used in an AKROSD string
		parameters: string (AKROSD string)
		return: newstring (interpreted AKROSD string)
		*/
	
		AKROSD newstring = string;
	
		TString searchfor[6] = {"++", "--", "=" , "!=", "+" , "-" }; // order of arguments is important!
		TString replaceby[6] = {">" , "<" , "==", "!=", ">=", "<="}; // order of arguments is important!
	
		for(int i = 0; i<6; ++i){
			newstring = newstring.ReplaceAll(searchfor[i], replaceby[i]);
	
		return newstring;	
	
	}
	
	
	//____________________________________________________________________________
	inline AKROSD InterpretString(AKROSD string){
		/*
		performs the interpretation of the AKROSD string
		parameters: string (AKROSD string)
		return: newstring (interpreted AKROSD string)
		*/
	
		AKROSD newstring;
	
		newstring = string.ReplaceAll(" ", "");
		newstring = InterpretRangeStatements(newstring);	
		newstring = InterpretIfThElStatements(newstring);
		newstring = newstring.ReplaceAll(",", " && ");
		newstring = newstring.ReplaceAll("|", " || ");
		newstring = InterpretAbbreviations(newstring);
		newstring = InterpretOperators(newstring);
		
		return $newstring;
	
	}



}

#endif
