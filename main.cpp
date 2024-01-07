/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

#define PAUSE 10ms

PortOut schrittmotor(PortC, 0b1111);
bool stopped = false;

int bitfolge[4] = {
    0b1001,
    0b1100,
    0b0110,
    0b0011
};

void pause() {
    ThisThread::sleep_for(PAUSE);
}

void stopSchrittmotor() {
    schrittmotor = 0;
    stopped = true;
}

void startSchrittmotor() {
    stopped = false;
}

void a() {
    while (true) {
        if (!stopped) {
            for (int i = 0; i <= 4; i++) {
                if (!stopped) {
                    schrittmotor = bitfolge[i];
                    pause();   
                }
            }
        }
    }
}

void b() {
    InterruptIn stop(PA_10);
    stop.mode(PullDown);
    stop.rise(&stopSchrittmotor);
    stop.enable_irq();
}

void c() {
    InterruptIn start(PA_6);
    start.mode(PullDown);
    start.rise(&startSchrittmotor);
    start.enable_irq();
}

int main()
{
    schrittmotor = 0;

    //b();
    InterruptIn stop(PA_10);
    stop.mode(PullDown);
    stop.rise(&stopSchrittmotor);
    stop.enable_irq();
    
    //c();
    InterruptIn start(PA_6);
    start.mode(PullDown);
    start.rise(&startSchrittmotor);
    start.enable_irq();

    a();
    
    while (true) {

    }
}
