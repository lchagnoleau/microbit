#include <stdint.h>
#include <ARMCM4.h>
#include <core_cm4.h>

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#endif

extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t __bss_start__;
extern uint32_t __bss_end__;
extern uint32_t __stack;
extern uint32_t _stack_size;
extern void __libc_init_array(void);
extern int main(void);

__NO_RETURN __attribute__((naked)) void default_IRQHandler(void)
{
    __ASM("b .");
}

__NO_RETURN void NMI_Handler(void) __attribute__((weak, alias("default_IRQHandler")));
__NO_RETURN void HardFault_Handler(void) __attribute__((weak));
__NO_RETURN void Reset_Handler(void);

typedef void (*VECTOR_TABLE_Type)(void);

const VECTOR_TABLE_Type __VECTOR_TABLE[] __attribute__((used, section(".isr_vector"))) = {
    (VECTOR_TABLE_Type)(&__stack), Reset_Handler, /* Reset Handler */
    NMI_Handler, /* NMI Handler */
    HardFault_Handler, /* Hard Fault Handler */
};

__NO_RETURN __attribute__((noreturn)) void Reset_Handler(void)
{
    __disable_irq();

    __set_MSP((uint32_t)(&__stack));
    SCB->VTOR = (uint32_t)(__VECTOR_TABLE);

    /*
     * Copy data section from FLASH to RAM.
     */
    const uint32_t *src_ptr = &_etext;
    uint32_t *dst_ptr = &_sdata;
    const uint32_t *dst_end = &_edata;

    while (dst_ptr < dst_end) {
        *dst_ptr++ = *src_ptr++;
    }

    /*
     * Clear the BSS segment
     */
    dst_ptr = &__bss_start__;
    dst_end = &__bss_end__;

    while (dst_ptr < dst_end) {
        *dst_ptr++ = 0;
    }

    /*
     * Call constructors.
     */
    __libc_init_array();
    /*
     * Jump in main.
     */
    main();
    __builtin_unreachable();
}
