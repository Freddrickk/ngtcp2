add_executable(ServerHandshakeFuzzer fuzzer.c
                                     ${CMAKE_SOURCE_DIR}/tests/ngtcp2_conn_test.c
                                     ${CMAKE_SOURCE_DIR}/tests/ngtcp2_test_helper.c)

target_include_directories(ServerHandshakeFuzzer PUBLIC "${CMAKE_SOURCE_DIR}/tests/"
                                                        "${CMAKE_SOURCE_DIR}/lib"
                                                        "${CMAKE_SOURCE_DIR}/lib/includes"
                                                        "${CMAKE_BINARY_DIR}/lib/includes"
                                                        ${CUNIT_INCLUDE_DIRS})

target_link_libraries(ServerHandshakeFuzzer PUBLIC ngtcp2_static ${CUNIT_LIBRARIES})
target_compile_options(ServerHandshakeFuzzer PUBLIC -g -fsanitize=fuzzer,address,signed-integer-overflow)
target_link_options(ServerHandshakeFuzzer PUBLIC -g -fsanitize=fuzzer,address,signed-integer-overflow)

target_compile_options(ngtcp2_static PUBLIC -g -fsanitize=fuzzer,address)
target_link_options(ngtcp2_static PUBLIC -g -fsanitize=fuzzer,address)

target_compile_definitions(ngtcp2_static PUBLIC NDEBUG)
