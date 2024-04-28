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

    wxTextCtrl* searchInput;

    static constexpr char SEARCH_LABEL_TEXT[] = "검색";
    static constexpr int SEARCH_LABEL_X = 20;
    static constexpr int SEARCH_LABEL_Y = 25;
    static constexpr int SEARCH_INPUT_X = 60;
    static constexpr int SEARCH_INPUT_Y = 20;
    static constexpr int SEARCH_INPUT_FIELD_WIDTH = 700;
    static constexpr int INPUT_FIELD_HEIGHT = 25;
};

#endif //PICTURE_WITH_TAG_SEARCHPAGE_H
