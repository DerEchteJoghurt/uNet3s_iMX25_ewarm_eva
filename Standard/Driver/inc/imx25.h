/****************************************************************************
       Micro C Cube Standard, DEVICE DRIVER
       Freescale Semiconductor i.MX25 (ARM926EJ-S core)
                      registers definitions

       Copyright (c)  2010-2012, eForce Co., Ltd.  All rights reserved.

       Version Information
               2010.11.02: Created.
               2010.11.16: Added FEC controller definition
               2011.12.24: Corrected the I2C register definition.
                           Added the NFC register definition.
               2012.02.01: Added the eSDHC register definition.
               2012.02.26: Corrected the GPT register definition.
               2012.02.27: Added the M3IF&WEIM register definition.
****************************************************************************/

#ifndef _IMX25_H_
#define _IMX25_H_

#ifdef __cplusplus
extern "C" {
#endif


/* Simple Interrupt Controller registers                                    */

struct t_asic {
    UW      INTCNTL;            /* Interrupt Control Register               */
    UW      NIMASK;             /* Normal Interrupt mask Register           */
    UW      INTENNUM;           /* Interrupt Enable number Register         */
    UW      INTDISNUM;          /* Interrupt Disable number Register        */
    UW      INTENABLEH;         /* Interrupt enable Register high           */
    UW      INTENABLEL;         /* Interrupt enable Register low            */
    UW      INTTYPEH;           /* Interrupt Type Register high             */
    UW      INTTYPEL;           /* Interrupt Type Register low              */
    UW      NIPRIORITY[8];      /* Normal Interrupt priority level Register */
    UW      NIVECSR;            /* Normal interrupt vector and status register  */
    UW      FIVECSR;            /* Fast interrupt vector and status register    */
    UW      INTSRCH;            /* Interrupt source register high           */
    UW      INTSRCL;            /* Interrupt source register low            */
    UW      INTFRCH;            /* Interrupt Force register high            */
    UW      INTFRCL;            /* Interrupt Force register low             */
    UW      NIPNDH;             /* Normal Interrupt pending register high   */
    UW      NIPNDL;             /* Normal Interrupt pending register low    */
    UW      FIPNDH;             /* Fast Interrupt pending register high     */
    UW      FIPNDL;             /* Fast Interrupt pending register low      */
};

#define REG_ASIC        (*(volatile struct t_asic *)0x68000000)


/* Enhanced Periodic Interrupt Timer Controller registers                   */

struct t_epit {
    UW      CR;                 /* Control register                         */
    UW      SR;                 /* Status register                          */
    UW      LR;                 /* Load register                            */
    UW      CMPR;               /* Compare register                         */
    UW      CNR;                /* Counter register                         */
};

#define REG_EPIT1       (*(volatile struct t_epit *)0x53F94000)
#define REG_EPIT2       (*(volatile struct t_epit *)0x53F98000)


/* General Purpose Timer Controller registers                               */

struct t_gpt {
    UW      CR;                 /* Control register                         */
    UW      PR;                 /* Prescalar register                       */
    UW      SR;                 /* Status register                          */
    UW      IR;                 /* Interrupt register                       */
    UW      OCR1;               /* Output Compare register 1                */
    UW      OCR2;               /* Output Compare register 2                */
    UW      OCR3;               /* Output Compare register 3                */
    UW      ICR1;               /* Input Capture register 1                 */
    UW      ICR2;               /* Input Capture register 2                 */
    UW      CNT;                /* Counter register                         */
};

#define REG_GPT1        (*(volatile struct t_gpt *)0x53F90000)
#define REG_GPT2        (*(volatile struct t_gpt *)0x53F8C000)
#define REG_GPT3        (*(volatile struct t_gpt *)0x53F88000)
#define REG_GPT4        (*(volatile struct t_gpt *)0x53F84000)


/* UART Controller registers                                                */

struct t_uart {
    UW      URXD;               /* UART receiver register                   */
    UW      fill1[15];          /* Reserved space                           */
    UW      UTXD;               /* UART transmitter register                */
    UW      fill2[15];          /* Reserved space                           */
    UW      UCR1;               /* UART control register-1                  */
    UW      UCR2;               /* UART control register-2                  */
    UW      UCR3;               /* UART control register-3                  */
    UW      UCR4;               /* UART control register-4                  */
    UW      UFCR;               /* UART FIFO control register               */
    UW      USR1;               /* UART Status register-1                   */
    UW      USR2;               /* UART Status register-2                   */
    UW      UESC;               /* UART Escape character register           */
    UW      UTIM;               /* UART Escape timer register               */
    UW      UBIR;               /* UART BRM incremental register            */
    UW      UBMR;               /* UART BRM modulator register              */
    UW      UBRC;               /* UART baud rate count register            */
    UW      ONEMS;              /* UART One Millisecond register            */
    UW      UTS;                /* UART Test register                       */
};

#define REG_UART1       (*(volatile struct t_uart *)0x43F90000)
#define REG_UART2       (*(volatile struct t_uart *)0x43F94000)
#define REG_UART3       (*(volatile struct t_uart *)0x5000C000)
#define REG_UART4       (*(volatile struct t_uart *)0x50008000)
#define REG_UART5       (*(volatile struct t_uart *)0x5002C000)


/* General-Purpose I/O Controller registers                                 */

struct t_gpio {
    UW      DR;                 /* GPIO Data register                       */
    UW      GDIR;               /* GPIO Data Direction register             */
    UW      PSR;                /* GPIO Pad Status register                 */
    UW      ICR1;               /* GPIO Interrupt Configuration register-1  */
    UW      ICR2;               /* GPIO Interrupt Configuration register-2  */
    UW      IMR;                /* GPIO Interrupt mask register             */
    UW      ISR;                /* GPIO Interrupt Status register           */
    UW      EDGE_SEL;           /* GPIO edge select register                */
};

#define REG_GPIO1       (*(volatile struct t_gpio *)0x53FCC000)
#define REG_GPIO2       (*(volatile struct t_gpio *)0x53FD0000)
#define REG_GPIO3       (*(volatile struct t_gpio *)0x53FA4000)
#define REG_GPIO4       (*(volatile struct t_gpio *)0x53F9C000)


/* Inter IC Module registers                                                */

struct t_i2c {
    UH      IADR;               /* I2C Address register                     */
    UH      fill1;              /* Reserved space                           */
    UH      IFDR;               /* I2C Frequency Divider register           */
    UH      fill2;              /* Reserved space                           */
    UH      I2CR;               /* I2C Control register                     */
    UH      fill3;              /* Reserved space                           */
    UH      I2SR;               /* I2C Status register                      */
    UH      fill4;              /* Reserved space                           */
    UH      I2DR;               /* I2C Data I/O register                    */
};

#define REG_I2C1        (*(volatile struct t_i2c *)0x43F80000)
#define REG_I2C2        (*(volatile struct t_i2c *)0x43F98000)
#define REG_I2C3        (*(volatile struct t_i2c *)0x43F84000)


/* Controller Area Network registers                                        */

struct t_can {
    UW      MCR;                /* Module configuration register            */
    UW      CTRL;               /* Control register                         */
    UW      TIMER;              /* Free-running timer register              */
    UW      fill1;              /* Reserved space                           */
    UW      RXGMASK;            /* Rx global mask register                  */
    UW      RX14MASK;           /* Rx buffer 14 mask register               */
    UW      RX15MASK;           /* Rx buffer 15 masks register              */
    UW      ECR;                /* Error counter register                   */
    UW      ESR;                /* Error and status register                */
    UW      IMASK2;             /* Interrupt masks 2 register               */
    UW      IMASK1;             /* Interrupt masks 1 register               */
    UW      IFLAG2;             /* Interrupt flags 2 register               */
    UW      IFLAG1;             /* Interrupt flags 1 register               */
    UW      fill2[0x4C/4];      /* Reserved space                           */
    UW      MB[64][4];          /* Message buffers 0-63                     */
    UW      fill3[0x400/4];     /* Reserved space                           */
    UW      RXIMR[64];          /* Rx individual mask registers 0-63        */
};

#define REG_CAN1        (*(volatile struct t_can *)0x43F88000)
#define REG_CAN2        (*(volatile struct t_can *)0x43F8C000)


/*** 1-Wire Controller registers                                            */

struct t_owire {
    UH      CONTROL;            /* Control register                         */
    UH      TIME_DIVIDER;       /* Time Divider register                    */
    UH      RESET;              /* Reset register                           */
    UH      COMMAND;            /* Command register                         */
    UH      TX_RX;              /* Transmit/Receive register                */
    UH      INTERRUPT;          /* Interrupt register                       */
    UH      INTERRUPT_EN;       /* Interrupt Enable register                */
};

#define REG_OWIRE   (*(volatile struct t_owire *)0x43F9C000)


/* Configurable Serial Peripheral Interface Controller registers            */

struct t_cspi {
    UW      RXData;             /* Receive Data register                    */
    UW      TXData;             /* Transmit Data register                   */
    UW      CONREG;             /* Control register                         */
    UW      INTREG;             /* Interrupt Control register               */
    UW      DMAREG;             /* DMA Control register                     */
    UW      STATREG;            /* Status register                          */
    UW      PERIODREG;          /* Sample Period Control register           */
    UW      TEST;               /* Test Control register                    */
};

#define REG_CSPI1   (*(volatile struct t_cspi *)0x43FA4000)
#define REG_CSPI2   (*(volatile struct t_cspi *)0x50010000)
#define REG_CSPI3   (*(volatile struct t_cspi *)0x50004000)


/* Keypad Port registers */

struct t_kpp {
    UH      KPCR;               /* Keypad Control register                  */
    UH      KPSR;               /* Keypad Status register                   */
    UH      KDDR;               /* Keypad Data Direction register           */
    UH      KPDR;               /* Keypad Data register                     */
};

#define REG_KPP     (*(volatile struct t_kpp *)0x43FA8000)


/* Digital Audio Mux registers                                              */

struct t_audmux {
    UW      PTCR1;              /* Port Timing Contron register 1           */
    UW      PDCR1;              /* Port Data Control register 1             */
    UW      PTCR2;              /* Port Timing Contron register 2           */
    UW      PDCR2;              /* Port Data Control register 2             */
    UW      PTCR3;              /* Port Timing Contron register 3           */
    UW      PDCR3;              /* Port Data Control register 3             */
    UW      PTCR4;              /* Port Timing Contron register 4           */
    UW      PDCR4;              /* Port Data Control register 4             */
    UW      PTCR5;              /* Port Timing Contron register 5           */
    UW      PDCR5;              /* Port Data Control register 5             */
    UW      PTCR6;              /* Port Timing Contron register 6           */
    UW      PDCR6;              /* Port Data Control register 6             */
    UW      PTCR7;              /* Port Timing Contron register 7           */
    UW      PDCR7;              /* Port Data Control register 7             */
    UW      CNMCR;              /* CE Bus Network Mode Control register     */
};

#define REG_AUDMUX  (*(volatile struct t_audmux *)0x43FB0000)


/* Synchronous Serial Interfacs 1 Controller registers                      */

struct t_ssi {
    UW      STX0;               /* Transmit Data register 0                 */
    UW      STX1;               /* Transmit Data register 1                 */
    UW      SRX0;               /* Receivet Data register 0                 */
    UW      SRX1;               /* Receivet Data register 1                 */
    UW      SCR;                /* Control register                         */
    UW      SISR;               /* Interrupt Status register                */
    UW      SIER;               /* Interrupt Enable register                */
    UW      STCR;               /* Transmit Configuaration register         */
    UW      SRCR;               /* Receive Configuaration register          */
    UW      STCCR;              /* Transmit Clock Control register          */
    UW      SRCCR;              /* Receive Clock Control register           */
    UW      SFCSR;              /* FIFO Control Status register             */
    UW      STR;                /* Test register                            */
    UW      SOR;                /* Option register                          */
    UW      SACNT;              /* AC97 Control register                    */
    UW      SACADD;             /* AC97 Command Address register            */
    UW      SACDAT;             /* AC97 Command DAta register               */
    UW      SATAG;              /* AC97 Tag register                        */
    UW      STMSK;              /* Transmit Time Slot Mask register         */
    UW      SRMSK;              /* Receive Time Slot Mask register          */
    UW      SACCST;             /* AC97 Channel Status register             */
    UW      SACCEN;             /* AC97 Channel Enable register             */
    UW      SACCDIS;            /* AC97 Channel Disable register            */
    UW      PHCONFIG1;          /* Phase Configuration register             */
    UW      FREQMEAS1;          /* Frequency Measurement register           */
};

#define REG_SSI1    (*(volatile struct t_ssi *)0x50034000)
#define REG_SSI2    (*(volatile struct t_ssi *)0x50011000)


/* Enhanced Serial Audio Interfacs 1 Controller registers                   */

struct t_esai {
    UW      ETDR;               /* ESAI Transmit Data register              */
    UW      ERDR;               /* ESAI Receive Data register               */
    UW      ECR;                /* ESAI Control register                    */
    UW      ESR;                /* ESAI Status register                     */
    UW      TFCR;               /* Transmit FIFO Configuration register     */
    UW      TFSR;               /* Transmit FIFO Status register            */
    UW      RFCR;               /* Receive FIFO Configuration register      */
    UW      RFSR;               /* Receive FIFO Status register             */
    UW      fill1[0x60/4];      /* Reserved space                           */
    UW      TX0;                /* Transmit Data register 0                 */
    UW      TX1;                /* Transmit Data register 1                 */
    UW      TX2;                /* Transmit Data register 2                 */
    UW      TX3;                /* Transmit Data register 3                 */
    UW      TX4;                /* Transmit Data register 4                 */
    UW      TX5;                /* Transmit Data register 5                 */
    UW      TSR;                /* Transmit Slot register                   */
    UW      fill2;              /* Reserved space                           */
    UW      RX0;                /* Receive Data register 0                  */
    UW      RX1;                /* Receive Data register 1                  */
    UW      RX2;                /* Receive Data register 2                  */
    UW      RX3;                /* Receive Data register 3                  */
    UW      fill3[0x1C/4];      /* Reserved space                           */
    UW      SAISR;              /* Serial Audio Interface Status register   */
    UW      SAICR;              /* Serial Audio Interface Control register  */
    UW      TCR;                /* Transmit Control register                */
    UW      TCCR;               /* Transmit Clock Control register          */
    UW      RCR;                /* Receive Control register                 */
    UW      RCCR;               /* Receive Clock Control register           */
    UW      TSMA;               /* Transmit Slot Mask register A            */
    UW      TSMB;               /* Transmit Slot Mask register B            */
    UW      RSMA;               /* Receive Slot Mas register A              */
    UW      RSMB;               /* Receive Slot Mas register B              */
    UW      PRRC;               /* Port C Direction register                */
    UW      PCRC;               /* Port C Control register                  */
};

#define REG_ESAI    (*(volatile struct t_esai *)0x50018000)


/* Touch Screen Controller and Analog-to-Digital Converter registers        */

struct t_tsc {
    UW      TGCR;               /* TSC General Config register              */
    UW      TGSR;               /* TSC General Status register              */
    UW      TICR;               /* TSC IDLE Config register                 */
    UW      fill1[0x3F4/4];     /* Reserved space                           */
    UW      TCQFIFO;            /* Touch Screen Convert Queue FIFO register */
    UW      TCQCR;              /* Touch Screen Convert Queue Control register   */
    UW      TCQSR;              /* Touch Screen Convert Queue Status register    */
    UW      TTCQMR;             /* Touch Screen Convert Queue Mask register */
    UW      fill2[0x10/4];      /* Reserved space                           */
    UW      TCQITEM_7_0;        /* Touch Screen Convert Queue ITEM 7~0 register  */
    UW      TCQITEM_15_8;       /* Touch Screen Convert Queue ITEM 15~8 register */
    UW      fill3[0x18/4];      /* Reserved space                           */
    UW      TCC0;               /* Touch Screen Convert Config 0 register   */
    UW      TCC1;               /* Touch Screen Convert Config 1 register   */
    UW      TCC2;               /* Touch Screen Convert Config 2 register   */
    UW      TCC3;               /* Touch Screen Convert Config 3 register   */
    UW      TCC4;               /* Touch Screen Convert Config 4 register   */
    UW      TCC5;               /* Touch Screen Convert Config 5 register   */
    UW      TCC6;               /* Touch Screen Convert Config 6 register   */
    UW      TCC7;               /* Touch Screen Convert Config 7 register   */
    UW      fill4[0x3A0/4];     /* Reserved space                           */
    UW      GCQFIFO;            /* General ADC Convert Queue FIFO register  */
    UW      GCQCR;              /* General ADC Convert Queue Control register    */
    UW      GCQSR;              /* General ADC Convert Queue Status register     */
    UW      GCQMR;              /* General ADC Convert Queue Mask register  */
    UW      fill5[0x10/4];      /* Reserved space                           */
    UW      GCQITEM_7_0;        /* General ADC Convert Queue ITEM 7~0 register   */
    UW      GCQITEM_15_8;       /* General ADC Convert Queue ITEM 15~8 register  */
    UW      fill6[0x18/4];      /* Reserved space                           */
    UW      GCC0;               /* General ADC Convert Config 0 register    */
    UW      GCC1;               /* General ADC Convert Config 1 register    */
    UW      GCC2;               /* General ADC Convert Config 2 register    */
    UW      GCC3;               /* General ADC Convert Config 3 register    */
    UW      GCC4;               /* General ADC Convert Config 4 register    */
    UW      GCC5;               /* General ADC Convert Config 5 register    */
    UW      GCC6;               /* General ADC Convert Config 6 register    */
    UW      GCC7;               /* General ADC Convert Config 7 register    */
};

#define REG_TSC     (*(volatile struct t_tsc *)0x50030000)


/*** Pulse-Width Modulator registers                                        */

struct t_pwm {
    UW      PWMCR;              /* Control register                         */
    UW      PWMSR;              /* Status register                          */
    UW      PWMIR;              /* Interrupt register                       */
    UW      PWMSAR;             /* Sample register                          */
    UW      PWMPR;              /* Period register                          */
    UW      PWMCNR;             /* Counter register                         */
};

#define REG_PWM1    (*(volatile struct t_pwm *)0x53FE0000)
#define REG_PWM2    (*(volatile struct t_pwm *)0x53FA0000)
#define REG_PWM3    (*(volatile struct t_pwm *)0x53FA8000)
#define REG_PWM4    (*(volatile struct t_pwm *)0x53FC8000)


/* WatchDog Timer Modle registers                                           */

struct t_wdog {
    UH      WCR;                /* WatchDog Control register                */
    UH      WSR;                /* WatchDog Service register                */
    UH      WRSR;               /* WatchDog Reset Status register           */
    UH      WICR;               /* WatchDog Interrupt Control register      */
    UH      WMCR;               /* WatchDog Miscellaneous Control register  */
};

#define REG_WDOG    (*(volatile struct t_wdog *)0x53FDC000)


/* Clock Controller Module registers                                        */

struct t_ccm {
    UW      MPCTL;              /* MCU PLL Control register                 */
    UW      UPCTL;              /* USB PLL Control register                 */
    UW      CCTL;               /* Clock Control register                   */
    UW      CGCR0;              /* Clock Gating Control register 0          */
    UW      CGCR1;              /* Clock Gating Control register 1          */
    UW      CGCR2;              /* Clock Gating Control register 2          */
    UW      PCDR0;              /* PRE Clock Divider register 0             */
    UW      PCDR1;              /* PRE Clock Divider register 1             */
    UW      PCDR2;              /* PRE Clock Divider register 0             */
    UW      PCDR3;              /* PRE Clock Divider register 1             */
    UW      RCSR;               /* CCM Reset Control and Source register    */
    UW      CRDR;               /* CCM Reset Control and Debug register     */
    UW      DCVR0;              /* DPTC Comparator Value register 0         */
    UW      DCVR1;              /* DPTC Comparator Value register 1         */
    UW      DCVR2;              /* DPTC Comparator Value register 2         */
    UW      DCVR3;              /* DPTC Comparator Value register 3         */
    UW      LTR0;               /* Load Tracking register 0                 */
    UW      LTR1;               /* Load Tracking register 1                 */
    UW      LTR2;               /* Load Tracking register 2                 */
    UW      LTR3;               /* Load Tracking register 3                 */
    UW      LTBR0;              /* Load Tracking Buffer register 0          */
    UW      LTBR1;              /* Load Tracking Buffer register 1          */
    UW      PMCR0;              /* Power Management Control register 0      */
    UW      PMCR1;              /* Power Management Control register 1      */
    UW      PMCR2;              /* Power Management Control register 2      */
    UW      MCR;                /* Miscellaneous Control register           */
    UW      LPIMR0;             /* Low Power Interrupt Mask register 0      */
    UW      LPIMR1;             /* Low Power Interrupt Mask register 1      */
};

#define REG_CCM         (*(volatile struct t_ccm *)0x53F80000)


/* Liquid Crystal Display Controller registers                              */

struct t_lcdc {
    UW      LSSAR;              /* Screen Start Address register            */
    UW      LSR;                /* Size register                            */
    UW      LVPWR;              /* Virtual Page Width register              */
    UW      LCPR;               /* Cursor Position register                 */
    UW      LCWHBR;             /* Cursor Width Height and Blink register   */
    UW      LCCMR;              /* Color Cursor Mapping register            */
    UW      LPCR;               /* Panel Configuration register             */
    UW      LHCR;               /* Horizontal Confiugration register        */
    UW      LVCR;               /* Vertical Configuration register          */
    UW      LPOR;               /* Panning Offset register                  */
    UW      LSCR;               /* Sharp Configuration register             */
    UW      LPCCR;              /* PWM Contrast Control register            */
    UW      LDCR;               /* Graphic Window DMA Control register      */
    UW      LRMCR;              /* Refresh Mode Control register            */
    UW      LICR;               /* Interrupt Configuration register         */
    UW      LIER;               /* Interrupt Enable register                */
    UW      LISR;               /* Interrupt Status register                */
    UW      fill1[3];           /* Reserved space                           */
    UW      LGWSAR;             /* Graphic Window Start Address register    */
    UW      LGWSR;              /* Graphic Window Size register             */
    UW      LGWVPWR;            /* Graphic Window Virtual Page Width register   */
    UW      LGWPOR;             /* Graphic Window Panning Offset register   */
    UW      LGWPR;              /* Graphic Window Position register         */
    UW      LGWCR;              /* Graphic Window Control register          */
    UW      LGWDCR;             /* Graphic Window DMA Control register      */
    UW      fill2[5];           /* Reserved space                           */
    UW      LAUSCR;             /* AUS Mode Control register                */
    UW      LAUSCCR;            /* AUS Mode Cursor Control register         */
    UW      fill3[0x778/4];     /* Reserved space                           */
    UW      BGLUT[256];         /* Background Lookup Table                  */
    UW      GWLUT[256];         /* Graphic Window Lookup Table              */
};

#define REG_LCDC        (*(volatile struct t_lcdc *)0x53FBC000)


/* IOMUX Controller registers                                               */

struct t_iomuxc {
    UW      GPR1;               /* General Purpose register                 */
    UW      OBSERVE_INT_MUX;    /* Select Instance Pin for Observability    */
    UW      SW_MUX_CTL_PAD_A10;
    UW      SW_MUX_CTL_PAD_A13;
    UW      SW_MUX_CTL_PAD_A14;
    UW      SW_MUX_CTL_PAD_A15;
    UW      SW_MUX_CTL_PAD_A16;
    UW      SW_MUX_CTL_PAD_A17;
    UW      SW_MUX_CTL_PAD_A18;
    UW      SW_MUX_CTL_PAD_A19;
    UW      SW_MUX_CTL_PAD_A20;
    UW      SW_MUX_CTL_PAD_A21;
    UW      SW_MUX_CTL_PAD_A22;
    UW      SW_MUX_CTL_PAD_A23;
    UW      SW_MUX_CTL_PAD_A24;
    UW      SW_MUX_CTL_PAD_A25;
    UW      SW_MUX_CTL_PAD_EB0;
    UW      SW_MUX_CTL_PAD_EB1;
    UW      SW_MUX_CTL_PAD_OE;
    UW      SW_MUX_CTL_PAD_CS0;
    UW      SW_MUX_CTL_PAD_CS1;
    UW      SW_MUX_CTL_PAD_CS4;
    UW      SW_MUX_CTL_PAD_CS5;
    UW      SW_MUX_CTL_PAD_NF_CE0;
    UW      SW_MUX_CTL_PAD_ECB;
    UW      SW_MUX_CTL_PAD_LBA;
    UW      SW_MUX_CTL_PAD_BCLK;
    UW      SW_MUX_CTL_PAD_RW;
    UW      SW_MUX_CTL_PAD_NFWE_B;
    UW      SW_MUX_CTL_PAD_NFRE_B;
    UW      SW_MUX_CTL_PAD_NFALE;
    UW      SW_MUX_CTL_PAD_NFCLE;
    UW      SW_MUX_CTL_PAD_NFWP_B;
    UW      SW_MUX_CTL_PAD_NFRB;
    UW      SW_MUX_CTL_PAD_D15;
    UW      SW_MUX_CTL_PAD_D14;
    UW      SW_MUX_CTL_PAD_D13;
    UW      SW_MUX_CTL_PAD_D12;
    UW      SW_MUX_CTL_PAD_D11;
    UW      SW_MUX_CTL_PAD_D10;
    UW      SW_MUX_CTL_PAD_D9;
    UW      SW_MUX_CTL_PAD_D8;
    UW      SW_MUX_CTL_PAD_D7;
    UW      SW_MUX_CTL_PAD_D6;
    UW      SW_MUX_CTL_PAD_D5;
    UW      SW_MUX_CTL_PAD_D4;
    UW      SW_MUX_CTL_PAD_D3;
    UW      SW_MUX_CTL_PAD_D2;
    UW      SW_MUX_CTL_PAD_D1;
    UW      SW_MUX_CTL_PAD_D0;
    UW      SW_MUX_CTL_PAD_LD0;
    UW      SW_MUX_CTL_PAD_LD1;
    UW      SW_MUX_CTL_PAD_LD2;
    UW      SW_MUX_CTL_PAD_LD3;
    UW      SW_MUX_CTL_PAD_LD4;
    UW      SW_MUX_CTL_PAD_LD5;
    UW      SW_MUX_CTL_PAD_LD6;
    UW      SW_MUX_CTL_PAD_LD7;
    UW      SW_MUX_CTL_PAD_LD8;
    UW      SW_MUX_CTL_PAD_LD9;
    UW      SW_MUX_CTL_PAD_LD10;
    UW      SW_MUX_CTL_PAD_LD11;
    UW      SW_MUX_CTL_PAD_LD12;
    UW      SW_MUX_CTL_PAD_LD13;
    UW      SW_MUX_CTL_PAD_LD14;
    UW      SW_MUX_CTL_PAD_LD15;
    UW      SW_MUX_CTL_PAD_HSYNC;
    UW      SW_MUX_CTL_PAD_VSYNC;
    UW      SW_MUX_CTL_PAD_LSCLK;
    UW      SW_MUX_CTL_PAD_OE_ACD;
    UW      SW_MUX_CTL_PAD_CONTRAST;
    UW      SW_MUX_CTL_PAD_PWM;
    UW      SW_MUX_CTL_PAD_CSI_D2;
    UW      SW_MUX_CTL_PAD_CSI_D3;
    UW      SW_MUX_CTL_PAD_CSI_D4;
    UW      SW_MUX_CTL_PAD_CSI_D5;
    UW      SW_MUX_CTL_PAD_CSI_D6;
    UW      SW_MUX_CTL_PAD_CSI_D7;
    UW      SW_MUX_CTL_PAD_CSI_D8;
    UW      SW_MUX_CTL_PAD_CSI_D9;
    UW      SW_MUX_CTL_PAD_CSI_MCLK;
    UW      SW_MUX_CTL_PAD_CSI_VSYNC;
    UW      SW_MUX_CTL_PAD_CSI_HSYNC;
    UW      SW_MUX_CTL_PAD_CSI_PIXCLK;
    UW      SW_MUX_CTL_PAD_I2C1_CLK;
    UW      SW_MUX_CTL_PAD_I2C1_DAT;
    UW      SW_MUX_CTL_PAD_CSPI1_MOSI;
    UW      SW_MUX_CTL_PAD_CSPI1_MISO;
    UW      SW_MUX_CTL_PAD_CSPI1_SS0;
    UW      SW_MUX_CTL_PAD_CSPI1_SS1;
    UW      SW_MUX_CTL_PAD_CSPI1_SCLK;
    UW      SW_MUX_CTL_PAD_CSPI1_RDY;
    UW      SW_MUX_CTL_PAD_UART1_RXD;
    UW      SW_MUX_CTL_PAD_UART1_TXD;
    UW      SW_MUX_CTL_PAD_UART1_RTS;
    UW      SW_MUX_CTL_PAD_UART1_CTS;
    UW      SW_MUX_CTL_PAD_UART2_RXD;
    UW      SW_MUX_CTL_PAD_UART2_TXD;
    UW      SW_MUX_CTL_PAD_UART2_RTS;
    UW      SW_MUX_CTL_PAD_UART2_CTS;
    UW      SW_MUX_CTL_PAD_SD1_CMD;
    UW      SW_MUX_CTL_PAD_SD1_CLK;
    UW      SW_MUX_CTL_PAD_SD1_DATA0;
    UW      SW_MUX_CTL_PAD_SD1_DATA1;
    UW      SW_MUX_CTL_PAD_SD1_DATA2;
    UW      SW_MUX_CTL_PAD_SD1_DATA3;
    UW      SW_MUX_CTL_PAD_KPP_ROW0;
    UW      SW_MUX_CTL_PAD_KPP_ROW1;
    UW      SW_MUX_CTL_PAD_KPP_ROW2;
    UW      SW_MUX_CTL_PAD_KPP_ROW3;
    UW      SW_MUX_CTL_PAD_KPP_COL0;
    UW      SW_MUX_CTL_PAD_KPP_COL1;
    UW      SW_MUX_CTL_PAD_KPP_COL2;
    UW      SW_MUX_CTL_PAD_KPP_COL3;
    UW      SW_MUX_CTL_PAD_FEC_MDC;
    UW      SW_MUX_CTL_PAD_FEC_MDIO;
    UW      SW_MUX_CTL_PAD_FEC_TDATA0;
    UW      SW_MUX_CTL_PAD_FEC_TDATA1;
    UW      SW_MUX_CTL_PAD_FEC_TX_EN;
    UW      SW_MUX_CTL_PAD_FEC_RDATA0;
    UW      SW_MUX_CTL_PAD_FEC_RDATA1;
    UW      SW_MUX_CTL_PAD_FEC_RX_DV;
    UW      SW_MUX_CTL_PAD_FEC_TX_CLK;
    UW      SW_MUX_CTL_PAD_RTCK;
    UW      SW_MUX_CTL_PAD_DE_B;
    UW      SW_MUX_CTL_PAD_GPIO_A;
    UW      SW_MUX_CTL_PAD_GPIO_B;
    UW      SW_MUX_CTL_PAD_GPIO_C;
    UW      SW_MUX_CTL_PAD_GPIO_D;
    UW      SW_MUX_CTL_PAD_GPIO_E;
    UW      SW_MUX_CTL_PAD_GPIO_F;
    UW      SW_MUX_CTL_PAD_EXT_ARMCLK;
    UW      SW_MUX_CTL_PAD_UPLL_BYPCLK;
    UW      SW_MUX_CTL_PAD_VSTBY_REQ;
    UW      SW_MUX_CTL_PAD_VSTBY_ACK;
    UW      SW_MUX_CTL_PAD_POWER_FAIL;
    UW      SW_MUX_CTL_PAD_CLKO;
    UW      SW_MUX_CTL_PAD_BOOT_MODE0;
    UW      SW_MUX_CTL_PAD_BOOT_MODE1;
    UW      SW_PAD_CTL_PAD_A13;
    UW      SW_PAD_CTL_PAD_A14;
    UW      SW_PAD_CTL_PAD_A15;
    UW      SW_PAD_CTL_PAD_A17;
    UW      SW_PAD_CTL_PAD_A18;
    UW      SW_PAD_CTL_PAD_A19;
    UW      SW_PAD_CTL_PAD_A20;
    UW      SW_PAD_CTL_PAD_A21;
    UW      SW_PAD_CTL_PAD_A23;
    UW      SW_PAD_CTL_PAD_A24;
    UW      SW_PAD_CTL_PAD_A25;
    UW      SW_PAD_CTL_PAD_EB0;
    UW      SW_PAD_CTL_PAD_EB1;
    UW      SW_PAD_CTL_PAD_OE;
    UW      SW_PAD_CTL_PAD_CS4;
    UW      SW_PAD_CTL_PAD_CS5;
    UW      SW_PAD_CTL_PAD_NF_CE0;
    UW      SW_PAD_CTL_PAD_ECB;
    UW      SW_PAD_CTL_PAD_LBA;
    UW      SW_PAD_CTL_PAD_RW;
    UW      SW_PAD_CTL_PAD_NFRB;
    UW      SW_PAD_CTL_PAD_D15;
    UW      SW_PAD_CTL_PAD_D14;
    UW      SW_PAD_CTL_PAD_D13;
    UW      SW_PAD_CTL_PAD_D12;
    UW      SW_PAD_CTL_PAD_D11;
    UW      SW_PAD_CTL_PAD_D10;
    UW      SW_PAD_CTL_PAD_D9;
    UW      SW_PAD_CTL_PAD_D8;
    UW      SW_PAD_CTL_PAD_D7;
    UW      SW_PAD_CTL_PAD_D6;
    UW      SW_PAD_CTL_PAD_D5;
    UW      SW_PAD_CTL_PAD_D4;
    UW      SW_PAD_CTL_PAD_D3;
    UW      SW_PAD_CTL_PAD_D2;
    UW      SW_PAD_CTL_PAD_D1;
    UW      SW_PAD_CTL_PAD_D0;
    UW      SW_PAD_CTL_PAD_LD0;
    UW      SW_PAD_CTL_PAD_LD1;
    UW      SW_PAD_CTL_PAD_LD2;
    UW      SW_PAD_CTL_PAD_LD3;
    UW      SW_PAD_CTL_PAD_LD4;
    UW      SW_PAD_CTL_PAD_LD5;
    UW      SW_PAD_CTL_PAD_LD6;
    UW      SW_PAD_CTL_PAD_LD7;
    UW      SW_PAD_CTL_PAD_LD8;
    UW      SW_PAD_CTL_PAD_LD9;
    UW      SW_PAD_CTL_PAD_LD10;
    UW      SW_PAD_CTL_PAD_LD11;
    UW      SW_PAD_CTL_PAD_LD12;
    UW      SW_PAD_CTL_PAD_LD13;
    UW      SW_PAD_CTL_PAD_LD14;
    UW      SW_PAD_CTL_PAD_LD15;
    UW      SW_PAD_CTL_PAD_HSYNC;
    UW      SW_PAD_CTL_PAD_VSYNC;
    UW      SW_PAD_CTL_PAD_LSCLK;
    UW      SW_PAD_CTL_PAD_OE_ACD;
    UW      SW_PAD_CTL_PAD_CONTRAST;
    UW      SW_PAD_CTL_PAD_PWM;
    UW      SW_PAD_CTL_PAD_CSI_D2;
    UW      SW_PAD_CTL_PAD_CSI_D3;
    UW      SW_PAD_CTL_PAD_CSI_D4;
    UW      SW_PAD_CTL_PAD_CSI_D5;
    UW      SW_PAD_CTL_PAD_CSI_D6;
    UW      SW_PAD_CTL_PAD_CSI_D7;
    UW      SW_PAD_CTL_PAD_CSI_D8;
    UW      SW_PAD_CTL_PAD_CSI_D9;
    UW      SW_PAD_CTL_PAD_CSI_MCLK;
    UW      SW_PAD_CTL_PAD_CSI_VSYNC;
    UW      SW_PAD_CTL_PAD_CSI_HSYNC;
    UW      SW_PAD_CTL_PAD_CSI_PIXCLK;
    UW      SW_PAD_CTL_PAD_I2C1_CLK;
    UW      SW_PAD_CTL_PAD_I2C1_DAT;
    UW      SW_PAD_CTL_PAD_CSPI1_MOSI;
    UW      SW_PAD_CTL_PAD_CSPI1_MISO;
    UW      SW_PAD_CTL_PAD_CSPI1_SS0;
    UW      SW_PAD_CTL_PAD_CSPI1_SS1;
    UW      SW_PAD_CTL_PAD_CSPI1_SCLK;
    UW      SW_PAD_CTL_PAD_CSPI1_RDY;
    UW      SW_PAD_CTL_PAD_UART1_RXD;
    UW      SW_PAD_CTL_PAD_UART1_TXD;
    UW      SW_PAD_CTL_PAD_UART1_RTS;
    UW      SW_PAD_CTL_PAD_UART1_CTS;
    UW      SW_PAD_CTL_PAD_UART2_RXD;
    UW      SW_PAD_CTL_PAD_UART2_TXD;
    UW      SW_PAD_CTL_PAD_UART2_RTS;
    UW      SW_PAD_CTL_PAD_UART2_CTS;
    UW      SW_PAD_CTL_PAD_SD1_CMD;
    UW      SW_PAD_CTL_PAD_SD1_CLK;
    UW      SW_PAD_CTL_PAD_SD1_DATA0;
    UW      SW_PAD_CTL_PAD_SD1_DATA1;
    UW      SW_PAD_CTL_PAD_SD1_DATA2;
    UW      SW_PAD_CTL_PAD_SD1_DATA3;
    UW      SW_PAD_CTL_PAD_KPP_ROW0;
    UW      SW_PAD_CTL_PAD_KPP_ROW1;
    UW      SW_PAD_CTL_PAD_KPP_ROW2;
    UW      SW_PAD_CTL_PAD_KPP_ROW3;
    UW      SW_PAD_CTL_PAD_KPP_COL0;
    UW      SW_PAD_CTL_PAD_KPP_COL1;
    UW      SW_PAD_CTL_PAD_KPP_COL2;
    UW      SW_PAD_CTL_PAD_KPP_COL3;
    UW      SW_PAD_CTL_PAD_FEC_MDC;
    UW      SW_PAD_CTL_PAD_FEC_MDIO;
    UW      SW_PAD_CTL_PAD_FEC_TDATA0;
    UW      SW_PAD_CTL_PAD_FEC_TDATA1;
    UW      SW_PAD_CTL_PAD_FEC_TX_EN;
    UW      SW_PAD_CTL_PAD_FEC_RDATA0;
    UW      SW_PAD_CTL_PAD_FEC_RDATA1;
    UW      SW_PAD_CTL_PAD_FEC_RX_DV;
    UW      SW_PAD_CTL_PAD_FEC_TX_CLK;
    UW      SW_PAD_CTL_PAD_RTCK;
    UW      SW_PAD_CTL_PAD_TDO;
    UW      SW_PAD_CTL_PAD_DE_B;
    UW      SW_PAD_CTL_PAD_GPIO_A;
    UW      SW_PAD_CTL_PAD_GPIO_B;
    UW      SW_PAD_CTL_PAD_GPIO_C;
    UW      SW_PAD_CTL_PAD_GPIO_D;
    UW      SW_PAD_CTL_PAD_GPIO_E;
    UW      SW_PAD_CTL_PAD_GPIO_F;
    UW      SW_PAD_CTL_PAD_VSTBY_REQ;
    UW      SW_PAD_CTL_PAD_VSTBY_ACK;
    UW      SW_PAD_CTL_PAD_POWER_FAIL;
    UW      SW_PAD_CTL_PAD_CLKO;
    UW      SW_PAD_CTL_GRP_DVS_MISC;
    UW      SW_PAD_CTL_GRP_DSE_FEC;
    UW      SW_PAD_CTL_GRP_DVS_JTAG;
    UW      SW_PAD_CTL_GRP_DSE_NFC;
    UW      SW_PAD_CTL_GRP_DSE_CSI;
    UW      SW_PAD_CTL_GRP_DSE_WEIM;
    UW      SW_PAD_CTL_GRP_DSE_DDR;
    UW      SW_PAD_CTL_GRP_DVS_CCM;
    UW      SW_PAD_CTL_GRP_DSE_KPP;
    UW      SW_PAD_CTL_GRP_DSE_SDHC1;
    UW      SW_PAD_CTL_GRP_DSE_LCD;
    UW      SW_PAD_CTL_GRP_DSE_UART;
    UW      SW_PAD_CTL_GRP_DVS_NFC;
    UW      SW_PAD_CTL_GRP_DVS_CSI;
    UW      SW_PAD_CTL_GRP_DSE_CSPI1;
    UW      SW_PAD_CTL_GRP_DDRTYPE;
    UW      SW_PAD_CTL_GRP_DVS_SDHC1;
    UW      SW_PAD_CTL_GRP_DVS_LCD;
    UW      AUDMUX_P4_INPUT_DA_AMX_SELECT_INPUT;
    UW      AUDMUX_P4_INPUT_DB_AMX_SELECT_INPUT;
    UW      AUDMUX_P4_INPUT_RXCLK_AMX_SELECT_INPUT;
    UW      AUDMUX_P4_INPUT_RXFS_AMX_SELECT_INPUT;
    UW      AUDMUX_P4_INPUT_TXCLK_AMX_SELECT_INPUT;
    UW      AUDMUX_P4_INPUT_TXFS_AMX_SELECT_INPUT;
    UW      AUDMUX_P7_INPUT_DA_AMX_SELECT_INPUT;
    UW      AUDMUX_P7_INPUT_TXFS_AMX_SELECT_INPUT;
    UW      CAN1_IPP_IND_CANRX_SELECT_INPUT;
    UW      CAN2_IPP_IND_CANRX_SELECT_INPUT;
    UW      CSI_IPP_CSI_D_0_SELECT_INPUT;
    UW      CSI_IPP_CSI_D_1_SELECT_INPUT;
    UW      CSPI1_IPP_IND_SS3_B_SELECT_INPUT;
    UW      CSPI2_IPP_CSPI_CLK_IN_SELECT_INPUT;
    UW      CSPI2_IPP_IND_DATAREADY_B_SELECT_INPUT;
    UW      CSPI2_IPP_IND_MISO_SELECT_INPUT;
    UW      CSPI2_IPP_IND_MOSI_SELECT_INPUT;
    UW      CSPI2_IPP_IND_SS0_B_SELECT_INPUT;
    UW      CSPI2_IPP_IND_SS1_B_SELECT_INPUT;
    UW      CSPI3_IPP_CSPI_CLK_IN_SELECT_INPUT;
    UW      CSPI3_IPP_IND_DATAREADY_B_SELECT_INPUT;
    UW      CSPI3_IPP_IND_MISO_SELECT_INPUT;
    UW      CSPI3_IPP_IND_MOSI_SELECT_INPUT;
    UW      CSPI3_IPP_IND_SS0_B_SELECT_INPUT;
    UW      CSPI3_IPP_IND_SS1_B_SELECT_INPUT;
    UW      CSPI3_IPP_IND_SS2_B_SELECT_INPUT;
    UW      CSPI3_IPP_IND_SS3_B_SELECT_INPUT;
    UW      ESDHC1_IPP_DAT4_IN_SELECT_INPUT;
    UW      ESDHC1_IPP_DAT5_IN_SELECT_INPUT;
    UW      ESDHC1_IPP_DAT6_IN_SELECT_INPUT;
    UW      ESDHC1_IPP_DAT7_IN_SELECT_INPUT;
    UW      ESDHC2_IPP_CARD_CLK_IN_SELECT_INPUT;
    UW      ESDHC2_IPP_CMD_IN_SELECT_INPUT;
    UW      ESDHC2_IPP_DAT0_IN_SELECT_INPUT;
    UW      ESDHC2_IPP_DAT1_IN_SELECT_INPUT;
    UW      ESDHC2_IPP_DAT2_IN_SELECT_INPUT;
    UW      ESDHC2_IPP_DAT3_IN_SELECT_INPUT;
    UW      ESDHC2_IPP_DAT4_IN_SELECT_INPUT;
    UW      ESDHC2_IPP_DAT5_IN_SELECT_INPUT;
    UW      ESDHC2_IPP_DAT6_IN_SELECT_INPUT;
    UW      ESDHC2_IPP_DAT7_IN_SELECT_INPUT;
    UW      FEC_FEC_COL_SELECT_INPUT;
    UW      FEC_FEC_CRS_SELECT_INPUT;
    UW      FEC_FEC_RDATA_2_SELECT_INPUT;
    UW      FEC_FEC_RDATA_3_SELECT_INPUT;
    UW      FEC_FEC_RX_CLK_SELECT_INPUT;
    UW      FEC_FEC_RX_ER_SELECT_INPUT;
    UW      I2C2_IPP_SCL_IN_SELECT_INPUT;
    UW      I2C2_IPP_SDA_IN_SELECT_INPUT;
    UW      I2C3_IPP_SCL_IN_SELECT_INPUT;
    UW      I2C3_IPP_SDA_IN_SELECT_INPUT;
    UW      KPP_IPP_IND_COL_4_SELECT_INPUT;
    UW      KPP_IPP_IND_COL_5_SELECT_INPUT;
    UW      KPP_IPP_IND_COL_6_SELECT_INPUT;
    UW      KPP_IPP_IND_COL_7_SELECT_INPUT;
    UW      KPP_IPP_IND_ROW_4_SELECT_INPUT;
    UW      KPP_IPP_IND_ROW_5_SELECT_INPUT;
    UW      KPP_IPP_IND_ROW_6_SELECT_INPUT;
    UW      KPP_IPP_IND_ROW_7_SELECT_INPUT;
    UW      SIM1_PIN_SIM_RCVD1_IN_SELECT_INPUT;
    UW      SIM1_PIN_SIM_SIMPD1_SELECT_INPUT;
    UW      SIM1_SIM_RCVD1_IO_SELECT_INPUT;
    UW      SIM2_PIN_SIM_RCVD1_IN_SELECT_INPUT;
    UW      SIM2_PIN_SIM_SIMPD1_SELECT_INPUT;
    UW      SIM2_SIM_RCVD1_IO_SELECT_INPUT;
    UW      UART3_IPP_UART_RTS_B_SELECT_INPUT;
    UW      UART3_IPP_UART_RXD_MUX_SELECT_INPUT;
    UW      UART4_IPP_UART_RTS_B_SELECT_INPUT;
    UW      UART4_IPP_UART_RXD_MUX_SELECT_INPUT;
    UW      UART5_IPP_UART_RTS_B_SELECT_INPUT;
    UW      UART5_IPP_UART_RXD_MUX_SELECT_INPUT;
    UW      USB_TOP_IPP_IND_OTG_USB_OC_SELECT_INPUT;
    UW      USB_TOP_IPP_IND_UH2_USB_OC_SELECT_INPUT;
};

#define REG_IOMUXC      (*(volatile struct t_iomuxc *)0x43FAC000)


/* Wireless External Interface Module registers                             */

struct t_weim {
    UW      CSCR0U;             /* Chip Select 0 Upper Control register     */
    UW      CSCR0L;             /* Chip Select 0 Lower Control register     */
    UW      CSCR0A;             /* Chip Select 0 Additional Control register*/
    UW      fill1;              /* Reserved space                           */
    UW      CSCR1U;             /* Chip Select 1 Upper Control register     */
    UW      CSCR1L;             /* Chip Select 1 Lower Control register     */
    UW      CSCR1A;             /* Chip Select 1 Additional Control register*/
    UW      fill2;              /* Reserved space                           */
    UW      CSCR2U;             /* Chip Select 2 Upper Control register     */
    UW      CSCR2L;             /* Chip Select 2 Lower Control register     */
    UW      CSCR2A;             /* Chip Select 2 Additional Control register*/
    UW      fill3;              /* Reserved space                           */
    UW      CSCR3U;             /* Chip Select 3 Upper Control register     */
    UW      CSCR3L;             /* Chip Select 3 Lower Control register     */
    UW      CSCR3A;             /* Chip Select 3 Additional Control register*/
    UW      fill4;              /* Reserved space                           */
    UW      CSCR4U;             /* Chip Select 4 Upper Control register     */
    UW      CSCR4L;             /* Chip Select 4 Lower Control register     */
    UW      CSCR4A;             /* Chip Select 4 Additional Control register*/
    UW      fill5;              /* Reserved space                           */
    UW      CSCR5U;             /* Chip Select 5 Upper Control register     */
    UW      CSCR5L;             /* Chip Select 5 Lower Control register     */
    UW      CSCR5A;             /* Chip Select 5 Additional Control register*/
    UW      fill6;              /* Reserved space                           */
    UW      WEIM_WCR;           /* WEIM Configuration register              */
};

#define REG_WEIM    (*(volatile struct t_weim *)0xB8002000)


/* Multi-Master Memory Interface (M3IF) registers                           */

struct t_m3if {
    UW      M3IFCTL;            /* Control register                         */
    UW      M3IFWCFG0;          /* Watermark Configuration register 0       */
    UW      M3IFWCFG1;          /* Watermark Configuration register 1       */
    UW      M3IFWCFG2;          /* Watermark Configuration register 2       */
    UW      M3IFWCFG3;          /* Watermark Configuration register 3       */
    UW      M3IFWCFG4;          /* Watermark Configuration register 4       */
    UW      M3IFWCFG5;          /* Watermark Configuration register 5       */
    UW      M3IFWCFG6;          /* Watermark Configuration register 6       */
    UW      M3IFWCFG7;          /* Watermark Configuration register 7       */
    UW      M3IFWCSR;           /* Watermark Control and Status register    */
    UW      M3IFSCFG0;          /* Snooping Configuration register 0        */
    UW      M3IFSCFG1;          /* Snooping Configuration register 1        */
    UW      M3IFSCFG2;          /* Snooping Configuration register 2        */
    UW      M3IFSSR0;           /* Snooping Status register 0               */
    UW      M3IFSSR1;           /* Snooping Status register 1               */
    UW      fill1;              /* Reserved space                           */
    UW      M3IFMLWE0;          /* Master Lock WEIM CS0 register            */
    UW      M3IFMLWE1;          /* Master Lock WEIM CS1 register            */
    UW      M3IFMLWE2;          /* Master Lock WEIM CS2 register            */
    UW      M3IFMLWE3;          /* Master Lock WEIM CS3 register            */
    UW      M3IFMLWE4;          /* Master Lock WEIM CS4 register            */
    UW      M3IFMLWE5;          /* Master Lock WEIM CS5 register            */
};

#define REG_M3IF    (*(volatile struct t_m3if *)0xB8003000)


/* Fast Ethernet Controller (FEC) registers                                 */

struct t_fec {
    UW      fill_1[1];          /* Reserved space                           */
    UW      EIR;                /* Ethernet interrupt event register        */
    UW      EIMR;               /* Ethernet interrupt mask register         */
    UW      fill_2[1];          /* Reserved space                           */
    UW      RDAR;               /* Receive descriptor active register       */
    UW      TDAR;               /* Transmit descriptor active register      */
    UW      fill_3[3];          /* Reserved space                           */
    UW      ECR;                /* Ethernet control register                */
    UW      fill_4[6];          /* Reserved space                           */
    UW      MMFR;               /* MII management frame register            */
    UW      MSCR;               /* MII speed control register               */
    UW      fill_5[7];          /* Reserved space                           */
    UW      MIBC;               /* MIB control register                     */
    UW      fill_6[7];          /* Reserved space                           */
    UW      RCR;                /* Receive control register                 */
    UW      fill_7[15];         /* Reserved space                           */
    UW      TCR;                /* Tarnsmit control register                */
    UW      fill_8[7];          /* Reserved space                           */
    UW      PALR;               /* Physical address low register            */
    UW      PAUR;               /* Physical address upper register          */
    UW      OPDR;               /* Opcode and pause duration register       */
    UW      fill_9[10];         /* Reserved space                           */
    UW      IAUR;               /* Descriptor individual address upper register */
    UW      IALR;               /* Descriptor individual address low register */
    UW      GAUR;               /* Descriptor group address upper register  */
    UW      GALR;               /* Descriptor group address low register    */
    UW      fill_10[7];         /* Reserved space                           */
    UW      TFWR;               /* Transmit FIFO watermark register         */
    UW      fill_11[1];         /* Reserved space                           */
    UW      FRBR;               /* FIFO receive bound register              */
    UW      FRSR;               /* FIFO receive FIFO start register         */
    UW      fill_12[11];        /* Reserved space                           */
    UW      ERDSR;              /* Receive buffer descriptor ring start register */
    UW      ETDSR;              /* Transmit buffer descriptor ring start register */
    UW      EMRBR;              /* Maximum receive buffer size register     */

    UW      fill_13[(0x200-0x188-1)/4]; /* Reserved space                   */

/* 0x200.. MIB Counter */
    struct {
        UW  RMON_T_DROP;        /* Count of frames not counted correcly     */
        UW  RMON_T_PACKETS;     /* Tx packet count                          */
        UW  RMON_T_BC_PKT;      /* Tx broadcast packets                     */
        UW  RMON_T_MC_PKT;      /* Tx multicatst packets                    */
        UW  RMON_T_CRC_ALIGN;   /* Tx packets w CRC/Align error             */
        UW  RMON_T_UNDERSIZE;   /* Tx packets < 64 bytes, good crc          */
        UW  RMON_T_OVERSIZE;    /* Tx packets > MAX_FL bytes, good crc      */
        UW  RMON_T_FRAG;        /* Tx packets < 64 bytes, bad crc           */
        UW  RMON_T_JAB;         /* Tx packets > MAX_FL bytes, bad crc       */
        UW  RMON_T_COL;         /* Tx collision count                       */
        UW  RMON_T_P64;         /* Tx 64 byte packets                       */
        UW  RMON_T_P65TO127;    /* Tx 65 to 127 byte packets                */
        UW  RMON_T_P128TO255;   /* Tx 128 to 255 byte packets               */
        UW  RMON_T_P256TO511;   /* Tx 256 to 511 byte packets               */
        UW  RMON_T_P512TO1023;  /* Tx 512 to 1023 byte packets              */
        UW  RMON_T_P1024TO2047; /* Tx 1024 to 2047 byte packets             */
        UW  RMON_T_P_GTE2048;   /* Tx packets w > 2048 bytes                */
        UW  RMON_T_OCTETS;      /* Tx octets                                */
        UW  IEEE_T_DROP;        /* Count of frames not counted correcly     */
        UW  IEEE_T_FRAME_OK;    /* Frames transmitted OK                    */
        UW  IEEE_T_1COL;        /* Frames transmitted with single collision */
        UW  IEEE_T_MCOL;        /* Frames transmitted with multiple collisions */
        UW  IEEE_T_DEF;         /* Frames transmitted after deferral delay  */
        UW  IEEE_T_LCOL;        /* Frames transmitted with late collision   */
        UW  IEEE_T_EXCOL;       /* Frames transmitted with excessive collisions */
        UW  IEEE_T_MACERR;      /* Frames transmitted with Tx FIFO underrun */
        UW  IEEE_T_CSERR;       /* Frames transmitted with carrier sense error */
        UW  IEEE_T_SQE;         /* Frames transmitted with SQE error        */
        UW  IEEE_T_FDXFC;       /* Flow control pause frames transmitted    */
        UW  IEEE_T_OCTETS_OK;   /* Octets count for frames transmitted w/o error */
        UW  fill_14[3];         /* Reserved space                           */
        UW  RMON_R_PACKETS;     /* Rx packet count                          */
        UW  RMON_R_BC_PKT;      /* Rx broadcast packets                     */
        UW  RMON_R_MC_PKT;      /* Rx multicast packets                     */
        UW  RMON_R_CRC_ALIGN;   /* Rx packets w CRC/Align error             */
        UW  RMON_R_UNDERSIZE;   /* Rx packets < 64 bytes, good crc          */
        UW  RMON_R_OVERSIZE;    /* Rx packets > MAX_FL bytes, good crc      */
        UW  RMON_R_FRAG;        /* Rx packets < 64 bytes, bad crc           */
        UW  RMON_R_JAB;         /* Rx packets > MAX_FL bytes, bad crc       */
        UW  RMON_R_RESVD_0;     /* ---                                      */
        UW  RMON_R_P64;         /* Rx 64 byte packets                       */
        UW  RMON_R_P65TO127;    /* Rx 65 to 127 byte packets                */
        UW  RMON_R_P128TO255;   /* Rx 128 to 255 byte packets               */
        UW  RMON_R_P256TO511;   /* Rx 256 to 511 byte packets               */
        UW  RMON_R_P512TO1023;  /* Rx 512 to 1023 byte packets              */
        UW  RMON_R_P1024TO2047; /* Rx 1024 to 2047 byte packets             */
        UW  RMON_R_P_GTE2048;   /* Rx packets w > 2048 bytes                */
        UW  RMON_R_OCTETS;      /* Rx octets                                */
        UW  IEEE_R_DROP;        /* Count of frames not counted correcly     */
        UW  IEEE_R_FRAME_OK;    /* Frames received OK                       */
        UW  IEEE_R_CRC;         /* Frames received with CRC error           */
        UW  IEEE_R_ALIGN;       /* Frames received with alignment error     */
        UW  IEEE_R_MACERR;      /* Rreceive Rx FIFO overrun                 */
        UW  IEEE_R_FDXFC;       /* Flow control pause frames received       */
        UW  IEEE_R_OCTETS_OK;   /* Octets count for frames received w/o error */
    } MIB;

    UW      fill_15[(0x300-0x2e0-1)/4]; /* Reserved space                   */

/* 0x300.. MIIGSK */
    struct {
        UW  CFGR;               /* MIIGSK Configuration register            */
        UW  fill_16[1];         /* Reserved space                           */
        UW  ENR;                /* MIIGSK Enable register                   */
    } MIIGSK;
};

#define REG_FEC         (*(volatile struct t_fec *)0x50038000)

/* NAND Flash Controller registers                                          */

struct t_nfc {
    struct t_main_area {
        UH    buffer[512/2];        /* Main Area Buffer                     */
    } MAIN_AREA[8];
    struct t_spare_area {
        UH    buffer[64/2];         /* Spare Area Buffer                    */
    } SPARE_AREA[8];
    UW      fill1[0xC00/4];         /* Reserved space                       */
    UH      fill2[2];               /* Reserved space                       */
    UH      RAM_BUFFER_ADDRESS;     /* RAM buffer address register          */
    UH      NAND_FALSH_ADDR;        /* NAND Flash address register          */
    UH      NAND_FLASH_CMD;         /* NAND Flash command register          */
    UH      NFC_CONFIGURATION;      /* NFC internal buffer lock control register     */
    UH      ECC_STATUS_RESULT1;     /* RS ECC status register 1             */
    UH      ECC_STATUS_RESULT2;     /* RS ECC status register 2             */
    UH      SPAS;                   /* Spare only size register             */
    UH      NF_WR_PROT;             /* NAND Flash write protection register */
    UH      fill3[2];               /* Reserved space                       */
    UH      NAND_FLASH_WR_PR_ST;    /* NAND Flash write protection status register   */
    UH      NAND_FLASH_CONFIG1;     /* NAND Flash operation configuration register 1 */
    UH      NAND_FLASH_CONFIG2;     /* NAND Flash operation configuration register 2 */
                                    /* Address to unlock in write protection mode.   */
    UH      fill4;                  /* Reserved space                       */
    UH      UNLOCK_START_BLK_ADD0;  /* start register 0                     */
    UH      UNLOCK_END_BLK_ADD0;    /* end register 0                       */
    UH      UNLOCK_START_BLK_ADD1;  /* start register 1                     */
    UH      UNLOCK_END_BLK_ADD1;    /* end register 1                       */
    UH      UNLOCK_START_BLK_ADD2;  /* start register 2                     */
    UH      UNLOCK_END_BLK_ADD2;    /* end register 2                       */
    UH      UNLOCK_START_BLK_ADD3;  /* start register 3                     */
    UH      UNLOCK_END_BLK_ADD3;    /* end register 3                       */
};

#define REG_NFC     (*(volatile struct t_nfc *)0xBB000000)


/* Enhanced Secured Digital Host Controller registers                       */

struct t_esdhc {
    UW      DSADDR;                 /* DMA system address register          */
    UW      BLKATTR;                /* Block attributes register            */
    UW      CMDARG;                 /* Command argument register            */
    UW      XFERTYP;                /* Transfer type register               */
    UW      CMDRSP0;                /* Command response 0 register          */
    UW      CMDRSP1;                /* Command response 1 register          */
    UW      CMDRSP2;                /* Command response 2 register          */
    UW      CMDRSP3;                /* Command response 3 register          */
    UW      DATPORT;                /* Data buffer access port register     */
    UW      PRSSTAT;                /* Present state register               */
    UW      PROCTL;                 /* Protocol control register            */
    UW      SYSCTL;                 /* System control register              */
    UW      IRQSTAT;                /* Interrupt status register            */
    UW      IRQSTATEN;              /* Interrupt status enable register     */
    UW      IRQSIGEN;               /* Interrupt signal enable register     */
    UW      AUTOC12ERR;             /* Auto CMD12 status register           */
    UW      HOSTCAPBLT;             /* Host controller capabilities register*/
    UW      WML;                    /* Watermark level register             */
    UW      fill1[0x08/4];          /* Reserved space                       */
    UW      FEVT;                   /* Force event register                 */
    UW      fill2[0xA8/4];          /* Reserved space                       */
    UW      HOSTVER;                /* Host controller version register     */
};

#define REG_eSDHC1  (*(volatile struct t_esdhc *)0x53FB4000)
#define REG_eSDHC2  (*(volatile struct t_esdhc *)0x53FB8000)


/* Interrupt Number                                                         */

#define INT_CSPI3       0       /* Configurable Serial Peripheral Interface3*/
#define INT_GPT4        1       /* General Purpose Timer 4                  */
#define INT_1WIRE       2       /* 1-Wire Module                            */
#define INT_I2C1        3       /* Inter-Integrated Circuit 1               */
#define INT_I2C2        4       /* Inter-Integrated Circuit 2               */
#define INT_UART4       5       /* UART 4                                   */
#define INT_RTIC        6       /* Real-Time Integrity Checker              */
#define INT_ESAI        7       /* Enhanced Serial Audio Interface          */
#define INT_ESDHC2      8       /* MultiMedia/SecureData Host Controller 2  */
#define INT_ESDHC1      9       /* MultiMedia/SecureData Host Controller 1  */
#define INT_I2C3        10      /* Inter-Integrated Circuit 3               */
#define INT_SSI2        11      /* Synchronous Serial Interface 1           */
#define INT_SSI1        12      /* Synchronous Serial Interface 2           */
#define INT_CSPI2       13      /* Configurable Serial Peripheral Interface2*/
#define INT_CSPI1       14      /* Configurable Serial Peripheral Interface1*/
#define INT_ATA         15      /* Hard Drive (ATA) Controller              */
#define INT_GPIO3       16      /* General Purpose I/O 3                    */
#define INT_CSI         17      /* CMOS Sensor Interface                    */
#define INT_UART3       18      /* UART3                                    */
#define INT_IIM         19      /* IC Identification Module                 */
#define INT_SIM1        20      /* Subscriber Identification Module 1       */
#define INT_SIM2        21      /* Subscriber Identification Module 2       */
#define INT_RNGB        22      /* Random Number Generator Accelerator      */
#define INT_GPIO4       23      /* General Purpose I/O 4                    */
#define INT_KPP         24      /* Key Pad Port(KPP)                        */
#define INT_RTC         25      /* Real-Time Clock(RTC)                     */
#define INT_PWM1        26      /* Pulse Width Modulator(PWM) 1             */
#define INT_EPIT2       27      /* Enhanced Periodic Timer 2                */
#define INT_EPIT1       28      /* Enhanced Periodic Timer 1                */
#define INT_GPT3        29      /* General Purpose Timer 3                  */
#define INT_PWFAIL      30      /* Power Fail                               */
#define INT_CCM         31      /* CCM(DVFS)                                */
#define INT_UART2       32      /* UART2                                    */
#define INT_NANDFC      33      /* NAND Flash Controller                    */
#define INT_SDMA        34      /* Smart Direct Memory Access               */
#define INT_USBHTG      35      /* USB Host                                 */
#define INT_PWM2        36      /* Pulse Width Modulator(PWM) 2             */
#define INT_USBOTG      37      /* USB OTG                                  */
#define INT_SLCDC       38      /* Smart Liquid Crystal Display Controller  */
#define INT_LCDC        39      /* Liquid Crystal Display Controller        */
#define INT_UART5       40      /* UART 5                                   */
#define INT_PWM3        41      /* Pulse Width Modulator(PWM) 3             */
#define INT_PWM4        42      /* Pulse Width Modulator(PWM) 4             */
#define INT_CAN1        43      /* Controller Area Network 1                */
#define INT_CAN2        44      /* Controller Area Network 2                */
#define INT_UART1       45      /* UART1                                    */
#define INT_TSC         46      /* Touch Screen Controller                  */
                                /* 47 : Reserved                            */
#define INT_ECT         48      /* Embedded Cross Trigger                   */
#define INT_SCCSCM      49      /* SCM Interrupt                            */
#define INT_SCCSMN      50      /* SMN Interrupt                            */
#define INT_GPIO2       51      /* General Purpose I/O 2                    */
#define INT_GPIO1       52      /* General Purpose I/O 1                    */
#define INT_GPT2        53      /* General Purpose Timer 2                  */
#define INT_GPT1        54      /* General Purpose Timer 1                  */
#define INT_WDOG        55      /* Watchdog(WDOG)                           */
#define INT_SECVIO      56      /* Security violation interrupt             */
#define INT_FEC         57      /* Fast Ethernet Controller                 */
#define INT_EXTINT5     58      /* External (Power Management)              */
#define INT_EXTINT4     59      /* External (Temper)                        */
#define INT_EXTINT3     60      /* External (Sensor)                        */
#define INT_EXTINT2     61      /* External (Sensor)                        */
#define INT_EXTINT1     62      /* External (WDOG)                          */
#define INT_EXTINT0     63      /* External (TV)                            */

#ifdef __cplusplus
}
#endif
#endif /* _MCIMX31_H_ */
