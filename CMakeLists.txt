# Main configuration

cmake_minimum_required(VERSION 3.28)
project(ChatRoom_backend)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")


file(GLOB SOURCES "${SOURCE_DIR}/*.cpp")



# Adding dependencies

include(FetchContent)

FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG master
)

FetchContent_Declare(
        ixwebsocket
        GIT_REPOSITORY https://github.com/machinezone/IXWebSocket.git
        GIT_TAG master
)

FetchContent_MakeAvailable(json ixwebsocket)


# Link the project

add_executable(ChatRoom_backend ${SOURCE_DIR}/main.cpp)

target_link_libraries(
        ChatRoom_backend
        nlohmann_json::nlohmann_json
        ixwebsocket
)


