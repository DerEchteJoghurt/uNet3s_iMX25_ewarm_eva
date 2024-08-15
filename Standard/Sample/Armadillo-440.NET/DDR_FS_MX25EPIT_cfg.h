/***********************************************************************
  　Interval Timer code for i.MX25, EPIT

  　 Copyright (c)  2010, eForce Co., Ltd. All rights reserved.

 ***********************************************************************/


/* 高周波発信器の周波数 */

#define CLKIH       24000000

/* 低周波発信器の周波数 */

#define CLKIL       32768

/* 周期タイマ割込みの優先度（0～15） */

#define IPL_EPIT 0

/* 周期タイマのチャネル番号（1～2） */

#define CH_EPIT  1

