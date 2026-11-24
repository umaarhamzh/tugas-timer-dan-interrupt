#include "stm32f411xe.h"
#include <stdint.h>

#define LED1 (1U << 5)   // PA5
#define LED2 (1U << 6)   // PA6
#define LED3 (1U << 7)   // PA7

void GPIO_Init(void)
{
    // Enable clock GPIOA
    RCC->AHB1ENR |= (1U << 0);

    // PA5, PA6, PA7 sebagai output
    GPIOA->MODER &= ~((3U << 10) |
                      (3U << 12) |
                      (3U << 14));

    GPIOA->MODER |= ((1U << 10) |
                     (1U << 12) |
                     (1U << 14));

    // Output push-pull
    GPIOA->OTYPER &= ~(LED1 | LED2 | LED3);

    // Kecepatan output
    GPIOA->OSPEEDR |= ((2U << 10) |
                       (2U << 12) |
                       (2U << 14));

    // Semua LED awalnya mati
    GPIOA->ODR &= ~(LED1 | LED2 | LED3);
}

void TIM2_Init(void)
{
    RCC->APB1ENR |= (1U << 0);

    TIM2->PSC = 15999;
    TIM2->ARR = 499;

    TIM2->CNT = 0;

    TIM2->EGR = TIM_EGR_UG;
    TIM2->SR = 0;

    TIM2->DIER |= TIM_DIER_UIE;

    NVIC->ISER[0] = (1U << TIM2_IRQn);

    TIM2->CR1 |= TIM_CR1_CEN;
}

void TIM3_Init(void)
{
    RCC->APB1ENR |= (1U << 1);

    TIM3->PSC = 15999;
    TIM3->ARR = 249;

    TIM3->CNT = 0;

    TIM3->EGR = TIM_EGR_UG;
    TIM3->SR = 0;

    TIM3->DIER |= TIM_DIER_UIE;

    NVIC->ISER[0] = (1U << TIM3_IRQn);

    TIM3->CR1 |= TIM_CR1_CEN;
}

void TIM4_Init(void)
{
    RCC->APB1ENR |= (1U << 2);

    TIM4->PSC = 15999;
    TIM4->ARR = 124;

    TIM4->CNT = 0;

    TIM4->EGR = TIM_EGR_UG;
    TIM4->SR = 0;

    TIM4->DIER |= TIM_DIER_UIE;

    NVIC->ISER[0] = (1U << TIM4_IRQn);

    TIM4->CR1 |= TIM_CR1_CEN;
}

// Interrupt TIM2
void TIM2_IRQHandler(void)
{
    if (TIM2->SR & TIM_SR_UIF)
    {
        TIM2->SR &= ~TIM_SR_UIF;
        GPIOA->ODR ^= LED1;
    }
}

// Interrupt TIM3
void TIM3_IRQHandler(void)
{
    if (TIM3->SR & TIM_SR_UIF)
    {
        TIM3->SR &= ~TIM_SR_UIF;
        GPIOA->ODR ^= LED2;
    }
}

// Interrupt TIM4
void TIM4_IRQHandler(void)
{
    if (TIM4->SR & TIM_SR_UIF)
    {
        TIM4->SR &= ~TIM_SR_UIF;
        GPIOA->ODR ^= LED3;
    }
}

int main(void)
{
    GPIO_Init();

    TIM2_Init();
    TIM3_Init();
    TIM4_Init();

    while (1)
    {
        // Proses utama tidak perlu melakukan apa-apa.
        // LED dikendalikan oleh interrupt timer.
    }
}