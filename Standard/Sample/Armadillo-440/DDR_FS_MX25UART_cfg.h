/************************************************************************
    Serial Interface for Freescale i.MX25

     Copyright (c)  2010, eForce Co.,Ltd.  All rights reserved.

 ************************************************************************/


/* UART�`���l��2�̐ݒ�l */

#define UART_2                  /* ���g�p�̏ꍇ�̓R�����g�A�E�g         */

#define TXBUF_SZ2   1024        /* ���M�o�b�t�@�T�C�Y                   */
#define RXBUF_SZ2   1024        /* ��M�o�b�t�@�T�C�Y                   */
#define XOFF_SZ2    768         /* XOFF���o��M�o�b�t�@�f�[�^���g���K   */
#define XON_SZ2     128         /* XON���o��M�o�b�t�@�f�[�^���g���K    */
                                /* ���V�[�uFIFO�f�[�^���g���K           */
#define RXTL_2      24          /* 0�`32                                */
                                /* �g�����X�~�b�gFIFO�f�[�^���g���K     */
#define TXTL_2      8           /* 2�`32                                */
                                /* RTS�o�̓A�N�e�B�u�g���K              */
#define RTSTL_2     24          /* 0�`32                                */
                                /* �����݃��x��                         */
#define DCEDTE_2    1           /* DCE(0)/DTE(1)                        */
#define IPL_UART2   2           /* 0(Lowest)�`15(Highest)               */

