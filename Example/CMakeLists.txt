file(GLOB_RECURSE SKOGA_EXAMPLE_SRC CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_executable(skoga_example ${SKOGA_EXAMPLE_SRC})

target_compile_definitions(skoga_example PUBLIC FMT_UNICODE=0)
target_include_directories(skoga_example PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

# Link internal libraries
target_link_libraries(skoga_example PRIVATE skoga)
if (MSVC)
    set_target_properties(skoga_example PROPERTIES
        LINK_FLAGS "/SUBSYSTEM:CONSOLE"
    )
endif()

target_compile_definitions(skoga_example PUBLIC GLM_ENABLE_EXPERIMENTAL)