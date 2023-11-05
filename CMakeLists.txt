﻿cmake_minimum_required (VERSION 3.8)

project ("TSP")

set(SOURCES
	"src/app/preconfigured_application.cpp"
	"src/app/menu_application.cpp"
	"src/io/file/ini/parser.cpp"
	"src/io/file/tsp/parser.cpp"
	"src/io/reader.cpp"
	"src/tsp/algorithm/algorithm.cpp"
	"src/tsp/algorithm/bf.cpp"
	"src/ui/menu/callable_entry.cpp"
	"src/ui/menu/entry.cpp"
	"src/ui/menu/submenu.cpp"
	"src/ui/menu.cpp"
	"src/utils/tokenizer.cpp"
	"src/main.cpp"
	)

add_executable (TSP ${SOURCES})
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
	include
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()