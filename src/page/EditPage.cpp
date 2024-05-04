#include "EditPage.h"
#include "../helper/GlobalColors.h"
#include "../helper/UIHelpers.h"
#include "../helper/Constants.h"
#include "../data/DataManager.h"
#include <wx/filename.h>
#include <fstream>

EditPage::EditPage(const wxString& title, const wxPoint& pos, const wxSize& size, const PageID currentPage)
        : BasePage(title, pos, size, currentPage) {
    EditPage::InitUI();
}

void EditPage::InitUI() {
    BasePage::InitUI();

    // 제목 입력 필드
    UIHelpers::CreateStaticText(this->panel, TITLE_LABEL_TEXT, wxPoint(TITLE_LABEL_X, TITLE_LABEL_Y), wxDefaultSize);
    this->titleInput = UIHelpers::CreateTextCtrl(this->panel, "", wxPoint(TITLE_INPUT_X, TITLE_INPUT_Y), wxSize(TITLE_INPUT_FIELD_WIDTH, INPUT_FIELD_HEIGHT), 0);
    this->titleInput->Bind(wxEVT_TEXT, &EditPage::OnTitleTextChange, this);

    // 태그 입력 필드
    UIHelpers::CreateStaticText(this->panel, TAG_LABEL_TEXT, wxPoint(TITLE_LABEL_X, TITLE_LABEL_Y + TAG_INPUT_Y_OFFSET), wxDefaultSize);
    this->tagInput = UIHelpers::CreateTextCtrl(this->panel, "", wxPoint(TITLE_INPUT_X, TITLE_INPUT_Y + TAG_INPUT_Y_OFFSET), wxSize(TAG_INPUT_FIELD_WIDTH, INPUT_FIELD_HEIGHT), 0);
    this->tagInput->Bind(wxEVT_TEXT, &EditPage::OnTagTextChange, this);

    // 태그 입력 버튼
    this->tagButton = UIHelpers::CreateButton(this->panel, TAG_BUTTON_TEXT, wxPoint(TAG_INPUT_FIELD_WIDTH + TAG_BUTTON_X_OFFSET, TITLE_INPUT_Y + TAG_INPUT_Y_OFFSET), wxSize(TAG_BUTTON_WIDTH, INPUT_FIELD_HEIGHT), 0);
    this->tagButton->Bind(wxEVT_BUTTON, &EditPage::OnTagButtonClick, this);
    this->tagButton->Enable(false);

    // 태그 리스트 박스 초기화
    this->tagList = UIHelpers::CreateListBox(this->panel, wxPoint(LISTBOX_X, LISTBOX_Y), wxSize(LISTBOX_WIDTH, LISTBOX_HEIGHT), wxLB_MULTIPLE);
    this->tagList->Bind(wxEVT_LISTBOX, &EditPage::OnTagSelected, this);

    // 태그 삭제 버튼 초기화
    this->deleteTagButton = UIHelpers::CreateButton(this->panel, _("-"), wxDefaultPosition, wxSize(20, BUTTON_HEIGHT), 0);
    this->deleteTagButton->Bind(wxEVT_BUTTON, &EditPage::OnDeleteTagButtonClick, this);
    this->deleteTagButton->Hide();

    // 본문 텍스트 입력 필드
    UIHelpers::CreateStaticText(this->panel, BODY_LABEL_TEXT, wxPoint(BODY_LABEL_X, BODY_LABEL_Y), wxDefaultSize);
    this->bodyInput = UIHelpers::CreateTextCtrl(this->panel, "", wxPoint(BODY_INPUT_X, BODY_INPUT_Y), wxSize(BODY_TEXT_WIDTH, BODY_TEXT_HEIGHT), wxTE_MULTILINE);
    this->bodyInput->Bind(wxEVT_TEXT, &EditPage::OnBodyTextChange, this);

    // pictureDisplay 정적 비트맵 설정
    this->pictureDisplay = new wxStaticBitmap(this->panel, wxID_ANY, wxNullBitmap, wxPoint(PICTURE_DISPLAY_X, PICTURE_DISPLAY_Y), wxSize(MAX_IMAGE_WIDTH, MAX_IMAGE_HEIGHT));

    // 사진 추가 및 제거 버튼 초기화
    int centerX = (MAX_IMAGE_WIDTH - ADD_PAGE_BUTTON_WIDTH) / 2;
    int centerY = (MAX_IMAGE_HEIGHT - ADD_PAGE_BUTTON_HEIGHT) / 2;
    this->addPictureButton = UIHelpers::CreateButton(this->pictureDisplay, PICTURE_ADD_TEXT, wxPoint(centerX, centerY), wxSize(ADD_PAGE_BUTTON_WIDTH, ADD_PAGE_BUTTON_HEIGHT), 0);
    this->addPictureButton->Bind(wxEVT_BUTTON, &EditPage::OnAddPhoto, this);

    this->removePictureButton = UIHelpers::CreateButton(this->pictureDisplay, PICTURE_REMOVE_TEXT, wxPoint(centerX, centerY), wxSize(ADD_PAGE_BUTTON_WIDTH, ADD_PAGE_BUTTON_HEIGHT), 0);
    this->removePictureButton->Bind(wxEVT_BUTTON, &EditPage::OnRemovePicture, this);
    this->removePictureButton->Hide();

    // 마우스 이벤트 바인딩
    this->pictureDisplay->Bind(wxEVT_ENTER_WINDOW, &EditPage::OnMouseEnterPhoto, this);
    this->pictureDisplay->Bind(wxEVT_LEAVE_WINDOW, &EditPage::OnMouseLeavePhoto, this);

    // 초기화 및 확인 버튼
    auto* resetButton = UIHelpers::CreateButton(this->panel, CLEAR_BUTTON_TEXT, wxPoint(RIGHT_BUTTON_X, CLEAR_BUTTON_Y), defaultButtonSize, 0);
    resetButton->Bind(wxEVT_BUTTON, &EditPage::OnResetButtonClick, this);

    this->confirmButton = UIHelpers::CreateButton(this->panel, CONFIRM_BUTTON_LABEL, wxPoint(RIGHT_BUTTON_X, CONFIRM_BUTTON_Y), defaultButtonSize, 0);
    this->confirmButton->Bind(wxEVT_BUTTON, &EditPage::OnClickConfirm, this);

    // 패널 클릭 이벤트
    this->panel->Bind(wxEVT_LEFT_DOWN, &EditPage::OnPanelClick, this);
}

