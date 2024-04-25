#ifndef PICTUREFRAME_H
#define PICTUREFRAME_H

#include <wx/wx.h>

class PictureFrame : public wxFrame {
public:
    PictureFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

private:
    void OnSize(wxSizeEvent& event);
};

#endif // PICTUREFRAME_H
