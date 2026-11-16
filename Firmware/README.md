# Custom STM32F072CBT6 keyboard — QMK firmware source

This is a QMK keyboard source project based on the two KiCad schematic screenshots supplied in the conversation.

## Controller and matrix

- MCU: STM32F072CBT6
- Matrix: 5 rows × 15 columns
- Switch diodes: 1N4148W
- Diode direction configured as `COL2ROW`
- USB firmware protocol: USB HID keyboard
- Bootloader: STM32 factory DFU (`stm32-dfu`)

### GPIO map

| Signal | STM32 GPIO |
|---|---|
| R0 | PB11 |
| R1 | PB10 |
| R2 | PB2 |
| R3 | PB1 |
| R4 | PB0 |
| C0 | PB12 |
| C1 | PB13 |
| C2 | PA3 |
| C3 | PA4 |
| C4 | PB14 |
| C5 | PB15 |
| C6 | PA8 |
| C7 | PA5 |
| C8 | PA9 |
| C9 | PA10 |
| C10 | PA6 |
| C11 | PA7 |
| C12 | PA15 |
| C13 | PB3 |
| C14 | PB4 |

## Important layout note

The switch sheet appears to contain 61 switches. The matrix coordinates for the populated positions were read from the drawing, but some bottom-row/offset positions are not perfectly unambiguous at the screenshot resolution. The `keymap.c` includes comments for those positions. Before treating this as final production firmware, compare each switch's column/row net labels against the KiCad project and run a switch-by-switch matrix test.

The bottom-row placement in the sample keymap is a practical starting point, not a verified physical keycap layout. Change the keycodes in `keymaps/default/keymap.c` to match your exact physical layout.

## Build

Install the QMK CLI and QMK build environment, then place this folder in `keyboards/custom/stm32f072_keyboard/` inside your `qmk_firmware` checkout. Rename the folder or update the command if you choose a different path.

Build from the QMK firmware root:

```sh
qmk compile -kb custom/stm32f072_keyboard -km default
```

The resulting firmware is expected to be a `.bin` file for the STM32 DFU bootloader. This archive contains source/configuration, not a precompiled binary: a successful build against your installed QMK version is still required.

## Enter STM32 DFU mode and flash

1. Disconnect the keyboard USB cable.
2. Hold the BOOT0 button (the schematic shows BOOT0 switched to 3V3).
3. While holding BOOT0, press and release RESET.
4. Release BOOT0. Connect USB if it was disconnected.
5. Confirm that the device appears as an STM32 DFU device.
6. Flash using QMK Toolbox or `dfu-util`. QMK's STM32 DFU command uses device `0483:DF11`.

Example:

```sh
dfu-util -a 0 -d 0483:DF11 -s 0x08000000:leave -D path/to/firmware.bin
```

Do not flash until the exact matrix wiring and the firmware build have been checked on the assembled board.

## Scope / limitations

- This project provides normal keyboard typing and a function layer.
- The supplied schematic does not show an OLED/LCD display, so it cannot display the time without additional display hardware and wiring.
- It does not assign website-opening actions to every key. A keyboard normally sends key events to the host; opening URLs requires host-side shortcuts/software and should be implemented deliberately rather than replacing normal typing.
- I have not electrically tested the PCB or compiled this source against your local QMK checkout.
