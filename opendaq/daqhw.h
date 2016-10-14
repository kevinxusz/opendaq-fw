/*
 *  Copyright (C) 2012 INGEN10 Ingenieria SL
 *  http://www.ingen10.com
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 2.1 of the License, or
 *  (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.

 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Version:    150701
 *  Author:     JRB
 *  Revised by: AV (17/07/15)
 */


/**
 * @file daqhw.h
 * Header file for source code in daqhw.cpp
*/
#ifndef DAQHW_H
#define DAQHW_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <pins_arduino.h>
#include "Timer1.h"

extern "C" {
#include <stdlib.h>
}

#define LEDGREEN    0
#define LEDRED      1

#ifndef INPUT
#define INPUT 0
#endif
#ifndef OUTPUT
#define OUTPUT 0
#endif
#ifndef LOW
#define LOW 0
#endif
#ifndef HIGH
#define HIGH 1
#endif

void SetpioMode(uint8_t pio, uint8_t mode);
int GetpioMode(uint8_t pio);
void pioWrite(uint8_t pio, uint8_t val);
int pioRead(uint8_t pio);

int ReadDigital();
void OutputDigital(int value);

void SetDigitalDir(int value);
int GetDigitalDir();

void ledSet(uint8_t nb, uint8_t val);

void ActivateAnalogInput(int number);

signed int ReadAnalog();
signed int ReadADC();
signed int ReadNADC(int nsamples);
signed int ReadAnalogIn(int n);

void ConfigAnalogChannels(uint8_t chp, uint8_t chm);
void ConfigAnalogGain(uint8_t gain);
void ConfigAnalog(uint8_t chp, uint8_t chm, uint8_t gain);

int SetDacOutput(int16_t value);
int SetAnalogVoltage(signed int mv);

void pwmInit(int duty, long microseconds);
void PwmStop();
void setPwmDuty(int duty);

void captureInit(unsigned long microseconds);
void captureStop();
int getCapture(int state);

void encoderInit(unsigned int secondChannelPIO, unsigned int resolution);
void encoderStop();
int getEncoder();

void counterInit(int edge);
int getCounter(int reset);

void daqInit();
int availableMemory();

#if HW_VERSION==2       //OPENDAQ-S

//#error

//ADS7871 gain constants
#define ADCPGAX01 0X00
#define ADCPGAX02 0X10
#define ADCPGAX04 0X20
#define ADCPGAX05 0X30
#define ADCPGAX08 0X40
#define ADCPGAX10 0X50
#define ADCPGAX16 0X60
#define ADCPGAX20 0X70

static int myChannels = 0, myGains = 0;
void setupLTC2630();

void Config7871();
void config7871PIO(int x);
void set7871PIO(int x);

const uint8_t PROGMEM ain_to_deadc_PGM[] = {
    0x00,
    0x04,
    0x01,
    0x05,
    0x02,
    0x06,
    0x03,
    0x07
};

const uint8_t PROGMEM gain_to_adcset_PGM[] = {
    ADCPGAX01,
    ADCPGAX02,
    ADCPGAX04,
    ADCPGAX05,
    ADCPGAX08,
    ADCPGAX10,
    ADCPGAX16,
    ADCPGAX20
};

#define ainToDEChan(P) ( pgm_read_byte( ain_to_deadc_PGM + (P) ) )
#define ainToSEChan(P) ( 0x08 + (P) )
#define gainToAdcset(P) ( pgm_read_byte( gain_to_adcset_PGM + (P) ) )

#else               //OPENDAQ-M

//Analog input channel definitions (MMA-MMB-MMC-MPA-MPB-MPC bits select)
#define AIN1    0X0
#define AIN2    0X4
#define AIN3    0X2
#define AIN4    0X6
#define AIN5    0X1
#define AIN6    0X5
#define AIN7    0X3
#define AIN8    0X7
#define AGND    0X0
#define AREF    0X4

//Analog gain definitions
#define GAINX0_5    0
#define GAINX001    1
#define GAINX002    2
#define GAINX010    3
#define GAINX100    4

const uint8_t PROGMEM ain_to_port_PGM[] = {
    AGND,
    AIN1,
    AIN2,
    AIN3,
    AIN4,
    AIN5,
    AIN6,
    AIN7,
    AIN8,
    AREF
};

#define ainToPort(P) ( pgm_read_byte( ain_to_port_PGM + (P) ) )

#endif

#endif
