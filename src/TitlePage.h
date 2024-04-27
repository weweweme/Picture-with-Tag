#ifndef PICTUREFRAME_H
#define PICTUREFRAME_H

#include <wx/wx.h>

class TitlePage : public wxFrame {
public:
    TitlePage(const wxString& title, const wxPoint& pos, const wxSize& size);

private:
    wxButton* CreateButton(const wxString& label, void (TitlePage::*eventHandler)(wxCommandEvent&));

    void OnClickAdd(wxCommandEvent& event);
    void OnClickSearch(wxCommandEvent& event);
    void OnClickManageData(wxCommandEvent& event);
    void OnClickExit(wxCommandEvent& event);
    void InitUI();

    wxBoxSizer* vSizer;
    wxButton* btnAdd{};
    wxButton* btnSearch{};
    wxButton* btnManage{};
    wxButton* btnExit{};
};

#endif // PICTUREFRAME_H
