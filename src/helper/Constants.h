#ifndef PICTURE_WITH_TAG_CONSTANTS_H
#define PICTURE_WITH_TAG_CONSTANTS_H

#include <wx/defs.h>
#include <wx/wx.h>

// AppInitialize 상수 ========================================
static constexpr int INIT_WINDOW_WIDTH = 1440;
static constexpr int INIT_WINDOW_HEIGHT = 810;
static constexpr int INIT_WINDOW_X = 50;
static constexpr int INIT_WINDOW_Y = 50;
static constexpr char INIT_WINDOW_TITLE[] = "Picture with Tag";
static constexpr char INIT_WINDOW_ADD[] = "Add Page";
static constexpr char INIT_WINDOW_SEARCH[] = "Search Page";

// TitlePage 상수 ========================================
static constexpr int BUTTON_SPACE = 3;  // 버튼 사이의 공간
static constexpr int BUTTON_WIDTH = 300;
static constexpr int BUTTON_HEIGHT = 150;
static constexpr char BTN_LABEL_ADD[] = "추가";
static constexpr char BTN_LABEL_SEARCH[] = "검색";
static constexpr char BTN_LABEL_EXIT[] = "종료";
static constexpr int SPACER_OPTIONS = 1;
static constexpr int NO_EXPAND = 0;
static const int ALIGNMENT_OPTIONS = wxALIGN_CENTER_HORIZONTAL | wxALL;

// BasePage 상수 ========================================
static constexpr int SIZE_BUTTON_X = 224;
static constexpr int SIZE_BUTTON_Y = 35;
static constexpr char BACK_BUTTON_LABEL[] = "뒤로가기";
static constexpr int RIGHT_BUTTON_X = 1188;
static constexpr int BACK_BUTTON_Y = 720;

// AddPage 상수 ========================================
// 결과 저장
static constexpr char CONFIRM_BUTTON_LABEL[] = "저장";
static constexpr int CONFIRM_BUTTON_Y = 640;

// 초기화
static constexpr int CLEAR_BUTTON_Y = 680;

// 제목
static constexpr int INPUT_FIELD_HEIGHT = 25;
static constexpr int TITLE_INPUT_FIELD_WIDTH = 900;
static constexpr int TITLE_LABEL_X = 20;
static constexpr int TITLE_LABEL_Y = 25;
static constexpr int TITLE_INPUT_X = 60;
static constexpr int TITLE_INPUT_Y = 20;
static constexpr char TITLE_LABEL_TEXT[] = "제목";
static constexpr size_t MAX_TITLE_LENGTH = 32;

// 태그
static constexpr int TAG_BUTTON_WIDTH = 100;
static constexpr int TAG_INPUT_FIELD_WIDTH = 780;
static constexpr int TAG_BUTTON_X_OFFSET = 78;
static constexpr int TAG_INPUT_Y_OFFSET = 50;
static constexpr char TAG_LABEL_TEXT[] = "태그";
static constexpr char TAG_BUTTON_TEXT[] = "태그 추가";
static constexpr size_t MAX_TAGS = 32;
static constexpr size_t MAX_TAG_LENGTH = 16;

// 본문
static constexpr int BODY_TEXT_WIDTH = 900;
static constexpr int BODY_TEXT_HEIGHT = 130;
static constexpr int BODY_LABEL_X = 20;
static constexpr int BODY_LABEL_Y = 690;
static constexpr int BODY_INPUT_X = 60;
static constexpr int BODY_INPUT_Y = 630;
static constexpr char BODY_LABEL_TEXT[] = "본문";
static constexpr size_t MAX_BODY_LENGTH = 256;

// 사진
static constexpr int PICTURE_DISPLAY_X = 18;
static constexpr int PICTURE_DISPLAY_Y = 122;
static constexpr int ADD_PAGE_BUTTON_WIDTH = 100;
static constexpr int ADD_PAGE_BUTTON_HEIGHT = 50;
static constexpr int MAX_IMAGE_WIDTH = 940;
static constexpr int MAX_IMAGE_HEIGHT = 480;

// 리스트 박스
static constexpr int LISTBOX_X = 1185;
static constexpr int LISTBOX_Y = 18;
static constexpr int LISTBOX_WIDTH = 230;
static constexpr int LISTBOX_HEIGHT = 600;

// 태그 삭제 버튼
static constexpr int DELETE_BUTTON_OFFSET_X = LISTBOX_X + LISTBOX_WIDTH - 30;
static constexpr int DELETE_BUTTON_OFFSET_Y = 14;

