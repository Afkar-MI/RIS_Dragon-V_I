#include <msp430.h>
#include "driverlib.h"
#include "spi_recv.h"
#include "pin_config.h"


void spi_init(void);
void pins_config(void);
void set_pins(void);


int main(void)
{
	pins_config();
	spi_init();

	while(1){

	    if (flag_spi_recv == 1){

	        set_pins();  // Assigns values to pins output

	    }


	    flag_spi_recv = 0;
	}


}
