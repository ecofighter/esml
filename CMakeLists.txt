cmake_minimum_required(VERSION 3.21)

project(esml VERSION 0.0.1 LANGUAGES C)
add_compile_options(-g -Wall -Wextra -Wpedantic)

set(SRC_DIR "src")
file(GLOB SRCS "${SRC_DIR}/*.c")

find_package(FLEX 2.6 REQUIRED)
find_package(BISON 3.0 REQUIRED)
set(PARSER_DIR "${CMAKE_CURRENT_BINARY_DIR}")
set(LEXER_OUT "${PARSER_DIR}/lexer.c")
set(PARSER_OUT "${PARSER_DIR}/parser.c")

flex_target(LEXER "${SRC_DIR}/lexer.l" "${LEXER_OUT}"
            COMPILE_FLAGS --posix-compat
            DEFINES_FILE "${PARSER_DIR}/lexer.h")
bison_target(PARSER "${SRC_DIR}/parser.y" "${PARSER_OUT}"
             COMPILE_FLAGS -y
             DEFINES_FILE "${PARSER_DIR}/parser.h")
add_flex_bison_dependency(LEXER PARSER)

add_executable(esml ${SRCS} ${LEXER_OUT} ${PARSER_OUT})
target_include_directories(esml PRIVATE "${SRC_DIR}")
target_include_directories(esml PRIVATE "${PARSER_DIR}")
set_property(TARGET esml PROPERTY C_EXTENSIONS OFF)
set_property(TARGET esml PROPERTY C_STANDARD 11)

# enable_testing()
# set(TEST_DIR "test")
# add_executable(test_lexer "${TEST_DIR}/test_lexer.c" "${SRC_DIR}/token.c" "${SRC_DIR}/lexer.c")
# target_include_directories(test_lexer PRIVATE ${SRC_DIR})
# add_test(NAME test_lexer COMMAND $<TARGET_FILE:test_lexer>)
