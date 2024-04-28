#include "AddPage.h"
#include "DataItem.h"
#include "GlobalColors.h"
#include "UIHelpers.h"
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <fstream>
#include <boost/archive/text_oarchive.hpp>

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
    this->tagList->Bind(wxEVT_LISTBOX, &AddPage::OnTagSelected, this);

    // 태그 삭제 버튼 초기화
    this->deleteTagButton = new wxButton(this->panel, wxID_ANY, _("-"), wxDefaultPosition, wxSize(20, BUTTON_HEIGHT));
    this->deleteTagButton->Bind(wxEVT_BUTTON, &AddPage::OnDeleteTagButtonClick, this);
    this->deleteTagButton->Hide();  // 초기에 비활성화

    // 본문 텍스트 입력 필드
    auto* bodyLabel = new wxStaticText(this->panel, wxID_ANY, BODY_LABEL_TEXT, wxPoint(BODY_LABEL_X, BODY_LABEL_Y));
    this->bodyInput = new wxTextCtrl(this->panel, wxID_ANY, "", wxPoint(BODY_INPUT_X, BODY_INPUT_Y), wxSize(BODY_TEXT_WIDTH, BODY_TEXT_HEIGHT), wxTE_MULTILINE);
    this->bodyInput->Bind(wxEVT_TEXT, &AddPage::OnBodyTextChange, this);

    // photoDisplay 정적 비트맵 설정
    this->photoDisplay = new wxStaticBitmap(this->panel, wxID_ANY, wxNullBitmap, wxPoint(PHOTO_DISPLAY_X, PHOTO_DISPLAY_Y), wxSize(MAX_IMAGE_WIDTH, MAX_IMAGE_HEIGHT));

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

    // 초기화 버튼
    auto* resetButton = new wxButton(this->panel, wxID_ANY, CLEAR_BUTTON_TEXT, wxPoint(RIGHT_BUTTON_X, CLEAR_BUTTON_Y), defaultButtonSize);
    resetButton->Bind(wxEVT_BUTTON, &AddPage::OnResetButtonClick, this);

    // 확인 버튼
    this->confirmButton = new wxButton(this->panel, wxID_ANY, CONFIRM_BUTTON_LABEL, wxPoint(RIGHT_BUTTON_X, CONFIRM_BUTTON_Y), defaultButtonSize);
    this->confirmButton->Bind(wxEVT_BUTTON, &AddPage::OnClickConfirm, this);

    // 패널의 클릭 이벤트를 바인딩합니다.
    this->panel->Bind(wxEVT_LEFT_DOWN, &AddPage::OnPanelClick, this);
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

void AddPage::OnTagButtonClick(wxCommandEvent& _) {
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

void AddPage::OnTagSelected(wxCommandEvent& event) {
    int selection = this->tagList->GetSelection();
    int itemHeight = LISTBOX_Y;  // 예상 아이템 높이
    int itemTop = itemHeight * selection;  // 선택된 항목의 상단 위치 계산
    this->deleteTagButton->SetPosition(wxPoint(DELETE_BUTTON_OFFSET_X, itemTop + DELETE_BUTTON_OFFSET_Y));
    this->deleteTagButton->Show();
}


void AddPage::OnDeleteTagButtonClick(wxCommandEvent& _) {
    int selection = this->tagList->GetSelection();

    wxString tag = this->tagList->GetString(selection);  // 선택된 태그의 문자열 가져오기
    bool shouldDelete = wxMessageBox(_("선택한 태그를 정말로 삭제하시겠습니까?"), _("태그 삭제 확인"), wxYES_NO | wxICON_WARNING) == wxYES;

    if (shouldDelete) {
        this->tags.erase(tag);
        this->tagList->Delete(selection);
        this->deleteTagButton->Hide();
    }
}


void AddPage::OnBodyTextChange(wxCommandEvent& _) {
    wxString text = bodyInput->GetValue();
    SetBackgroundColourBasedOnLength(bodyInput, MAX_BODY_LENGTH);
}

void AddPage::OnAddPhoto(wxCommandEvent& _) {
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

void AddPage::OnRemovePhoto(wxCommandEvent& _) {
    // 사진 제거 로직
    this->removePhotoButton->Hide();
    this->photoDisplay->SetBitmap(wxNullBitmap);
    this->addPhotoButton->Show();
    this->photoDisplay->Refresh();
}

void AddPage::OnResetButtonClick(wxCommandEvent& _) {
    if (wxMessageBox(_("정말로 모든 정보를 초기화하시겠습니까?"), _("경고"), wxICON_WARNING | wxYES_NO | wxNO_DEFAULT) == wxYES) {
        this->titleInput->Clear();
        this->tagInput->Clear();
        this->tagList->Clear();
        this->bodyInput->Clear();
        this->photoDisplay->SetBitmap(wxNullBitmap);
        this->addPhotoButton->Show();
        this->removePhotoButton->Hide();
        this->panel->Refresh();
    }
}

void AddPage::OnPanelClick(wxMouseEvent& event) {
    wxPoint pt = event.GetPosition();
    // 패널 클릭 위치가 ListBox 범위 내에 없을 경우
    if (!this->tagList->GetRect().Contains(pt)) {
        this->tagList->SetSelection(wxNOT_FOUND);  // 선택 취소
        this->deleteTagButton->Hide();  // 삭제 버튼 숨기기
    }

    event.Skip();
}

void AddPage::OnClickConfirm(wxCommandEvent& _) {
    bool inputValid = true;
    wxString validationMessage = _("유효한 값을 입력해주세요:");

    // 입력 데이터 수집
    wxString title = this->titleInput->GetValue();
    wxString body = this->bodyInput->GetValue();
    wxBitmap bitmap = this->photoDisplay->GetBitmap();

    // 태그 집합 생성
    std::set<wxString> tags;
    for (unsigned int i = 0; i < this->tagList->GetCount(); ++i) {
        tags.insert(this->tagList->GetString(i));
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
    if (tags.empty()) {
        validationMessage += _("\n- 태그가 최소 1개 이상 등록되어야 합니다.");
        inputValid = false;
    }

    // 입력 검증에 실패한 경우 함수를 조기 종료하고 메시지를 로그로 출력
    if (!inputValid) {
        wxLogMessage(validationMessage);
        return;
    }

    // DataItem 객체 생성
    wxImage image = bitmap.ConvertToImage();
    DataItem newItem(title, tags, body, image);

    // 파일 경로 설정
    wxString docDir = wxStandardPaths::Get().GetDocumentsDir();
    wxString targetDir = docDir + "/Picture-with-Tag";
    if (!wxDirExists(targetDir)) {
        wxMkdir(targetDir);
    }
    wxString filePath = targetDir + "/" + title + ".pwt";

    // 데이터 직렬화 및 파일 저장
    std::ofstream ofs(filePath.ToStdString(), std::ios::binary);
    boost::archive::text_oarchive oa(ofs);
    oa << newItem;

    wxLogMessage(_("데이터가 성공적으로 저장되었습니다."));
}

void AddPage::SetBackgroundColourBasedOnLength(wxTextCtrl* input, size_t max_length) {
    wxString text = input->GetValue();
    bool isTooLong = text.length() > max_length;
    wxColour backgroundColour = isTooLong ? LIGHT_RED : DEFAULT_BG_COLOR;

    UIHelpers::SetControlColours(input, backgroundColour, GlobalColors::textColour);
    input->Refresh();
}
