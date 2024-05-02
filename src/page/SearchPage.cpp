#include "SearchPage.h"
#include "../helper/Constants.h"
#include "../data/DataManager.h"
#include "../helper/UIHelpers.h"

SearchPage::SearchPage(const wxString& title, const wxPoint& pos, const wxSize& size, const PageID currentPage)
        : BasePage(title, pos, size, currentPage) {
    SearchPage::InitUI();
}

void SearchPage::InitUI() {
    BasePage::InitUI();

    // 검색값 입력 필드 생성
    UIHelpers::CreateStaticText(this->panel, SEARCH_LABEL_TEXT, wxPoint(SEARCH_LABEL_X, SEARCH_LABEL_Y), wxDefaultSize);
    this->searchInput = UIHelpers::CreateTextCtrl(this->panel, "", wxPoint(SEARCH_INPUT_X, SEARCH_INPUT_Y), wxSize(SEARCH_INPUT_FIELD_WIDTH, INPUT_FIELD_HEIGHT));

    // 검색 조건 선택 드롭다운 생성
    wxArrayString searchOptions;
    searchOptions.Add(SEARCH_OPTION_TITLE);
    searchOptions.Add(SEARCH_OPTION_TAG);
    this->searchCondition = UIHelpers::CreateChoice(this->panel, searchOptions, wxPoint(SEARCH_INPUT_X + SEARCH_INPUT_FIELD_WIDTH + SEARCH_CONDITION_OFFSET, SEARCH_INPUT_Y + SEARCH_CONDITION_TOP_OFFSET), wxDefaultSize);
    this->searchCondition->SetSelection(0); // 기본값 설정

    // 검색 버튼 생성
    this->searchButton = UIHelpers::CreateButton(this->panel, SEARCH_LABEL_TEXT, wxPoint(SEARCH_INPUT_X + SEARCH_INPUT_FIELD_WIDTH + SEARCH_BUTTON_OFFSET, SEARCH_INPUT_Y + SEARCH_BUTTON_TOP_OFFSET), wxSize(SIZE_BUTTON_X, SIZE_BUTTON_Y));
    this->searchButton->Bind(wxEVT_BUTTON, &SearchPage::OnSearchConfirm, this);

    // 태그 보기 필드 (읽기 전용 입력 필드) 생성
    UIHelpers::CreateStaticText(this->panel, TAG_LABEL_TEXT, wxPoint(TITLE_LABEL_X, TITLE_LABEL_Y + TAG_INPUT_Y_OFFSET), wxDefaultSize);
    this->tagView = UIHelpers::CreateTextCtrl(this->panel, "", wxPoint(TITLE_INPUT_X, TITLE_INPUT_Y + TAG_INPUT_Y_OFFSET), wxSize(SEARCH_TAG_INPUT_FIELD_WIDTH, INPUT_FIELD_HEIGHT), wxTE_READONLY);

    // 글 목록 리스트 생성
    this->articleList = UIHelpers::CreateListBox(this->panel, wxPoint(LISTBOX_X, LISTBOX_Y), wxSize(LISTBOX_WIDTH, LISTBOX_HEIGHT), wxLB_MULTIPLE);
    this->articleList->Bind(wxEVT_LISTBOX, &SearchPage::OnArticleSelected, this);

    // PictureDisplay 정적 비트맵 설정
    this->pictureDisplay = new wxStaticBitmap(this->panel, wxID_ANY, wxNullBitmap, wxPoint(PICTURE_DISPLAY_X, PICTURE_DISPLAY_Y), wxSize(MAX_IMAGE_WIDTH, MAX_IMAGE_HEIGHT));

    // 본문 텍스트 입력 필드 생성
    UIHelpers::CreateStaticText(this->panel, BODY_LABEL_TEXT, wxPoint(BODY_LABEL_X, BODY_LABEL_Y), wxDefaultSize);
    this->bodyView = UIHelpers::CreateTextCtrl(this->panel, "", wxPoint(BODY_INPUT_X, BODY_INPUT_Y), wxSize(BODY_TEXT_WIDTH, BODY_TEXT_HEIGHT), wxTE_MULTILINE);

    // 초기화 버튼 생성
    auto* resetButton = UIHelpers::CreateButton(this->panel, CLEAR_BUTTON_TEXT, wxPoint(RIGHT_BUTTON_X, CLEAR_BUTTON_Y), wxSize(SIZE_BUTTON_X, SIZE_BUTTON_Y));
    resetButton->Bind(wxEVT_BUTTON, &SearchPage::OnClickReset, this);

    // 데이터 저장 버튼 생성
    this->saveButton = UIHelpers::CreateButton(this->panel, SAVE_BUTTON_TEXT, wxPoint(RIGHT_BUTTON_X, SAVE_BUTTON_Y), wxSize(SIZE_BUTTON_X, SIZE_BUTTON_Y));
    this->saveButton->Bind(wxEVT_BUTTON, &SearchPage::OnClickDataSave, this);

    // 폴더 경로 오픈 버튼 생성
    auto* dirOpenButton = UIHelpers::CreateButton(this->panel, FILE_DIR_BUTTON_TEXT, wxPoint(FILE_DIR_BUTTON_X, FILE_DIR_BUTTON_Y), wxSize(FILE_DIR_BUTTON_WIDTH, FILE_DIR_BUTTON_HEIGHT));
    dirOpenButton->Bind(wxEVT_BUTTON, &SearchPage::OnClickFolderDir, this);
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
        wxLogMessage(ERROR_MESSAGE_LOAD_FAIL);
        this->pictureDisplay->SetBitmap(wxNullBitmap);
        this->pictureDisplay->Refresh();
    }
}

