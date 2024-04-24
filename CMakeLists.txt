cmake_minimum_required(VERSION 3.28)
project(Picture_with_Tag)

# C++ 표준 설정
set(CMAKE_CXX_STANDARD 20)

# wxWidgets 설정
find_package(wxWidgets REQUIRED core base)
include(${wxWidgets_USE_FILE})

# 실행 파일 이름과 소스 파일 경로를 지정.
add_executable(Picture_with_Tag src/main.cpp)

# wxWidgets 라이브러리 링크
target_link_libraries(Picture_with_Tag ${wxWidgets_LIBRARIES})