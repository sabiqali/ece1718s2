# Generated from TopMilestone2Design2

set(filenames
	TopMilestone2Design2.c
	Source.c
	Duplicate.c
	Approx.c
	Abs_Diff.c
	Sum.c
	Printer.c
)

# [MSVC] Ensure OpenCV imported targets are reachable in this file
# They may be imported in ${extra_libraries}
find_package(OpenCV QUIET)

include_directories(${extra_includes})
add_definitions(${extra_definitions})
add_executable(TopMilestone2Design2 ${filenames})

# Build library without any external library required
target_link_libraries(TopMilestone2Design2 orcc-native orcc-runtime ${extra_libraries})
