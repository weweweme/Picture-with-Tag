#include "SearchPage.h"

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

    // 글 목록 리스트
    this->articleList = new wxListBox(this->panel, wxID_ANY, wxPoint(LISTBOX_X, LISTBOX_Y), wxSize(LISTBOX_WIDTH, LISTBOX_HEIGHT));
    this->articleList->Bind(wxEVT_LISTBOX, &SearchPage::OnArticleSelected, this);
}

void SearchPage::OnTitleTextChange(wxCommandEvent &_) {

}

void SearchPage::OnArticleSelected(wxCommandEvent &_) {

}

void SearchPage::OnSearchConfirm(wxCommandEvent &_) {

}
