#ifndef PICTURE_WITH_TAG_EDITPAGE_H
#define PICTURE_WITH_TAG_EDITPAGE_H

#include "BasePage.h"
#include "../data/DataItem.h"
#include <set>

class EditPage : public BasePage {
public:
    EditPage(const wxString& title, const wxPoint& pos, const wxSize& size, const PageID currentPage);
    void DisplayDataItem(const DataItem& item);

protected:
    void InitUI() override;
    void OnClickBack(wxCommandEvent& _) override;

private:
    static void SetBackgroundColourBasedOnLength(wxTextCtrl* input, size_t max_length);
    void DisplayImage(const wxImage& originalImage);
    void OnClickConfirm(wxCommandEvent& _);
    void OnTitleTextChange(wxCommandEvent& _);
    void OnTagTextChange(wxCommandEvent& _);
    void OnTagButtonClick(wxCommandEvent& _);
    void OnTagSelected(wxCommandEvent& _);
    void OnDeleteTagButtonClick(wxCommandEvent& _);
    void OnBodyTextChange(wxCommandEvent& _);
    void OnAddPhoto(wxCommandEvent& _);
    void OnRemovePicture(wxCommandEvent& _);
    void OnMouseEnterPhoto(wxMouseEvent& event);
    void OnMouseLeavePhoto(wxMouseEvent& event);
    void UpdatePictureDisplay(const wxString& path);
    void OnResetButtonClick(wxCommandEvent& _);
    void OnPanelClick(wxMouseEvent& event);
    void Clear();

    bool isEditing{};
    wxString originalTitle; // 편집 중인 게시물의 원래 제목 저장

    wxTextCtrl* titleInput{};
    wxTextCtrl* tagInput{};
    wxButton* tagButton{};
    wxListBox* tagList{};
    wxButton* deleteTagButton{};
    std::set<wxString> tags;
    wxTextCtrl* bodyInput{};
    wxButton* addPictureButton{};
    wxButton* removePictureButton{};
    wxButton* confirmButton{};
    wxStaticBitmap* pictureDisplay{};
};

#endif // PICTURE_WITH_TAG_EDITPAGE_H
