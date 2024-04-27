#ifndef PICTURE_WITH_TAG_DATAMANAGEMENTPAGE_H
#define PICTURE_WITH_TAG_DATAMANAGEMENTPAGE_H

#include "BasePage.h"

class DataManagementPage : public BasePage {
public:
    DataManagementPage(const wxString& title, const wxPoint& pos, const wxSize& size, const PageID currentPage);
    void SetupPage() override;
};

#endif //PICTURE_WITH_TAG_DATAMANAGEMENTPAGE_H
