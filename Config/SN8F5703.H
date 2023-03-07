/*--------------------------------------------------------------------------
SN8F5703.H

Header file for SNOiX SN8F5703 microcontroller.
Copyright (c) 2015 SONiX Technology Co., Ltd.

Version 1.0    2015-02-11
Version 1.3    2015-09-09
Version 1.7    2015-10-14
--------------------------------------------------------------------------*/

#ifndef __SN8F5703_H__
#define __SN8F5703_H__

/*      Register      */
sfr     P0       = 0x80;
  sbit  P07      = P0^7;
  sbit  P06      = P0^6;
  sbit  P05      = P0^5;
  sbit  P04      = P0^4;
  sbit  P03      = P0^3;
  sbit  P02      = P0^2;
  sbit  P01      = P0^1;
  sbit  P00      = P0^0;
sfr     SP       = 0x81;
sfr     DPL      = 0x82;
sfr     DPH      = 0x83;
sfr     WDTR     = 0x86;
sfr     PCON     = 0x87;
sfr     TCON     = 0x88;
  sbit  TF1      = TCON^7;
  sbit  TR1      = TCON^6;
  sbit  TF0      = TCON^5;
  sbit  TR0      = TCON^4;
  sbit  IE1      = TCON^3;
  sbit  IE0      = TCON^1;
sfr     TMOD     = 0x89;
sfr     TL0      = 0x8A;
sfr     TL1      = 0x8B;
sfr     TH0      = 0x8C;
sfr     TH1      = 0x8D;
sfr     CKCON    = 0x8E;
sfr     PEDGE    = 0x8F;
sfr     P1       = 0x90;
  sbit  P17      = P1^7;
  sbit  P16      = P1^6;
  sbit  P15      = P1^5;
  sbit  P14      = P1^4;
  sbit  P13      = P1^3;
  sbit  P12      = P1^2;
  sbit  P11      = P1^1;
  sbit  P10      = P1^0;
sfr     P1W      = 0x91;
sfr     DPC      = 0x93;
sfr     PECMD    = 0x94;
sfr16   PEROM    = 0x95;
sfr     PEROML   = 0x95;
sfr     PEROMH   = 0x96;
sfr     PERAM    = 0x97;
sfr     S0CON    = 0x98;
  sbit  SM0      = S0CON^7;
  sbit  SM1      = S0CON^6;
  sbit  SM20     = S0CON^5;
  sbit  REN0     = S0CON^4;
  sbit  TB80     = S0CON^3;
  sbit  RB80     = S0CON^2;
  sbit  TI0      = S0CON^1;
  sbit  RI0      = S0CON^0;
sfr     S0BUF    = 0x99;
sfr     IEN2     = 0x9A;
sfr     OPM      = 0x9B;
sfr     CMPM     = 0x9C;
sfr     P2CON    = 0x9E;
sfr     P2       = 0xA0;
  sbit  P25      = P2^5;
  sbit  P24      = P2^4;
  sbit  P23      = P2^3;
  sbit  P22      = P2^2;
  sbit  P21      = P2^1;
  sbit  P20      = P2^0;
sfr     IEN0     = 0xA8;
  sbit   EAL     = IEN0^7;
  sbit   ET2     = IEN0^5;
  sbit   ES0     = IEN0^4;
  sbit   ET1     = IEN0^3;
  sbit   EX1     = IEN0^2;
  sbit   ET0     = IEN0^1;
  sbit   EX0     = IEN0^0;
sfr     IP0      = 0xA9;
sfr     S0RELL   = 0xAA;
sfr     PW1M     = 0xAB;
sfr16   PW1Y     = 0xAC;
sfr     PW1YL    = 0xAC;
sfr     PW1YH    = 0xAD;
sfr16   PW1B     = 0xAE;
sfr     PW1BL    = 0xAE;
sfr     PW1BH    = 0xAF;
sfr     IEN1     = 0xB8;
  sbit  ET2RL    = IEN1^7;
  sbit  ET2C3    = IEN1^5;
  sbit  ET2C2    = IEN1^4;
  sbit  ET2C1    = IEN1^3;
  sbit  ET2C0    = IEN1^2;
  sbit  ESPI     = IEN1^1;
  sbit  EI2C     = IEN1^0;
