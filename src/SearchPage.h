#ifndef PICTURE_WITH_TAG_SEARCHPAGE_H
#define PICTURE_WITH_TAG_SEARCHPAGE_H

#include "BasePage.h"

class SearchPage : public BasePage {
public:
    SearchPage(const wxString& title, const wxPoint& pos, const wxSize& size, const PageID currentPage);
    void SetupPage() override;
};

#endif //PICTURE_WITH_TAG_SEARCHPAGE_H
