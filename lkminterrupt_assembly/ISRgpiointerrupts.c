#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#include <linux/irq.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/init.h>


#include "ISRgpiointerrupts.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Franzò Damiano, Borzacchi Marco, Alisa Arakelyan");
MODULE_DESCRIPTION("It raise up pin 12 when pin 7 is up");
MODULE_VERSION("1.0");

static bool off=false;
static int irq_n;


static irqreturn_t ISRrising(unsigned int irq, void* dev_id,struct pt_regs *regs) {
  asm(
      "mov	r0, #12\n\t"
      "bl	gpio_to_desc\n\t"
      "mov	r1, #1\n\t"
      "bl	gpiod_set_raw_value\n\t"
      );

  udelay(DELAY_TIME);

  asm(
      "mov	r0, #12\n\t"
      "bl	gpio_to_desc\n\t"
      "mov	r1, #0\n\t"
      "bl	gpiod_set_raw_value\n\t"
      );
  return IRQ_HANDLED;
}

// it's called only when the module is loaded in the kernel, then the kernel module is initialized
int static ISRgpiointerrupt_init(void){
  if(!gpio_is_valid(OUTPUT_GPIO) || !gpio_is_valid(INPUT_GPIO)){
    return -ENODEV;
  }
  //it's checked if the OUTPUT_GPIO and INPUT_GPIO are valid

  if(DELAY_TIME <= 0){
    return -EBADF;
  }
  //it's checked if the delay time is a positive value
  

  gpio_request(OUTPUT_GPIO,"output_signal");
  //GPIO associated to the number of OUTPUT_GPIO is requested by the kernel, then label is associated to the request
  gpio_direction_output(OUTPUT_GPIO,off);
  //GPIO core is informed that the OUTPUT_GPIO pin will be used as output, and has to be off.
  
  gpio_request(INPUT_GPIO,"interrupt_input");
  //GPIO associated to the number of OUTPUT_GPIO is requested by the kernel
  gpio_direction_input(INPUT_GPIO);
  //GPIO core is informed that the OUTPUT_GPIO pin will be used as input

  
  irq_n=gpio_to_irq(INPUT_GPIO);
  //GPIO associated to INPUT_GPIO is mapped to a IRQ number
  if(irq_n < 0){
    printk(KERN_ERR "GPIO: Failed to map GPIO %d into IRQ numbers\nError number: %d\n",INPUT_GPIO,irq_n);
  }
  
  if (request_irq(irq_n,(irq_handler_t)ISRrising,IRQF_TRIGGER_RISING | IRQF_ONESHOT,"gpiointerrupts",NULL)){
      printk(KERN_ERR "GPIO: problem with the incoming request %d\n",irq_n);
      return -ESRCH;//to be riew ---------> doc
    }
  //Interrupt line associated to the IRQ is enabled, then the handler functions will be invoked when the conditions are verified
  //The flag IRQF_TRIGGER_RISING indicates that the ISR has to be called when the voltage in the GPIO associated to INPUT_GPIO rises
  //The flag IRQ_ONESHOT indicates that the ISR has to be called only one time at times

  printk(KERN_INFO "Module Initialized");
  return 0;
}

void static ISRgpiointerrupt_exit(void){
  free_irq(irq_n,NULL);
  //the interrupt handler is removed
  gpio_free(OUTPUT_GPIO);
  //the GPIO associated to OUTPUT_GPIO is released
  gpio_free(INPUT_GPIO);
  //the GPIO associated to INPUT_GPIO is released
  printk(KERN_INFO "Goodbye from Alisa, Damiano and Marco\n");
  return;
}

module_init(ISRgpiointerrupt_init);
//it's specified what function has to be called when the module it's initialized
module_exit(ISRgpiointerrupt_exit);
//it's specified what function has to be called when the module it's removed
