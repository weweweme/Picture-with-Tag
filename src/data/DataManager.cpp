#include "DataManager.h"
#include <boost/archive/text_iarchive.hpp>
#include "../helper/Constants.h"

std::vector<DataItem> DataManager::LoadDataItems() {
    std::vector<DataItem> items; // DataItem 객체들을 저장할 벡터

    // OS 문서 디렉토리 경로를 가져옵니다.
    wxString docDir = wxStandardPaths::Get().GetDocumentsDir();
    // 검색 대상이 될 디렉토리 경로를 설정합니다.
    wxString targetDir = docDir + DATA_ITEMS_DIR;

    // 해당 디렉토리가 존재하는지 확인합니다.
    if (!(wxDirExists(targetDir))) {
        // TODO: 디렉터리가 존재하지 않을 경우 피드백 구현
    }

    wxDir dir(targetDir); // 디렉토리 객체를 생성합니다.
    wxString filename; // 파일 이름을 저장할 변수
    // 첫 번째 '.pwt' 확장자를 가진 파일 이름을 가져옵니다.
    bool cont = dir.GetFirst(&filename, "*.pwt", wxDIR_FILES);

    // 파일이 존재하는 동안 반복합니다.
    while (cont) {
        // 파일의 전체 경로를 구성합니다.
        wxString filePath = targetDir + "/" + filename;
        // 파일을 바이너리 모드로 읽기 위해 열기 시도
        std::ifstream ifs(filePath.ToStdString(), std::ios::binary);
        if (ifs.is_open()) { // 파일 열기 성공 시
            try {
                boost::archive::text_iarchive ia(ifs); // 역직렬화를 위한 아카이브 객체 생성
                DataItem item; // 데이터 아이템 객체
                ia >> item; // 파일에서 데이터 아이템 역직렬화
                items.push_back(item); // 벡터에 데이터 아이템 추가
            } catch (const boost::archive::archive_exception& e) {
                // 파일 읽기 또는 역직렬화 중 발생한 예외 처리
                wxLogError(_("Failed to load data item from %s, error: %s"), filePath, wxString(e.what()));
            }
            ifs.close(); // 파일 스트림 닫기
        }
        // 다음 파일로 이동
        cont = dir.GetNext(&filename);
    }

    return items; // 로드된 데이터 아이템의 벡터 반환
}

void DataManager::OpenDataDirectory() {
    wxString path = wxStandardPaths::Get().GetDocumentsDir() + DATA_ITEMS_DIR;

    if (!wxDirExists(path)) {
        if (!wxMkdir(path)) {
            wxLogError(DIRECTORY_CREATION_FAIL, path);
            wxMessageBox(DIRECTORY_CREATION_FAIL, ERROR_TITLE, wxICON_ERROR);
            return;
        }
    }

#ifdef __WXMSW__
    wxExecute("explorer \"" + path + "\"", wxEXEC_ASYNC);
#elif defined(__WXMAC__)
    wxExecute("open \"" + path + "\"", wxEXEC_ASYNC);
#else
    wxExecute("xdg-open \"" + path + "\"", wxEXEC_ASYNC);
#endif
}
