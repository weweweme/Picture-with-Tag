#ifndef PICTURE_WITH_TAG_ADDPAGE_H
#define PICTURE_WITH_TAG_ADDPAGE_H

#include "BasePage.h"

class AddPage : public BasePage {
public:
    AddPage(const wxString& title, const wxPoint& pos, const wxSize& size, const PageID currentPage);

protected:
    void InitUI() override;

private:
    void OnClickConfirm(wxCommandEvent& _);
    static void OnTitleTextChange(wxCommandEvent& event);
};

#endif // PICTURE_WITH_TAG_ADDPAGE_H
