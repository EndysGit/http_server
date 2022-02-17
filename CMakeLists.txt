cmake_minimum_required(VERSION 3.7...3.20)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(QtHttpServerTestTask
        VERSION 0.0.1
        DESCRIPTION "Simple http server"
        LANGUAGES CXX)

# Set up compile flags
if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-std=c++17 -Wall -Wextra -Wpedantic -O3)
endif()

# Add include dir
set(INCLUDE_DIRS include)
include_directories(${INCLUDE_DIRS})

add_executable(${PROJECT_NAME} src/main.cpp
        src/TestTaskApp.cpp  include/TestTaskApp.hpp
        src/ApiResolver.cpp  include/ApiResolver.hpp
        src/TestResolver.cpp include/TestResolver.hpp
        src/HttpServer.cpp   include/HttpServer.hpp
        src/Database.cpp     include/Database.hpp
        src/HttpRequest.cpp  include/HttpRequest.hpp
        src/HttpResponse.cpp include/HttpResponse.hpp
        src/HttpBody.cpp     include/HttpBody.hpp
        src/HttpHeader.cpp   include/HttpHeader.hpp
        src/http_core.cpp    include/http_core.hpp)

find_package(Qt5 COMPONENTS Network REQUIRED)
if(TARGET Qt5::Network)
    target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Network)
endif()
