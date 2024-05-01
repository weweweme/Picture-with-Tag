#include "AppInitializer.h"
#include "page/TitlePage.h"
#include "page/AddPage.h"
#include "page/PageManager.h"
#include "page/SearchPage.h"
#include "helper/GlobalColors.h"

// 상수 정의
constexpr int INIT_WINDOW_WIDTH = 1440;
constexpr int INIT_WINDOW_HEIGHT = 810;
constexpr int INIT_WINDOW_X = 50;
constexpr int INIT_WINDOW_Y = 50;
constexpr char INIT_WINDOW_TITLE[] = "Picture with Tag";
constexpr char INIT_WINDOW_ADD[] = "Add Page";
constexpr char INIT_WINDOW_SEARCH[] = "Search Page";

bool AppInitializer::OnInit() {
    wxInitAllImageHandlers();
    GlobalColors::Init();

    InitPage(PageID::ID_Title);
    InitPage(PageID::ID_Add);
    InitPage(PageID::ID_Search);

    return true;
}

void AppInitializer::InitPage(const PageID id) {
    PageManager* manager = PageManager::GetInstance();
    wxSize initSize = wxSize(INIT_WINDOW_WIDTH, INIT_WINDOW_HEIGHT);
    wxPoint initPosition = wxPoint(INIT_WINDOW_X, INIT_WINDOW_Y);
    wxFrame* frame;

    switch (id) {
        case PageID::ID_Title:
            frame = new TitlePage(INIT_WINDOW_TITLE, initPosition, initSize);
            frame->Show();
            break;
        case PageID::ID_Add:
            frame = new AddPage(INIT_WINDOW_ADD, initPosition, initSize, ID_Add);
            break;
        case PageID::ID_Search:
            frame = new SearchPage(INIT_WINDOW_SEARCH, initPosition, initSize, ID_Search);
            break;
    }

    // 창의 크기 고정을 위한 기본값
    frame->SetMinSize(initSize);
    frame->SetMaxSize(initSize);

    manager->RegisterPage(id, frame);
}

wxIMPLEMENT_APP(AppInitializer);
