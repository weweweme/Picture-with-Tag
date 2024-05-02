#ifndef PICTUREFRAME_H
#define PICTUREFRAME_H

#include <wx/wx.h>
#include "PageID.h"

class TitlePage : public wxFrame {
public:
    TitlePage(const wxString& title, const wxPoint& pos, const wxSize& size);

private:
    void CreateButton(const wxString& label, PageID pageID);

    void InitUI();
    static void OnClickGeneric(wxCommandEvent& _, PageID pageID);

    wxBoxSizer* vSizer;
};

#endif // PICTUREFRAME_H
