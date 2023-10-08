#pragma once

#include <fstream>
#include <string>

#include "io/file/ini/parser.hpp"
#include "io/reader.hpp"
#include "math/matrix.hpp"
#include "tsp.hpp"

class Application final {
public:
	Application(const std::string& config_file);
	~Application();

public:
	void Start();

protected:
	TSP::PositionList Solve(const math::Matrix<uint32_t>& matrix, int32_t start_position = -1);

private:
	io::file::ini::Parser::Parameters parameters_;
	std::ofstream output_file_;
};