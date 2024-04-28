#include "AddPage.h"

constexpr char CONFIRM_BUTTON_LABEL[] = "저장";
constexpr int CONFIRM_BUTTON_Y = 640;
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

constexpr int BODY_TEXT_WIDTH = 900;
constexpr int BODY_TEXT_HEIGHT = 130;
constexpr int BODY_LABEL_X = 20;
constexpr int BODY_LABEL_Y = 690;
constexpr int BODY_INPUT_X = 60;
constexpr int BODY_INPUT_Y = 630;
constexpr char BODY_LABEL_TEXT[] = "본문";
constexpr size_t MAX_BODY_LENGTH = 256;

AddPage::AddPage(const wxString& title, const wxPoint& pos, const wxSize& size, const PageID currentPage)
        : BasePage(title, pos, size, currentPage) {
    AddPage::InitUI();
}

void AddPage::InitUI() {
    BasePage::InitUI();

    // 제목 입력 필드
    auto* titleLabel = new wxStaticText(this->panel, wxID_ANY, TITLE_LABEL_TEXT, wxPoint(TITLE_LABEL_X, TITLE_LABEL_Y));
    this->titleInput = new wxTextCtrl(this->panel, wxID_ANY, "", wxPoint(TITLE_INPUT_X, TITLE_INPUT_Y), wxSize(TITLE_INPUT_FIELD_WIDTH, INPUT_FIELD_HEIGHT));
    this->titleInput->Bind(wxEVT_TEXT, &AddPage::OnTitleTextChange, this);

    // 태그 입력 필드
    auto* tagLabel = new wxStaticText(this->panel, wxID_ANY, TAG_LABEL_TEXT, wxPoint(TITLE_LABEL_X, TITLE_LABEL_Y + TAG_INPUT_Y_OFFSET));
    this->tagInput = new wxTextCtrl(this->panel, wxID_ANY, "", wxPoint(TITLE_INPUT_X, TITLE_INPUT_Y + TAG_INPUT_Y_OFFSET), wxSize(TAG_INPUT_FIELD_WIDTH, INPUT_FIELD_HEIGHT));
    this->tagInput->Bind(wxEVT_TEXT, &AddPage::OnTagTextChange, this);

    // 태그 입력 버튼
    this->tagButton = new wxButton(this->panel, wxID_ANY, TAG_BUTTON_TEXT, wxPoint(TAG_INPUT_FIELD_WIDTH + TAG_BUTTON_X_OFFSET, TITLE_INPUT_Y + TAG_INPUT_Y_OFFSET), wxSize(TAG_BUTTON_WIDTH, INPUT_FIELD_HEIGHT));
    this->tagButton->Bind(wxEVT_BUTTON, &AddPage::OnTagButtonClick, this);
    this->tagButton->Enable(false);

    // 태그 리스트 박스 초기화
    this->tagList = new wxListBox(this->panel, wxID_ANY, wxPoint(LISTBOX_X, LISTBOX_Y), wxSize(LISTBOX_WIDTH, LISTBOX_HEIGHT));

    // 본문 텍스트 입력 필드
    auto* bodyLabel = new wxStaticText(this->panel, wxID_ANY, BODY_LABEL_TEXT, wxPoint(BODY_LABEL_X, BODY_LABEL_Y));
    this->bodyInput = new wxTextCtrl(this->panel, wxID_ANY, "", wxPoint(BODY_INPUT_X, BODY_INPUT_Y), wxSize(BODY_TEXT_WIDTH, BODY_TEXT_HEIGHT), wxTE_MULTILINE);
    this->bodyInput->Bind(wxEVT_TEXT, &AddPage::OnBodyTextChange, this);

    // 확인 버튼
    auto* confirmButton = new wxButton(this->panel, wxID_ANY, CONFIRM_BUTTON_LABEL, wxPoint(RIGHT_BUTTON_X, CONFIRM_BUTTON_Y), defaultButtonSize);
    confirmButton->Bind(wxEVT_BUTTON, &AddPage::OnClickConfirm, this);
}

void AddPage::OnTitleTextChange(wxCommandEvent& _) {
    SetBackgroundColourBasedOnLength(this->titleInput, MAX_TITLE_LENGTH);
}

void AddPage::OnTagTextChange(wxCommandEvent& _) {
    wxString text = this->tagInput->GetValue();
    bool isValid = !text.IsEmpty() && text.length() <= MAX_TAG_LENGTH && this->tagList->GetCount() <= MAX_TAGS;

    this->tagButton->Enable(isValid);

    SetBackgroundColourBasedOnLength(this->tagInput, MAX_TAG_LENGTH);
}

void AddPage::OnTagButtonClick(wxCommandEvent& event) {
    wxString tag = this->tagInput->GetValue().Trim().Trim(false);

    // 태그에 공백이 포함된 경우 경고
    if (tag.Contains(" ")) {
        wxLogMessage("태그에 공백을 포함할 수 없습니다");
        return;  // 함수 종료
    }

    // 먼저 태그의 중복 여부를 검사
    if (!(this->tags.insert(tag).second)) {
        wxLogMessage("중복된 태그입니다");
        return;  // 중복된 태그인 경우 추가 로직을 수행하지 않고 함수를 종료
    }

    // 중복되지 않은 경우, 태그 리스트에 추가
    this->tagList->Append(tag);
    this->tagInput->Clear(); // 입력 필드 초기화
    this->tagInput->SetFocus(); // 포커스 재설정
}

void AddPage::OnBodyTextChange(wxCommandEvent& _) {
    wxString text = bodyInput->GetValue();
    SetBackgroundColourBasedOnLength(bodyInput, MAX_BODY_LENGTH);
}

void AddPage::OnClickConfirm(wxCommandEvent& event) {
    // 확인 버튼 클릭 시 수행할 작업
    wxLogMessage("저장 버튼 클릭");
}

void AddPage::SetBackgroundColourBasedOnLength(wxTextCtrl* input, size_t max_length) {
    wxString text = input->GetValue();
    bool isTooLong = text.length() > max_length;

    input->SetBackgroundColour(isTooLong ? LIGHT_RED : DEFAULT_BG_COLOR);
    input->Refresh();
}
