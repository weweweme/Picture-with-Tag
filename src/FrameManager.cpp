#include "FrameManager.h"

FrameManager* FrameManager::instance = nullptr;

FrameManager* FrameManager::GetInstance() {
    if (instance == nullptr) {
        instance = new FrameManager();
    }

    return instance;
}

void FrameManager::RegisterPage(PageID id, wxFrame* frame) {
    frames[id] = frame;
}

void FrameManager::ShowPage(PageID id) {
    frames[id]->Show();
    frames[id]->Raise(); // 프레임을 전면으로 가져옴
}

void FrameManager::HidePage(PageID id) {
    frames[id]->Hide();
}

