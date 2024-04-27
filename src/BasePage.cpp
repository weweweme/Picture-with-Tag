#include "BasePage.h"
#include "PageManager.h"

// 상수 정의
constexpr int SIZE_BUTTON_X = 100;
constexpr int SIZE_BUTTON_Y = 35;
constexpr char BACK_BUTTON_LABEL[] = "뒤로가기";


BasePage::BasePage(const wxString& title, const wxPoint& pos, const wxSize& size, const PageID currentPage)
        : wxFrame(nullptr, wxID_ANY, title, pos, size),
          buttonSize(SIZE_BUTTON_X, SIZE_BUTTON_Y),
          currentPage(currentPage) {
}

void BasePage::InitUI() {
    panel = new wxPanel(this);
    auto* backButton = new wxButton(panel, wxID_ANY, BACK_BUTTON_LABEL, wxPoint(RIGHT_BUTTON_X, BACK_BUTTON_Y), buttonSize);
    backButton->Bind(wxEVT_BUTTON, &BasePage::OnClickBack, this);
}

void BasePage::OnClickBack(wxCommandEvent& _) {
    PageManager* manager = PageManager::GetInstance();
    manager->HidePage(this->currentPage);
    manager->ShowPage(PageID::ID_Title);
}
