#ifndef PICTUREFRAME_H
#define PICTUREFRAME_H

#include <wx/wx.h>

class TitleFrame : public wxFrame {
public:
    TitleFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

private:
    wxButton* CreateButton(const wxString& label, void (TitleFrame::*eventHandler)(wxCommandEvent&));

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
