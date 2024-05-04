#ifndef BASEPAGE_H
#define BASEPAGE_H

#include <wx/wx.h>
#include "PageID.h"

// 추상 클래스 선언
class BasePage : public wxFrame {
public:
    BasePage(const wxString& title, const wxPoint& pos, const wxSize& size, PageID currentPage);
    ~BasePage() override = default;

protected:
    virtual void InitUI();
    virtual void OnClickBack(wxCommandEvent& _);
    wxPanel* panel{};
    wxSize defaultButtonSize;

private:
    PageID currentPage;
};

#endif // BASEPAGE_H
