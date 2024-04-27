#ifndef APPINITIALIZER_H
#define APPINITIALIZER_H

#include <wx/wx.h>
#include "TitlePage.h"
#include "PageID.h"
#include <map>

/**
 * @class AppInitializer
 * @brief 애플리케이션의 초기화를 담당하는 클래스.
 *
 * AppInitializer 클래스는 wxWidgets 애플리케이션의 진입점 역할을 하며,
 * 초기 프레임을 설정하고 FrameManager를 이용하여 프레임 관리를 수행합니다.
 */
class AppInitializer : public wxApp {
public:
    bool OnInit() override;

private:
    static void InitPage(PageID id);
};

#endif // APPINITIALIZER_H
