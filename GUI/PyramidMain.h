/***************************************************************
 * Name:      PyramidMain.h
 * Purpose:   Defines Application Frame
 * Author:    Marc Burns (m4burns@uwaterloo.ca)
 * Created:   2011-03-07
 * Copyright: Marc Burns (convextech.ca)
 * License:
 **************************************************************/

#ifndef PYRAMIDMAIN_H
#define PYRAMIDMAIN_H

//(*Headers(PyramidFrame)
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/panel.h>
#include <wx/frame.h>
#include <wx/timer.h>
#include <wx/statbmp.h>
//*)

class PyramidFrame: public wxFrame
{
    public:

        PyramidFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~PyramidFrame();

    private:

        //(*Handlers(PyramidFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnCheckPorts(wxTimerEvent& event);
        void OnReload(wxCommandEvent& event);
        //*)

        //(*Identifiers(PyramidFrame)
        static const long ID_STATICBITMAP1;
        static const long ID_BUTTON1;
        static const long ID_BUTTON2;
        static const long ID_PANEL1;
        static const long ID_TIMER1;
        //*)

        //(*Declarations(PyramidFrame)
        wxPanel* Panel1;
        wxButton* Button1;
        wxButton* Button2;
        wxTimer Timer1;
        wxStaticBitmap* StaticBitmap1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // PYRAMIDMAIN_H
