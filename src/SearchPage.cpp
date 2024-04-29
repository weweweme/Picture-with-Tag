#include "SearchPage.h"
#include "DataItem.h"
#include <boost/archive/text_iarchive.hpp>
#include <fstream>
#include <wx/dir.h>
#include <wx/filename.h>
#include <wx/stdpaths.h>

SearchPage::SearchPage(const wxString& title, const wxPoint& pos, const wxSize& size, const PageID currentPage)
        : BasePage(title, pos, size, currentPage) {
    SearchPage::InitUI();
}

void SearchPage::InitUI() {
    BasePage::InitUI();

    // 검색값 입력 필드
    new wxStaticText(this->panel, wxID_ANY, SEARCH_LABEL_TEXT, wxPoint(SEARCH_LABEL_X, SEARCH_LABEL_Y));
    this->searchInput = new wxTextCtrl(this->panel, wxID_ANY, "", wxPoint(SEARCH_INPUT_X, SEARCH_INPUT_Y), wxSize(SEARCH_INPUT_FIELD_WIDTH, INPUT_FIELD_HEIGHT));
    this->searchInput->Bind(wxEVT_TEXT, &SearchPage::OnTitleTextChange, this);

    // 검색 조건 선택 드롭다운
    wxArrayString searchOptions;
    searchOptions.Add(SEARCH_OPTION_TITLE);
    searchOptions.Add(SEARCH_OPTION_TAG);
    this->searchCondition = new wxChoice(this->panel, wxID_ANY, wxPoint(SEARCH_INPUT_X + SEARCH_INPUT_FIELD_WIDTH + SEARCH_CONDITION_OFFSET, SEARCH_INPUT_Y + SEARCH_CONDITION_TOP_OFFSET), wxDefaultSize, searchOptions);
    this->searchCondition->SetSelection(0); // 기본값 설정

    // 검색 버튼
    this->searchButton = new wxButton(this->panel, wxID_ANY, "검색", wxPoint(SEARCH_INPUT_X + SEARCH_INPUT_FIELD_WIDTH + SEARCH_BUTTON_OFFSET, SEARCH_INPUT_Y + SEARCH_BUTTON_TOP_OFFSET), defaultButtonSize);
    this->searchButton->Bind(wxEVT_BUTTON, &SearchPage::OnSearchConfirm, this);

    // 태그 보기 필드 (읽기 전용 입력 필드)
    new wxStaticText(this->panel, wxID_ANY, TAG_LABEL_TEXT, wxPoint(TITLE_LABEL_X, TITLE_LABEL_Y + TAG_INPUT_Y_OFFSET));
    this->tagView = new wxTextCtrl(this->panel, wxID_ANY, "", wxPoint(TITLE_INPUT_X, TITLE_INPUT_Y + TAG_INPUT_Y_OFFSET), wxSize(TAG_INPUT_FIELD_WIDTH, INPUT_FIELD_HEIGHT), wxTE_READONLY);

    // 글 목록 리스트
    this->articleList = new wxListBox(this->panel, wxID_ANY, wxPoint(LISTBOX_X, LISTBOX_Y), wxSize(LISTBOX_WIDTH, LISTBOX_HEIGHT));
    this->articleList->Bind(wxEVT_LISTBOX, &SearchPage::OnArticleSelected, this);

    // PictureDisplay 정적 비트맵 설정
    this->pictureDisplay = new wxStaticBitmap(this->panel, wxID_ANY, wxNullBitmap, wxPoint(PHOTO_DISPLAY_X, PHOTO_DISPLAY_Y), wxSize(MAX_IMAGE_WIDTH, MAX_IMAGE_HEIGHT));

    // 본문 텍스트 입력 필드 (읽기 전용 입력 필드)
    new wxStaticText(this->panel, wxID_ANY, BODY_LABEL_TEXT, wxPoint(BODY_LABEL_X, BODY_LABEL_Y));
    this->bodyView = new wxTextCtrl(this->panel, wxID_ANY, "", wxPoint(BODY_INPUT_X, BODY_INPUT_Y), wxSize(BODY_TEXT_WIDTH, BODY_TEXT_HEIGHT), wxTE_MULTILINE);

    // 초기화 버튼
    auto* resetButton = new wxButton(this->panel, wxID_ANY, CLEAR_BUTTON_TEXT, wxPoint(RIGHT_BUTTON_X, CLEAR_BUTTON_Y), defaultButtonSize);
    resetButton->Bind(wxEVT_BUTTON, &SearchPage::OnClickReset, this);
}

void SearchPage::OnTitleTextChange(wxCommandEvent &_) {

}

void SearchPage::OnArticleSelected(wxCommandEvent &_) {

}

void SearchPage::OnSearchConfirm(wxCommandEvent &_) {
    wxString searchText = searchInput->GetValue();
    int selectedOption = searchCondition->GetSelection();

    // 데이터 로드
    std::vector<DataItem> items = LoadDataItems();

    std::vector<DataItem> results;

    // TODO: 탐색할 데이터 아이템 목록 가져오는 로직 구현

    if (selectedOption == 0) {
        // TODO: 제목으로 검색하는 로직 구현
    } else if (selectedOption == 1) {
        // TODO: 태그로 검색하는 로직 구현
    }

    // TODO: 결과 표시 로직 구현
}

void SearchPage::OnClickReset(wxCommandEvent &_) {

}

std::vector<DataItem> LoadDataItems() {
    std::vector<DataItem> items; // DataItem 객체들을 저장할 벡터

    // OS 문서 디렉토리 경로를 가져옵니다.
    wxString docDir = wxStandardPaths::Get().GetDocumentsDir();
    // 검색 대상이 될 디렉토리 경로를 설정합니다.
    wxString targetDir = docDir + "/Picture-with-Tag";

    // 해당 디렉토리가 존재하는지 확인합니다.
    if (!(wxDirExists(targetDir))) {
        // TODO: 디렉터리가 존재하지 않을 경우 피드백 구현
    }

    wxDir dir(targetDir); // 디렉토리 객체를 생성합니다.
    wxString filename; // 파일 이름을 저장할 변수
    // 첫 번째 '.pwt' 확장자를 가진 파일 이름을 가져옵니다.
    bool cont = dir.GetFirst(&filename, "*.pwt", wxDIR_FILES);

    // 파일이 존재하는 동안 반복합니다.
    while (cont) {
        // 파일의 전체 경로를 구성합니다.
        wxString filePath = targetDir + "/" + filename;
        // 파일을 바이너리 모드로 읽기 위해 열기 시도
        std::ifstream ifs(filePath.ToStdString(), std::ios::binary);
        if (ifs.is_open()) { // 파일 열기 성공 시
            try {
                boost::archive::text_iarchive ia(ifs); // 역직렬화를 위한 아카이브 객체 생성
                DataItem item; // 데이터 아이템 객체
                ia >> item; // 파일에서 데이터 아이템 역직렬화
                items.push_back(item); // 벡터에 데이터 아이템 추가
            } catch (const boost::archive::archive_exception& e) {
                // 파일 읽기 또는 역직렬화 중 발생한 예외 처리
                wxLogError(_("Failed to load data item from %s, error: %s"), filePath, wxString(e.what()));
            }
            ifs.close(); // 파일 스트림 닫기
        }
        // 다음 파일로 이동
        cont = dir.GetNext(&filename);
    }

    return items; // 로드된 데이터 아이템의 벡터 반환
}
