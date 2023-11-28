/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *  http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#pragma once

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace math {
/**
 * @brief The class represents a matrix and all the operations that can be completed on it
 * 
 * @tparam T the underlying type of the matrix
 */
template <class T, template <class, class> class Container>
class Matrix {
public:
	using Type = T;
	using RowType = Container<T, std::allocator<T>>;

public:
	/**
	 * @brief Access to the cell of the matrix
	 * 
	 * @param column - the column of the cell
	 * @param row - the row of the cell
	 * @return T& - the value that the cell contains
	 */
	T& operator()(uint32_t row, uint32_t column) {
		return const_cast<T&>(const_cast<const Matrix*>(this)->operator()(row, column));
	}

	/**
	 * @brief Access to the cell of the matrix
	 * 
	 * @param column - the column of the cell
	 * @param row - the row of the cell
	 * @return const T& - the value that the cell contains
	 */
	const T& operator()(uint32_t row, uint32_t column) const {
		if(column >= Columns() || row >= Rows()) {
			throw std::runtime_error("Size of the matrix is smaller than the provided position");
		}

		const auto index = (row * columns_) + column;
		return values_.at(index);
	}

	/**
	 * @brief Get the amount of rows inside of the matrix
	 * 
	 * @return size_t - the amount of rows
	 */
	size_t Rows() const {
		return rows_;
	}

	/**
	 * @brief Get the amount of columns in the matrix
	 * 
	 * @return size_t - the amount of columns
	 */
	size_t Columns() const {
		return columns_;
	}

	/**
	 * @brief Insert a new row into the matrix
	 * 
	 * @param value - the row to insert
	 */
	void InsertRow(RowType&& value) {
		// TODO : add a check for the size of the new row

		if(rows_ == 0) {
			columns_ = value.size();
		}

		// Insert all the values from the row to the end of the container
		values_.insert(values_.end(),
					   std::make_move_iterator(value.begin()),
					   std::make_move_iterator(value.end()));

		// Increment the amount of rows
		++rows_;
	}

private:
	Container<T, std::allocator<T>> values_;
	size_t rows_{};
	size_t columns_{};
};
} // namespace math

/**
 * @brief Overloaded operator << for matrixes
 * 
 * @tparam T - the underlying type of the matrix
 * @param stream - the stream to put data into
 * @param matrix - the matrix to print
 * @return std::ostream& - the same stream
 */
template <class T, template <class, class> class Container>
std::ostream& operator<<(std::ostream& stream, const math::Matrix<T, Container>& matrix) {
	for(uint32_t row{}; row < matrix.Rows(); ++row) {
		for(uint32_t column{}; column < matrix.Columns(); ++column) {
			stream << matrix(row, column) << " ";
		}
		stream << std::endl;
	}

	return stream;
}