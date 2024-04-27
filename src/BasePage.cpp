#include "BasePage.h"

// 상수 정의
constexpr char BACK_BUTTON_LABEL[] = "뒤로가기";
constexpr int BACK_BUTTON_X = 350;
constexpr int BACK_BUTTON_Y = 250;

BasePage::BasePage(const wxString& title, const wxPoint& pos, const wxSize& size)
        : wxFrame(nullptr, wxID_ANY, title, pos, size) {
    CreateBackButton();
}

void BasePage::CreateBackButton() {
    backButton = new wxButton(this, wxID_ANY, BACK_BUTTON_LABEL, wxPoint(BACK_BUTTON_X, BACK_BUTTON_Y), wxDefaultSize);
    backButton->Bind(wxEVT_BUTTON, &BasePage::OnClickBack, this);
}

void BasePage::OnClickBack(wxCommandEvent& event) {
    this->Close(true);  // 현재 페이지 닫기
}
