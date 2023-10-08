#pragma once

#include <fstream>
#include <string>
#include <vector>

namespace io {
class Reader {
public:
	using Data = std::vector<std::string>;

public:
	Reader(const std::string& file);

public:
	bool Process();
	const Data& Get() const noexcept;

protected:
	Data data_;
	std::string filename_;
};
} // namespace io