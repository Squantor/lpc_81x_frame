#include <chip.h>
#include "main.h"
#include "board.h"

volatile uint32_t msTicks = 0;

void SysTick_Handler(void) {
	msTicks++;
}

void delay_ms(uint32_t ms) {
	uint32_t now = msTicks;
	while ((msTicks-now) < ms);
}

int main(void)
{
    char buf[] = "Hello World\n\r";
	SystemCoreClockUpdate();

	SysTick_Config(SystemCoreClock / 1000);

	// Enable the clock to the SWM
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_SWM);
    /* Connect the U0_TXD_O and U0_RXD_I signals to port pins(P0.4, P0.0) */
	Chip_SWM_DisableFixedPin(SWM_FIXED_ACMP_I1);
	Chip_SWM_MovablePinAssign(SWM_U0_TXD_O, UART_TX_PIN);
	Chip_SWM_MovablePinAssign(SWM_U0_RXD_I, UART_RX_PIN);
	// Disable the clock to the SWM
	Chip_Clock_DisablePeriphClock(SYSCTL_CLOCK_SWM);

    // GPIO inits
	Chip_GPIO_Init(LPC_GPIO_PORT);
	LPC_GPIO_PORT->DIR[LED_RED_PORT] |= (1<<LED_RED_PIN)|(1<<LED_GRN_PIN)|(1<<LED_BLU_PIN);

	// UART inits
	Chip_Clock_SetUARTClockDiv(1);
    Chip_UART_Init(LPC_USART0);
	Chip_UART_ConfigData(LPC_USART0, UART_CFG_DATALEN_8 | UART_CFG_PARITY_NONE | UART_CFG_STOPLEN_1);
	Chip_Clock_SetUSARTNBaseClockRate((115200 * 16), true);
	Chip_UART_SetBaud(LPC_USART0, 115200);
	Chip_UART_Enable(LPC_USART0);
	Chip_UART_TXEnable(LPC_USART0);

	while (1)
	{
        Chip_UART_SendBlocking(LPC_USART0, buf, sizeof(buf));
		LPC_GPIO_PORT->CLR[LED_RED_PORT] = 1<<LED_RED_PIN;
		LPC_GPIO_PORT->SET[LED_RED_PORT] = 1<<LED_GRN_PIN;
		delay_ms(1000);
		LPC_GPIO_PORT->SET[LED_RED_PORT] = 1<<LED_BLU_PIN;
		LPC_GPIO_PORT->CLR[LED_RED_PORT] = 1<<LED_GRN_PIN;
		delay_ms(1000);
		LPC_GPIO_PORT->SET[LED_RED_PORT] = 1<<LED_RED_PIN;
		LPC_GPIO_PORT->CLR[LED_RED_PORT] = 1<<LED_BLU_PIN;
		delay_ms(1000);
	}

}

