;***************************************************************************
; Å@MMU configuration table for Armadillo-440 Platform (CPU: i.MX257)
;
; Å@ Copyright (c)  2010, eForce Co., Ltd. All rights reserved.
;
;
;       ATR_RO .... Read Only (Read/Write by privilege mode)
;       ATR_RW .... Read/Write
;       ATR_NA .... No access
;       ATR_CE .... Cache enable
;       ATR_CD .... Cache disable
;       ATR_BE .... Buffer enable
;       ATR_BD .... Buffer disable
;
;       ATR = {ATR_RO|ATR_RW|ATR_NA} + {ATR_CE|ATR_CD} + {ATR_BE|ATR_BD}
;
;***************************************************************************/

        EXTERN  _PRST

        ALIGNROM 2
        DATA

mmu_cfgtbl
;       DCD     SIZE,       PADDR,      VADDR,      ATR
        DCD     0x00001000, _PRST,      0x00000000, ATR_RO+ATR_CE+ATR_BD ; Boot (SDRAM image)
        DCD     0x00100000, 0x43F00000, 0x43F00000, ATR_RW+ATR_CD+ATR_BD ; Internal peripheral
        DCD     0x02000000, 0x50000000, 0x50000000, ATR_RW+ATR_CD+ATR_BD ; Internal peripheral
        DCD     0x00100000, 0x53F00000, 0x53F00000, ATR_RW+ATR_CD+ATR_BD ; Internal peripheral
        DCD     0x00100000, 0x68000000, 0x68000000, ATR_RW+ATR_CD+ATR_BD ; Internal peripheral
        DCD     0x00020000, 0x78000000, 0x78000000, ATR_RW+ATR_CE+ATR_BE ; Internal SRAM
        DCD     0x07800000, 0x80000000, 0x80000000, ATR_RW+ATR_CE+ATR_BE ; Program (SDRAM)
        DCD     0x00700000, 0x87800000, 0x87800000, ATR_RW+ATR_CD+ATR_BD ; No cache data (SDRAM)
        DCD     0x00100000, 0x87F00000, 0x87F00000, ATR_RO+ATR_CD+ATR_BD ; TTLB
        DCD     0x02000000, 0xA0000000, 0xA0000000, ATR_RW+ATR_CD+ATR_BD ; Flash memory
        DCD     0x00000000, 0x00000000, 0x00000000, 0

mmu_ttb
        DCD     0x87F00000

