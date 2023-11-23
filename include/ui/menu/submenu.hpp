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

#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "ui/menu/entry.hpp"

namespace ui {
class Menu;
}

namespace ui::menu {
/**
 * @brief The class represents the entry of a menu
 * 
 */
class Submenu : public Entry, public std::enable_shared_from_this<Submenu> {
public:
	/**
	 * @brief Construct a new Submenu object
	 * 
	 * @param name - the name of the submenu
	 * @param menu - the menu to operate on
	 */
	Submenu(std::string name, ui::Menu* menu);

public:
	/**
	 * @brief Enter the menu entry
	 * 
	 */
	void Enter();

	/**
	 * @brief Set the parent entry
	 * 
	 * @param parent - the parent of this submenu
	 */
	void SetParent(std::weak_ptr<Entry> parent);

	/**
	 * @brief Add the child to the entry
	 * 
	 * @param child - the child ot add to the entry
	 */
	void AddChild(std::shared_ptr<Entry> child);

	/**
	 * @brief Get the child with the given index
	 * 
	 * @param index - the index of the child
	 * @return std::weak_ptr<Entry> - the child of the submenu
	 */
	std::shared_ptr<Entry> GetChild(const size_t index) const noexcept;

	/**
	 * @brief Get the children of the object
	 * 
	 * @return const std::vector<std::weak_ptr<Entry>>&  - the child entries of this entry
	 */
	const std::vector<std::shared_ptr<Entry>>& GetChildren() const noexcept;

protected:
	ui::Menu* menu_;
	std::weak_ptr<Entry> parent_;
	std::vector<std::shared_ptr<Entry>> children_;
};
} // namespace ui::menu