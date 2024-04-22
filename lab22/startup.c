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

#define SRAM_START  0x20000000U                  /* Início da SRAM CORTEX-M */
#define SRAM_SIZE   (128U * 1024U)               /* Tamanho da SRAM STM32F411 128K */
#define SRAM_END    ((SRAM_START) + (SRAM_SIZE)) /* Final da SRAM STM32F411 */

#define STACK_START SRAM_END                     /* Início da Stack */

/****************************************************************************
 * Protótipos de Funções Privadas
 ****************************************************************************/

int main(void);

/* Protótipos de funções para as System Exceptions */

void reset_handler     (void);
void nmi_handler       (void) __attribute__ ((weak, alias("default_handler")));
void hardfault_handler (void) __attribute__ ((weak, alias("default_handler")));
void memmanage_handler (void) __attribute__ ((weak, alias("default_handler")));
void busfault_handler  (void) __attribute__ ((weak, alias("default_handler")));
void usagefault_handler(void) __attribute__ ((weak, alias("default_handler")));
void svc_handler       (void) __attribute__ ((weak, alias("default_handler")));
void debugmon_handler  (void) __attribute__ ((weak, alias("default_handler")));
void pendsv_handler    (void) __attribute__ ((weak, alias("default_handler")));
void systick_handler   (void) __attribute__ ((weak, alias("default_handler")));

/****************************************************************************
 * Dados Externos
 ****************************************************************************/

/* Variáveis exportadas pelo linker script */

extern uint32_t _sdata;     /* Início da seção .data */
extern uint32_t _edata;     /* Fim da seção .data */
extern uint32_t _la_data;   /* Origem da seção .data na FLASH */

extern uint32_t _sbss;      /* Início da seção .bss */
extern uint32_t _ebss;      /* Fim da seção .bss */

/****************************************************************************
 * Dados Privados
 ****************************************************************************/

/* Tabela de Vetores de Interrupção */

uint32_t vectors[] __attribute__((section(".isr_vectors"))) =
{
  STACK_START,                            /* 0x0000 0000 */
  (uint32_t)reset_handler,                /* 0x0000 0004 */
  (uint32_t)nmi_handler,                  /* 0x0000 0008 */
  (uint32_t)hardfault_handler,            /* 0x0000 000c */
  (uint32_t)memmanage_handler,            /* 0x0000 0010 */
  (uint32_t)busfault_handler,             /* 0x0000 0014 */
  (uint32_t)usagefault_handler,           /* 0x0000 0018 */
  0,                                      /* 0x0000 001c */
  0,                                      /* 0x0000 0020 */
  0,                                      /* 0x0000 0024 */
  0,                                      /* 0x0000 0028 */
  (uint32_t)svc_handler,                  /* 0x0000 002c */
  (uint32_t)debugmon_handler,             /* 0x0000 0030 */
  0,                                      /* 0x0000 0034 */
  (uint32_t)pendsv_handler,               /* 0x0000 0038 */
  (uint32_t)systick_handler,              /* 0x0000 003c */
};

/****************************************************************************
 * Funções Privadas
 ****************************************************************************/

void reset_handler(void)
{
  uint32_t i; 

  /* Copia a seção .data para a RAM */
   
  uint32_t size = (uint32_t)&_edata - (uint32_t)&_sdata;
  uint8_t *pDst = (uint8_t*)&_sdata;                      /* SRAM */
  uint8_t *pSrc = (uint8_t*)&_la_data;                    /* FLASH */
  
  for(i = 0; i < size; i++)
  {
    *pDst++ = *pSrc++;
  }

  /* Preenche a seção .bss com zero */

  size = (uint32_t)&_ebss - (uint32_t)&_sbss;
  pDst = (uint8_t*)&_sbss;
  for(i = 0 ; i < size; i++)
  {
    *pDst++ = 0;
  }

  /* Chama a função main() */

  main();
}

void default_handler(void)
{
  while(1){};
}
