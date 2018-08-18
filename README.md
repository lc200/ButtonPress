# ButtonPress

https://github.com/lc200/ButtonPress

## Arduino Button Press with debounce
A simple library for use with Arduino IDE that debounces a button press. It will also detect a long button press (> 1 sec) to allow a single button to have two modes.

It will remember the button was pressed until it has been executed within the loop, this avoids presses being 'lost' should the button be let go before it has had chance to be checked in the loop.

## Examples
The following example sketch is included with the library:
DebounceButtonPress

## License
Button Press Library Copyright (C) 2018 L Carpenter GNU GPL v3.0

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License v3.0 as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see https://www.gnu.org/licenses/gpl.html
