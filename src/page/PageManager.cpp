#include "PageManager.h"

PageManager* PageManager::instance = nullptr;

PageManager* PageManager::GetInstance() {
    if (instance == nullptr) {
        instance = new PageManager();
    }

    return instance;
}

void PageManager::RegisterPage(PageID id, wxFrame* page) {
    this->pages[id] = page;
}

wxFrame* PageManager::GetPage(PageID id) {
    return this->pages[id];
}

void PageManager::ShowPage(PageID id) {
    if (id == PageID::ID_None) {
        wxTheApp->Exit();
        return;
    }

    this->pages[currentVisiblePage]->Hide();
    this->currentVisiblePage = id;
    this->pages[id]->Show();
    this->pages[id]->Raise();
}

void PageManager::HidePage(PageID id) {
    this->currentVisiblePage = id;
    this->pages[id]->Hide();
}
