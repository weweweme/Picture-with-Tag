#include "UIHelpers.h"

wxStaticText* UIHelpers::CreateStaticText(wxWindow* parent, const wxString& label, const wxPoint& pos, const wxSize& size) {
    return new wxStaticText(parent, wxID_ANY, label, pos, size);
}

wxTextCtrl* UIHelpers::CreateTextCtrl(wxWindow* parent, const wxString& defaultValue, const wxPoint& pos, const wxSize& size, long style) {
    return new wxTextCtrl(parent, wxID_ANY, defaultValue, pos, size, style);
}

wxButton* UIHelpers::CreateButton(wxWindow* parent, const wxString& label, const wxPoint& pos, const wxSize& size, long style) {
    return new wxButton(parent, wxID_ANY, label, pos, size, style);
}

wxListBox* UIHelpers::CreateListBox(wxWindow* parent, const wxPoint& pos, const wxSize& size, long style) {
    return new wxListBox(parent, wxID_ANY, pos, size, 0, nullptr, style);
}

wxChoice* UIHelpers::CreateChoice(wxWindow* parent, const wxArrayString& choices, const wxPoint& pos, const wxSize& size) {
    auto* choice = new wxChoice(parent, wxID_ANY, pos, size);
    for (const auto& item : choices) {
        choice->Append(item);
    }

    return choice;
}

// SetControlColours 구현은 컨트롤에 대한 배경색과 전경색을 설정합니다.
void UIHelpers::SetControlColours(wxWindow* control, const wxColour& background, const wxColour& foreground) {
    control->SetBackgroundColour(background);
    control->SetForegroundColour(foreground);
}
