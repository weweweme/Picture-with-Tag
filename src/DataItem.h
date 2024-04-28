#ifndef DATAITEM_H
#define DATAITEM_H

#include <wx/string.h>
#include <wx/image.h>
#include <set>
#include <utility>

/**
 * @class DataItem
 * @brief 어플리케이션을 위한 단일 데이터 항목을 나타냅니다.
 *
 * 이 클래스는 하나의 데이터 항목에 필요한 모든 정보를 저장하기 위해 설계되었습니다.
 * 제목, 태그 집합, 설명적인 본문 텍스트 및 관련 이미지를 포함합니다.
 *
 * @param title 데이터 항목의 제목을 나타내는 wxString.
 * @param tags 데이터 항목과 연관된 태그들을 포함하는 wxString의 집합.
 * @param body 데이터 항목의 주요 설명 텍스트를 포함하는 wxString.
 * @param picture 데이터 항목과 관련된 이미지를 담고 있는 wxImage.
 */
class DataItem {
public:
    wxString title;
    std::set<wxString> tags;
    wxString body;
    wxImage picture;

    DataItem(wxString title, const std::set<wxString>& tags, wxString body, wxImage picture)
            : title(std::move(title)), tags(tags), body(std::move(body)), picture(std::move(picture)) {}
};

#endif // DATAITEM_H
