#include "UIHelpers.h"

// SetControlColours 구현은 컨트롤에 대한 배경색과 전경색을 설정합니다.
void UIHelpers::SetControlColours(wxWindow* control, const wxColour& background, const wxColour& foreground) {
    control->SetBackgroundColour(background);
    control->SetForegroundColour(foreground);
}
