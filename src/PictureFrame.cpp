#include "PictureFrame.h"

// 상수 정의
constexpr int ASPECT_RATIO_WIDTH = 16;
constexpr int ASPECT_RATIO_HEIGHT = 9;

PictureFrame::PictureFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
        : wxFrame(nullptr, wxID_ANY, title, pos, size) {
    this->Bind(wxEVT_SIZE, &PictureFrame::HandleSizeChange, this);
}

void PictureFrame::HandleSizeChange(wxSizeEvent& event) {
    wxSize size = event.GetSize();
    int newWidth = size.GetWidth();
    int newHeight = size.GetHeight();

    // 최적의 너비와 높이 계산
    int expectedHeight = newWidth * ASPECT_RATIO_HEIGHT / ASPECT_RATIO_WIDTH;
    int expectedWidth = newHeight * ASPECT_RATIO_WIDTH / ASPECT_RATIO_HEIGHT;

    // 너비 또는 높이가 예상치와 다른 경우 조정
    if (newHeight != expectedHeight) {
        newHeight = expectedHeight;
    } else if (newWidth != expectedWidth) {
        newWidth = expectedWidth;
    }

    this->SetSize(wxSize(newWidth, newHeight));
    event.Skip();  // 다른 핸들러가 이벤트를 처리할 수 있도록 함
}
