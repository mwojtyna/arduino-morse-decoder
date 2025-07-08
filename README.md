# arduino-morse-decoder

Morse code decoder software for ATmega 328P board.

## Building

Required software:

- `avr-gcc` >= 11 (C23 support)
- `avr-binutils`
- `avr-libc`
- `make`
- `avrdude` (for uploading)
- `tio` (for reading logs over UART)

1. Change the `PORT` variable in Makefile to the port name where the microcontroller is connected
2. Run `make` in project folder to build
3. Run `make upload` to upload the binary
4. Run `make listen` to read logs

## Resources

- [avr-libc](https://avrdudes.github.io/avr-libc/avr-libc-user-manual-2.2.0/index.html)
- [ATmega 328P datasheet](https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf)
