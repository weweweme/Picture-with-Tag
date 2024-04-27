#include "AppInitializer.h"
#include "TitleFrame.h"

// 상수 정의
constexpr int INIT_WINDOW_WIDTH = 1440;
constexpr int INIT_WINDOW_HEIGHT = 810;
constexpr int INIT_WINDOW_X = 50;
constexpr int INIT_WINDOW_Y = 50;
constexpr char INIT_WINDOW_TITLE[] = "Picture with Tag";

bool AppInitializer::OnInit() {
    auto* titleFrame = new TitleFrame(INIT_WINDOW_TITLE,
                                      wxPoint(INIT_WINDOW_X, INIT_WINDOW_Y),
                                      wxSize(INIT_WINDOW_WIDTH, INIT_WINDOW_HEIGHT));
    frames[ID_Title] = titleFrame; // 저장

    titleFrame->Show(true); // 기본적으로 타이틀 프레임을 활성화

    return true;
}

wxIMPLEMENT_APP(AppInitializer);
