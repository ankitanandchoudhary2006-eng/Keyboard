#pragma once

#define MATRIX_ROWS 5
#define MATRIX_COLS 15

/* The schematic shows one diode in series with each switch.
 * Current direction is column to row (COL2ROW).
 */
#define DIODE_DIRECTION COL2ROW

/* Conservative debounce for a first hardware test. */
#define DEBOUNCE 5
