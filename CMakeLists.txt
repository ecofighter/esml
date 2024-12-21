cmake_minimum_required(VERSION 3.21)

project(esml VERSION 0.0.1 LANGUAGES C)
add_compile_options(-Wall -Wextra -Wpedantic)
set(CMAKE_C_FLAGS_DEBUG "-g3 -O0")
set(CMAKE_C_FLAGS_RELEASE "-g -O2")

set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")
file(GLOB SRCS "${SRC_DIR}/*.c")

set(PARSER_DIR "${CMAKE_CURRENT_BINARY_DIR}")
set(PARSER_INPUT "${SRC_DIR}/parser.y")
set(PARSER_OUTPUT_C "${PARSER_DIR}/parser.c")
set(PARSER_OUTPUT_H "${PARSER_DIR}/parser.h")
set(PARSER_OUTPUT "${PARSER_OUTPUT_C}" "${PARSER_OUTPUT_H}")
set(LEXER_INPUT "${SRC_DIR}/lexer.l")
set(LEXER_OUTPUT_C "${PARSER_DIR}/lexer.c")
set(LEXER_OUTPUT_H "${PARSER_DIR}/lexer.h")
set(LEXER_OUTPUT "${LEXER_OUTPUT_C}" "${LEXER_OUTPUT_H}")

find_program(BYACC_EXECUTABLE NAMES byacc DOC "path to byacc executable")
mark_as_advanced(BYACC_EXECUTABLE)
find_program(FLEX_EXECUTABLE NAMES flex DOC "path to flex executable")
mark_as_advanced(FLEX_EXECUTABLE)

add_custom_command(OUTPUT ${PARSER_OUTPUT}
  COMMAND ${BYACC_EXECUTABLE} -H ${PARSER_OUTPUT_H} -o ${PARSER_OUTPUT_C} ${PARSER_INPUT}
  DEPENDS ${PARSER_INPUT}
)
add_custom_command(OUTPUT ${LEXER_OUTPUT}
  COMMAND ${FLEX_EXECUTABLE} --header-file=${LEXER_OUTPUT_H} -o ${LEXER_OUTPUT_C} ${LEXER_INPUT}
  DEPENDS ${LEXER_INPUT}
)

add_executable(esml ${SRCS} ${LEXER_OUTPUT} ${PARSER_OUTPUT})
target_include_directories(esml PRIVATE "${SRC_DIR}")
target_include_directories(esml PRIVATE "${PARSER_DIR}")
set_property(TARGET esml PROPERTY C_EXTENSIONS OFF)
set_property(TARGET esml PROPERTY C_STANDARD 99)
if(UNIX)
  add_compile_definitions(_POSIX_C_SOURCE=200809L)
endif(UNIX)

# enable_testing()
# set(TEST_DIR "test")
# add_executable(test_lexer "${TEST_DIR}/test_lexer.c" "${SRC_DIR}/token.c" "${SRC_DIR}/lexer.c")
# target_include_directories(test_lexer PRIVATE ${SRC_DIR})
# add_test(NAME test_lexer COMMAND $<TARGET_FILE:test_lexer>)
