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

#include <deque>
#include <iostream>
#include <stdexcept>
#include <string>

namespace math {
/**
 * @brief The class represents a matrix and all the operations that can be completed on it
 * 
 * @tparam T the underlying type of the matrix
 */
template <class T>
class Matrix {
private:
	using Values = std::deque<std::deque<T>>;

public:
	/**
	 * @brief Access to the cell of the matrix
	 * 
	 * @param column - the column of the cell
	 * @param row - the row of the cell
	 * @return T& - the value that the cell contains
	 */
	T& operator()(uint32_t column, uint32_t row) {
		return const_cast<T&>(const_cast<const Matrix*>(this)->operator()(column, row));
	}

	/**
	 * @brief Access to the cell of the matrix
	 * 
	 * @param column - the column of the cell
	 * @param row - the row of the cell
	 * @return const T& - the value that the cell contains
	 */
	const T& operator()(uint32_t column, uint32_t row) const {
		if(column >= Columns() || row >= Rows()) {
			throw std::runtime_error("Size of the matrix is smaller than the provided position");
		}

		auto& matrix_row = values_.at(row);
		return matrix_row.at(column);
	}

	/**
	 * @brief Get the amount of rows inside of the matrix
	 * 
	 * @return size_t - the amount of rows
	 */
	size_t Rows() const {
		return values_.size();
	}

	/**
	 * @brief Get the amount of columns in the matrix
	 * 
	 * @return size_t - the amount of columns
	 */
	size_t Columns() const {
		return Rows() == 0 ? 0 : values_.at(0).size();
	}

	/**
	 * @brief Insert a new row into the matrix
	 * 
	 * @param value - the row to insert
	 */
	void InsertRow(const std::deque<T>& value) {
		// TODO : add a check

		values_.push_back(value);
	}

private:
	Values values_;
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
template <class T>
std::ostream& operator<<(std::ostream& stream, const math::Matrix<T>& matrix) {
	for(uint32_t row{}; row < matrix.Rows(); ++row) {
		for(uint32_t column{}; column < matrix.Columns(); ++column) {
			stream << matrix(column, row) << " ";
		}
		stream << std::endl;
	}

	return stream;
}