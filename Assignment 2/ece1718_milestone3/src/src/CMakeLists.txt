# Generated from milestone3

set(filenames
	milestone3.c
	Source_host.c
	encrypt.c
	decrypt.c
	printer.c
)

# [MSVC] Ensure OpenCV imported targets are reachable in this file
# They may be imported in ${extra_libraries}
find_package(OpenCV QUIET)

include_directories(${extra_includes})
add_definitions(${extra_definitions})
add_executable(milestone3 ${filenames})

# Build library without any external library required
target_link_libraries(milestone3 orcc-native orcc-runtime ${extra_libraries})
