
add_executable(main
                ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/server.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/client.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/threadsHandler.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/allocator.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/watcher.cpp
)

target_include_directories(main PUBLIC inc)