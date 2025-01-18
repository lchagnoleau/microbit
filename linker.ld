ENTRY(Reset_Handler)

MEMORY
{
    flash      (rx) : ORIGIN = 0x00000000, LENGTH = 512K
    ram       (rwx) : ORIGIN = 0x20000000, LENGTH = 128K
}

_stack_size = 0x2000;

SECTIONS
{
    .isr_vector :
    {
        KEEP(*(.isr_vector))
        . = ALIGN(4);
    } > flash

    .text :
    {
        *(.text*)
        *(.glue_7)
        *(.glue_7t)

        KEEP (*(.init))
        KEEP (*(.fini))

        . = ALIGN(4);
        _etext = . ;
    } > flash

    .rodata :
    {
        *(.rodata)
        *(.rodata*)
        . = ALIGN(4);
    } > flash

    .preinit_array :
    {
        PROVIDE_HIDDEN (__preinit_array_start = .);
        KEEP (*(.preinit_array))
        PROVIDE_HIDDEN (__preinit_array_end = .);
    } > flash

    .init_array :
    {
        PROVIDE_HIDDEN (__init_array_start = .);
        KEEP (*(.init_array*))
        PROVIDE_HIDDEN (__init_array_end = .);
    } > flash

    .fini_array :
    {
        PROVIDE_HIDDEN (__fini_array_start = .);
        KEEP (*(.fini_array*))
        PROVIDE_HIDDEN (__fini_array_end = .);
    } > flash

    .bss (NOLOAD) :
    {
        __bss_start__ = . ;
        *(.bss*);
        *(COMMON);
        __bss_end__ = . ;
    } > ram

    .data :
    {
        _sdata = . ;
        *(.data*)
        _edata = . ;
    } > ram AT > flash

    .stack (NOLOAD) :
    {
        . = ALIGN(8);
        . = . + _stack_size;
        . = ALIGN(8);
        __stack = .;
    } > ram
}
