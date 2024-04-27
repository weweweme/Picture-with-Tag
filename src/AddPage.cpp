#include "AddPage.h"

constexpr char CONFIRM_BUTTON_LABEL[] = "저장";
constexpr int CONFIRM_BUTTON_Y = 600;

AddPage::AddPage(const wxString& title, const wxPoint& pos, const wxSize& size, const PageID currentPage)
        : BasePage(title, pos, size, currentPage) {
    AddPage::InitUI();
}

void AddPage::InitUI() {
    BasePage::InitUI();

    auto* backButton = new wxButton(panel, wxID_ANY, CONFIRM_BUTTON_LABEL, wxPoint(RIGHT_BUTTON_X, CONFIRM_BUTTON_Y), buttonSize);
    backButton->Bind(wxEVT_BUTTON, &AddPage::OnClickConfirm, this);
}

void AddPage::OnClickConfirm(wxCommandEvent &_) {

}
