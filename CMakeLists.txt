cmake_minimum_required (VERSION 3.8)

project ("TSP")

set(SOURCES
	"src/app/iapplication.cpp"
	"src/app/preconfigured_application.cpp"
	"src/app/menu_application.cpp"
	"src/io/file/configuration/ini/parser.cpp"
	"src/io/file/problem/tsp/parser.cpp"
	"src/io/file/problem/txt/parser.cpp"
	"src/io/file/problem/iproblemparser.cpp"
	"src/io/file/route/parser.cpp"
	"src/io/reader.cpp"
	"src/tsp/algorithm/accurate/bb/dfs.cpp"
	"src/tsp/algorithm/accurate/bf.cpp"
	"src/tsp/algorithm/algorithm.cpp"
	"src/tsp/neighborhood/random.cpp"
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