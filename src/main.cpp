#include <wx/wx.h>

class MyApp : public wxApp {
public:
    virtual bool OnInit() override; // 선언에서 반환 타입을 명시합니다.
};

class MyFrame : public wxFrame {
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
};

// MyApp 클래스의 OnInit 메서드 구현
bool MyApp::OnInit() {
    MyFrame* frame = new MyFrame("Picture with Tag", wxPoint(50, 50), wxSize(1920, 1080));
    frame->Show(true);
    return true;
}

// MyFrame 클래스의 생성자 구현
MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
        : wxFrame(NULL, wxID_ANY, title, pos, size) {
    // 여기에 추가적인 초기화 코드를 작성할 수 있습니다.
}

wxIMPLEMENT_APP(MyApp);
