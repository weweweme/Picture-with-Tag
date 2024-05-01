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
    wxButton* confirmButton;
    wxStaticBitmap* photoDisplay;
};

#endif // PICTURE_WITH_TAG_ADDPAGE_H
