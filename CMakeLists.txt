cmake_minimum_required(VERSION 3.28)
project(Picture_with_Tag)

# C++ 표준 설정
set(CMAKE_CXX_STANDARD 20)

# wxWidgets 설정
find_package(wxWidgets REQUIRED core base)
include(${wxWidgets_USE_FILE})

# Boost 설정
find_package(Boost 1.65 REQUIRED COMPONENTS serialization)
include_directories(${Boost_INCLUDE_DIRS})

# 실행 파일 이름과 소스 파일 경로를 지정
add_executable(Picture_with_Tag
        src/AppInitializer.h
        src/page/TitlePage.h
        src/AppInitializer.cpp
        src/page/TitlePage.cpp
        src/page/PageID.h
        src/page/BasePage.h
        src/page/BasePage.cpp
        src/page/AddPage.h
        src/page/AddPage.cpp
        src/page/PageManager.h
        src/page/PageManager.cpp
        src/page/SearchPage.h
        src/page/SearchPage.cpp
        src/data/DataItem.h
        src/helper/GlobalColors.h
        src/helper/GlobalColors.cpp
        src/helper/UIHelpers.h
        src/helper/UIHelpers.cpp
        src/helper/Constants.h)

target_link_libraries(Picture_with_Tag ${wxWidgets_LIBRARIES} ${Boost_LIBRARIES})

