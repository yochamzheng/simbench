#include "mem.h"
#include "constants.h"

static phys_mem_info_t phys_info = {
	.phys_mem_start = PHYS_MEM_START,
	.phys_mem_end   = PHYS_MEM_END,
	.next_mem = 0
};

static phys_mem_info_t device_sp810_info = {
	.phys_mem_start = 0x10000000,
	.phys_mem_end   = 0x10000fff,
	.next_mem       = 0
};

static phys_mem_info_t device_uart_info = {
	.phys_mem_start = UART0_MEM_START,
	.phys_mem_end   = UART0_MEM_END,
	.next_mem = &device_sp810_info
};

const phys_mem_info_t *mem_get_phys_info()
{
	return &phys_info;
}

const phys_mem_info_t *mem_get_device_info()
{
	return &device_uart_info;
}
