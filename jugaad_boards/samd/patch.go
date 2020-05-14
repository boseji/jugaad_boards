// Copyright (C) 2006-2020 Abhijit Bose <https://boseji.com>. All right reserved.
//
// This program is free software; you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the
// Free Software Foundation; version 2.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
//
// SPDX-License-Identifier: GPL-2.0-only
// https://spdx.org/licenses/GPL-2.0-only.html
//

package main

import (
	"fmt"
)

const (
	// Default Patch Directory
	patchDir = "patch_dir"
)

// configStore helps to keep the necessary modifyiable parameters
//  for this program
type configStore struct {
	BuildDir   string `json:"buildDir"`
	ReleaseTag string `json:"release_tag"`
}

func main() {
	fmt.Println("\n  Jugaad Boards Patcher Module")
	fmt.Println("---------------------------------")
	// Write Default Config to Patch file

}

// defaultConfig used to create the base configuration in
// the `patchDir`
func defaultConfig() {
	var def configStore
	def.BuildDir = "build/samd"
}
