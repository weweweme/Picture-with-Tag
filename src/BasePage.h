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
    wxPanel* panel{};
    wxSize buttonSize;
    static constexpr int RIGHT_BUTTON_X = 1300;
    static constexpr int BACK_BUTTON_Y = 700;

private:
    void OnClickBack(wxCommandEvent& _);

    PageID currentPage;
};

#endif // BASEPAGE_H
