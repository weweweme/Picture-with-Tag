#include "AddPage.h"

constexpr char CONFIRM_BUTTON_LABEL[] = "저장";
constexpr int CONFIRM_BUTTON_Y = 600;
constexpr int INPUT_FIELD_WIDTH = 900;
constexpr int INPUT_FIELD_HEIGHT = 25;

const wxColour LIGHT_RED(255, 204, 204);
const wxColour DEFAULT_BG_COLOR(*wxWHITE);
constexpr int TITLE_LABEL_X = 20;
constexpr int TITLE_LABEL_Y = 25;
constexpr int TITLE_INPUT_X = 60;
constexpr int TITLE_INPUT_Y = 20;
constexpr char TITLE_LABEL_TEXT[] = "제목";
constexpr size_t MAX_TITLE_LENGTH = 32;

AddPage::AddPage(const wxString& title, const wxPoint& pos, const wxSize& size, const PageID currentPage)
        : BasePage(title, pos, size, currentPage) {
    AddPage::InitUI();
}

void AddPage::InitUI() {
    BasePage::InitUI();

    // 제목 입력 필드 추가
    auto* titleLabel = new wxStaticText(panel, wxID_ANY, TITLE_LABEL_TEXT, wxPoint(TITLE_LABEL_X, TITLE_LABEL_Y));
    auto* titleInput = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(TITLE_INPUT_X, TITLE_INPUT_Y), wxSize(INPUT_FIELD_WIDTH, INPUT_FIELD_HEIGHT));
    titleInput->Bind(wxEVT_TEXT, &AddPage::OnTitleTextChange);

    auto* backButton = new wxButton(panel, wxID_ANY, CONFIRM_BUTTON_LABEL, wxPoint(RIGHT_BUTTON_X, CONFIRM_BUTTON_Y), buttonSize);
    backButton->Bind(wxEVT_BUTTON, &AddPage::OnClickConfirm, this);
}

void AddPage::OnTitleTextChange(wxCommandEvent& event) {
    auto* titleInput = dynamic_cast<wxTextCtrl*>(event.GetEventObject());
    wxString text = titleInput->GetValue();
    if (text.length() > MAX_TITLE_LENGTH) {
        titleInput->SetBackgroundColour(LIGHT_RED); // Light red background
        titleInput->Refresh();
    } else {
        titleInput->SetBackgroundColour(DEFAULT_BG_COLOR); // Reset to white background
        titleInput->Refresh();
    }
}

void AddPage::OnClickConfirm(wxCommandEvent &_) {

}
