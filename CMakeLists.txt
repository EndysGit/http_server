cmake_minimum_required(VERSION 3.7...3.20)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(QtHttpServerTestTask
        VERSION 0.0.1
        DESCRIPTION "Simple http server"
        LANGUAGES CXX)

# Add include dir
set(INCLUDE_DIRS include)
include_directories(${INCLUDE_DIRS})

add_library(cwt_http STATIC src/HttpRequest.cpp  include/HttpRequest.hpp
                            src/HttpResponse.cpp include/HttpResponse.hpp
                            src/HttpBody.cpp     include/HttpBody.hpp
                            src/HttpHeader.cpp   include/HttpHeader.hpp
                            src/http_core.cpp    include/http_core.hpp)
target_include_directories(cwt_http PUBLIC include)
target_compile_features(cwt_http PUBLIC cxx_std_17)
if (MSVC)
    target_compile_options(cwt_http PUBLIC /W4)
else()
    target_compile_options(cwt_http PUBLIC -std=c++17 -Wall -Wextra -Wpedantic -O3)
endif()

add_executable(${PROJECT_NAME} src/main.cpp
        src/TestTaskApp.cpp  include/TestTaskApp.hpp
        src/ApiResolver.cpp  include/ApiResolver.hpp
        src/TestResolver.cpp include/TestResolver.hpp
        src/HttpServer.cpp   include/HttpServer.hpp
        src/Database.cpp     include/Database.hpp)
if (MSVC)
    target_compile_options(${PROJECT_NAME} PUBLIC /W4)
else()
    target_compile_options(${PROJECT_NAME} PUBLIC -std=c++17 -Wall -Wextra -Wpedantic -O3)
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC cwt_http)

find_package(Qt5 COMPONENTS Network REQUIRED)
if(TARGET Qt5::Network)
    target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Network)
endif()
