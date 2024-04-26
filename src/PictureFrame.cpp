#include "PictureFrame.h"

// 상수 정의
constexpr int ASPECT_RATIO_WIDTH = 16;
constexpr int ASPECT_RATIO_HEIGHT = 9;
constexpr int BUTTON_SPACE = 5;  // 버튼 사이의 공간
constexpr int BUTTON_EXPAND_RATIO = 1;  // 버튼의 확장 비율
constexpr int BUTTON_WIDTH = 300;
constexpr int BUTTON_HEIGHT = 150;
constexpr char BTN_LABEL_ADD[] = "추가";
constexpr char BTN_LABEL_SEARCH[] = "검색";
constexpr char BTN_LABEL_MANAGE[] = "데이터 관리";
constexpr char BTN_LABEL_EXIT[] = "종료";

PictureFrame::PictureFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
        : wxFrame(nullptr, wxID_ANY, title, pos, size) {
    InitUI();
}

void PictureFrame::InitUI() {
    this->Bind(wxEVT_SIZE, &PictureFrame::HandleSizeChange, this);

    // 버튼 생성 및 배치
    btnAdd = new wxButton(this, wxID_ANY, BTN_LABEL_ADD, wxDefaultPosition, wxSize(BUTTON_WIDTH, BUTTON_HEIGHT));
    btnSearch = new wxButton(this, wxID_ANY, BTN_LABEL_SEARCH, wxDefaultPosition, wxSize(BUTTON_WIDTH, BUTTON_HEIGHT));
    btnManage = new wxButton(this, wxID_ANY, BTN_LABEL_MANAGE, wxDefaultPosition, wxSize(BUTTON_WIDTH, BUTTON_HEIGHT));
    btnExit = new wxButton(this, wxID_ANY, BTN_LABEL_EXIT, wxDefaultPosition, wxSize(BUTTON_WIDTH, BUTTON_HEIGHT));

    auto* sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(btnAdd, BUTTON_EXPAND_RATIO, wxEXPAND | wxALL, BUTTON_SPACE);
    sizer->Add(btnSearch, BUTTON_EXPAND_RATIO, wxEXPAND | wxALL, BUTTON_SPACE);
    sizer->Add(btnManage, BUTTON_EXPAND_RATIO, wxEXPAND | wxALL, BUTTON_SPACE);
    sizer->Add(btnExit, BUTTON_EXPAND_RATIO, wxEXPAND | wxALL, BUTTON_SPACE);

    this->SetSizer(sizer);
    this->Layout();

    // 이벤트 바인딩
    btnAdd->Bind(wxEVT_BUTTON, &PictureFrame::OnClickAdd, this);
    btnSearch->Bind(wxEVT_BUTTON, &PictureFrame::OnClickSearch, this);
    btnManage->Bind(wxEVT_BUTTON, &PictureFrame::OnClickManageData, this);
    btnExit->Bind(wxEVT_BUTTON, &PictureFrame::OnClickExit, this);
}

void PictureFrame::HandleSizeChange(wxSizeEvent& event) {
    wxSize size = event.GetSize();
    int newWidth = size.GetWidth();
    int newHeight = size.GetHeight();

    int expectedHeight = static_cast<int>(newWidth * ASPECT_RATIO_HEIGHT / static_cast<double>(ASPECT_RATIO_WIDTH));
    int expectedWidth = static_cast<int>(newHeight * ASPECT_RATIO_WIDTH / static_cast<double>(ASPECT_RATIO_HEIGHT));

    // 너비와 높이 비율 조정
    if (expectedHeight != newHeight) {
        newHeight = expectedHeight;
    } else if (expectedWidth != newWidth) {
        newWidth = expectedWidth;
    }

    this->SetSize(newWidth, newHeight); // 사이즈 재설정
    event.Skip(); // 다른 이벤트 핸들러가 처리할 수 있도록 함
}

void PictureFrame::OnClickAdd(wxCommandEvent& event) {
    // '추가' 버튼 로직
}

void PictureFrame::OnClickSearch(wxCommandEvent& event) {
    // '검색' 버튼 로직
}

void PictureFrame::OnClickManageData(wxCommandEvent& event) {
    // '데이터 관리' 버튼 로직
}

void PictureFrame::OnClickExit(wxCommandEvent& event) {
    Close(true);
}
