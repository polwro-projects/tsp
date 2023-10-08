#pragma once

#include <fstream>
#include <string>

#include "io/file/ini/parser.hpp"
#include "io/file/tsp/parser.hpp"
#include "io/reader.hpp"
#include "math/matrix.hpp"
#include "tsp.hpp"

class Application final {
	using DistanceMatrix = io::file::tsp::Parser::DistanceMatrix;

public:
	Application(const std::string& config_file);
	~Application();

public:
	void Start();

protected:
	TSP::PositionList Solve(const DistanceMatrix& matrix);

private:
	io::file::ini::Parser::Parameters parameters_;
	std::ofstream output_file_;
};