/****************************************************************************
 * startup.c
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

/****************************************************************************
 * Definições do Pré-processador
 ****************************************************************************/

/* Layout da Memória SRAM */
#define SRAM_START      0x20000000U
#define SRAM_SIZE       (128U * 1024U)
#define SRAM_END        (SRAM_START + SRAM_SIZE)
#define STACK_START     SRAM_END

/****************************************************************************
 * Protótipos de Funções Privadas
 ****************************************************************************/

int main(void);
void reset_handler(void);
void default_handler(void);

/* Protótipos dos Manipuladores de Exceção do Sistema */
void nmi_handler(void) __attribute__((weak, alias("default_handler")));
void hardfault_handler(void) __attribute__((weak, alias("default_handler")));
void memmanage_handler(void) __attribute__((weak, alias("default_handler")));
void busfault_handler(void) __attribute__((weak, alias("default_handler")));
void usagefault_handler(void) __attribute__((weak, alias("default_handler")));
void svc_handler(void) __attribute__((weak, alias("default_handler")));
void debugmon_handler(void) __attribute__((weak, alias("default_handler")));
void pendsv_handler(void) __attribute__((weak, alias("default_handler")));
void systick_handler(void) __attribute__((weak, alias("default_handler")));

/****************************************************************************
 * Dados Externos
 ****************************************************************************/

/* Variáveis exportadas do script de ligação */
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _la_data;

extern uint32_t _sbss;
extern uint32_t _ebss;

/****************************************************************************
 * Dados Privados
 ****************************************************************************/

/* Tabela de Vetores de Interrupção */
uint32_t vectors[] __attribute__((section(".isr_vectors"))) =
{
    STACK_START,                        /* Ponteiro de pilha inicial */
    (uint32_t)reset_handler,            /* Manipulador de reset */
    (uint32_t)nmi_handler,              /* Manipulador de NMI */
    (uint32_t)hardfault_handler,        /* Manipulador de Hard Fault */
    (uint32_t)memmanage_handler,        /* Manipulador de Memory Management Fault */
    (uint32_t)busfault_handler,         /* Manipulador de Bus Fault */
    (uint32_t)usagefault_handler,       /* Manipulador de Usage Fault */
    0,                                  /* Reservado */
    0,                                  /* Reservado */
    0,                                  /* Reservado */
    0,                                  /* Reservado */
    (uint32_t)svc_handler,              /* Manipulador de SVCall */
    (uint32_t)debugmon_handler,         /* Manipulador de Debug Monitor */
    0,                                  /* Reservado */
    (uint32_t)pendsv_handler,           /* Manipulador de PendSV */
    (uint32_t)systick_handler,          /* Manipulador de SysTick */
};

/****************************************************************************
 * Funções Privadas
 ****************************************************************************/

/* Manipulador de Reset */
void reset_handler(void)
{
    uint32_t i;

    /* Copia a seção .data da FLASH para a RAM */
    uint32_t size = (uint32_t)&_edata - (uint32_t)&_sdata;
    uint8_t *pDst = (uint8_t*)&_sdata;
    uint8_t *pSrc = (uint8_t*)&_la_data;

    for (i = 0; i < size; i++)
    {
        *pDst++ = *pSrc++;
    }

    /* Limpa a seção .bss */
    size = (uint32_t)&_ebss - (uint32_t)&_sbss;
    pDst = (uint8_t*)&_sbss;

    for (i = 0; i < size; i++)
    {
        *pDst++ = 0;
    }

    /* Chama a função principal */
    main();
}

/* Manipulador Padrão de Exceção/Interrupção */
void default_handler(void)
{
    while(1)
    {
        /* Loop infinito */
    }
}

/* Função Principal */
int main(void)
{
    /* Seu código principal aqui */
    while(1)
    {
        /* Loop infinito */
    }
}
