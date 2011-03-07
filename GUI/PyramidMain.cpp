/***************************************************************
 * Name:      PyramidMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Marc Burns (m4burns@uwaterloo.ca)
 * Created:   2011-03-07
 * Copyright: Marc Burns (convextech.ca)
 * License:
 **************************************************************/

#include "PyramidMain.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(PyramidFrame)
#include <wx/string.h>
#include <wx/intl.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(PyramidFrame)
const long PyramidFrame::ID_STATICBITMAP1 = wxNewId();
const long PyramidFrame::ID_BUTTON1 = wxNewId();
const long PyramidFrame::ID_BUTTON2 = wxNewId();
const long PyramidFrame::ID_PANEL1 = wxNewId();
const long PyramidFrame::ID_TIMER1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(PyramidFrame,wxFrame)
    //(*EventTable(PyramidFrame)
    //*)
END_EVENT_TABLE()

PyramidFrame::PyramidFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(PyramidFrame)
    wxStaticBoxSizer* StaticBoxSizer2;
    wxBoxSizer* BoxSizer3;
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer4;
    wxBoxSizer* BoxSizer1;
    wxStaticBoxSizer* StaticBoxSizer1;

    Create(parent, id, _("Pyramid"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
    SetClientSize(wxSize(400,276));
    Panel1 = new wxPanel(this, ID_PANEL1, wxPoint(272,168), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    BoxSizer1 = new wxBoxSizer(wxVERTICAL);
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    StaticBitmap1 = new wxStaticBitmap(Panel1, ID_STATICBITMAP1, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER, _T("ID_STATICBITMAP1"));
    BoxSizer2->Add(StaticBitmap1, 3, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer3 = new wxBoxSizer(wxVERTICAL);
    Button1 = new wxButton(Panel1, ID_BUTTON1, _("Reload"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    BoxSizer3->Add(Button1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button2 = new wxButton(Panel1, ID_BUTTON2, _("Quit"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    BoxSizer3->Add(Button2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2->Add(BoxSizer3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer1->Add(BoxSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, Panel1, _("Inputs"));
    BoxSizer4->Add(StaticBoxSizer1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    StaticBoxSizer2 = new wxStaticBoxSizer(wxHORIZONTAL, Panel1, _("Outputs"));
    BoxSizer4->Add(StaticBoxSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    BoxSizer1->Add(BoxSizer4, 2, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    Panel1->SetSizer(BoxSizer1);
    BoxSizer1->Fit(Panel1);
    BoxSizer1->SetSizeHints(Panel1);
    Timer1.SetOwner(this, ID_TIMER1);
    Timer1.Start(200, false);

    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PyramidFrame::OnReload);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PyramidFrame::OnQuit);
    Connect(ID_TIMER1,wxEVT_TIMER,(wxObjectEventFunction)&PyramidFrame::OnCheckPorts);
    //*)
}

PyramidFrame::~PyramidFrame()
{
    //(*Destroy(PyramidFrame)
    //*)
}

void PyramidFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void PyramidFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void PyramidFrame::OnCheckPorts(wxTimerEvent& event)
{
}

void PyramidFrame::OnReload(wxCommandEvent& event)
{
}
