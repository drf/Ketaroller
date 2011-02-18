include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${CMAKE_CURRENT_SOURCE_DIR}
                    ${CMAKE_SOURCE_DIR}/3rdparty/oscpack/ip
                    ${CMAKE_SOURCE_DIR}/3rdparty/oscpack)

add_executable(tuioredirector main.cpp)
target_link_libraries(tuioredirector oscpack)
