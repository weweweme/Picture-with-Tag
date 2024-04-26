#include "PictureFrame.h"

// 상수 정의
constexpr int ASPECT_RATIO_WIDTH = 16;
constexpr int ASPECT_RATIO_HEIGHT = 9;

PictureFrame::PictureFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
        : wxFrame(nullptr, wxID_ANY, title, pos, size) {
    this->Bind(wxEVT_SIZE, &PictureFrame::HandleSizeChange, this);
}

void PictureFrame::HandleSizeChange(wxSizeEvent& event) {
    // 사용자 정의 크기 조정 로직 먼저 실행
    wxSize size = event.GetSize();
    int newWidth = size.GetWidth();
    int newHeight = size.GetHeight();
    if (newWidth != ASPECT_RATIO_WIDTH * newHeight / ASPECT_RATIO_HEIGHT) {
        newHeight = newWidth * ASPECT_RATIO_HEIGHT / ASPECT_RATIO_WIDTH;
        this->SetSize(wxSize(newWidth, newHeight));
    }

    // 이벤트 처리를 계속 진행 함
    event.Skip();
}
