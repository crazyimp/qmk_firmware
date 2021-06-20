/* Copyright 2021 Martin Errenst
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "alya_v4.h"

#include "print.h"
#include "debug.h"

#include QMK_KEYBOARD_H

void setupBacklightPins(void){
	setPinOutput(BACKLIGHT_DATA_CLEAR);
	setPinOutput(BACKLIGHT_DATA_CLOCK);
	setPinOutput(BACKLIGHT_DATA_PIN);

	writePinHigh(BACKLIGHT_DATA_CLEAR);
	writePinHigh(BACKLIGHT_DATA_PIN);

	for(int i=0; i < 16*2+2; i++){
		writePinLow(BACKLIGHT_DATA_CLOCK);
		writePinHigh(BACKLIGHT_DATA_CLOCK);
	}

	print("backlight init done\n");
}

void board_init(void) {
	// enable debug
	debug_config.enable = true;

	setupBacklightPins();
}

void keyboard_post_init_user(void) {
	// Customise these values to desired behaviour
	debug_enable=true;
	debug_matrix=true;
	debug_keyboard=true;
	//debug_mouse=true;
	print("post init done\n");
}

