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
        src/TitlePage.h
        src/AppInitializer.cpp
        src/TitlePage.cpp
        src/PageID.h
        src/BasePage.h
        src/BasePage.cpp
        src/AddPage.h
        src/AddPage.cpp
        src/PageManager.h
        src/PageManager.cpp
        src/SearchPage.h
        src/SearchPage.cpp
        src/DataManagementPage.h
        src/DataManagementPage.cpp
        src/DataItem.h
        src/GlobalColors.h
        src/GlobalColors.cpp)

target_link_libraries(Picture_with_Tag ${wxWidgets_LIBRARIES} ${Boost_LIBRARIES})

