cmake_minimum_required(VERSION 3.16)
project(SLRParser LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(FLEX REQUIRED)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/generated)

set(LEXER_FILE ${CMAKE_SOURCE_DIR}/lexer/lexer.l)
set(GENERATED_LEXER ${CMAKE_BINARY_DIR}/generated/lexer.cpp)

FLEX_TARGET(Lexer ${LEXER_FILE} ${GENERATED_LEXER})

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_BINARY_DIR}/generated
)

# Библиотека парсера (без main)
set(PARSER_LIB_SOURCES
    src/parser.cpp
    src/slr_table.cpp
    src/tokens.cpp
    ${GENERATED_LEXER}
)

add_library(slr_parser_lib STATIC ${PARSER_LIB_SOURCES})

# Основной исполняемый файл
add_executable(slr_parser src/main.cpp)
target_link_libraries(slr_parser PRIVATE slr_parser_lib)

# Опция для тестов
option(ENABLE_TESTS "Build tests" OFF)

if(ENABLE_TESTS)
    add_executable(slr_tests tests/test_parser.cpp)
    target_link_libraries(slr_tests PRIVATE slr_parser_lib)
endif()