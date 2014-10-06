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


#include "src/helper/Style.hh"



//____________________________________________________________________________
TCanvas * Style::CreateCanvas(std::string canvas_name, int width, int height, bool set_margin){
	/*
  	creates a canvas with given width, height and sets margin, if needed
  	parameters: canvas_name, width, height, set_margin (true if default margin shall be set, false else)
  	return: the canvas
  	*/

	std::cout << "here" << std::endl;
	TCanvas * new_canvas;

//	TCanvas * new_canvas = new TCanvas(Tools::ConvertStdStringToCString(canvas_name), "C", width, height);
//	new_canvas -> SetTicks(1, 1);
//	if(set_margin) 
//		SetCanvasMargin(new_canvas);
	
	return new_canvas;
 
}


//____________________________________________________________________________
void Style::SetCanvas(TCanvas * canvas, std::string canvas_name, int width, int height, bool set_margin){
	/*
  	creates a canvas with given width, height and sets margin, if needed
  	parameters: canvas, canvas_name, width, height, set_margin (true if default margin shall be set, false else)
  	return: the canvas
  	*/

	std::cout << "here" << std::endl;

	canvas = new TCanvas(Tools::ConvertStdStringToCString(canvas_name), "C", width, height);
//	new_canvas -> SetTicks(1, 1);
//	if(set_margin) 
//		SetCanvasMargin(new_canvas);
	
//	return new_canvas;
 
}


//____________________________________________________________________________
void Style::SetCanvasMargin(TCanvas * canvas, float bottom, float left, float right, float top){
	/*
  	sets the margin of a canvas
  	parameters: canvas, bottom, left, right, top
  	return: none
  	*/

	canvas -> SetBottomMargin(bottom);
	canvas -> SetLeftMargin  (left);
	canvas -> SetRightMargin (right);
	canvas -> SetTopMargin   (top);

}


