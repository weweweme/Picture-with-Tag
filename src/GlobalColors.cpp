#include "GlobalColors.h"

wxColour GlobalColors::backgroundColour;
wxColour GlobalColors::textColour;
wxColour GlobalColors::inputBackgroundColour;
wxColour GlobalColors::inputTextColour;

void GlobalColors::Init() {
    backgroundColour = wxColour(255, 255, 255); // 흰색 배경
    textColour = wxColour(0, 0, 0); // 검은색 텍스트
    inputBackgroundColour = wxColour(240, 240, 240); // 입력 필드 배경색
    inputTextColour = wxColour(0, 0, 0); // 입력 필드 텍스트 색
}
