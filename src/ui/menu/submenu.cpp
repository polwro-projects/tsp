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

#include "ui/menu/submenu.hpp"

#include "ui/menu.hpp"

namespace ui::menu {
Submenu::Submenu(std::string name, ui::Menu* menu)
	: Entry{name}
	, menu_{menu} { }

void Submenu::Enter() {
	if(!menu_) {
		// TODO : handle this more in a appropriate way
		return;
	}

	menu_->root_ = shared_from_this();
}

void Submenu::SetParent(std::weak_ptr<Entry> parent) {
	parent_ = parent;
}

void Submenu::AddChild(std::shared_ptr<Entry> child) {
	children_.push_back(child);
}

std::shared_ptr<Entry> Submenu::GetChild(const size_t index) const noexcept {
	if(index >= children_.size()) {
		return {};
	}

	return children_.at(index);
}

const std::vector<std::shared_ptr<Entry>>& Submenu::GetChildren() const noexcept {
	return children_;
}

} // namespace ui::menu