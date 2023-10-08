cmake_minimum_required (VERSION 3.8)

project ("TSP")

set(SOURCES
	"src/io/file/ini/parser.cpp"
	"src/io/file/tsp/parser.cpp"
	"src/io/reader.cpp"
	"src/utils/tokenizer.cpp"
	"src/application.cpp"
	"src/main.cpp"
	"src/tsp.cpp"
	)

add_executable (TSP ${SOURCES})
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
	include
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()