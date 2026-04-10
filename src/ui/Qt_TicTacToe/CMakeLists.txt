# CMakeLists.txt
cmake_minimum_required(VERSION 3.16)
project(Qt_TicTacToe)
include_directories(../../engine/)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)  # Enable automatic MOC for Qt signals/slots
set(CMAKE_AUTOUIC ON)  # Enable automatic UIC for Qt UI files
set(CMAKE_AUTORCC ON)  # Enable automatic RCC for Qt resources

set(Qt6_DIR "F:\\Qt\\6.11.0\\msvc2022_64\\lib\\cmake\\Qt6")
# Find Qt6 or Qt5
find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

add_executable(Qt_TicTacToe
    Qt_TicTacToe.cpp
    QtTicTacToe_Board.cpp
../../engine/TicTacToeBoard.cpp
../../engine/SearchEngine.cpp
../../engine/types_tictactoe.cpp
../../engine/SearchEngineBase.cpp
../../engine/SearchEngineConsole.cpp
)

target_link_libraries(${PROJECT_NAME}
    Qt6::Widgets  # Or Qt5::Widgets
)

# Set properties (optional)
set_target_properties(${PROJECT_NAME} PROPERTIES
    WIN32_EXECUTABLE TRUE  # On Windows, create a GUI app without console
)