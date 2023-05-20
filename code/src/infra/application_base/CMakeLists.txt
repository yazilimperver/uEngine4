cmake_minimum_required(VERSION 3.10)

# Isimlendirme
set(LIB_NAME application_base)

# Baslik dosyalari
set(HEADER_FILES
	application_base.h
	client_graphic_application.h
	finger_data.h
	gamepad_axis_data.h
	gamepad_button_data.h
	gamepad_data.h
	gamepad_event_listener.h
	input_actions.h
	keyboard_codes.h
	keyboard_event_listener.h
	keyboard_modifiers.h
	mouse_buttons.h
	mouse_event_listener.h
	mouse_move_event_listener.h
	mouse_wheel_event_listener.h
	sdl_event_listener.h
	touch_action.h
	touch_data.h
	touch_event_handler.h
	touch_service.h
	window_parameter.h
	window_parameter_serializer.h
)

# Baslik dosya grubu (VS altindaki filtre gibi)
source_group("Header Files" FILES ${HEADER_FILES})

# Kaynak ve oluþturma dizinlerini otomatik olarak baslik dosyasi dizinine ekler
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Windows icin bir kac ek tanimlama
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

# Statik kutuphane olarak bu projeyi ekliyoruz
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
	add_library(${LIB_NAME} INTERFACE ${HEADER_FILES})
else()
	add_library(${LIB_NAME} INTERFACE)
endif()

# Windows icin bir kac ek tanimlama
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
	# Bu projeyi VS icerisinde ayri bir folderda tutalim
	set_target_properties(${LIB_NAME} PROPERTIES FOLDER infra)
endif()

# Kutuphaneleri baglayalim
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
	target_link_libraries(${LIB_NAME} INTERFACE spdlog_header_only)
endif()

# Baslik dosyalarinin yolunu ekleyelim
target_include_directories(${LIB_NAME} INTERFACE ${INFRA_INCLUDE_FOLDER})
target_include_directories(${LIB_NAME} INTERFACE .)