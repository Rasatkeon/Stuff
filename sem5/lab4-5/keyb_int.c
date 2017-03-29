#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>

/* We want an interrupt */
#include <linux/interrupt.h>
#include <asm/io.h>

MODULE_LICENSE("GPL");

/* Printing scancode and key status
 */
static void got_char(unsigned char scancode)
{
	printk("Scan Code %x %s.\n",
		   (int) scancode & 0x7F,
		   scancode & 0x80 ? "Released" : "Pressed");
}

/* This function services keyboard interrupts. It reads the relevant
 * information from the keyboard and then scheduales the bottom half
 * to run when the kernel considers it safe.
 */
irqreturn_t irq_handler(int irq, void *dev_id, struct pt_regs *regs)
{
	unsigned char scancode;

	/* Read scancode */
	scancode = inb(0x60);

	got_char(scancode);

	return IRQ_HANDLED;
}

/* Initialize the module - register the IRQ handler */
static int __init InterruptScancode_init(void)
{
	printk(KERN_INFO "Init custom keyboard interrupt handler\n");

	int result;

	/* Request IRQ 1, the keyboard IRQ */    
	result = request_irq(1,
						 (irq_handler_t) irq_handler,
						 IRQF_SHARED,
						 "keyboard_stats_irq",
						 (void *)(irq_handler));

	if (result)
		printk(KERN_INFO "can't get shared interrupt for keyboard\n");

	return result;
}

/* Cleanup */
static void __exit InterruptScancode_exit(void)
{
	printk(KERN_INFO "Exit custom keyboard interrupt handler\n");
	/* Shared interrupt, so no passing NULL */
	free_irq(1, (void *)(irq_handler));
}

module_init(InterruptScancode_init);
module_exit(InterruptScancode_exit);
