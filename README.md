# Firmware.ECP

The present firmware is intended as a demonstration of a really simply no-frills object oriented software paradigm for C and an implementation of the ECP Protocol for the ATmega2560 processor/Arduino Mega.

The firmware has the following capabilities:

1. A software timer system, that allow for an arbitrary number of one miliscond precision timers, which is based in hardware on the Timer 1.
2. A tic/toc system for measurements of timing with a microsecond precision based on Timer 3. 
3. Serial communication based on Serial Port 0
4. A digital I/O system that currently provides two digital output pins (PB7/D13: Debug Signal 1, and PB6/D12: Debug Signal 2).
5. Serial Communication according to the ECP Protocol.

