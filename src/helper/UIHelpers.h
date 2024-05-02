#ifndef UI_HELPERS_H
#define UI_HELPERS_H

#include <wx/window.h>
#include "GlobalColors.h"

class UIHelpers {
public:
    static void SetControlColours(wxWindow* control, const wxColour& background, const wxColour& foreground);
};

#endif // UI_HELPERS_H
