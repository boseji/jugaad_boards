# A.R.C - Jugaad AVR Boards

This project is design to help reduce the code density and still provide the easy of use can scalability.

---

## A.R.C = AVR Reduce Compilation Framework

In the existing *Arduino Core* there were certain things that the Author had a personal opinion about.
And as he did not like that he rewrote the complete internals of the AVR Execution framework 
which *Arduino* uses. This resulted in the new **A.R.C Framework**.


The main goals of this framework is to keep things simple in `C` and not to use much of dynamics of `C++`. By this the design consumes less FLASH space in the Microcontroller and also there is **no HEAP**.


All functions operate on `'Include to define'` method which mean if a function is not used then the resulting complied code is not present in your executable file. That effectively brings down the total flash size.
Though this project is in very nascent phase but the sale of compression already demonstrated helps to realize its true value.


It lives up to its name ***AVR Reduced Compilation Framework .aka. A.R.C***.


## License

 This software is distributed under the GNU Lesser General Public License version 3

 A.R.C Framework is free software: you can redistribute it and / or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

  A.R.C Framework is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License
 along with A.R.C Framework.
 If not, see <https://www.gnu.org/licenses/lgpl-3.0.txt>.
 You can also write to the Free Software Foundation, Inc.,
 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

