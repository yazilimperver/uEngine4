if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
	add_subdirectory(googletest-master)
endif()	

add_subdirectory(json-develop)
add_subdirectory(fmt-8.1.1)
add_subdirectory(glm)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
	set(EXT_PROJECTS_VS_FILTER uengine_ext)

	# Bu projeyi VS icerisinde ayri bir folderda tutalim
	set_target_properties(spdlog PROPERTIES FOLDER ${EXT_PROJECTS_VS_FILTER}/spdlog)
	set_target_properties(glm PROPERTIES FOLDER ${EXT_PROJECTS_VS_FILTER}/glm)
	set_target_properties(fmt PROPERTIES FOLDER ${EXT_PROJECTS_VS_FILTER}/fmt)
	set_target_properties(nlohmann_json PROPERTIES FOLDER ${EXT_PROJECTS_VS_FILTER}/json-develop)
	set_target_properties(gmock PROPERTIES FOLDER ${EXT_PROJECTS_VS_FILTER}/GoogleTest)
	set_target_properties(gtest PROPERTIES FOLDER ${EXT_PROJECTS_VS_FILTER}/GoogleTest)
	set_target_properties(gmock_main PROPERTIES FOLDER ${EXT_PROJECTS_VS_FILTER}/GoogleTest)
	set_target_properties(gtest_main PROPERTIES FOLDER ${EXT_PROJECTS_VS_FILTER}/GoogleTest)
endif()	