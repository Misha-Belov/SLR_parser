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

set(SOURCES
    src/main.cpp
    src/parser.cpp
    src/slr_table.cpp
    ${GENERATED_LEXER}
)

add_executable(slr_parser ${SOURCES})