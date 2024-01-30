cmake_minimum_required (VERSION 3.8)

project ("TSP")

set(SOURCES
	"src/application/iapplication.cpp"
	"src/application/menu/algorithm/algorithm.cpp"
	"src/application/menu/algorithm/branch_and_bound.cpp"
	"src/application/menu/algorithm/bruteforce.cpp"
	"src/application/menu/algorithm/genetic_algorithm.cpp"
	"src/application/menu/algorithm/simulated_annealing.cpp"
	"src/application/menu/math/matrix.cpp"
	"src/application/menu/route/route.cpp"
	"src/application/menu/application.cpp"
	"src/application/configuration/factory/algorithm/branch_and_bound.cpp"
	"src/application/configuration/factory/algorithm/bruteforce.cpp"
	"src/application/configuration/factory/algorithm/genetic.cpp"
	"src/application/configuration/factory/algorithm/simulated_annealing.cpp"
	"src/application/configuration/application.cpp"
	"src/io/file/configuration/ini/parser.cpp"
	"src/io/file/problem/tsp/parser.cpp"
	"src/io/file/problem/txt/parser.cpp"
	"src/io/file/problem/iproblemparser.cpp"
	"src/io/file/route/parser.cpp"
	"src/io/reader.cpp"
	"src/tsp/algorithm/accurate/bb/dfs.cpp"
	"src/tsp/algorithm/accurate/bf.cpp"
	"src/tsp/algorithm/inaccurate/genetic/algorithm.cpp"
	"src/tsp/algorithm/algorithm.cpp"
	"src/tsp/operators/crossover/algorithm.cpp"
	"src/tsp/operators/crossover/ox.cpp"
	"src/tsp/operators/mutation/algorithm.cpp"
	"src/tsp/operators/mutation/swap.cpp"
	"src/tsp/operators/selection/algorithm.cpp"
	"src/tsp/operators/selection/roulette.cpp"
	"src/tsp/operators/operator.cpp"
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