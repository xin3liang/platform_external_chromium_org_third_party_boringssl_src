include_directories(../include)

add_executable(
	bssl

	args.cc
	client.cc
	const.cc
	speed.cc
	tool.cc
)

if (APPLE)
	target_link_libraries(bssl ssl crypto)
else()
	target_link_libraries(bssl ssl crypto -lrt)
endif()
