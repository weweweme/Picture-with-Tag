#ifndef PICTURE_WITH_TAG_ADDPAGE_H
#define PICTURE_WITH_TAG_ADDPAGE_H

#include "BasePage.h"
#include <set>

class AddPage : public BasePage {
public:
    AddPage(const wxString& title, const wxPoint& pos, const wxSize& size, const PageID currentPage);

protected:
    void InitUI() override;

private:
    static void SetBackgroundColourBasedOnLength(wxTextCtrl* input, size_t max_length);
    void OnClickConfirm(wxCommandEvent& _);
    void OnTitleTextChange(wxCommandEvent& _);
    void OnTagTextChange(wxCommandEvent& _);
    void OnTagButtonClick(wxCommandEvent& _);
    void OnTagSelected(wxCommandEvent& _);
    void OnDeleteTagButtonClick(wxCommandEvent& _);
    void OnBodyTextChange(wxCommandEvent& _);
    void OnAddPhoto(wxCommandEvent& _);
    void OnRemovePhoto(wxCommandEvent& _);
    void OnMouseEnterPhoto(wxMouseEvent& event);
    void OnMouseLeavePhoto(wxMouseEvent& event);
    void UpdatePhotoDisplay(const wxString& path);
    void OnResetButtonClick(wxCommandEvent& _);
    void OnPanelClick(wxMouseEvent& event);

    wxTextCtrl* titleInput;
    wxTextCtrl* tagInput;
    wxButton* tagButton;
    wxListBox* tagList;
    wxButton* deleteTagButton;
    std::set<wxString> tags;
    wxTextCtrl* bodyInput;
    wxButton* addPhotoButton;
    wxButton* removePhotoButton;
    wxStaticBitmap* photoDisplay;

    static constexpr char CONFIRM_BUTTON_LABEL[] = "저장";
    static constexpr int CONFIRM_BUTTON_Y = 640;
    static constexpr int CLEAR_BUTTON_Y = 680;
    static constexpr int INPUT_FIELD_HEIGHT = 25;
    static constexpr int TITLE_INPUT_FIELD_WIDTH = 900;
    static constexpr int TITLE_LABEL_X = 20;
    static constexpr int TITLE_LABEL_Y = 25;
    static constexpr int TITLE_INPUT_X = 60;
    static constexpr int TITLE_INPUT_Y = 20;
    static constexpr char TITLE_LABEL_TEXT[] = "제목";
    static constexpr size_t MAX_TITLE_LENGTH = 32;
    static constexpr int TAG_BUTTON_WIDTH = 100;
    static constexpr int TAG_INPUT_FIELD_WIDTH = 780;
    static constexpr int TAG_BUTTON_X_OFFSET = 78;
    static constexpr int TAG_INPUT_Y_OFFSET = 50;
    static constexpr char TAG_LABEL_TEXT[] = "태그";
    static constexpr char TAG_BUTTON_TEXT[] = "태그 추가";
    static constexpr size_t MAX_TAGS = 32;
    static constexpr size_t MAX_TAG_LENGTH = 16;
    static constexpr int BODY_TEXT_WIDTH = 900;
    static constexpr int BODY_TEXT_HEIGHT = 130;
    static constexpr int BODY_LABEL_X = 20;
    static constexpr int BODY_LABEL_Y = 690;
    static constexpr int BODY_INPUT_X = 60;
    static constexpr int BODY_INPUT_Y = 630;
    static constexpr char BODY_LABEL_TEXT[] = "본문";
    static constexpr size_t MAX_BODY_LENGTH = 256;
    static constexpr int PHOTO_DISPLAY_X = 18;
    static constexpr int PHOTO_DISPLAY_Y = 122;
    static constexpr int BUTTON_WIDTH = 100;
    static constexpr int BUTTON_HEIGHT = 50;
    static constexpr int MAX_IMAGE_WIDTH = 940;
    static constexpr int MAX_IMAGE_HEIGHT = 480;
    static constexpr int LISTBOX_X = 1185;
    static constexpr int LISTBOX_Y = 18;
    static constexpr int LISTBOX_WIDTH = 230;
    static constexpr int LISTBOX_HEIGHT = 600;
    static constexpr int DELETE_BUTTON_OFFSET_X = LISTBOX_X + LISTBOX_WIDTH - 30;
    static constexpr int DELETE_BUTTON_OFFSET_Y = 14;
    static constexpr char CLEAR_BUTTON_TEXT[] = "초기화";
    static constexpr char TAG_DUPLICATE_TEXT[] = "중복된 태그입니다";
    static constexpr char TAG_SPACE_IN_TEXT[] = "태그에 공백을 포함할 수 없습니다";
    static constexpr char SAVING_BUTTON_CLICK[] = "저장 버튼 클릭";
    static constexpr char PHOTO_ADD_TEXT[] = "사진 추가";
    static constexpr char PHOTO_REMOVE_TEXT[] = "사진 제거";
    static constexpr char SELECT_PHOTO_TEXT[] = "사진 선택";
    static constexpr char IMAGE_LOAD_FAIL_TEXT[] = "이미지 파일을 로드할 수 없습니다.";
    static constexpr char FILE_DIALOG_FILTER[] = "JPEG files (*.jpg)|*.jpg|PNG files (*.png)|*.png";
};

#endif // PICTURE_WITH_TAG_ADDPAGE_H
