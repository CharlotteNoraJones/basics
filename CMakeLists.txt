cmake_minimum_required(VERSION 3.14.0)

project(Basics VERSION 0.1 LANGUAGES CXX)

# Dependencies
set(RAYLIB_VERSION 5.5)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)
        FetchContent_Declare(
        raylib
        DOWNLOAD_EXTRACT_TIMESTAMP OFF
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG ${RAYLIB_VERSION}
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()
endif()

FetchContent_Declare(
    flecs
    GIT_REPOSITORY "https://github.com/SanderMertens/flecs"
    GIT_TAG "master"
    GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(flecs)

add_executable(Basics src/main.cpp)

if (MSVC)
    target_compile_options(Basics PRIVATE /W4 /Wall /WX)
else()
    target_compile_options(Basics PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

set_target_properties(Basics PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS OFF)

target_link_libraries(Basics raylib)
target_link_libraries(Basics flecs::flecs_static)