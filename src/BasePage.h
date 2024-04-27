#ifndef BASEPAGE_H
#define BASEPAGE_H

#include <wx/wx.h>

// 추상 클래스 선언
class BasePage : public wxFrame {
public:
    BasePage(const wxString& title, const wxPoint& pos, const wxSize& size);
    ~BasePage() override = default;

    virtual void SetupPage() = 0;

private:
    void CreateBackButton();
    void OnClickBack(wxCommandEvent& event);

    wxButton* backButton{};
};

#endif // BASEPAGE_H
