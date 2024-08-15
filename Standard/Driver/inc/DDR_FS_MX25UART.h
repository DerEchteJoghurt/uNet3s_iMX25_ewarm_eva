/************************************************************************
    Micro C Cube Standard, DEVICE DRIVER
    Serial Interface for i.MX25, UART

    Copyright (c)  2010, eForce Co.,Ltd.  All rights reserved.

    Version Information  2010.10.21: Created.
 ************************************************************************/


typedef union t_mx25uart_msts {
    UH      word;
    struct {
        UH      init_flg:1;
        UH      ena_tx:1;
        UH      ena_rx:1;
        UH      sft_flw:1;
        UH      hrd_flw:1;
        UH      sns_brk:1;
        UH      tx_xoff:1;
        UH      rx_xoff:1;
        UH      req_xon_xoff:1;
        UH      er_buf_ovr:1;
        UH      dummy:6;
    } bit;
} T_MX25UART_MSTS;

typedef struct t_scif_mng {
    T_MX25UART_MSTS status;
    UH              flgid;
    UH              sndp;
    UH              rcvp;
    UH              tcnt;
    UH              rcnt;
    UH              tsize;
    UH              rsize;
    UH              tlockid;
    UH              rlockid;
    UH              xoff_size;
    UH              xon_size;
    UH              isrid;
    UH              intno;
    UH              wclnid;
    FP              devhdr;
    volatile struct t_uart *port;
    T_COM_SND       *SndData;
    T_COM_RCV       *RcvData;
    VB              *tbuf;
    VB              *rbuf;
    UB              *sbuf;
    UH              aux[2];
} T_MX25UART_MNG;

#define TXI_FLG     0x00000001
#define RXI_FLG     0x00000002
#define TEI_FLG     0x00000004

/* Bit definitions for UART receiver register (upper-byte)                              */

#define URXD_CHARRDY    0x80        /* Character Ready                                  */
#define URXD_ERR        0x40        /* Error Detect                                     */
#define URXD_OVERRUN    0x20        /* Receiver Overrun                                 */
#define URXD_FRMERR     0x10        /* Frame Error                                      */
#define URXD_BRK        0x08        /* BREAK Detect                                     */
#define URXD_PRERR      0x04        /* Parity Error                                     */

/* Bit definitions for UART Control Register 1                                          */

#define UCR1_ADEN       0x8000      /* Automatic Baud Rate Detection Interrupt Enable   */
#define UCR1_ADBR       0x4000      /* Automatic Detection of Baud Rate                 */
#define UCR1_TRDYEN     0x2000      /* Transmitter Ready Interrupt Enable               */
#define UCR1_IDEN       0x1000      /* Idle Condition Detected Interrupt Enable         */
#define UCR1_ICD4       0x0000      /* Idle Condition Detect if Idle for more than 4 frames     */
#define UCR1_ICD8       0x0400      /* Idle Condition Detect if Idle for more than 8 frames     */
#define UCR1_ICD16      0x0800      /* Idle Condition Detect if Idle for more than 16 frames    */
#define UCR1_ICD32      0x0C00      /* Idle Condition Detect if Idle for more than 32 frames    */
#define UCR1_RRDYEN     0x0200      /* Receiver Ready Interrupt Enable                  */
#define UCR1_RDMAEN     0x0100      /* Receiver Ready DMA Enable                        */
#define UCR1_IREN       0x0080      /* Infrared Interface Enable                        */
#define UCR1_TXMPTYEN   0x0040      /* Transmitter Empty Interrupt Enable               */
#define UCR1_RTSDEN     0x0020      /* RTS Delta Interrupt Enable                       */
#define UCR1_SNDBRK     0x0010      /* Send Break                                       */
#define UCR1_TDMAEN     0x0008      /* Transmitter Ready DMA Enable                     */
#define UCR1_UARTEN     0x0001      /* UART Enable                                      */

/* Bit definitions for UART Control Register 2                                          */

#define UCR2_ESCI       0x8000      /* Escape Sequence Interrupt Enable                 */
#define UCR2_IRTS       0x4000      /* Ignore RTS Pin                                   */
#define UCR2_CTSC       0x2000      /* CTS Pin Control                                  */
#define UCR2_CTS        0x1000      /* Clear to Send                                    */
#define UCR2_ESCEN      0x0800      /* Escape Enable                                    */
#define UCR2_RTEC_ANY   0x0400      /* Request to Send Edge Control on any edge         */
#define UCR2_RTEC_FALL  0x0200      /* Request to Send Edge Control on a falling edge   */
#define UCR2_RTEC_RISE  0x0000      /* Request to Send Edge Control on a rising edge    */
#define UCR2_PREN       0x0100      /* Parity Enable                                    */
#define UCR2_PROE       0x0080      /* Parity Even(0)/Odd(1)                            */
#define UCR2_STPB       0x0040      /* Stop 1-bit(0)/2-bits(1)                          */
#define UCR2_WS         0x0020      /* Word Size 7-bits(0)/8-bits(1)                    */
#define UCR2_RTSEN      0x0010      /* Request to Send Interrupt Enable                 */
#define UCR2_ATEN       0x0008      /* Aging Timer Enable                               */
#define UCR2_TXEN       0x0004      /* Transmitter Enable                               */
#define UCR2_RXEN       0x0002      /* Receiver Enable                                  */
#define UCR2_SRST       0x0001      /* Software Reset (active low)                      */

/* Bit definitions for UART Control Register 3                                          */

