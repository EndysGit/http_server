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

add_executable(${PROJECT_NAME} src/main.cpp include/HttpRequest.hpp include/HttpResponse.hpp include/http_message.hpp include/http_core.hpp include/Config.hpp include/ApiResolver.hpp include/TestResolver.hpp include/Resolver.hpp include/HttpServer.hpp include/HttpHeader.hpp include/HttpBody.hpp include/Database.hpp include/Application.hpp src/TestTaskApp.cpp include/TestTaskApp.hpp src/ApiResolver.cpp src/TestResolver.cpp src/HttpServer.cpp include/HttpMessageBase.hpp src/Database.cpp src/HttpRequest.cpp src/HttpResponse.cpp src/HttpBody.cpp src/HttpHeader.cpp src/http_core.cpp)

set(CMAKE_PREFIX_PATH "/home/endyxx/Applications/Qt/5.15.2/gcc_64")

find_package(Qt5 COMPONENTS Core Network REQUIRED)
if(TARGET Qt5::Network)
    target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Network)
endif()
