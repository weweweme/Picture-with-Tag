#include "AppInitializer.h"
#include "TitlePage.h"
#include "AddPage.h"
#include "FrameManager.h"

// 상수 정의
constexpr int INIT_WINDOW_WIDTH = 1440;
constexpr int INIT_WINDOW_HEIGHT = 810;
constexpr int INIT_WINDOW_X = 50;
constexpr int INIT_WINDOW_Y = 50;
constexpr char INIT_WINDOW_TITLE[] = "Picture with Tag";

bool AppInitializer::OnInit() {
    FrameManager* manager = FrameManager::GetInstance();

    InitPage(PageID::ID_Title);
    InitPage(PageID::ID_Add);

    // 기본적으로 타이틀 프레임을 활성화
    manager->ShowPage(PageID::ID_Title);

    return true;
}

void AppInitializer::InitPage(const PageID id) {
    FrameManager* manager = FrameManager::GetInstance();
    wxSize initSize = wxSize(INIT_WINDOW_WIDTH, INIT_WINDOW_HEIGHT);
    wxPoint initPosition = wxPoint(INIT_WINDOW_X, INIT_WINDOW_Y);
    wxFrame* frame;

    switch (id) {
        case PageID::ID_Title:
            frame = new TitlePage(INIT_WINDOW_TITLE, initPosition, initSize);
            break;
        case PageID::ID_Add:
            frame = new AddPage(INIT_WINDOW_TITLE, initPosition, initSize, ID_Add);
            break;
    }

    manager->RegisterPage(id, frame);
}

wxIMPLEMENT_APP(AppInitializer);
