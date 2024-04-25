#include "PictureFrame.h"

PictureFrame::PictureFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
        : wxFrame(NULL, wxID_ANY, title, pos, size) {
    this->Bind(wxEVT_SIZE, &PictureFrame::OnSize, this);
}

void PictureFrame::OnSize(wxSizeEvent& event) {
    event.Skip();
    wxSize size = event.GetSize();
    int newWidth = size.GetWidth();
    int newHeight = size.GetHeight();
    if (newWidth != 16 * newHeight / 9) {
        newHeight = newWidth * 9 / 16;
        this->SetSize(wxSize(newWidth, newHeight));
    }
}
