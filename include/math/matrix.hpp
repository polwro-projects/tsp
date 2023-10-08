#pragma once

#include <deque>
#include <iostream>
#include <stdexcept>
#include <string>

namespace math {
template <class T>
class Matrix {
private:
	using Values = std::deque<std::deque<T>>;

public:
	Matrix() = default;

	Matrix(uint32_t columns, uint32_t rows) {
		resize(columns, rows);
	}

	Matrix(const Matrix<T>& rhs)
		: values_{rhs.values_} { }

public:
	Matrix& operator=(const Matrix<T>& rhs) {
		values_ = rhs.values_;
		return *this;
	}

	T& operator()(uint32_t column, uint32_t row) {
		return const_cast<T&>(const_cast<const Matrix*>(this)->operator()(column, row));
	}

	const T& operator()(uint32_t column, uint32_t row) const {
		if(column >= Columns() || row >= Rows()) {
			throw std::runtime_error("Size of the matrix is smaller than the provided position");
		}

		auto& matrix_row = values_.at(row);
		return matrix_row.at(column);
	}

	size_t Rows() const {
		return values_.size();
	}

	size_t Columns() const {
		return Rows() == 0 ? 0 : values_.at(0).size();
	}

	void resize(uint32_t columns, uint32_t rows) {
		// TODO : add checks

		// Construct rows of the matrix
		for(uint32_t row{}; row < rows; ++row) {
			values_.emplace_back(columns);
		}
	}

	void insert(const std::deque<T>& value) {
		// TODO : add a check

		values_.push_back(value);
	}

private:
	Values values_;
};
} // namespace math

template <class T>
std::ostream& operator<<(std::ostream& stream, const math::Matrix<T>& matrix) {
	for(uint32_t row{}; row < matrix.Rows(); ++row) {
		for(uint32_t column{}; column < matrix.Columns(); ++column) {
			std::cout << matrix(column, row) << " ";
		}
		std::cout << std::endl;
	}

	return stream;
}