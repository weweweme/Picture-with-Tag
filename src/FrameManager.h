#ifndef FRAMEMANAGER_H
#define FRAMEMANAGER_H

#include <wx/wx.h>
#include <map>
#include "PageID.h"

/**
 * @class FrameManager
 * @brief 프레임 관리를 위한 싱글톤 클래스.
 *
 * 이 클래스는 애플리케이션에서 여러 프레임을 관리하는 싱글톤 인스턴스를 제공합니다.
 * 등록된 각 프레임은 특정 PageID로 식별됩니다. FrameManager는 이 프레임들의 표시와 숨김을 관리합니다.
 */
class FrameManager {
public:
    static FrameManager* GetInstance();

    void RegisterPage(PageID id, wxFrame *frame);
    void ShowPage(PageID id);
    void HidePage(PageID id);

private:
    FrameManager() = default; // 싱글톤 패턴을 위한 private 생성자

    static FrameManager *instance;
    std::map<PageID, wxFrame *> frames;
};

#endif // FRAMEMANAGER_H
