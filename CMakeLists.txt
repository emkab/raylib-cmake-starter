cmake_minimum_required(VERSION 3.16)

project(raylib-starter CXX C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 20)

if(NOT MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer -g")
endif()

add_subdirectory(vendor/raylib)


file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.c ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC include)

if(NOT MSVC)
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG}")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}")
endif()

# Add raylib include directory
target_include_directories(${PROJECT_NAME} PRIVATE vendor/raylib/src)


# Define path to ANGLE libraries if using ANGLE
if (USE_ANGLE)
    set(ANGLE_LIBRARY_DIR "${CMAKE_SOURCE_DIR}/libs")

    # Find ANGLE libraries
    find_library(ANGLE_GLESv2_LIBRARY libGLESv2.dylib PATHS ${ANGLE_LIBRARY_DIR})
    find_library(ANGLE_EGL_LIBRARY libEGL.dylib PATHS ${ANGLE_LIBRARY_DIR})

    # Check if the libraries were found
    if (NOT ANGLE_GLESv2_LIBRARY OR NOT ANGLE_EGL_LIBRARY)
        message(FATAL_ERROR "ANGLE libraries not found in ${ANGLE_LIBRARY_DIR}")
    endif()

    # Set runtime path for ANGLE libraries
    set_target_properties(${PROJECT_NAME} PROPERTIES
        BUILD_RPATH ${ANGLE_LIBRARY_DIR}
    )

    target_include_directories(${PROJECT_NAME} PUBLIC vendor/angle/include)
    target_include_directories(raylib PUBLIC vendor/angle/include)
endif()


# Link against raylib libraries and ANGLE if using ANGLE
target_link_libraries(${PROJECT_NAME} raylib)
if (USE_ANGLE)
    target_link_libraries(${PROJECT_NAME} ${ANGLE_GLESv2_LIBRARY} ${ANGLE_EGL_LIBRARY})
endif()