void SearchPage::OnSearchConfirm(wxCommandEvent& _) {
    wxString searchText = this->searchInput->GetValue().Lower();
    int selectedOption = this->searchCondition->GetSelection();

    // 데이터 로드
    std::vector<DataItem> items = DataManager::LoadDataItems();

    // 검색 결과를 클리어하고 새로운 검색을 수행합니다.
    this->searchResults.clear();
    this->articleList->Clear();

    // 검색 조건에 따라 필터링
    for (auto& item : items) {
        switch (selectedOption) {
            case 0: // 제목으로 검색
                // 제목에 searchText가 포함되어 있는지 확인
                if (item.title.Lower().Contains(searchText)) {
                    this->searchResults.push_back(item);
                }
                break;

            case 1: // 태그로 검색
                wxArrayString inputTags = wxSplit(searchText, ','); // 쉼표로 분리하여 배열 생성

                std::set<wxString> searchTags;
                for (wxString& tag : inputTags) {
                    wxString cleanTag = tag.Trim().Lower(); // 공백 제거 및 소문자 변환
                    if (!cleanTag.IsEmpty()) {
                        searchTags.insert(cleanTag); // 빈 태그 제외하고 집합에 추가
                    }
                }

                std::set<wxString> itemTags;
                for (const auto& itemTag : item.tags) {
                    itemTags.insert(itemTag.Lower().Trim()); // 아이템 태그를 소문자로 변환 및 저장
                }

                bool allTagsFound = true;
                for (const auto& searchTag : searchTags) {
                    if (itemTags.find(searchTag) == itemTags.end()) {
                        allTagsFound = false; // 하나라도 태그가 아이템 태그 집합에 없으면 false
                        break;
                    }
                }

                if (allTagsFound) {
                    this->searchResults.push_back(item); // 모든 태그가 일치하면 결과에 아이템 추가
                }
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

void SearchPage::OnClickDataSave(wxCommandEvent& _) {
    DataManager::SaveDataItems(this->articleList, this->searchResults);
}

void SearchPage::OnClickFolderDir(wxCommandEvent& _) {
    DataManager::OpenDataDirectory();
}