void EditPage::OnTitleTextChange(wxCommandEvent& _) {
    SetBackgroundColourBasedOnLength(this->titleInput, MAX_TITLE_LENGTH);
}

void EditPage::OnTagTextChange(wxCommandEvent& _) {
    wxString text = this->tagInput->GetValue();
    bool isValid = !text.IsEmpty() && text.length() <= MAX_TAG_LENGTH && this->tagList->GetCount() <= MAX_TAGS;

    this->tagButton->Enable(isValid);

    SetBackgroundColourBasedOnLength(this->tagInput, MAX_TAG_LENGTH);
}

void EditPage::OnTagButtonClick(wxCommandEvent& _) {
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

void EditPage::OnTagSelected(wxCommandEvent& event) {
    int selection = this->tagList->GetSelection();
    int itemHeight = LISTBOX_Y;  // 예상 아이템 높이
    int itemTop = itemHeight * selection;  // 선택된 항목의 상단 위치 계산
    this->deleteTagButton->SetPosition(wxPoint(DELETE_BUTTON_OFFSET_X, itemTop + DELETE_BUTTON_OFFSET_Y));
    this->deleteTagButton->Show();
}

void EditPage::OnDeleteTagButtonClick(wxCommandEvent& _) {
    int selection = this->tagList->GetSelection();

    wxString tag = this->tagList->GetString(selection);  // 선택된 태그의 문자열 가져오기
    bool shouldDelete = wxMessageBox(_(DIALOGUE_CONFIRM_DELETE), _(DIALOGUE_TITLE_DELETE), wxYES_NO | wxICON_WARNING) == wxYES;

    if (shouldDelete) {
        this->tags.erase(tag);
        this->tagList->Delete(selection);
        this->deleteTagButton->Hide();
    }
}

void EditPage::OnBodyTextChange(wxCommandEvent& _) {
    wxString text = bodyInput->GetValue();
    SetBackgroundColourBasedOnLength(bodyInput, MAX_BODY_LENGTH);
}

void EditPage::OnAddPhoto(wxCommandEvent& _) {
    wxFileDialog openFileDialog(this, _(SELECT_PHOTO_TEXT), "", "", _(FILE_DIALOG_FILTER), wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;

    wxString path = openFileDialog.GetPath();
    UpdatePictureDisplay(path);
}

void EditPage::UpdatePictureDisplay(const wxString& path) {
    wxImage image;
    if (!image.LoadFile(path, wxBITMAP_TYPE_ANY)) {
        wxLogMessage(_(ERROR_MESSAGE_LOAD_FAIL));
        return;
    }

    DisplayImage(image);
}

void EditPage::OnMouseEnterPhoto(wxMouseEvent& event) {
    if (this->pictureDisplay->GetBitmap().IsOk()) {  // Check if pictureDisplay has a valid bitmap
        this->removePictureButton->Show();
        this->pictureDisplay->Refresh();
    }
    event.Skip();
}

void EditPage::OnMouseLeavePhoto(wxMouseEvent& event) {
    this->removePictureButton->Hide();
    this->panel->Refresh();
    event.Skip();
}

void EditPage::OnRemovePicture(wxCommandEvent& _) {
    // 사진 제거 로직
    this->removePictureButton->Hide();
    this->pictureDisplay->SetBitmap(wxNullBitmap);
    this->addPictureButton->Show();
    this->pictureDisplay->Refresh();
}

void EditPage::OnResetButtonClick(wxCommandEvent& _) {
    if (wxMessageBox(_(DIALOGUE_TITLE_RESET), _(DIALOGUE_WARNING_RESET), wxICON_WARNING | wxYES_NO | wxNO_DEFAULT) == wxYES) {
        Clear();
    }
}

void EditPage::OnPanelClick(wxMouseEvent& event) {
    wxPoint pt = event.GetPosition();
    // 패널 클릭 위치가 ListBox 범위 내에 없을 경우
    if (!this->tagList->GetRect().Contains(pt)) {
        this->tagList->SetSelection(wxNOT_FOUND);  // 선택 취소
        this->deleteTagButton->Hide();  // 삭제 버튼 숨기기
    }

    event.Skip();
}

void EditPage::OnClickConfirm(wxCommandEvent& _) {
    bool inputValid = true;
    wxString validationMessage = _(_(SUCCESS_MESSAGE_DATA_SAVED));

    // 입력 데이터 수집
    wxString title = this->titleInput->GetValue();
    wxString body = this->bodyInput->GetValue();
    wxBitmap bitmap = this->pictureDisplay->GetBitmap();

    // 태그 집합 생성
    std::set<wxString> set;
    for (unsigned int i = 0; i < this->tagList->GetCount(); ++i) {
        set.insert(this->tagList->GetString(i));
    }

    // 1. 제목 검증
    if (title.IsEmpty()) {
        validationMessage += _("\n- 제목을 입력해야 합니다.");
        inputValid = false;
    }

    // 2. 이미지 검증
    if (!bitmap.IsOk()) {
        validationMessage += _("\n- 사진이 첨부되어야 합니다.");
        inputValid = false;
    }

    // 3. 태그 검증
    if (set.empty()) {
        validationMessage += _("\n- 태그가 최소 1개 이상 등록되어야 합니다.");
        inputValid = false;
    }

    // 입력 검증에 실패한 경우 함수를 조기 종료하고 메시지를 로그로 출력
    if (!inputValid) {
        wxLogMessage(validationMessage);
        return;
    }

    if (this->isEditing) {
        DataManager::DeleteDataItem(this->originalTitle); // 원본 게시물 삭제
    }

    // DataItem 객체 생성
    wxImage image = bitmap.ConvertToImage();
    DataItem newItem(title, set, body, image);
    DataManager::SaveDataItem(newItem);

    Clear();

    wxLogMessage(_(SUCCESS_MESSAGE_DATA_SAVED));
}

void EditPage::SetBackgroundColourBasedOnLength(wxTextCtrl* input, size_t max_length) {
    wxString text = input->GetValue();
    bool isTooLong = text.length() > max_length;
    wxColour backgroundColour = isTooLong ? LIGHT_RED : DEFAULT_BG_COLOR;

    UIHelpers::SetControlColours(input, backgroundColour, GlobalColors::textColour);
    input->Refresh();
}

void EditPage::DisplayDataItem(const DataItem& item) {
    this->isEditing = true; // 편집 모드 활성화
    this->originalTitle = item.title; // 원래 제목 저장

    // 제목 설정
    this->titleInput->SetValue(item.title);

    // 본문 설정
    this->bodyInput->SetValue(item.body);

    // 태그 리스트 설정
    this->tagList->Clear();  // 기존 태그 목록 클리어
    for (const auto& tag : item.tags) {
        this->tagList->Append(tag);
    }

    wxMemoryInputStream memStream(item.image_data.data(), item.image_data.size());
    wxImage image;
    if (image.LoadFile(memStream, wxBITMAP_TYPE_ANY)) {
        DisplayImage(image);
        this->removePictureButton->Show();
        this->addPictureButton->Hide();
    }

    this->pictureDisplay->Refresh();
    this->panel->Refresh();  // UI 새로고침
}

void EditPage::DisplayImage(const wxImage& originalImage) {
    wxImage resizedImage = originalImage;

    // 이미지 사이즈 조정
    if (originalImage.GetWidth() > MAX_IMAGE_WIDTH || originalImage.GetHeight() > MAX_IMAGE_HEIGHT) {
        resizedImage.Rescale(MAX_IMAGE_WIDTH, MAX_IMAGE_HEIGHT, wxIMAGE_QUALITY_HIGH);
    }

    // 이미지 설정
    this->pictureDisplay->SetBitmap(wxBitmap(resizedImage));
    this->addPictureButton->Hide();
    this->removePictureButton->Show(); // 수정된 내용은 항상 사진이 있으므로 제거 버튼을 활성화
    this->pictureDisplay->Refresh();
}

void EditPage::Clear() {
    this->titleInput->Clear();
    this->tagInput->Clear();
    this->tagList->Clear();
    this->bodyInput->Clear();
    this->pictureDisplay->SetBitmap(wxNullBitmap);
    this->addPictureButton->Show();
    this->removePictureButton->Hide();
    this->panel->Refresh();
    this->isEditing = false;
}

void EditPage::OnClickBack(wxCommandEvent &_) {
    BasePage::OnClickBack(_);

    Clear();
}
