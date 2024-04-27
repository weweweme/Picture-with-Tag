#include "PageManager.h"

PageManager* PageManager::instance = nullptr;

PageManager* PageManager::GetInstance() {
    if (instance == nullptr) {
        instance = new PageManager();
    }

    return instance;
}

void PageManager::RegisterPage(PageID id, wxFrame* frame) {
    frames[id] = frame;
}

void PageManager::ShowPage(PageID id) {
    if (id == PageID::ID_None) {
        wxTheApp->Exit();
        return;
    }

    frames[id]->Show(true);
    frames[id]->Raise(); // 프레임을 전면으로 가져옴
}

void PageManager::HidePage(PageID id) {
    frames[id]->Show(false);
    frames[id]->Hide();
}
