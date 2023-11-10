/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

int SEGMENTE [10] = {
                      0b00111111,
                      0b00000110,
                      0b01011011,
                      0b01001111,
                      0b01100110,
                      0b01101101,
                      0b01111101,
                      0b00000111,
                      0b01111111,
                      0b01101111
                    };

PortOut segment(PortC, 0xFF);

void anzeigen(int anzahl) {
    segment = SEGMENTE [anzahl];
}


int main()
{
    DigitalOut einerstelle(PC_11);

    DigitalIn keyEntry(PA_1);
    keyEntry.mode(PullDown);

    DigitalIn keyOut(PA_6);
    keyOut.mode(PullDown);

    einerstelle = 1;

    int parkingLots = 9;

    anzeigen(parkingLots);

    while (true) {
        if (keyEntry) {
            if (parkingLots > 0) {
                anzeigen(--parkingLots);

                while (keyEntry);
            }
        }

        if (keyOut) {
            if (parkingLots < 9) {
                anzeigen(++parkingLots);

                while (keyOut);
            }
        }
    }
}
