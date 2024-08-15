//**********************************************************************//
//      CSIDE initialization command file for Armadillo-440
//
//**********************************************************************//

{init
//  Disable WatchDog

    Outport(2, 0x53FDC000, 0x0030)
    Wait(10)

//  Setup clock distributer

    Outport(3, 0x53F80000, 0x800B2C01)  // MPLL 532MHz
    Outport(3, 0x53F80004, 0x84002800)  // UPLL 240MHz
    Outport(3, 0x53F80008, 0x2C034000)  // CCTL
    Wait(10)
    Outport(3, 0x53F80064, 0x43000000)  // PER_CLK = HCLK
    Wait(10)

//  Disable all Interrupts

    Outport(3, 0x68000004, 0x0000001F)
    Outport(3, 0x68000010, 0x00000000)
    Outport(3, 0x68000014, 0x00000000)
    Outport(3, 0x68000018, 0x00000000)
    Outport(3, 0x6800001C, 0x00000000)

//  Initializing for Flash-Memory

    Outport(3, 0xB8002000, 0x21414E85)
    Outport(3, 0xB8002004, 0x45002553)
    Outport(3, 0xB8002008, 0x00470800)

//  Initialize DDR SDRAM controller

    Outport(3, 0xB8001010, 0x00000046)  // DDR SDRAM, MA10 Enable
    Outport(3, 0xB8001004, 0x006AC73D)  // Configuration
    Outport(3, 0xB8001000, 0x80000000)  // Enable COntroller
    Wait(1)
    Outport(3, 0xB8001000, 0x90000000)  // Precharge ALL mode
    Inport(3, 0x80000400)
    Outport(3, 0xB8001000, 0xA0000000)  // Auto-Refresh mode
    Outport(3, 0x80000000, 0x00000000)  // Auto-Refresh command x2
    Outport(3, 0x80000000, 0x00000000)
    Outport(3, 0xB8001000, 0xB0000000)  // Load Mode Register
    Inport(1, 0x80000033)               // CAS=3, BL=8
    Inport(1, 0x80200000)               // Extended Mode
    Outport(3, 0xB8001000, 0x83216080)  // Normal mode
    Wait(1)

}
init
//**********************************************************************//
//  Load Debug project file now..
