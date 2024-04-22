/****************************************************************************
 * main.c
 *
 *   Bruno Mendes da Silva
 *   brunomendestk@ufu.br
 *   11921EAU016
 *
 *   Direitos autorais (C) 2024 Bruno Mendes da Silva.
 *   Todos os direitos reservados.
 *   Autores: Bruno Mendes da Silva <brunomendestk@ufu.br>
 *
 ****************************************************************************/

/****************************************************************************
 * Arquivos Incluídos
 ****************************************************************************/

#include <stdint.h>
#include <stdlib.h>

/****************************************************************************
 * Definições do Pré-processador
 ****************************************************************************/

/* Endereços Base AHB1 ******************************************************/

#define STM32_RCC_BASE       0x40023800     /* 0x40023800-0x40023bff: Reset and Clock control RCC */

/* Endereços Base GPIO ******************************************************/

#define STM32_GPIOC_BASE     0x40020800     /* 0x48000800- 0x48000bff: GPIO Port C */
#define STM32_GPIOA_BASE     0x40020000     /* 0x40020000- 0x400203ff: GPIO Port A */

/* Deslocamentos dos Registradores ******************************************/

#define STM32_RCC_AHB1ENR_OFFSET  0x0030   /* Registro de habilitação do clock do Periférico AHB1 */

#define STM32_GPIO_MODER_OFFSET   0x0000  /* Registro de modo do porto GPIO */
#define STM32_GPIO_OTYPER_OFFSET  0x0004  /* Registro de tipo de saída do porto GPIO */
#define STM32_GPIO_PUPDR_OFFSET   0x000c  /* Registro de pull-up/pull-down do porto GPIO */
#define STM32_GPIO_ODR_OFFSET     0x0014  /* Registro de dados de saída do porto GPIO */
#define STM32_GPIO_BSRR_OFFSET    0x0018  /* Registro de set/reset de bits do porto GPIO */

/* Endereços dos Registradores **********************************************/

#define STM32_RCC_AHB1ENR        (STM32_RCC_BASE + STM32_RCC_AHB1ENR_OFFSET)

#define STM32_GPIOC_MODER        (STM32_GPIOC_BASE + STM32_GPIO_MODER_OFFSET)
#define STM32_GPIOC_OTYPER       (STM32_GPIOC_BASE + STM32_GPIO_OTYPER_OFFSET)
#define STM32_GPIOC_PUPDR        (STM32_GPIOC_BASE + STM32_GPIO_PUPDR_OFFSET)
#define STM32_GPIOC_ODR          (STM32_GPIOC_BASE + STM32_GPIO_ODR_OFFSET)
#define STM32_GPIOC_BSRR         (STM32_GPIOC_BASE + STM32_GPIO_BSRR_OFFSET)

#define STM32_GPIOA_MODER        (STM32_GPIOA_BASE + STM32_GPIO_MODER_OFFSET)
#define STM32_GPIOA_OTYPER       (STM32_GPIOA_BASE + STM32_GPIO_OTYPER_OFFSET)
#define STM32_GPIOA_PUPDR        (STM32_GPIOA_BASE + STM32_GPIO_PUPDR_OFFSET)
#define STM32_GPIOA_ODR          (STM32_GPIOA_BASE + STM32_GPIO_ODR_OFFSET)
#define STM32_GPIOA_BSRR         (STM32_GPIOA_BASE + STM32_GPIO_BSRR_OFFSET)

/* Registro de Habilitação de Clock AHB1 */

#define RCC_AHB1ENR_GPIOCEN      (1 << 2)  /* Bit 2: Habilita clock do porto C */

#define RCC_AHB1ENR_GPIOAEN      (1 << 2)  /* Bit 2: Habilita clock do porto A */

/* Registro de Modo do Porto GPIO */

#define GPIO_MODER_INPUT           (0) /* Entrada */
#define GPIO_MODER_OUTPUT          (1) /* Modo de saída geral */
#define GPIO_MODER_ALT             (2) /* Modo alternativo */
#define GPIO_MODER_ANALOG          (3) /* Modo analógico */

#define GPIO_MODER_SHIFT(n)        (n << 1)
#define GPIO_MODER_MASK(n)         (3 << GPIO_MODER_SHIFT(n))

/* Registro de Tipo de Saída do Porto GPIO */

#define GPIO_OTYPER_PP             (0) /* 0=Saída push-pull */
#define GPIO_OTYPER_OD             (1) /* 1=Saída open-drain */

#define GPIO_OT_SHIFT(n)           (n)
#define GPIO_OT_MASK(n)            (1 << GPIO_OT_SHIFT(n))

/* Registro de Pull-up/Pull-down do Porto GPIO */

#define GPIO_PUPDR_NONE            (0) /* Sem pull-up, pull-down */
#define GPIO_PUPDR_PULLUP          (1) /* Pull-up */
#define GPIO_PUPDR_PULLDOWN        (2) /* Pull-down */

