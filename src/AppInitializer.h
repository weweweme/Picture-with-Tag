#ifndef APPINITIALIZER_H
#define APPINITIALIZER_H

#include <wx/wx.h>
#include "TitlePage.h"
#include "PageID.h"
#include <map>

class AppInitializer : public wxApp {
public:
    bool OnInit() override;

private:
    std::map<PageID, wxFrame*> frames;
};

#endif // APPINITIALIZER_H
