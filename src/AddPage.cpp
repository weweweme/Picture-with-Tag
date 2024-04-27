#include "AddPage.h"

AddPage::AddPage(const wxString& title, const wxPoint& pos, const wxSize& size, const PageID currentPage)
        : BasePage(title, pos, size, currentPage) {
    AddPage::SetupPage();
}

void AddPage::SetupPage() {

}