sfr     IP1      = 0xB9;
sfr     S0RELH   = 0xBA;
sfr16   PW1D     = 0xBB;
sfr     PW1DL    = 0xBB;
sfr     PW1DH    = 0xBC;
sfr     PW1A     = 0xBD;
sfr     PW1CH    = 0xBE;
sfr     IRCON2   = 0xBF;
sfr     IRCON    = 0xC0;
  sbit   TF2RL   = IRCON^7;
  sbit   TF2     = IRCON^6;
  sbit   TF2C3   = IRCON^5;
  sbit   TF2C2   = IRCON^4;
  sbit   TF2C1   = IRCON^3;
  sbit   TF2C0   = IRCON^2;
sfr     CCEN     = 0xC1;
sfr     CCL1     = 0xC2;
sfr     CCH1     = 0xC3;
sfr     CCL2     = 0xC4;
sfr     CCH2     = 0xC5;
sfr     CCL3     = 0xC6;
sfr     CCH3     = 0xC7;
sfr     T2CON    = 0xC8;
  sbit  T2PS     = T2CON^7;
  sbit  I3FR     = T2CON^6;
  sbit  GF1      = T2CON^5;
  sbit  T2R1     = T2CON^4;
  sbit  T2R0     = T2CON^3;
  sbit  T2CM     = T2CON^2;
  sbit  T2I1     = T2CON^1;
  sbit  T2I0     = T2CON^0;
sfr     CRCL     = 0xCA;
sfr     CRCH     = 0xCB;
sfr     TL2      = 0xCC;
sfr     TH2      = 0xCD;
sfr     CMPT     = 0xCE;
sfr     PSW      = 0xD0;
  sbit  CY       = PSW^7;
  sbit  AC       = PSW^6;
  sbit  F0       = PSW^5;
  sbit  RS1      = PSW^4;
  sbit  RS0      = PSW^3;
  sbit  OV       = PSW^2;
  sbit  F1       = PSW^1;
  sbit  P        = PSW^0;
sfr     IEN4     = 0xD1;
sfr     ADM      = 0xD2;
sfr     ADB      = 0xD3;
sfr     ADR      = 0xD4;
sfr     VREFH    = 0xD5;
sfr     P1CON    = 0xD6;
sfr     S0CON2   = 0xD8;
  sbit  BD       = S0CON2^7;
sfr     ADT      = 0xD9;
sfr     I2CDAT   = 0xDA;
sfr     I2CADR   = 0xDB;
sfr     I2CCON   = 0xDC;
sfr     I2CSTA   = 0xDD;
sfr     SMBSEL   = 0xDE;
sfr     SMBDST   = 0xDF;
sfr     ACC      = 0xE0;
sfr     SPSTA    = 0xE1;
sfr     SPCON    = 0xE2;
sfr     SPDAT    = 0xE3;
sfr     P0OC     = 0xE4;
sfr     CLKSEL   = 0xE5;
sfr     CLKCMD   = 0xE6;
sfr     TCON0    = 0xE7;
sfr     B        = 0xF0;
sfr     P0UR     = 0xF1;
sfr     P1UR     = 0xF2;
sfr     P2UR     = 0xF3;
sfr     SRST     = 0xF7;
sfr     P0M      = 0xF9;
sfr     P1M      = 0xFA;
sfr     P2M      = 0xFB;
sfr     PFLAG    = 0xFF;

/*      Interrupt Vector      */
#define ISRInt0    0
#define ISRTimer0  1
#define ISRInt1    2
#define ISRTimer1  3
#define ISRUart    4
#define ISRTimer2  5
#define ISRI2c     8
#define ISRSpi     9
#define ISRCom1    10
#define ISRCom2    11
#define ISRCom3    12
#define ISRCom4    13
#define ISRPwm1    16
#define ISRAdc     17
#define ISRCmp0    18

/*      C51 Macros      */
#ifdef __C51__
#include <intrins.h>
#define IDLE() {unsigned char data var_idle=PCON; var_idle |= 0x01; PCON = var_idle; }
#define STOP() {if (EAL == 0) {PCON |= 0x02;} else {EAL = 0; PCON |= 0x02; EAL = 1;}}
#define ISP(ROM_ADDRESS, RAM_ADDRESS) {PERAM = (RAM_ADDRESS); PEROM = ((ROM_ADDRESS) & 0xFFE0 | 0x0A); if (EAL == 0) {PECMD = 0x5A; _nop_(); _nop_();} else {EAL = 0; PECMD = 0x5A; _nop_(); _nop_(); EAL = 1;} PEROML = 0x00;}
#endif  // __C51__

#ifndef uint8_t
#define uint8_t unsigned char
#endif  // uint8_t

#ifndef uint16_t
#define uint16_t unsigned int
#endif  // uint16_t

#ifndef uint32_t
#define uint32_t unsigned long
#endif  // uint32_t

#endif  // __SN8F5703_H__
