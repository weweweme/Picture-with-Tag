#ifndef PICTURE_WITH_TAG_CONSTANTS_H
#define PICTURE_WITH_TAG_CONSTANTS_H

#include <wx/defs.h>

// AppInitialize 상수
constexpr int INIT_WINDOW_WIDTH = 1440;
constexpr int INIT_WINDOW_HEIGHT = 810;
constexpr int INIT_WINDOW_X = 50;
constexpr int INIT_WINDOW_Y = 50;
constexpr char INIT_WINDOW_TITLE[] = "Picture with Tag";
constexpr char INIT_WINDOW_ADD[] = "Add Page";
constexpr char INIT_WINDOW_SEARCH[] = "Search Page";

// TitlePage 상수
constexpr int BUTTON_SPACE = 3;  // 버튼 사이의 공간
constexpr int BUTTON_WIDTH = 300;
constexpr int BUTTON_HEIGHT = 150;
constexpr char BTN_LABEL_ADD[] = "추가";
constexpr char BTN_LABEL_SEARCH[] = "검색";
constexpr char BTN_LABEL_EXIT[] = "종료";
constexpr int SPACER_OPTIONS = 1;
constexpr int NO_EXPAND = 0;
const int ALIGNMENT_OPTIONS = wxALIGN_CENTER_HORIZONTAL | wxALL;

#endif // PICTURE_WITH_TAG_CONSTANTS_H