// 대화창 텍스트
static constexpr char DIALOGUE_TITLE_RESET[] = "정말로 모든 정보를 초기화하시겠습니까?";
static constexpr char DIALOGUE_TITLE_SAVE[] = "저장할 데이터를 선택하세요.";
static constexpr char DIALOGUE_WARNING_RESET[] = "경고";
static constexpr char DIALOGUE_CONFIRM_DELETE[] = "선택한 태그를 정말로 삭제하시겠습니까?";
static constexpr char DIALOGUE_TITLE_DELETE[] = "태그 삭제 확인";
static constexpr char CLEAR_BUTTON_TEXT[] = "초기화";
static constexpr char TAG_DUPLICATE_TEXT[] = "중복된 태그입니다";
static constexpr char TAG_SPACE_IN_TEXT[] = "태그에 공백을 포함할 수 없습니다";
static constexpr char PICTURE_ADD_TEXT[] = "사진 추가";
static constexpr char PICTURE_REMOVE_TEXT[] = "사진 제거";
static constexpr char SELECT_PHOTO_TEXT[] = "사진 선택";
static constexpr char IMAGE_LOAD_FAIL_TEXT[] = "이미지 파일을 로드할 수 없습니다.";
static constexpr char FILE_DIALOG_FILTER[] = "JPEG files (*.jpg)|*.jpg|PNG files (*.png)|*.png";
static const wxColour LIGHT_RED(255, 204, 204);
static const wxColour DEFAULT_BG_COLOR(*wxWHITE);

// Search Page 관련 상수 ========================================
// 검색 관련 상수
static constexpr char SEARCH_LABEL_TEXT[] = "검색";
static constexpr int SEARCH_LABEL_X = 20;
static constexpr int SEARCH_LABEL_Y = 25;
static constexpr int SEARCH_INPUT_X = 60;
static constexpr int SEARCH_INPUT_Y = 20;
static constexpr int SEARCH_INPUT_FIELD_WIDTH = 750;
static constexpr char SEARCH_OPTION_TITLE[] = "제목";
static constexpr char SEARCH_OPTION_TAG[] = "태그";
static constexpr int SEARCH_CONDITION_OFFSET = 12; // 입력 필드 끝에서 검색 조건 드롭다운까지의 오프셋
static constexpr int SEARCH_CONDITION_TOP_OFFSET = 2; // 검색 조건 드롭다운의 수직 정렬 오프셋
static constexpr int SEARCH_BUTTON_OFFSET = 80; // 조건 드롭다운에서 검색 버튼까지의 오프셋
static constexpr int SEARCH_BUTTON_TOP_OFFSET = -6; // 검색 버튼의 수직 정렬 오프셋

// 태그
static constexpr int SEARCH_TAG_INPUT_FIELD_WIDTH = 1055;

// 저장
static constexpr char SAVE_BUTTON_TEXT[] = "데이터 묶음 저장";
static constexpr int SAVE_BUTTON_Y = 640;

// 폴더 경로 오픈
static constexpr char FILE_DIR_BUTTON_TEXT[] = "폴더";
static constexpr int FILE_DIR_BUTTON_X = 1371;
static constexpr int FILE_DIR_BUTTON_Y = 5;
static constexpr int FILE_DIR_BUTTON_WIDTH = 40;
static constexpr int FILE_DIR_BUTTON_HEIGHT = 30;

// 데이터 관련 상수 ========================================
constexpr char DATA_SAVE_PROMPT[] = "선택한 데이터를 저장하시겠습니까?";
constexpr char SAVE_CONFIRM_TITLE[] = "저장 확인";
constexpr char DATA_SAVE_SUCCESS[] = "데이터가 성공적으로 저장되었습니다.";
constexpr char SAVE_COMPLETE_TITLE[] = "저장 완료";
constexpr char NO_DATA_SELECTED_ERROR[] = "저장할 데이터를 선택하세요.";
constexpr char WARNING_TITLE[] = "경고";
constexpr char DIRECTORY_CREATION_FAIL[] = "디렉토리 생성 실패.";
constexpr char ERROR_TITLE[] = "오류";
constexpr char FILE_NOT_FOUND_ERROR[] = "파일 '%s'를 찾을 수 없습니다.";
constexpr char FILE_READ_ERROR[] = "파일 '%s'를 읽을 수 없습니다.";
constexpr char BUNDLES_DIR_NAME[] = "/Bundles";
constexpr char DATA_ITEMS_DIR[] = "/Picture-with-Tag";
constexpr char PWT_EXTENSION[] = ".pwt";
constexpr char ZIP_EXTENSION_FORMAT[] = "%Y%m%d_%H%M%S.zip";
constexpr char ERROR_MESSAGE_FILE_NOT_FOUND[] = "파일 '%s'를 찾을 수 없습니다.";
constexpr char ERROR_MESSAGE_FILE_READ[] = "파일 '%s'를 읽을 수 없습니다.";
constexpr char SUCCESS_MESSAGE_DATA_SAVED[] = "데이터가 성공적으로 저장되었습니다.";
constexpr char ERROR_MESSAGE_DIRECTORY_CREATE[] = "디렉토리 '%s' 생성 실패.";
constexpr char ERROR_MESSAGE_LOAD_FAIL[] = "이미지 파일을 로드할 수 없습니다.";

#endif // PICTURE_WITH_TAG_CONSTANTS_H
