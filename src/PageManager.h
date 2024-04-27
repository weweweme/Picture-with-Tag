#ifndef FRAMEMANAGER_H
#define FRAMEMANAGER_H

#include <wx/wx.h>
#include <map>
#include "PageID.h"

/**
 * @class PageManager
 * @brief 페이지 관리를 위한 싱글톤 클래스.
 *
 * 이 클래스는 애플리케이션에서 여러 페이지를 관리하는 싱글톤 인스턴스를 제공합니다.
 * 등록된 각 페이지는 특정 PageID로 식별됩니다.
 */
class PageManager {
public:
    static PageManager* GetInstance();

    void RegisterPage(PageID id, wxFrame *frame);
    void ShowPage(PageID id);
    void HidePage(PageID id);

private:
    PageManager() = default; // 싱글톤 패턴을 위한 private 생성자

    static PageManager *instance;
    PageID currentVisiblePage = PageID::ID_Title;
    std::map<PageID, wxFrame *> pages;
};

#endif // FRAMEMANAGER_H
