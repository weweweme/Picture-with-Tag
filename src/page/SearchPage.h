#ifndef PICTURE_WITH_TAG_SEARCHPAGE_H
#define PICTURE_WITH_TAG_SEARCHPAGE_H

#include "BasePage.h"
#include "../data/DataItem.h"

class SearchPage : public BasePage {
public:
    SearchPage(const wxString& title, const wxPoint& pos, const wxSize& size, const PageID currentPage);

protected:
    void InitUI() override;

private:
    void OnArticleSelected(wxCommandEvent& _);
    void OnSearchConfirm(wxCommandEvent& _);
    void OnClickReset(wxCommandEvent& _);
    void OnClickDataSave(wxCommandEvent& _);
    void OnClickFolderDir(wxCommandEvent& _);

    wxTextCtrl* searchInput{};
    wxListBox* articleList{};
    wxChoice* searchCondition{};
    wxButton* searchButton{};
    wxButton* saveButton{};
    wxTextCtrl* tagView{};
    wxTextCtrl* bodyView{};
    wxStaticBitmap* pictureDisplay{};
    std::vector<DataItem> searchResults;
};

#endif //PICTURE_WITH_TAG_SEARCHPAGE_H
