cmake_minumum_required(VERSION 3.10)

project(TaxiFindApp)

set(CMAKE_CXX_STANDARD 17)

inlcude_direcotires(inlcude)

find_package(OpenGL REQUIRED)
inlcude_directories(${OPENGL_INCLUDE_DIRS})

add_executable(
    TaxiFindApp
    src/main.cpp
    src/ui/MainWindow.cpp
    src/backend/GPSModule.cpp
    src/backend/TaxiFinder.cpp 
    src/backend/DatabaseManager.cpp 
    src/backend/MapAPI.cpp 
    src/backend/CloudManager.cpp 
)

target_link_libraries(TaxiBookingApp ${OPENGL_LIBRARIES})