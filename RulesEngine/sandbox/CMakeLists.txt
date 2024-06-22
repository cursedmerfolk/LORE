file(GLOB sandboxSources *.cpp)
add_executable(run_sandbox ${sandboxSources} ${SOURCES})

# -fsanitize=address required to show stack trace.
target_compile_options(run_sandbox PUBLIC -g)

target_link_libraries(run_sandbox jsoncpp_lib)

add_custom_command(TARGET run_sandbox POST_BUILD COMMAND run_sandbox)
