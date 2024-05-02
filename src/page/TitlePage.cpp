#include "TitlePage.h"
#include "PageManager.h"
#include "../helper/Constants.h"

TitlePage::TitlePage(const wxString& title, const wxPoint& pos, const wxSize& size)
        : wxFrame(nullptr, wxID_ANY, title, pos, size) {
    this->vSizer = new wxBoxSizer(wxVERTICAL);
    InitUI();
}

void TitlePage::InitUI() {
    // 버튼이 추가될 수직 sizer에 상단 공간 추가
    this->vSizer->AddStretchSpacer(SPACER_OPTIONS);  // 상단의 stretchable 공간

    CreateButton(BTN_LABEL_ADD, PageID::ID_Add);
    CreateButton(BTN_LABEL_SEARCH, PageID::ID_Search);  // 예시 ID
    CreateButton(BTN_LABEL_EXIT, PageID::ID_None);  // 종료 버튼의 경우 특별한 처리 필요

    // 버튼이 추가될 수직 sizer에 하단 공간 추가
    this->vSizer->AddStretchSpacer(SPACER_OPTIONS);  // 하단의 stretchable 공간

    this->SetSizer(vSizer);
    this->Layout();
}

void TitlePage::CreateButton(const wxString& label, PageID pageID) {
    auto* button = new wxButton(this, wxID_ANY, label, wxDefaultPosition, wxSize(BUTTON_WIDTH, BUTTON_HEIGHT), 0);
    this->vSizer->Add(button, NO_EXPAND, ALIGNMENT_OPTIONS, BUTTON_SPACE);
    button->Bind(wxEVT_BUTTON, [this, pageID](wxCommandEvent& event) {
        OnClickGeneric(event, pageID);
    });
}

void TitlePage::OnClickGeneric(wxCommandEvent& _, PageID pageID) {
    PageManager::GetInstance()->ShowPage(pageID);
}
