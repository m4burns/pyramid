/***************************************************************
 * Name:      PyramidApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Marc Burns (m4burns@uwaterloo.ca)
 * Created:   2011-03-07
 * Copyright: Marc Burns (convextech.ca)
 * License:
 **************************************************************/

#include "PyramidApp.h"

//(*AppHeaders
#include "PyramidMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(PyramidApp);

bool PyramidApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	PyramidFrame* Frame = new PyramidFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
