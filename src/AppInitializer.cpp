#include "AppInitializer.h"
#include "TitleFrame.h"

// 상수 정의
constexpr int INIT_WINDOW_WIDTH = 1440;
constexpr int INIT_WINDOW_HEIGHT = 810;
constexpr int INIT_WINDOW_X = 50;
constexpr int INIT_WINDOW_Y = 50;
constexpr char INIT_WINDOW_TITLE[] = "Picture with Tag";

bool AppInitializer::OnInit() {
    auto* frame = new TitleFrame(INIT_WINDOW_TITLE,
                                 wxPoint(INIT_WINDOW_X, INIT_WINDOW_Y),
                                 wxSize(INIT_WINDOW_WIDTH, INIT_WINDOW_HEIGHT));
    frame->Show(true);

    return true;
}

wxIMPLEMENT_APP(AppInitializer);
