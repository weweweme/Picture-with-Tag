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

    wxTextCtrl* searchInput;
    wxListBox* articleList;

    static constexpr char SEARCH_LABEL_TEXT[] = "검색";
    static constexpr int SEARCH_LABEL_X = 20;
    static constexpr int SEARCH_LABEL_Y = 25;
    static constexpr int SEARCH_INPUT_X = 60;
    static constexpr int SEARCH_INPUT_Y = 20;
    static constexpr int SEARCH_INPUT_FIELD_WIDTH = 700;
    static constexpr int INPUT_FIELD_HEIGHT = 25;
    static constexpr int LISTBOX_X = 1185;
    static constexpr int LISTBOX_Y = 18;
    static constexpr int LISTBOX_WIDTH = 230;
    static constexpr int LISTBOX_HEIGHT = 600;
};

#endif //PICTURE_WITH_TAG_SEARCHPAGE_H
