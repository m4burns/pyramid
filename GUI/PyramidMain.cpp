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
#include <wx/bitmap.h>
#include <wx/image.h>
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
const long PyramidFrame::ID_STATICTEXT1 = wxNewId();
const long PyramidFrame::ID_STATICBITMAP2 = wxNewId();
const long PyramidFrame::ID_STATICTEXT11 = wxNewId();
const long PyramidFrame::ID_STATICBITMAP3 = wxNewId();
const long PyramidFrame::ID_STATICTEXT3 = wxNewId();
const long PyramidFrame::ID_STATICBITMAP4 = wxNewId();
const long PyramidFrame::ID_STATICTEXT4 = wxNewId();
const long PyramidFrame::ID_STATICBITMAP5 = wxNewId();
const long PyramidFrame::ID_STATICTEXT5 = wxNewId();
const long PyramidFrame::ID_STATICBITMAP6 = wxNewId();
const long PyramidFrame::ID_STATICTEXT6 = wxNewId();
const long PyramidFrame::ID_STATICBITMAP7 = wxNewId();
const long PyramidFrame::ID_STATICTEXT7 = wxNewId();
const long PyramidFrame::ID_STATICBITMAP8 = wxNewId();
const long PyramidFrame::ID_STATICTEXT8 = wxNewId();
const long PyramidFrame::ID_STATICBITMAP9 = wxNewId();
const long PyramidFrame::ID_STATICTEXT9 = wxNewId();
const long PyramidFrame::ID_STATICBITMAP10 = wxNewId();
const long PyramidFrame::ID_STATICTEXT10 = wxNewId();
const long PyramidFrame::ID_STATICBITMAP11 = wxNewId();
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
    wxBoxSizer* BoxSizer10;
    wxBoxSizer* BoxSizer7;
    wxBoxSizer* BoxSizer11;
    wxBoxSizer* BoxSizer13;
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer9;
    wxBoxSizer* BoxSizer4;
    wxBoxSizer* BoxSizer8;
    wxBoxSizer* BoxSizer1;
    wxBoxSizer* BoxSizer12;
    wxBoxSizer* BoxSizer14;
    wxBoxSizer* BoxSizer6;
    wxBoxSizer* BoxSizer5;
    wxStaticBoxSizer* StaticBoxSizer1;

    Create(parent, id, _("Pyramid"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
    SetClientSize(wxSize(400,276));
    Panel1 = new wxPanel(this, ID_PANEL1, wxPoint(272,168), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    BoxSizer1 = new wxBoxSizer(wxVERTICAL);
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    StaticBitmap1 = new wxStaticBitmap(Panel1, ID_STATICBITMAP1, wxBitmap(wxImage(_T("logo.png"))), wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER, _T("ID_STATICBITMAP1"));
    BoxSizer2->Add(StaticBitmap1, 3, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer3 = new wxBoxSizer(wxVERTICAL);
    Button1 = new wxButton(Panel1, ID_BUTTON1, _("Reload"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    BoxSizer3->Add(Button1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button2 = new wxButton(Panel1, ID_BUTTON2, _("Quit"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    BoxSizer3->Add(Button2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2->Add(BoxSizer3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer1->Add(BoxSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    StaticBoxSizer1 = new wxStaticBoxSizer(wxVERTICAL, Panel1, _("Inputs"));
    BoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
    InName1 = new wxStaticText(Panel1, ID_STATICTEXT1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    BoxSizer5->Add(InName1, 4, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    InStat1 = new wxStaticBitmap(Panel1, ID_STATICBITMAP2, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER, _T("ID_STATICBITMAP2"));
    BoxSizer5->Add(InStat1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer1->Add(BoxSizer5, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
    InName2 = new wxStaticText(Panel1, ID_STATICTEXT11, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
    BoxSizer6->Add(InName2, 4, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    InStat2 = new wxStaticBitmap(Panel1, ID_STATICBITMAP3, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER, _T("ID_STATICBITMAP3"));
    BoxSizer6->Add(InStat2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer1->Add(BoxSizer6, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer7 = new wxBoxSizer(wxHORIZONTAL);
    InName3 = new wxStaticText(Panel1, ID_STATICTEXT3, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    BoxSizer7->Add(InName3, 4, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    InStat3 = new wxStaticBitmap(Panel1, ID_STATICBITMAP4, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER, _T("ID_STATICBITMAP4"));
    BoxSizer7->Add(InStat3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer1->Add(BoxSizer7, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer8 = new wxBoxSizer(wxHORIZONTAL);
    InName4 = new wxStaticText(Panel1, ID_STATICTEXT4, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    BoxSizer8->Add(InName4, 4, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    InStat4 = new wxStaticBitmap(Panel1, ID_STATICBITMAP5, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER, _T("ID_STATICBITMAP5"));
    BoxSizer8->Add(InStat4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer1->Add(BoxSizer8, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer9 = new wxBoxSizer(wxHORIZONTAL);
    InName5 = new wxStaticText(Panel1, ID_STATICTEXT5, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    BoxSizer9->Add(InName5, 4, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    InStat5 = new wxStaticBitmap(Panel1, ID_STATICBITMAP6, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER, _T("ID_STATICBITMAP6"));
    BoxSizer9->Add(InStat5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer1->Add(BoxSizer9, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer4->Add(StaticBoxSizer1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    StaticBoxSizer2 = new wxStaticBoxSizer(wxVERTICAL, Panel1, _("Outputs"));
    BoxSizer10 = new wxBoxSizer(wxHORIZONTAL);
    OutName1 = new wxStaticText(Panel1, ID_STATICTEXT6, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    BoxSizer10->Add(OutName1, 4, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    OutStat1 = new wxStaticBitmap(Panel1, ID_STATICBITMAP7, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER, _T("ID_STATICBITMAP7"));
    BoxSizer10->Add(OutStat1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer2->Add(BoxSizer10, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer11 = new wxBoxSizer(wxHORIZONTAL);
    OutName2 = new wxStaticText(Panel1, ID_STATICTEXT7, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
    BoxSizer11->Add(OutName2, 4, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    OutStat2 = new wxStaticBitmap(Panel1, ID_STATICBITMAP8, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER, _T("ID_STATICBITMAP8"));
    BoxSizer11->Add(OutStat2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer2->Add(BoxSizer11, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer12 = new wxBoxSizer(wxHORIZONTAL);
    OutName3 = new wxStaticText(Panel1, ID_STATICTEXT8, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
    BoxSizer12->Add(OutName3, 4, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    OutStat3 = new wxStaticBitmap(Panel1, ID_STATICBITMAP9, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER, _T("ID_STATICBITMAP9"));
    BoxSizer12->Add(OutStat3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer2->Add(BoxSizer12, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer13 = new wxBoxSizer(wxHORIZONTAL);
    OutName4 = new wxStaticText(Panel1, ID_STATICTEXT9, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
    BoxSizer13->Add(OutName4, 4, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    OutStat4 = new wxStaticBitmap(Panel1, ID_STATICBITMAP10, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER, _T("ID_STATICBITMAP10"));
    BoxSizer13->Add(OutStat4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer2->Add(BoxSizer13, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer14 = new wxBoxSizer(wxHORIZONTAL);
    OutName5 = new wxStaticText(Panel1, ID_STATICTEXT10, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
    BoxSizer14->Add(OutName5, 4, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    OutStat5 = new wxStaticBitmap(Panel1, ID_STATICBITMAP11, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER, _T("ID_STATICBITMAP11"));
    BoxSizer14->Add(OutStat5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer2->Add(BoxSizer14, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer4->Add(StaticBoxSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    BoxSizer1->Add(BoxSizer4, 2, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    Panel1->SetSizer(BoxSizer1);
    BoxSizer1->Fit(Panel1);
    BoxSizer1->SetSizeHints(Panel1);
    Timer1.SetOwner(this, ID_TIMER1);
    Timer1.Start(100, false);

    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PyramidFrame::OnReload);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PyramidFrame::OnQuit);
    Connect(ID_TIMER1,wxEVT_TIMER,(wxObjectEventFunction)&PyramidFrame::OnCheckPorts);
    //*)

    port_act = new wxBitmap(wxImage(_("port_act.png")));
    port_inact = new wxBitmap(wxImage(_("port_inact.png")));
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
    InStat1->SetBitmap(*port_inact);
    InStat2->SetBitmap(*port_inact);
    InStat3->SetBitmap(*port_inact);
    InStat4->SetBitmap(*port_inact);
    InStat5->SetBitmap(*port_inact);
    OutStat1->SetBitmap(*port_inact);
    OutStat2->SetBitmap(*port_inact);
    OutStat3->SetBitmap(*port_inact);
    OutStat4->SetBitmap(*port_inact);
    OutStat5->SetBitmap(*port_inact);
}

void PyramidFrame::OnReload(wxCommandEvent& event)
{
}