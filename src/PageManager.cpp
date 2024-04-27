#include "PageManager.h"

PageManager* PageManager::instance = nullptr;

PageManager* PageManager::GetInstance() {
    if (instance == nullptr) {
        instance = new PageManager();
    }

    return instance;
}

void PageManager::RegisterPage(PageID id, wxFrame* frame) {
    pages[id] = frame;
}

void PageManager::ShowPage(PageID id) {
    if (id == PageID::ID_None) {
        wxTheApp->Exit();
        return;
    }

    pages[currentVisiblePage]->Hide();
    currentVisiblePage = id;
    pages[id]->Show();
    pages[id]->Raise();
}

void PageManager::HidePage(PageID id) {
    currentVisiblePage = id;
    pages[id]->Hide();
}
