if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
	add_subdirectory(googletest-master)
endif()	

add_subdirectory(json-develop)
add_subdirectory(spdlog-1.x)
add_subdirectory(fmt-8.1.1)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
	# Bu projeyi VS icerisinde ayri bir folderda tutalim
	set_target_properties(fmt PROPERTIES FOLDER ext/fmt)
	set_target_properties(nlohmann_json PROPERTIES FOLDER ext/json-develop)
	set_target_properties(spdlog PROPERTIES FOLDER ext/spdlog)
	set_target_properties(gmock PROPERTIES FOLDER ext/GoogleTest)
	set_target_properties(gtest PROPERTIES FOLDER ext/GoogleTest)
	set_target_properties(gmock_main PROPERTIES FOLDER ext/GoogleTest)
	set_target_properties(gtest_main PROPERTIES FOLDER ext/GoogleTest)
endif()	