#define GPIO_PUPDR_SHIFT(n)        (n << 1)
#define GPIO_PUPDR_MASK(n)         (3 << GPIO_PUPDR_SHIFT(n))

/* Registro de Set/Reset de Bits do Porto GPIO */

#define GPIO_BSRR_SET(n)           (1 << (n))
#define GPIO_BSRR_RESET(n)         (1 << ((n) + 16))

/* Configuração ************************************************************/

#define LED_DELAY  100000

/****************************************************************************
 * Tipos Privados
 ****************************************************************************/

/****************************************************************************
 * Protótipos de Funções Privadas
 ****************************************************************************/

/****************************************************************************
 * Dados Privados
 ****************************************************************************/

 /****************************************************************************
 * Funções Privadas
 ****************************************************************************/

/****************************************************************************
 * Funções Públicas
 ****************************************************************************/

int main(int argc, char *argv[])
{
    uint32_t reg;

    /* Ponteiros para registradores */

    uint32_t *pRCC_AHB1ENR  = (uint32_t *)STM32_RCC_AHB1ENR;
    uint32_t *pGPIOC_MODER  = (uint32_t *)STM32_GPIOC_MODER;
    uint32_t *pGPIOC_OTYPER = (uint32_t *)STM32_GPIOC_OTYPER;
    uint32_t *pGPIOC_PUPDR  = (uint32_t *)STM32_GPIOC_PUPDR;
    uint32_t *pGPIOC_BSRR   = (uint32_t *)STM32_GPIOC_BSRR;

    uint32_t *pGPIOA_MODER  = (uint32_t *)STM32_GPIOA_MODER;
    uint32_t *pGPIOA_OTYPER = (uint32_t *)STM32_GPIOA_OTYPER;
    uint32_t *pGPIOA_PUPDR  = (uint32_t *)STM32_GPIOA_PUPDR;
    uint32_t *pGPIOA_BSRR   = (uint32_t *)STM32_GPIOA_BSRR;

    /* Habilita clock GPIOC */

    reg  = *pRCC_AHB1ENR;
    reg |= RCC_AHB1ENR_GPIOCEN;
    *pRCC_AHB1ENR = reg;

    reg  = *pRCC_AHB1ENR;
    reg |= RCC_AHB1ENR_GPIOAEN;
    *pRCC_AHB1ENR = reg;

    /* Configura PC13 como saída pull-up off e pull-down off */

    reg = *pGPIOC_MODER;
    reg &= ~GPIO_MODER_MASK(13);
    reg |= (GPIO_MODER_OUTPUT << GPIO_MODER_SHIFT(13));
    *pGPIOC_MODER = reg;

    reg = *pGPIOC_OTYPER;
    reg &= ~GPIO_OT_MASK(13);
    reg |= (GPIO_OTYPER_PP << GPIO_OT_SHIFT(13));
    *pGPIOC_OTYPER = reg;

    reg = *pGPIOC_PUPDR;
    reg &= ~GPIO_PUPDR_MASK(13);
    reg |= (GPIO_PUPDR_NONE << GPIO_PUPDR_SHIFT(13));
    *pGPIOC_PUPDR = reg;

    /* Configura PA0 como entrada pull-up off e pull-down off */

    reg = *pGPIOA_MODER;
    reg &= ~GPIO_MODER_MASK(0);
    reg |= (GPIO_MODER_INPUT << GPIO_MODER_SHIFT(0));
    *pGPIOA_MODER = reg;

    reg = *pGPIOA_OTYPER;
    reg &= ~GPIO_OT_MASK(0);
    reg |= (GPIO_OTYPER_OD << GPIO_OT_SHIFT(0));
    *pGPIOA_OTYPER = reg;

    reg = *pGPIOA_PUPDR;
    reg &= ~GPIO_PUPDR_MASK(0);
    reg |= (GPIO_PUPDR_NONE << GPIO_PUPDR_SHIFT(0));
    *pGPIOA_PUPDR = reg;

    static int state = 0; // Estado inicial do LED
    *pGPIOC_BSRR = GPIO_BSRR_SET(13); // Apaga o LED inicialmente

    while(1)
    {
        if (*pGPIOA_BSRR == 1) // Se o botão está pressionado
        {
            if (state == 0) // Se o LED está apagado
            {
                state = 1;
                *pGPIOC_BSRR = GPIO_BSRR_RESET(13); // Acende o LED
            }
            else // Se o LED está aceso
            {
                state = 0;
                *pGPIOC_BSRR = GPIO_BSRR_SET(13); // Apaga o LED
            }
            for (int i = 0; i < LED_DELAY; i++)
            {
                // Atraso para estabilização do botão
            }
        }
    }

    /* Nunca deveria chegar aqui */

    return EXIT_FAILURE;
}
