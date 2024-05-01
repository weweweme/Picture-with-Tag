#ifndef PICTURE_WITH_TAG_CONSTANTS_H
#define PICTURE_WITH_TAG_CONSTANTS_H

#include <wx/defs.h>
#include <wx/wx.h>

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

// BasePage 상수
constexpr int SIZE_BUTTON_X = 224;
constexpr int SIZE_BUTTON_Y = 35;
constexpr char BACK_BUTTON_LABEL[] = "뒤로가기";

// AddPage 상수
constexpr int CONFIRM_BUTTON_Y = 640;
constexpr int CLEAR_BUTTON_Y = 680;
constexpr int INPUT_FIELD_HEIGHT = 25;
constexpr int TITLE_INPUT_FIELD_WIDTH = 900;
constexpr int TITLE_LABEL_X = 20;
constexpr int TITLE_LABEL_Y = 25;
constexpr int TITLE_INPUT_X = 60;
constexpr int TITLE_INPUT_Y = 20;
constexpr char TITLE_LABEL_TEXT[] = "제목";
constexpr size_t MAX_TITLE_LENGTH = 32;
constexpr int TAG_BUTTON_WIDTH = 100;
constexpr int TAG_INPUT_FIELD_WIDTH = 780;
constexpr int TAG_BUTTON_X_OFFSET = 78;
constexpr int TAG_INPUT_Y_OFFSET = 50;
constexpr char TAG_LABEL_TEXT[] = "태그";
constexpr char TAG_BUTTON_TEXT[] = "태그 추가";
constexpr size_t MAX_TAGS = 32;
constexpr size_t MAX_TAG_LENGTH = 16;
constexpr int BODY_TEXT_WIDTH = 900;
constexpr int BODY_TEXT_HEIGHT = 130;
constexpr int BODY_LABEL_X = 20;
constexpr int BODY_LABEL_Y = 690;
constexpr int BODY_INPUT_X = 60;
constexpr int BODY_INPUT_Y = 630;
constexpr char BODY_LABEL_TEXT[] = "본문";
constexpr size_t MAX_BODY_LENGTH = 256;
constexpr int PHOTO_DISPLAY_X = 18;
constexpr int PHOTO_DISPLAY_Y = 122;
constexpr int ADD_PAGE_BUTTON_WIDTH = 100;
constexpr int ADD_PAGE_BUTTON_HEIGHT = 50;
constexpr int MAX_IMAGE_WIDTH = 940;
constexpr int MAX_IMAGE_HEIGHT = 480;
constexpr int LISTBOX_X = 1185;
constexpr int LISTBOX_Y = 18;
constexpr int LISTBOX_WIDTH = 230;
constexpr int LISTBOX_HEIGHT = 600;
constexpr int DELETE_BUTTON_OFFSET_X = LISTBOX_X + LISTBOX_WIDTH - 30;
constexpr int DELETE_BUTTON_OFFSET_Y = 14;
constexpr char CLEAR_BUTTON_TEXT[] = "초기화";
constexpr char TAG_DUPLICATE_TEXT[] = "중복된 태그입니다";
constexpr char TAG_SPACE_IN_TEXT[] = "태그에 공백을 포함할 수 없습니다";
constexpr char SAVING_BUTTON_CLICK[] = "저장 버튼 클릭";
constexpr char PHOTO_ADD_TEXT[] = "사진 추가";
constexpr char PHOTO_REMOVE_TEXT[] = "사진 제거";
constexpr char SELECT_PHOTO_TEXT[] = "사진 선택";
constexpr char IMAGE_LOAD_FAIL_TEXT[] = "이미지 파일을 로드할 수 없습니다.";
constexpr char FILE_DIALOG_FILTER[] = "JPEG files (*.jpg)|*.jpg|PNG files (*.png)|*.png";
const wxColour LIGHT_RED(255, 204, 204);
const wxColour DEFAULT_BG_COLOR(*wxWHITE);

#endif // PICTURE_WITH_TAG_CONSTANTS_H
