#pragma once 

#include <string>
#include <fstream>

#include "tsp.hpp"
#include "io/reader.hpp"
#include "math/matrix.hpp"

class Application final {
public:
	Application(const std::string& config_file);
	~Application();

public:
	void Start();

protected:
	TSP::PositionList Solve(const math::Matrix<uint32_t>& matrix, int32_t start_position = -1);

private:
	io::Reader<io::FileTypes::kIni>::Parameters parameters_;
	std::ofstream output_file_;
};