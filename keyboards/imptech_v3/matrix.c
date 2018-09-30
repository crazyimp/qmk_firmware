/*
Copyright 2017 Balz Guenat
based on work by Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
 * scan matrix
 */
#include <stdint.h>
#include <stdbool.h>
#include "config.h"
#include "wait.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "timer.h"
#include "matrix.h"
#include "led.h"
// #include QMK_KEYBOARD_H


// Timer resolution check
#if (1000000/TIMER_RAW_FREQ > 20)
#   error "Timer resolution(>20us) is not enough for HHKB matrix scan tweak on V-USB."
#endif

static void clockMatrixSR(void){
    MATRIX_SR_PORT |= (1<<MATRIX_SR_CLK);
    _delay_us(120);
    MATRIX_SR_PORT &= ~(1<<MATRIX_SR_CLK);
    _delay_us(120);
}

// matrix state buffer(1:on, 0:off)
static matrix_row_t *matrix;
static matrix_row_t *matrix_prev;
static matrix_row_t _matrix0[MATRIX_ROWS];
static matrix_row_t _matrix1[MATRIX_ROWS];

__attribute__ ((weak))
void matrix_init_kb(void) {
    matrix_init_user();
}

__attribute__ ((weak))
void matrix_scan_kb(void) {
    matrix_scan_user();
}

__attribute__ ((weak))
void matrix_init_user(void) {
}

__attribute__ ((weak))
void matrix_scan_user(void) {
}


void matrix_init(void)
{
    debug_enable = false;
    debug_matrix = false;

	// setup input pins
	// port D
	MATRIX_INPUT_DDR = 0;

	// setup shift registers
	MATRIX_SR_DDR |= (1<<MATRIX_SR_DATA)|(1<<MATRIX_SR_CLK)|(1<<MATRIX_SR_CLR);
	MATRIX_SR_PORT |= (1<<MATRIX_SR_CLR);

    // empty shift registers
	MATRIX_SR_PORT &= ~(1<<MATRIX_SR_DATA);
    for(uint8_t i = 0; i < MATRIX_COLS; i++){
	    clockMatrixSR();
    }

    // initialize matrix state: all keys off
    for (uint8_t row=0; row < MATRIX_ROWS; row++){
        _matrix0[row] = 0x00;
        _matrix1[row] = 0x00;
    }
    matrix = _matrix0;
    matrix_prev = _matrix1;
    matrix_init_quantum();
}

uint8_t matrix_scan(void)
{
    uint8_t cols[MATRIX_COLS];
    matrix_row_t *tmp;

    tmp = matrix_prev;
    matrix_prev = matrix;
    matrix = tmp;

    // enable first col:
	MATRIX_SR_PORT |= (1<<MATRIX_SR_DATA);
    clockMatrixSR();
    MATRIX_SR_PORT &= ~(1<<MATRIX_SR_DATA);
    clockMatrixSR();

    uint8_t col;
    for (col = 0; col < MATRIX_COLS; col++) {
        cols[col] = MATRIX_INPUT_PIN;
	    clockMatrixSR();
    }
    clockMatrixSR();
    // transform cols->rows
    uint8_t row;
    for(row = 0; row < MATRIX_ROWS; row++){
        // reset row
        matrix[row] = 0;
        // fill row
        for(col = 0; col < MATRIX_COLS; col++){
            matrix[row] |= (((cols[col] & (1<<row))?1:0)<<col);
        }
    }
    matrix_scan_quantum();
	return 1;
}

inline
matrix_row_t matrix_get_row(uint8_t row) {
    return matrix[row];
}


void matrix_print(void)
{
#if (MATRIX_COLS <= 8)
    print("r/c 01234567\n");
#elif (MATRIX_COLS <= 16)
    print("r/c 0123456789ABCDEF\n");
#elif (MATRIX_COLS <= 32)
    print("r/c 0123456789ABCDEF0123456789ABCDEF\n");
#endif

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {

#if (MATRIX_COLS <= 8)
        xprintf("%02X: %08b%s\n", row, bitrev(matrix_get_row(row)),
#elif (MATRIX_COLS <= 16)
        xprintf("%02X: %016b%s\n", row, bitrev16(matrix_get_row(row)),
#elif (MATRIX_COLS <= 32)
        xprintf("%02X: %032b%s\n", row, bitrev32(matrix_get_row(row)),
#endif
#ifdef MATRIX_HAS_GHOST
        matrix_has_ghost_in_row(row) ?  " <ghost" : ""
#else
        ""
#endif
        );
    }
}

