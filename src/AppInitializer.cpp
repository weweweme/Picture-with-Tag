#include "AppInitializer.h"
#include "PictureFrame.h"

bool AppInitializer::OnInit() {
    PictureFrame* frame = new PictureFrame("Picture with Tag", wxPoint(50, 50), wxSize(1920, 1080));
    frame->Show(true);
    return true;
}

wxIMPLEMENT_APP(AppInitializer);
