cmake_minimum_required(VERSION 3.17)
project(todo_list)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_PREFIX_PATH "/usr/bin/cmake")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets Sql)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Sql)

add_executable(${PROJECT_NAME} main.cpp MainWindow.cpp MainWindow.h AuthorizationWindow.cpp AuthorizationWindow.h RegistrationWindow.cpp RegistrationWindow.h UserService.cpp UserService.h)

if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\" or -DCMAKE_PREFIX_PATH=/usr/include/{host}/qt{version}/ on Ubuntu)")
endif ()

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
