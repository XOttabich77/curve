cmake_minimum_required(VERSION 3.4.0)

project(shape3d  CXX)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_CXX_STANDARD 17)
set(INCLUDE_LIB shapelib)
set(DLIB_NAME ShapeLibDynamic)

add_compile_options(
    -Werror

    -Wall
    -Wextra
    -Wpedantic

    -Wcast-align
    -Wcast-qual
    -Wconversion
    -Wctor-dtor-privacy
    -Wenum-compare
    -Wfloat-equal
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Woverloaded-virtual
    -Wredundant-decls
    -Wsign-conversion
    -Wsign-promo
    -fopenmp-simd
)

if(NOT CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

#add_library(${DLIB_NAME} SHARED ${INCLUDE_LIB}/circle.cpp ${INCLUDE_LIB}/ellipse.cpp ${INCLUDE_LIB}/helixe.cpp)
#target_include_directories((${DLIB_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/${INCLUDE_LIB})
#target_include_directories((${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/${INCLUDE_LIB})
#target_link_libraries(${PROJECT_NAME})

add_executable(${PROJECT_NAME} main.cpp ${INCLUDE_LIB}/circle.cpp ${INCLUDE_LIB}/ellipse.cpp ${INCLUDE_LIB}/helixe.cpp 
${INCLUDE_LIB}/shape.h 
${INCLUDE_LIB}/circle.h ${INCLUDE_LIB}/ellipse.h ${INCLUDE_LIB}/helixe.h
log_duration.h)
