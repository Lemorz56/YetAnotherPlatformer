cmake_minimum_required(VERSION 3.16)
project(YetAnotherPlatformer)

set(CMAKE_CXX_STANDARD 14)

# Setting SDL2 Variable to path
set(SDL2 ${SDL2} "C:/Dev/SDL2-MINGW")
set(SDL2_IMAGE_PATH ${SDL2_IMAGE_PATH} "C:/Dev/SDL2_image-2.0.5")
set(SDL2_TTF_PATH ${SDL2_TTF_PATH} "C:/Dev/SDL2_ttf-2.0.15")

# Use modified FindSDL2* module
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/findmods")
# Setting OUTPUT dir for BINARIES
#set(BIN_DIR ${BrickBreaker_SOURCE_DIR}/bin)

# Bump up warning levels appropriately for clang, gcc & msvc
# Also set debug/optimization flags depending on the build type. IDE users choose this when
# selecting the build mode in their IDE
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++11")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -g")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -O2")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
endif()

# Look up SDL2 and add the include directory to our include path
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})

add_executable(YetAnotherPlatformer src/main.cpp src/graphics.cpp src/game.cpp src/input.cpp src/sprite.cpp src/animatedsprite.cpp)

target_link_libraries(YetAnotherPlatformer ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})

#install(TARGETS YetAnotherPlatformer RUNTIME DESTINATION ${BIN_DIR})