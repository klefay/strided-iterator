find_package(Catch2 REQUIRED)

include(CTest)
include(Catch)

set(SOURCES
    catch_main.cpp
    buffer_2d_test.cpp)

add_executable(tests ${SOURCES})
target_include_directories(tests 
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(tests
    PRIVATE
        Catch2::Catch2)

catch_discover_tests(tests)
add_test(
    NAME tests
    COMMAND $<TARGET_FILE:tests>
)
