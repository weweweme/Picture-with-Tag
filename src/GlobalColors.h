#ifndef GLOBAL_COLORS_H
#define GLOBAL_COLORS_H

#include <wx/colour.h>

// 전역 색상 설정을 위한 구조체
struct GlobalColors {
    static wxColour backgroundColour;
    static wxColour textColour;
    static wxColour inputBackgroundColour;
    static wxColour inputTextColour;

    // 초기화 함수
    static void Init();
};

#endif // GLOBAL_COLORS_H
