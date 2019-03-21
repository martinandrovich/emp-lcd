#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "driver.h"
#include "tp.h"
#include "btn.h"
#include "led.h"
#include "ledctrl.h"
#include "lcd.h"

/*****************************    Defines    *******************************/

#define LAMBDA(c_) ({ c_ _; })

/*****************************   Constants   *******************************/

#define SYSTICK_DUR_MS 1

/*****************************   Variables   *******************************/

/************************    External Methods    ***************************/

/************************   Interrupt Handlers   ***************************/

void ISR_SYSTICK(void)
{
	tp.systick();
}

/*******************************   Main   **********************************/

int main(void)
{

	// disable interrupts
	__disable_irq();

	// init SYSTICK
	tp.init_systick(SYSTICK_DUR_MS, ms);
	sys_tick_init(SYSTICK_DUR_MS);

	// enable interrupts
	__enable_irq();


	// init BUTTON instance (SW1)
	BUTTON* btn_sw1 = btn.new(SW1);

	// set single press callback
	btn.set_callback(btn_sw1, SINGLE_PRESS, LAMBDA(void _(void)
		{
			//ledctrl.set_mode(ctrl1, NORWEGIAN);
	        lcd.init();

		}
	));

	// set double press callback
	btn.set_callback(btn_sw1, DOUBLE_PRESS, LAMBDA(void _(void)
		{
			//ledctrl.set_mode(ctrl1, EMERGENCY);
	        lcd.write_char('H', 0, 0);
		}
	 ));

	const uint8_t buf[32] = "HelloWorld";

	// set long press callback
	btn.set_callback(btn_sw1, LONG_PRESS, LAMBDA(void _(void)
		{
			//ledctrl.set_mode(ctrl1, NORMAL);
	        lcd.write_string(buf, 0, 12, 1, 1);
		}
	));

	// super-loop
	for(;;)
	{
	    btn.controller(btn_sw1);
	}

	return 0;
}
