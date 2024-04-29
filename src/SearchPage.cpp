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

void SearchPage::OnTitleTextChange(wxCommandEvent& _) {

}

void SearchPage::OnArticleSelected(wxCommandEvent& _) {
    int selection = this->articleList->GetSelection();

    // 항목이 선택되지 않은 경우 에러 메시지를 로그하고 함수를 종료합니다.
    if (selection == wxNOT_FOUND) {
        wxLogMessage("No item selected.");
        return;
    }

    const DataItem& selectedItem = this->searchResults.at(selection);

    // 태그와 본문 정보를 표시
    wxString tagsStr;
    for (const auto& tag : selectedItem.tags) {
        if (!tagsStr.IsEmpty()) tagsStr += ", ";
        tagsStr += tag;
    }
    this->tagView->SetValue(tagsStr);
    this->bodyView->SetValue(selectedItem.body);

    // 이미지 데이터 처리
    wxMemoryInputStream memStream(&selectedItem.image_data[0], selectedItem.image_data.size());
    wxImage image;
    if (image.LoadFile(memStream, wxBITMAP_TYPE_PNG)) {
        // 이미지 크기 조정
        if (image.GetWidth() > MAX_IMAGE_WIDTH || image.GetHeight() > MAX_IMAGE_HEIGHT) {
            image = image.Scale(MAX_IMAGE_WIDTH, MAX_IMAGE_HEIGHT, wxIMAGE_QUALITY_HIGH);
        }
        this->pictureDisplay->SetBitmap(wxBitmap(image));
        this->pictureDisplay->Refresh();
    } else {
        wxLogMessage("Failed to load image.");
        this->pictureDisplay->SetBitmap(wxNullBitmap);
        this->pictureDisplay->Refresh();
    }
}

void SearchPage::OnSearchConfirm(wxCommandEvent& _) {
    wxString searchText = this->searchInput->GetValue().Lower();
    int selectedOption = this->searchCondition->GetSelection();

    // 데이터 로드
    std::vector<DataItem> items = LoadDataItems();

    // 검색 결과를 클리어하고 새로운 검색을 수행합니다.
    this->searchResults.clear();
    this->articleList->Clear();

    // 검색 조건에 따라 필터링
    for (auto& item : items) {
        switch (selectedOption) {
            case 0: // 제목으로 검색
                if (item.title.Lower().Contains(searchText)) {
                    this->searchResults.push_back(item);
                }
                break;
            case 1: // 태그로 검색
                for (const auto& tag : item.tags) {
                    if (tag.Lower().Contains(searchText)) {
                        this->searchResults.push_back(item);
                        break; // 일치하는 태그를 찾으면 더 이상의 태그 검사는 불필요
                    }
                }
                break;
        }
    }

    // 검색 결과를 ListBox에 표시
    for (auto& result : this->searchResults) {
        this->articleList->Append(result.title);
    }
}

void SearchPage::OnClickReset(wxCommandEvent& _) {
    // 사용자에게 리셋을 확인하는 메시지 박스를 표시
    int response = wxMessageBox("검색 설정과 결과를 모두 초기화하시겠습니까?", "리셋 확인", wxICON_QUESTION | wxYES_NO, this);
    if (response == wxYES) {
        this->searchInput->Clear();
        this->searchCondition->SetSelection(0);
        this->searchResults.clear();
        this->articleList->Clear();
        this->tagView->Clear();
        this->bodyView->Clear();
        this->pictureDisplay->SetBitmap(wxNullBitmap);
        this->pictureDisplay->Refresh();
    }
}

std::vector<DataItem> SearchPage::LoadDataItems() {
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
