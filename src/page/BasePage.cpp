#include "BasePage.h"
#include "PageManager.h"
#include "../helper/Constants.h"

BasePage::BasePage(const wxString& title, const wxPoint& pos, const wxSize& size, const PageID currentPage)
        : wxFrame(nullptr, wxID_ANY, title, pos, size),
          defaultButtonSize(SIZE_BUTTON_X, SIZE_BUTTON_Y),
          currentPage(currentPage) {
}

void BasePage::InitUI() {
    this->panel = new wxPanel(this);
    auto* backButton = new wxButton(panel, wxID_ANY, BACK_BUTTON_LABEL, wxPoint(RIGHT_BUTTON_X, BACK_BUTTON_Y), defaultButtonSize);
    backButton->Bind(wxEVT_BUTTON, &BasePage::OnClickBack, this);
}

void BasePage::OnClickBack(wxCommandEvent& _) {
    PageManager* manager = PageManager::GetInstance();
    manager->HidePage(this->currentPage);
    manager->ShowPage(PageID::ID_Title);
}
