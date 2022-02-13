cmake_minimum_required(VERSION 3.20)
project(QtHttpServer_test)

set(CMAKE_CXX_STANDARD 17)
# Set up compile flags
if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-std=c++17 -Wall -Wextra -Wpedantic -O3 )
endif()

# Add include dir
set(INCLUDE_DIRS include)
include_directories(${INCLUDE_DIRS})

add_executable(${PROJECT_NAME} src/main.cpp include/http_request.h include/http_response.hpp include/http_message.hpp include/http_core.hpp include/config.hpp include/api.hpp include/test.hpp include/resolver.hpp include/http_server.hpp include/http_header.hpp include/http_body.hpp)

set(CMAKE_PREFIX_PATH "/home/endyxx/Applications/Qt/5.15.2/gcc_64")

find_package(Qt5 COMPONENTS Core Network REQUIRED)
if(TARGET Qt5::Network)
    target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Network)
endif()
