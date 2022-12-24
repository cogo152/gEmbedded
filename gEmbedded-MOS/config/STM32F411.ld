ENTRY (Reset_Handler)

MEMORY
{
    ROM(rx)     :ORIGIN =0x08000000,LENGTH =512K
    SRAM(rwx)   :ORIGIN =0x20000000,LENGTH =128K
}

SECTIONS
{
    .ROM :
    {
        *(.vector_table)
        *(.text)
            *(.text.*)
        *(.rodata)
            *(.rodata.*)
        . = ALIGN(0x4);
        _eROM = .;
    }> ROM AT> ROM

    .ROMTOSRAM :
    {
        _bROMtoSRAM = .;
        *(.data)
            *(.data.*)
        . = ALIGN(0x4);
        _eROMtoSRAM = .;
    }> SRAM AT> ROM

    .SRAM :
    {
        _bSRAM = .;
        *(COMMON)
        *(.bss)
            *(.bss.*)
        . = ALIGN(0x4);
        _eSRAM = .;
    }> SRAM AT> SRAM
}