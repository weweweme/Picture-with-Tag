#include "AddPage.h"

constexpr char CONFIRM_BUTTON_LABEL[] = "저장";
constexpr int CONFIRM_BUTTON_Y = 600;
constexpr int INPUT_FIELD_HEIGHT = 25;

const wxColour LIGHT_RED(255, 204, 204);
const wxColour DEFAULT_BG_COLOR(*wxWHITE);
constexpr int TITLE_INPUT_FIELD_WIDTH = 900;
constexpr int TITLE_LABEL_X = 20;
constexpr int TITLE_LABEL_Y = 25;
constexpr int TITLE_INPUT_X = 60;
constexpr int TITLE_INPUT_Y = 20;
constexpr char TITLE_LABEL_TEXT[] = "제목";
constexpr size_t MAX_TITLE_LENGTH = 32;

constexpr int TAG_BUTTON_WIDTH = 100;
constexpr int TAG_INPUT_FIELD_WIDTH = 780;
constexpr int TAG_BUTTON_X_OFFSET = 78;
constexpr int TAG_INPUT_Y_OFFSET = 50;
constexpr char TAG_LABEL_TEXT[] = "태그";
constexpr char TAG_BUTTON_TEXT[] = "태그 추가";
constexpr size_t MAX_TAGS = 32;
constexpr size_t MAX_TAG_LENGTH = 16;

AddPage::AddPage(const wxString& title, const wxPoint& pos, const wxSize& size, const PageID currentPage)
        : BasePage(title, pos, size, currentPage) {
    AddPage::InitUI();
}

void AddPage::InitUI() {
    BasePage::InitUI();

    // 제목 입력 필드
    auto* titleLabel = new wxStaticText(panel, wxID_ANY, TITLE_LABEL_TEXT, wxPoint(TITLE_LABEL_X, TITLE_LABEL_Y));
    titleInput = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(TITLE_INPUT_X, TITLE_INPUT_Y), wxSize(TITLE_INPUT_FIELD_WIDTH, INPUT_FIELD_HEIGHT));
    titleInput->Bind(wxEVT_TEXT, &AddPage::OnTitleTextChange, this);

    // 태그 입력 필드
    auto* tagLabel = new wxStaticText(panel, wxID_ANY, TAG_LABEL_TEXT, wxPoint(TITLE_LABEL_X, TITLE_LABEL_Y + TAG_INPUT_Y_OFFSET));
    tagInput = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(TITLE_INPUT_X, TITLE_INPUT_Y + TAG_INPUT_Y_OFFSET), wxSize(TAG_INPUT_FIELD_WIDTH, INPUT_FIELD_HEIGHT));
    tagInput->Bind(wxEVT_TEXT, &AddPage::OnTagTextChange, this);

    // 태그 입력 버튼
    auto* tagButton = new wxButton(panel, wxID_ANY, TAG_BUTTON_TEXT, wxPoint(TAG_INPUT_FIELD_WIDTH + TAG_BUTTON_X_OFFSET, TITLE_INPUT_Y + TAG_INPUT_Y_OFFSET), wxSize(TAG_BUTTON_WIDTH, INPUT_FIELD_HEIGHT));
    tagButton->Bind(wxEVT_BUTTON, &AddPage::OnTagButtonClick, this);

    // 확인 버튼
    auto* confirmButton = new wxButton(panel, wxID_ANY, CONFIRM_BUTTON_LABEL, wxPoint(RIGHT_BUTTON_X, CONFIRM_BUTTON_Y), buttonSize);
    confirmButton->Bind(wxEVT_BUTTON, &AddPage::OnClickConfirm, this);
}

void AddPage::OnTitleTextChange(wxCommandEvent& _) {
    SetBackgroundColourBasedOnLength(titleInput, MAX_TITLE_LENGTH);
}

void AddPage::OnTagTextChange(wxCommandEvent& _) {
    SetBackgroundColourBasedOnLength(tagInput, MAX_TAG_LENGTH);
}

void AddPage::OnTagButtonClick(wxCommandEvent& event) {
    wxLogMessage("태그 버튼 클릭");
}

void AddPage::OnClickConfirm(wxCommandEvent& event) {
    // 확인 버튼 클릭 시 수행할 작업
    wxLogMessage("저장 버튼 클릭");
}

void AddPage::SetBackgroundColourBasedOnLength(wxTextCtrl* input, size_t max_length) {
    wxString text = input->GetValue();
    if (text.length() > max_length) {
        input->SetBackgroundColour(LIGHT_RED);
    } else {
        input->SetBackgroundColour(DEFAULT_BG_COLOR);
    }
    input->Refresh();
}
