#Jugaad Boards

This is a collection of boards created to work in the arduino IDE. This framework includes the necessary files as well as libraries and tools to make sure the loading of the programs easy.

There is one important principle that was followed in the development and which makes this some what beginner friendly is = No touching the hardware while loading the code. It should just load automatically.

Another key focus area was to constain the actual `code space` used. Meaning the reduction of the amount of memory required to store the compiled code. And still provide the most comprehensive set of core functions.

In order to be able to to care to these main 2 requirements the design was made to fit into the popular arduino IDE which supports the `code and forget` way of doing things. Due to compatibility issues the core of the various architectures were rewritten. This helped in supporting the compression in code size, yet increase the functionality.


## How to Add to Arduino IDE:

Download the Repository from the [Link](https://github.com/boseji/jugaad_boards/archive/master.zip)

Then Extract it `as-Is` under `<Arduino IDE Dir>\hardware` such that the folder new structure looks like
`<Arduino IDE Dir>\hardware\juggad_boards-master\jugaad-avr-boards`

Here `<Arduino IDE Dir>` is the location of the installation / Extraction of the Arduino IDE.



## License

This software is released under the GNU Lesser General Public License Version 3.

The licesne text included in the file `LICENSE.txt` of this repository.
see <https://www.gnu.org/licenses/lgpl-3.0.txt>.

![Image of LGPL3 Logo](https://raw.githubusercontent.com/boseji/jugaad_boards/master/lgplv3-logo.png)

