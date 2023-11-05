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

#include "ui/menu.hpp"

#include <iostream>

#include "ui/menu/submenu.hpp"

namespace ui {
void Menu::SetRootEntry(std::shared_ptr<menu::Submenu> root) noexcept {
	root_ = std::move(root);
}

void Menu::Choose(size_t index) const {
	if(!root_) {
		// Add more appropriate handling
		return;
	}

	auto entry = root_->GetChild(index);
	if(!entry) {
		std::cout << "The index is inapropriate. Please, enter the valid entry index." << std::endl;
		return;
	}

	entry->Enter();
}

void Menu::Show() const {
	if(!root_) {
		// Add more appropriate handling
		return;
	}

	std::cout << std::endl << "==============" << std::endl;
	std::cout << root_->GetName() << std::endl;
	std::cout << "==============" << std::endl << std::endl;

	size_t index{};
	for(const auto entry : root_->GetChildren()) {
		std::cout << index++ << ". " << entry->GetName() << std::endl;
	}
	std::cout << std::endl;
}
} // namespace ui