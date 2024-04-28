#include "AddPage.h"

static const wxColour LIGHT_RED(255, 204, 204);
static const wxColour DEFAULT_BG_COLOR(*wxWHITE);

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

    // photoDisplay 정적 비트맵 설정
    this->photoDisplay = new wxStaticBitmap(this->panel, wxID_ANY, wxNullBitmap, wxPoint(PHOTO_DISPLAY_X, PHOTO_DISPLAY_Y), wxSize(MAX_IMAGE_WIDTH, MAX_IMAGE_HEIGHT));
    this->photoDisplay->SetBackgroundColour(*wxWHITE);

    // 사진 추가 버튼 초기화
    int centerX = (MAX_IMAGE_WIDTH - BUTTON_WIDTH) / 2;
    int centerY = (MAX_IMAGE_HEIGHT - BUTTON_HEIGHT) / 2;
    this->addPhotoButton = new wxButton(this->photoDisplay, wxID_ANY, PHOTO_ADD_TEXT, wxPoint(centerX, centerY), wxSize(BUTTON_WIDTH, BUTTON_HEIGHT));
    this->addPhotoButton->Bind(wxEVT_BUTTON, &AddPage::OnAddPhoto, this);

    // 사진 제거 버튼 추가
    this->removePhotoButton = new wxButton(this->photoDisplay, wxID_ANY, PHOTO_REMOVE_TEXT, wxPoint(centerX, centerY), wxSize(BUTTON_WIDTH, BUTTON_HEIGHT));
    this->removePhotoButton->Bind(wxEVT_BUTTON, &AddPage::OnRemovePhoto, this);
    this->removePhotoButton->Hide();  // 초기에는 숨김

    // 마우스 이벤트 바인딩
    this->photoDisplay->Bind(wxEVT_ENTER_WINDOW, &AddPage::OnMouseEnterPhoto, this);
    this->photoDisplay->Bind(wxEVT_LEAVE_WINDOW, &AddPage::OnMouseLeavePhoto, this);

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
        wxLogMessage(TAG_SPACE_IN_TEXT);
        return;
    }

    // 먼저 태그의 중복 여부를 검사
    if (!(this->tags.insert(tag).second)) {
        wxLogMessage(TAG_DUPLICATE_TEXT);
        return;
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

void AddPage::OnAddPhoto(wxCommandEvent& event) {
    wxFileDialog openFileDialog(this, _(SELECT_PHOTO_TEXT), "", "", _(FILE_DIALOG_FILTER), wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;

    wxString path = openFileDialog.GetPath();
    UpdatePhotoDisplay(path);
}

void AddPage::UpdatePhotoDisplay(const wxString& path) {
    wxImage image;
    if (!image.LoadFile(path, wxBITMAP_TYPE_ANY)) {
        wxLogMessage(_(IMAGE_LOAD_FAIL_TEXT));
        return;
    }

    if (image.GetWidth() > MAX_IMAGE_WIDTH || image.GetHeight() > MAX_IMAGE_HEIGHT) {
        image.Rescale(MAX_IMAGE_WIDTH, MAX_IMAGE_HEIGHT, wxIMAGE_QUALITY_HIGH);
    }

    this->photoDisplay->SetBitmap(wxBitmap(image));
    this->addPhotoButton->Hide();
    this->panel->Refresh();
    this->photoDisplay->Refresh();
}

void AddPage::OnMouseEnterPhoto(wxMouseEvent& event) {
    if (this->photoDisplay->GetBitmap().IsOk()) {  // Check if photoDisplay has a valid bitmap
        this->removePhotoButton->Show();
        this->photoDisplay->Refresh();
    }
    event.Skip();
}

void AddPage::OnMouseLeavePhoto(wxMouseEvent& event) {
    this->removePhotoButton->Hide();
    this->panel->Refresh();
    event.Skip();
}

void AddPage::OnRemovePhoto(wxCommandEvent& event) {
    // 사진 제거 로직
    this->removePhotoButton->Hide();
    this->photoDisplay->SetBitmap(wxNullBitmap);
    this->addPhotoButton->Show();
    this->photoDisplay->Refresh();
}

void AddPage::OnClickConfirm(wxCommandEvent& event) {
    wxLogMessage(_(SAVING_BUTTON_CLICK));
}

void AddPage::SetBackgroundColourBasedOnLength(wxTextCtrl* input, size_t max_length) {
    wxString text = input->GetValue();
    bool isTooLong = text.length() > max_length;

    input->SetBackgroundColour(isTooLong ? LIGHT_RED : DEFAULT_BG_COLOR);
    input->Refresh();
}
