#include <stdint.h>

#define RCC_BASE 0x40021000 //memory address of rcc, add values to get other rcc registers
#define RCC_AHBENR_REGISTER (*(volatile uint32_t *) (RCC_BASE + 0x14)) //adress offset has value of 0x14
#define RCC_AHBENR_GPIOEEN (1 << 21) //21st bit

//address of gpioe
#define GPIOE_BASE (0x48001000)

typedef struct {
    volatile uint32_t MODER;
    volatile uint32_t DUMMY[5]; //4 registers before odr and ion need them so jus keep it like this
    volatile uint32_t ODR;
} GPIO_TypeDef;
#define OD_R_OFFSET				(0x14UL)
#define GPIOE_OD_R				(* (volatile unsigned int *) (GPIOE_BASE + OD_R_OFFSET))

#define GPIOE ((GPIO_TypeDef*) GPIOE_BASE)

void delay(void) {
    for (uint32_t i = 0; i < 400000; ++i) {
            __asm__ volatile("nop");
    }
}

int main(void) {
    RCC_AHBENR_REGISTER |= RCC_AHBENR_GPIOEEN; //set 21st bit to 1, ie enable gpio port e
    //set pin 9 to output
    GPIOE->MODER |= (1 << 18);
    GPIOE->MODER &= ~(1 << 19);

    while (1) {
        //toggle the bit
    	GPIOE_OD_R ^= (1U << 9);
		delay();
    }
}
