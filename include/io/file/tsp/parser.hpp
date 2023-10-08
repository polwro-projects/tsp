#pragma once

#include <string>

#include "io/file/iparser.hpp"
#include "io/reader.hpp"
#include "math/matrix.hpp"

namespace io::file::tsp {
class Parser : virtual public IParser {
public:
	using DistanceMatrix = math::Matrix<uint32_t>;
	using Data = io::Reader::Data;

public:
	Parser(Data data);

public:
	bool Process();
	const DistanceMatrix& Get() const noexcept;

protected:
	static DistanceMatrix GetDistanceMatrix(const Data& data);

protected:
	DistanceMatrix matrix_;
	Data data_;
};
} // namespace io::file::tsp