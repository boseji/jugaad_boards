# Jugaad Boards

This is a collection of boards created to work in the arduino IDE. This framework includes the necessary files as well as libraries and tools to make sure the loading of the programs easy.

There is one important principle that was followed in the development and which makes this some what 
beginner friendly is = *No touching the hardware while loading the code*. 
It should just load *automagically*.

Another key focus area was to constrain the actual `code space` used. Meaning the reduction of the amount of memory required to store the compiled code. And still provide the most comprehensive set of core functions.

In order to be able to to care to these main 2 requirements the design was made to fit into the popular arduino IDE which supports the `code and forget` way of doing things. Due to compatibility issues the core of the various architectures were rewritten. This helped in supporting the compression in code size, yet increase the functionality.


## How to Add to Arduino IDE:

Copy and paste the following URL into the File > Preferences > "Additional Boards Manager" textbox.

`https://boseji.com/files/package_boseji_jugaad_boards_index.json`

### Older URI

`https://raw.githubusercontent.com/boseji/jugaad_boards/master/bm/package_boseji_jugaad_boards_index.json`

## License

This software is released under the GNU General Public License v2.0 only.
All the files in this repository conform to GNU General Public License v2.0 unless otherwise specified.

`SPDX-License-Identifier: GPL-2.0-only`

[**SPDX Identifier: GPL-2.0-only**](https://spdx.org/licenses/GPL-2.0-only.html)

The license text included in the file `LICENSE.txt` of this repository.
see <https://www.gnu.org/licenses/old-licenses/gpl-2.0.txt>.

### Copyright (C) 2006-2020 Abhijit Bose <https://boseji.com>. All right reserved.

> Keeping liberty of mind, work, and soul.
> 
> कोशिश करने वालों की कभी हार नहीं होती |
