aux_source_directory(. DIR_TESTS_SRCS)
add_executable(Test ${DIR_TESTS_SRCS} ${DIR_TESTS_SRCS})

target_link_libraries(Test WebEnginx CppUTest)