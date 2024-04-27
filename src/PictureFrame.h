#ifndef PICTUREFRAME_H
#define PICTUREFRAME_H

#include <wx/wx.h>

class PictureFrame : public wxFrame {
public:
    PictureFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

private:
    void OnClickAdd(wxCommandEvent& event);
    void OnClickSearch(wxCommandEvent& event);
    void OnClickManageData(wxCommandEvent& event);
    void OnClickExit(wxCommandEvent& event);
    void InitUI();

    wxButton* btnAdd{};
    wxButton* btnSearch{};
    wxButton* btnManage{};
    wxButton* btnExit{};
};

#endif // PICTUREFRAME_H
