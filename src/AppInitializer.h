#ifndef APPINITIALIZER_H
#define APPINITIALIZER_H

#include <wx/wx.h>
#include "TitleFrame.h"
#include "FrameID.h"
#include <map>

class AppInitializer : public wxApp {
public:
    bool OnInit() override;

private:
    std::map<FrameID, wxFrame*> frames;
};

#endif // APPINITIALIZER_H
