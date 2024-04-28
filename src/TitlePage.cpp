#include "TitlePage.h"
#include "PageManager.h"

// 상수 정의
constexpr int BUTTON_SPACE = 3;  // 버튼 사이의 공간
constexpr int BUTTON_WIDTH = 300;
constexpr int BUTTON_HEIGHT = 150;
constexpr char BTN_LABEL_ADD[] = "추가";
constexpr char BTN_LABEL_SEARCH[] = "검색";
constexpr char BTN_LABEL_MANAGE[] = "데이터 관리";
constexpr char BTN_LABEL_EXIT[] = "종료";
constexpr int SPACER_OPTIONS = 1;
constexpr int NO_EXPAND = 0;
const int ALIGNMENT_OPTIONS = wxALIGN_CENTER_HORIZONTAL | wxALL;

TitlePage::TitlePage(const wxString& title, const wxPoint& pos, const wxSize& size)
        : wxFrame(nullptr, wxID_ANY, title, pos, size) {
    vSizer = new wxBoxSizer(wxVERTICAL);
    InitUI();
}

void TitlePage::InitUI() {
    // 버튼이 추가될 수직 sizer에 상단 공간 추가
    vSizer->AddStretchSpacer(SPACER_OPTIONS);  // 상단의 stretchable 공간

    CreateButton(BTN_LABEL_ADD, PageID::ID_Add);
    CreateButton(BTN_LABEL_SEARCH, PageID::ID_Search);  // 예시 ID
    CreateButton(BTN_LABEL_MANAGE, PageID::ID_DataManagement);
    CreateButton(BTN_LABEL_EXIT, PageID::ID_None);  // 종료 버튼의 경우 특별한 처리 필요

    // 버튼이 추가될 수직 sizer에 하단 공간 추가
    vSizer->AddStretchSpacer(SPACER_OPTIONS);  // 하단의 stretchable 공간

    this->SetSizer(vSizer);
    this->Layout();
}

void TitlePage::CreateButton(const wxString& label, PageID pageID) {
    auto* button = new wxButton(this, wxID_ANY, label, wxDefaultPosition, wxSize(BUTTON_WIDTH, BUTTON_HEIGHT), 0);
    vSizer->Add(button, NO_EXPAND, ALIGNMENT_OPTIONS, BUTTON_SPACE);
    button->Bind(wxEVT_BUTTON, [this, pageID](wxCommandEvent& event) {
        OnClickGeneric(event, pageID);
    });
}

void TitlePage::OnClickGeneric(wxCommandEvent& _, PageID pageID) {
    PageManager::GetInstance()->ShowPage(pageID);
}
