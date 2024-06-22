enable_testing()

include(GoogleTest)

file(GLOB testSources *.cpp)
add_executable(run_gtests ${testSources} ${SOURCES})

# -fsanitize=address required to show stack trace.
target_compile_options(run_gtests PUBLIC -fsanitize=address -g)

target_link_libraries(run_gtests asan gtest gtest_main jsoncpp_lib)

add_custom_command(TARGET run_gtests POST_BUILD COMMAND run_gtests --output-on-failure --gmock_verbose=info --gtest_stack_trace_depth=10)

# file(COPY ../../../allCards.json ../)
