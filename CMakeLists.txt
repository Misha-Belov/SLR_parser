cmake_minimum_required(VERSION 3.16)
project(SLRParser LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# -----------------------------
# Flex
# -----------------------------
find_package(FLEX REQUIRED)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/generated)

# Путь к lexer.l
set(LEXER_FILE ${CMAKE_SOURCE_DIR}/lexer/lexer.l)
set(GENERATED_LEXER ${CMAKE_BINARY_DIR}/generated/lexer.cpp)

# Генерация lexer.cpp
FLEX_TARGET(
    Lexer
    ${LEXER_FILE}
    ${GENERATED_LEXER}
)

# -----------------------------
# Include directories
# -----------------------------
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_BINARY_DIR}/generated
)

# -----------------------------
# Source files
# -----------------------------
set(SOURCES
    src/main.cpp
    src/parser.cpp
    src/slr_table.cpp
    ${FLEX_Lexer_OUTPUTS}
)

# -----------------------------
# Executable
# -----------------------------
add_executable(slr_parser ${SOURCES})

# Link Flex library
if(UNIX)
    target_link_libraries(slr_parser PRIVATE fl)
endif()
