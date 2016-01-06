#include "platform.h"
#include "uart.h"
#include "printf.h"
#include "console.h"

void platform_init()
{
	uart_init();
	printf_register_uart(uart_putc);

	console_init();	
	printf_register_stdout(console_putc);
}

void platform_shutdown()
{
	
}

uint32_t* platform_get_null_devptr()
{
	return (uint32_t*)0x10000008;
}

uint32_t platform_get_null_devval()
{
	return 0xff;
}
