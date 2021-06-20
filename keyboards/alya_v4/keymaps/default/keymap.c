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
#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    QMKBEST = SAFE_RANGE,
    QMKURL,
    MOVE_LED_LEFT,
    MOVE_LED_RIGHT
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
        MOVE_LED_LEFT,  KC_B, KC_C, KC_D, KC_E, KC_F, KC_H,
        KC_A,  KC_B, KC_C, KC_D, KC_E, KC_F, KC_H,
        KC_A,        KC_C, KC_D, KC_E, KC_F, KC_H,
        KC_A,  KC_B, KC_C, KC_D, KC_E, KC_F, KC_H,
        KC_A,  KC_B, KC_C, KC_D, KC_E, KC_F, KC_H,

	KC_1,  KC_2, KC_3, KC_4, KC_5, KC_6, MOVE_LED_RIGHT,
	KC_1,  KC_2, KC_3, KC_4, KC_5, KC_6, BL_STEP,
	KC_1,  KC_2, KC_3, KC_4, KC_5,       KC_7,
               KC_2, KC_3, KC_4, KC_5, KC_6, KC_7,
	KC_1,  KC_2, KC_3, KC_4, KC_5, KC_6, KC_7
    )
   // [_FN] = LAYOUT(
   //     QMKBEST, QMKURL,  _______,
   //         RESET,    XXXXXXX
   // )
};

void pulse_backlight_clk(void);
void pulse_backlight_clk(void){
	writePinLow(BACKLIGHT_DATA_CLOCK);
	writePinHigh(BACKLIGHT_DATA_CLOCK);
}

void move_led(int8_t dir);
void move_led(int8_t dir){
	static uint8_t pos = 0;
	pos = (pos + dir) % 16;

	for(size_t i = 0; i < 8; i++){
		if(i == pos){
			writePinHigh(BACKLIGHT_DATA_PIN);
		} else {
			writePinLow(BACKLIGHT_DATA_PIN);
		}
		pulse_backlight_clk();
	}
	for(size_t i = 15; i >= 8; i--){
		if(i == pos){
			writePinHigh(BACKLIGHT_DATA_PIN);
		} else {
			writePinLow(BACKLIGHT_DATA_PIN);
		}
		pulse_backlight_clk();
	}
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	//print("process_record_user()\n");
    switch (keycode) {
	case MOVE_LED_LEFT:
		move_led(-1);
		break;
	case MOVE_LED_RIGHT:
		move_led(1);
		break;
        case QMKBEST:
            if (record->event.pressed) {
                // when keycode QMKBEST is pressed
                SEND_STRING("QMK is the best thing ever!");
            } else {
                // when keycode QMKBEST is released
            }
            break;
        case QMKURL:
            if (record->event.pressed) {
                // when keycode QMKURL is pressed
                SEND_STRING("https://qmk.fm/\n");
            } else {
                // when keycode QMKURL is released
            }
            break;
    }
    return true;
}
