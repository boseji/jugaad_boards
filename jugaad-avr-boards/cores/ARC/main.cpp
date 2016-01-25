/**
 * @file main.cpp
 *
 * @brief Main function host file that calls the "loop" and "setup" functions
 *
 *
 * @version 1.0.0 First Version Release - 25th Jan 2016
 *
 * @author Abhijit Bose (salearj@hotmail.com)
 *
 * @copy Copyright (c) 2016 Abhijit Bose.  All right reserved.
 *
 * @license
 * This file is part of Jugaad Boards Framework (JBF) for A.R.C. Core.
 *
 * JBF is free software: you can redistribute it and / or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 *   JBF is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with JBF.
 * If not, see <https://www.gnu.org/licenses/lgpl-3.0.txt>.
 * You can also write to the Free Software Foundation, Inc.,
 * 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * @note Arduino - Copyright owned by Arduino LLC and we are not associated
 *  with them in any what so ever manner. JBF is an independently developed entity
 *  and hence Arduino LLC or Associated collaborators cannot claim ownership
 *  of this work under any legal on permissible context.
 *
 */
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <util/atomic.h>

#include <Arduino.h>

// Weak empty variant initialization function.
// May be redefined by variant files.
void init() __attribute__((weak));
void init() { }

void initVariant() __attribute__((weak));
void initVariant() { }

int main(void)
{
  init();

  initVariant();

  setup();

  for (;;) {
      loop();
  }

  return 0;
}
