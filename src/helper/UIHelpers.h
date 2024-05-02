#ifndef UIHELPERS_H
#define UIHELPERS_H

#include <wx/stdpaths.h>
#include <wx/wx.h>
#include <wx/datetime.h>
#include <wx/txtstrm.h>
#include <wx/stattext.h>
#include <wx/osx/stattext.h>

class UIHelpers {
public:
    static wxStaticText* CreateStaticText(wxWindow* parent, const wxString& label, const wxPoint& pos, const wxSize& size);
    static wxTextCtrl* CreateTextCtrl(wxWindow* parent, const wxString& defaultValue, const wxPoint& pos, const wxSize& size, long style = 0);
    static wxButton* CreateButton(wxWindow* parent, const wxString& label, const wxPoint& pos, const wxSize& size, long style = 0);
    static wxListBox* CreateListBox(wxWindow* parent, const wxPoint& pos, const wxSize& size, long style = 0);
    static wxChoice* CreateChoice(wxWindow* parent, const wxArrayString& choices, const wxPoint& pos, const wxSize& size);
    static void SetControlColours(wxWindow* control, const wxColour& background, const wxColour& foreground);
};

#endif // UIHELPERS_H
