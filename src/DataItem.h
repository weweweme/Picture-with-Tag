#ifndef DATAITEM_H
#define DATAITEM_H

#include <wx/string.h>
#include <wx/image.h>
#include <wx/mstream.h>
#include <set>
#include <vector>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/set.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/string.hpp>

/**
 * @class DataItem
 * @brief 어플리케이션을 위한 단일 데이터 항목을 나타냅니다.
 * 이 클래스는 하나의 데이터 항목에 필요한 모든 정보를 저장하기 위해 설계되었습니다.
 * 제목, 태그 집합, 설명적인 본문 텍스트 및 관련 이미지를 포함합니다.
 */
class DataItem {
public:
    wxString title;
    std::set<wxString> tags;
    wxString body;
    std::vector<unsigned char> image_data; // 이미지 데이터를 바이너리 형태로 저장합니다.

    DataItem() = default;

    // 사용자로부터 입력받은 데이터로 DataItem 객체를 초기화합니다.
    // 이미지는 wxImage 객체로 받아, 이를 PNG 형식의 바이너리 데이터로 변환하여 저장합니다.
    // 이후, 메모리스트림을 사용하여 wxImage로부터 바로 바이너리 데이터를 추출 합니다.
    // wxWidgets에서는 이미지를 파일이 아닌 메모리 버퍼로 직접 저장하는 공식적인 방법을 제공하지 않으므로,
    // wxMemoryOutputStream을 사용하여 이미지 데이터를 메모리에 저장하고, 이를 std::vector로 복사합니다.
    // 이 방식을 사용함으로써 파일 시스템을 거치지 않고 데이터를 직접 메모리로 관리할 수 있습니다.
    DataItem(wxString title, const std::set<wxString>& tags, wxString body, const wxImage& picture)
            : title(std::move(title)), tags(tags), body(std::move(body)) {
        // 메모리 스트림을 생성합니다.
        wxMemoryOutputStream memStream;
        // 이미지를 PNG 형식으로 스트림에 저장합니다.
        picture.SaveFile(memStream, wxBITMAP_TYPE_PNG);

        size_t size = memStream.GetSize(); // 스트림의 크기를 가져옵니다.
        image_data.resize(size); // 이미지 데이터 벡터의 크기를 조정합니다.
        memStream.CopyTo(&image_data[0], size); // 스트림의 데이터를 이미지 데이터 벡터에 복사합니다.
    }

private:
    // Boost.Serialization 라이브러리를 위한 serialize 함수
    // 이 함수는 Boost.Serialization에 의해 호출되며, DataItem 객체의 데이터를 직렬화하고 역직렬화하는 데 사용됩니다.
    // friend class boost::serialization::access; 선언으로 인해,
    // Boost.Serialization 라이브러리가 이 private 멤버 함수에 접근할 수 있습니다.
    // Archive 타입은 데이터를 저장하거나 불러올 때 사용되는 아카이브 타입을 의미하며,
    // 이를 통해 다양한 형태의 데이터 저장 매체(예: 파일, 메모리, 네트워크 등)를 지원합니다.
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & title;
        ar & tags;
        ar & body;
        ar & image_data;
    }
};

// boost::serialization 네임스페이스 내에 wxString에 대한 커스텀 직렬화 함수 정의
namespace boost::serialization {

    // wxString 객체를 직렬화할 때 호출되는 save 함수
    // wxString을 std::string으로 변환하여 직렬화를 수행합니다.
    template<class Archive>
    void save(Archive & ar, const wxString& t, unsigned int version) {
        std::string s = std::string(t.mb_str()); // wxString을 std::string으로 변환
        ar & s; // 변환된 std::string을 직렬화
    }

    // wxString 객체를 역직렬화할 때 호출되는 load 함수
    // 직렬화된 데이터(std::string)을 읽어 wxString 객체를 복원합니다.
    template<class Archive>
    void load(Archive & ar, wxString& t, unsigned int version) {
        std::string s;
        ar & s; // 직렬화된 데이터(std::string)를 읽음
        t = wxString(s.c_str(), wxConvUTF8); // 읽은 데이터를 wxString 객체로 변환
    }

    // split_free 함수를 사용하여 wxString의 save와 load 함수를 분리하여 정의합니다.
    // 이는 직렬화와 역직렬화 로직을 별도로 구현할 수 있게 해줍니다.
    template<class Archive>
    void serialize(Archive & ar, wxString & t, const unsigned int version) {
        boost::serialization::split_free(ar, t, version);
    }

}

#endif // DATAITEM_H
