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
    void OnTagTextChange(wxCommandEvent& event);
    void OnTagButtonClick(wxCommandEvent& event);

    wxTextCtrl* titleInput{};
    wxTextCtrl* tagInput{};
    wxButton* tagButton{};
    wxListBox* tagList{};
    std::set<wxString> tags;
};

#endif // PICTURE_WITH_TAG_ADDPAGE_H
