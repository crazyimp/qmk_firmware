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

#pragma once

#include "quantum.h"

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT( \
 kl11,  kl12,  kl13, kl14, kl15,  kl16, kl17, \
 kl21,  kl22,  kl23, kl24, kl25,  kl26, kl27, \
 kl31,         kl33, kl34, kl35,  kl36, kl37, \
 kl41,  kl42,  kl43, kl44, kl45,  kl46, kl47, \
 kl51,  kl52,  kl53, kl54, kl55,  kl56, kl57, \
  \
 kr61,  kr62,  kr63, kr64, kr65,  kr66, kr67, \
 kr71,  kr72,  kr73, kr74, kr75,  kr76, kr77, \
 kr81,  kr82,  kr83, kr84, kr85,        kr87, \
        kr92,  kr93, kr94, kr95,  kr96, kr97, \
 krA1,  krA2,  krA3, krA4, krA5,  krA6, krA7  \
) { \
    {  kl11,  kl12,  kl13, kl14, kl15,  kl16, kl17 }, \
    {  kl21,  kl22,  kl23, kl24, kl25,  kl26, kl27 }, \
    {  kl31, KC_NO,  kl33, kl34, kl35,  kl36, kl37 }, \
    {  kl41,  kl42,  kl43, kl44, kl45,  kl46, kl47 }, \
    {  kl51,  kl52,  kl53, kl54, kl55,  kl56, kl57 }, \
	\
    {  kr61,  kr62,  kr63, kr64, kr65,  kr66, kr67 }, \
    {  kr71,  kr72,  kr73, kr74, kr75,  kr76, kr77 }, \
    {  kr81,  kr82,  kr83, kr84, kr85, KC_NO, kr87 }, \
    { KC_NO,  kr92,  kr93, kr94, kr95,  kr96, kr97 }, \
    {  krA1,  krA2,  krA3, krA4, krA5,  krA6, krA7 } \
}
