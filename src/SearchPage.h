#ifndef PICTURE_WITH_TAG_SEARCHPAGE_H
#define PICTURE_WITH_TAG_SEARCHPAGE_H

#include "BasePage.h"

class SearchPage : public BasePage {
public:
    SearchPage(const wxString& title, const wxPoint& pos, const wxSize& size, const PageID currentPage);

protected:
    void InitUI() override;

private:
    void OnTitleTextChange(wxCommandEvent& _);
    void OnArticleSelected(wxCommandEvent& _);
    void OnSearchConfirm(wxCommandEvent& _);

    wxTextCtrl* searchInput;
    wxListBox* articleList;
    wxChoice* searchCondition;
    wxButton* searchButton;
    wxTextCtrl* tagView;
    wxStaticBitmap* pictureDisplay;

    // Label constants
    static constexpr char SEARCH_LABEL_TEXT[] = "검색";
    static constexpr int SEARCH_LABEL_X = 20;
    static constexpr int SEARCH_LABEL_Y = 25;
    static constexpr int SEARCH_INPUT_X = 60;
    static constexpr int SEARCH_INPUT_Y = 20;
    static constexpr int SEARCH_INPUT_FIELD_WIDTH = 750;
    static constexpr int INPUT_FIELD_HEIGHT = 25;

    // ListBox constants
    static constexpr int LISTBOX_X = 1185;
    static constexpr int LISTBOX_Y = 18;
    static constexpr int LISTBOX_WIDTH = 230;
    static constexpr int LISTBOX_HEIGHT = 600;

    // Search condition dropdown and button positioning
    static constexpr char SEARCH_OPTION_TITLE[] = "제목";
    static constexpr char SEARCH_OPTION_TAG[] = "태그";
    static constexpr int SEARCH_CONDITION_OFFSET = 12; // Offset from the end of the input field
    static constexpr int SEARCH_CONDITION_TOP_OFFSET = 2; // Vertical alignment offset
    static constexpr int SEARCH_BUTTON_OFFSET = 80; // Offset for button from the condition dropdown
    static constexpr int SEARCH_BUTTON_TOP_OFFSET = -6; // Vertical alignment offset for button

    // 태그
    static constexpr char TAG_LABEL_TEXT[] = "태그";
    static constexpr int TITLE_LABEL_X = 20;
    static constexpr int TITLE_LABEL_Y = 25;
    static constexpr int TITLE_INPUT_X = 60;
    static constexpr int TITLE_INPUT_Y = 20;
    static constexpr int TAG_INPUT_FIELD_WIDTH = 1055;
    static constexpr int TAG_INPUT_Y_OFFSET = 50;

    // 사진
    static constexpr int PHOTO_DISPLAY_X = 18;
    static constexpr int PHOTO_DISPLAY_Y = 122;
    static constexpr int MAX_IMAGE_WIDTH = 940;
    static constexpr int MAX_IMAGE_HEIGHT = 480;
};

#endif //PICTURE_WITH_TAG_SEARCHPAGE_H
