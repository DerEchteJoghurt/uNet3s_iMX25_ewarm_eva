/************************************************************************
    Serial Interface for Freescale i.MX25

     Copyright (c)  2010, eForce Co.,Ltd.  All rights reserved.

 ************************************************************************/


/* UARTチャネル2の設定値 */

#define UART_2                  /* 未使用の場合はコメントアウト         */

#define TXBUF_SZ2   1024        /* 送信バッファサイズ                   */
#define RXBUF_SZ2   1024        /* 受信バッファサイズ                   */
#define XOFF_SZ2    768         /* XOFF送出受信バッファデータ数トリガ   */
#define XON_SZ2     128         /* XON送出受信バッファデータ数トリガ    */
                                /* レシーブFIFOデータ数トリガ           */
#define RXTL_2      24          /* 0～32                                */
                                /* トランスミットFIFOデータ数トリガ     */
#define TXTL_2      8           /* 2～32                                */
                                /* RTS出力アクティブトリガ              */
#define RTSTL_2     24          /* 0～32                                */
                                /* 割込みレベル                         */
#define DCEDTE_2    1           /* DCE(0)/DTE(1)                        */
#define IPL_UART2   2           /* 0(Lowest)～15(Highest)               */

