#include "BasePage.h"
#include "PageManager.h"

// 상수 정의
constexpr char BACK_BUTTON_LABEL[] = "뒤로가기";
constexpr int BACK_BUTTON_X = 1300;
constexpr int BACK_BUTTON_Y = 700;

BasePage::BasePage(const wxString& title, const wxPoint& pos, const wxSize& size, const PageID currentPage)
        : wxFrame(nullptr, wxID_ANY, title, pos, size) {
    this->currentPage = currentPage;
    CreateBackButton();
}

void BasePage::CreateBackButton() {
    auto* panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    backButton = new wxButton(panel, wxID_ANY, BACK_BUTTON_LABEL, wxPoint(BACK_BUTTON_X, BACK_BUTTON_Y), wxDefaultSize);
    backButton->Bind(wxEVT_BUTTON, &BasePage::OnClickBack, this);
}

void BasePage::OnClickBack(wxCommandEvent& _) {
    PageManager* manager = PageManager::GetInstance();
    manager->HidePage(this->currentPage);
    manager->ShowPage(PageID::ID_Title);
}