#define UCR3_DPEC_EITH  0x8000      /* DTR Interrupt Edge Control on either edge        */
#define UCR3_DPEC_FALL  0x4000      /* DTR Interrupt Edge Control on a falling edge     */
#define UCR3_DPEC_RISE  0x0000      /* DTR Interrupt Edge Control on a rising edge      */
#define UCR3_DTREN      0x2000      /* Data Terminal Ready Interrupt Enable             */
#define UCR3_PARERREN   0x1000      /* Parity Error Interrupt Enable                    */
#define UCR3_FRAERREN   0x0800      /* Frame Error Interrupt Enable                     */
#define UCR3_DSR        0x0400      /* Data Set Ready                                   */
#define UCR3_DCD        0x0200      /* Data Carrier Detect (only DCE mode)              */
#define UCR3_RI         0x0100      /* Ring Indicator (only DCE mode)                   */
#define UCR3_ADNIMP     0x0080      /* Autobaud Detection Not Improved                  */
#define UCR3_RXDSEN     0x0040      /* Receive Status Interrupt Enable                  */
#define UCR3_AIRINTEN   0x0020      /* Asynchronous IR WAKE Interrupt Enable            */
#define UCR3_AWAKEN     0x0010      /* Asynchronous WAKE Interrupt Enable               */
#define UCR3_RXDMUXSEL  0x0004      /* RXD Muxed Input Selected                         */
#define UCR3_INVT       0x0002      /* Inverted Infrared transmission                   */
#define UCR3_ACIEN      0x0001      /* Autobaud Counter Interrupt Enable                */

/* Bit definitions for UART Control Register 4                                          */

#define UCR4_INVR       0x0200      /* Inverted Infrared Reception                      */
#define UCR4_ENIRI      0x0100      /* Serial Infrared Interrupt Enable                 */
#define UCR4_WKEN       0x0080      /* WAKE Interrupt Enable                            */
#define UCR4_IRSC       0x0020      /* IR Special Case                                  */
#define UCR4_LPBYP      0x0010      /* Low Power Bypass                                 */
#define UCR4_TCEN       0x0008      /* Transmit Complete Interrupt Enable               */
#define UCR4_BKEN       0x0004      /* BREAK Condition Detected Interrupt Enable        */
#define UCR4_OREN       0x0002      /* Receiver Overrun Interrupt Enable                */
#define UCR4_DREN       0x0001      /* Receiver Data Ready Interrupt Enable             */

/* Bit definitions for UART Status Register 1                                           */

#define USR1_PARITYERR  0x8000      /* Parity Error Interrupt Flag                      */
#define USR1_RTSS       0x4000      /* RTS Pin Status                                   */
#define USR1_TRDY       0x2000      /* Transmitter Ready Interrupt/DMA Flag             */
#define USR1_RTSD       0x1000      /* RTS Delta                                        */
#define USR1_ESCF       0x0800      /* Escape Sequence Interrupt Flag                   */
#define USR1_FRAMERR    0x0400      /* Frame Error Interrupt Flag                       */
#define USR1_RRDY       0x0200      /* Receiver Ready Interrupt/DMA Flag                */
#define USR1_AGTIM      0x0100      /* Ageing Timer Interrupt Flag                      */
#define USR1_RXDS       0x0040      /* Receiver IDLE Interrupt Flag                     */
#define USR1_AIRINT     0x0020      /* Asynchronous IR WAKE Interrupt Flag              */
#define USR1_AWAKE      0x0010      /* Asynchronous WAKE Interrupt Flag                 */

/* Bit definitions for UART Status Register 2                                           */

#define USR2_ADET       0x8000      /* Automatic Baud Rate Detect complete              */
#define USR2_TXFE       0x4000      /* Transmit Buffer FIFO Empty                       */
#define USR2_DTRF       0x2000      /* DTR edge triggered interrupt Flag                */
#define USR2_IDLE       0x1000      /* Idle Condition                                   */
#define USR2_ACST       0x0800      /* Autobaud Counter Stopped                         */
#define USR2_RIDELT     0x0400      /* Ring Indicator Delta                             */
#define USR2_RIIN       0x0200      /* Ring Indicator Input                             */
#define USR2_IRINT      0x0100      /* Serial Infrared Interrupt Flag                   */
#define USR2_WAKE       0x0080      /* WAKE                                             */
#define USR2_DCDDELT    0x0040      /* Data Carrier Detect Delta                        */
#define USR2_DCDIN      0x0020      /* Data Carrier Detect Input                        */
#define USR2_RTSF       0x0010      /* RTS Edge Triggered Interrupt Flag                */
#define USR2_TXDC       0x0008      /* Transmitter Complete                             */
#define USR2_BRCD       0x0004      /* BREAK Condition Detected                         */
#define USR2_ORE        0x0002      /* Overrun Error                                    */
#define USR2_RDR        0x0001      /* Receive Data Ready                               */

/* Bit definitions for UART Test Register                                               */

#define UTS_FRCPERR     0x2000      /* Force Parity Error                               */
#define UTS_LOOP        0x1000      /* Loop Tx and Rx for Test                          */
#define UTS_DBGEN       0x0800      /* Debug Enable                                     */
#define UTS_LOOPIR      0x0400      /* Loop TX and RX for IR Test                       */
#define UTS_RXDBG       0x0100      /* RXFIFO Debug Mode                                */
#define UTS_TXEMPTY     0x0040      /* Tx FIFO Empty                                    */
#define UTS_RXEMPTY     0x0020      /* Rx FIFO Empty                                    */
#define UTS_TXFULL      0x0010      /* Tx FIFO Full                                     */
#define UTS_RXFULL      0x0008      /* Rx FIFO Full                                     */
#define UTS_SOFTRST     0x0001      /* Software Reset                                   */

ER _ddr_fs_mx25uart_init(ID, volatile struct t_uart *);
