/*
 * audio-melody.c
 *
 *  Created on: 9 nov. 2017
 *      Author: dimercur
 */

#include "audio-synth.h"
#include "audio-melody.h"

uint16_t MELODY_CurrentPtr;
MELODY_Notes *MELODY_CurrentMusic;
uint32_t MELODY_Length;

TIM_HandleTypeDef MelodyTimHandle;

MELODY_Status MELODY_Init(void)
{
	RCC_ClkInitTypeDef    clkconfig;
	uint32_t              uwTimclock, uwAPB1Prescaler = 0U;
	uint32_t              uwPrescalerValue = 0U;
	uint32_t              pFLatency;

	/* Configure the TIM4 IRQ priority */
	HAL_NVIC_SetPriority(TIM4_IRQn, 0x4U ,0U);

	/* Enable the TIM4 global Interrupt */
	HAL_NVIC_EnableIRQ(TIM4_IRQn);

	/* Enable TIM4 clock */
	__HAL_RCC_TIM4_CLK_ENABLE();

	/* Get clock configuration */
	HAL_RCC_GetClockConfig(&clkconfig, &pFLatency);

	/* Get APB1 prescaler */
	uwAPB1Prescaler = clkconfig.APB1CLKDivider;

	/* Compute TIM4 clock */
	if (uwAPB1Prescaler == RCC_HCLK_DIV1)
	{
		uwTimclock = HAL_RCC_GetPCLK1Freq();
	}
	else
	{
		uwTimclock = 2*HAL_RCC_GetPCLK1Freq();
	}

	/* Compute the prescaler value to have TIM4 counter clock equal to 10KHz */
	uwPrescalerValue = (uint32_t) ((uwTimclock / 10000U) - 1U);

	/* Initialize TIM4 */
	MelodyTimHandle.Instance = TIM4;

	/* Initialize TIMx peripheral as follow:
			  + Period = 65535
			  + Prescaler = (uwTimclock/10000 - 1) to have a 0.01MHz counter clock.
			  + ClockDivision = 0
			  + Counter direction = Up
	 */
	MelodyTimHandle.Init.Period = 65535;
	MelodyTimHandle.Init.Prescaler = uwPrescalerValue;
	MelodyTimHandle.Init.ClockDivision = 0;
	MelodyTimHandle.Init.CounterMode = TIM_COUNTERMODE_UP;
	MelodyTimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

	if(HAL_TIM_Base_Init(&MelodyTimHandle) == HAL_OK)
	{
		/* Start the TIM time Base generation with interrupt disabled  */
		//HAL_TIM_Base_Start(&MelodyTimHandle);
	}

	return MELODY_SUCCESS;
}

MELODY_Status MELODY_Start(MELODY_Notes *music, uint32_t length)
{
	//	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	//	NVIC_InitTypeDef NVIC_InitStructure;
	//
	//	/* TIM4 Periph clock enable */
	//	RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM4, ENABLE);
	//	RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM4, DISABLE);
	//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	//	TIM_Cmd(TIM4, DISABLE);
	//	TIM_ClearFlag(TIM4, TIM_FLAG_Update);
	//
	//	/* Time base configuration */
	//	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	//	TIM_TimeBaseStructure.TIM_Period = 65535; // Valeur max -> 65.536 s
	//	TIM_TimeBaseStructure.TIM_Prescaler = 7200-1; // prescaler pour avoir un increment minimal de 0.1 ms
	//	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
	//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	//	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	//
	//	/* TIM4 IRQ channel configuration */
	//	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
	//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	//	NVIC_Init(&NVIC_InitStructure);

	MELODY_CurrentMusic = music;
	MELODY_CurrentPtr = 0;
	MELODY_Length = length;

	do {
		SYNTH_NoteOn(music[MELODY_CurrentPtr].channel, music[MELODY_CurrentPtr].note);

		//if (music[MELODY_CurrentPtr].duree != 0) TIM_SetAutoreload(TIM4, music[MELODY_CurrentPtr].duree);
		if (music[MELODY_CurrentPtr].duree != 0) {
			__HAL_TIM_SET_AUTORELOAD(&MelodyTimHandle, music[MELODY_CurrentPtr].duree);
		}

		MELODY_CurrentPtr++;
	} while (music[MELODY_CurrentPtr-1].duree == 0);

	/* Lance le timer4 */
	/* Enable Up IT */
	HAL_TIM_Base_Start_IT(&MelodyTimHandle);
//	TIM_ClearFlag(TIM4, TIM_FLAG_Update);
//	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
//	TIM_Cmd(TIM4, ENABLE);

	return MELODY_SUCCESS;
}

MELODY_Status MELODY_Stop(void)
{
	/* arret du Timer 4 */
	HAL_TIM_Base_Stop_IT(&MelodyTimHandle);
//	TIM_Cmd(TIM4, DISABLE);
//	TIM_ClearFlag(TIM4, TIM_FLAG_Update);
//	RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM4, ENABLE);
//	RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM4, DISABLE);

	MELODY_CurrentPtr=0;
	MELODY_CurrentMusic = 0;

	return MELODY_SUCCESS;
}

MELODY_Status MELODY_GetPosition(uint8_t *pos)
{
	*pos = (uint8_t)(MELODY_CurrentPtr*255/MELODY_Length);
	return MELODY_SUCCESS;
}

/**
 * @brief  This function handles TIM4 interrupt request.
 * @retval None
 */

void TIM4_IRQHandler(void)
{
	/* Acquitement du timer 4 */
	HAL_TIM_IRQHandler(&MelodyTimHandle);

	__HAL_TIM_DISABLE(&MelodyTimHandle);
	/* arret du Timer 4 */
//	TIM_Cmd(TIM4, DISABLE);
//	TIM_ClearFlag(TIM4, TIM_FLAG_Update);

	if (MELODY_CurrentPtr<MELODY_Length)
	{
		do {
			SYNTH_NoteOn(
					MELODY_CurrentMusic[MELODY_CurrentPtr].channel,
					MELODY_CurrentMusic[MELODY_CurrentPtr].note);

			//if (MELODY_CurrentMusic[MELODY_CurrentPtr].duree != 0) TIM_SetAutoreload(TIM4, MELODY_CurrentMusic[MELODY_CurrentPtr].duree);
			if (MELODY_CurrentMusic[MELODY_CurrentPtr].duree != 0) {
				__HAL_TIM_SET_AUTORELOAD(&MelodyTimHandle, MELODY_CurrentMusic[MELODY_CurrentPtr].duree);
			}

			MELODY_CurrentPtr++;
		} while ((MELODY_CurrentMusic[MELODY_CurrentPtr-1].duree == 0) && (MELODY_CurrentPtr<MELODY_Length));

		/* reconfigure le timer4 */
		__HAL_TIM_ENABLE(&MelodyTimHandle);

	}
	else HAL_TIM_Base_Stop_IT(&MelodyTimHandle);
}
