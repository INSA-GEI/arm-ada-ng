/*
 * audio-synth-const.c
 *
 *  Created on: 9 nov. 2017
 *      Author: dimercur
 */

#include <audio-synth/audio-synth-const-16.h>
#include "audio-synth.h"

#define TickAudio			(float)(1.0f/44100.0f)

const SYNTH_Wave SYNTH_SinWave[WaveTableLength];
const SYNTH_Wave SYNTH_TriangleWave[WaveTableLength];
const SYNTH_Wave SYNTH_HalfTriangleWave[WaveTableLength];
const SYNTH_Wave SYNTH_HalfSinWave[WaveTableLength];
const SYNTH_Wave SYNTH_QuarterSinWave[WaveTableLength];
const SYNTH_Wave SYNTH_SquareWave[WaveTableLength];
const SYNTH_Wave SYNTH_HalfSquareWave[WaveTableLength];
const SYNTH_Wave SYNTH_SquareHachWave[WaveTableLength];
const SYNTH_Wave SYNTH_NoiseWave[WaveTableLength];
const SYNTH_Wave SYNTH_HalfNoiseWave[WaveTableLength];
const SYNTH_Wave SYNTH_SawWave[WaveTableLength];
const SYNTH_Wave SYNTH_HalfSawWave[WaveTableLength];
const SYNTH_Wave SYNTH_SinHachWave[WaveTableLength];

const SYNTH_Wave SYNTH_SinWave[WaveTableLength]=
{
		0,
		3735,
		7421,
		11011,
		14457,
		17715,
		20742,
		23498,
		25949,
		28060,
		29806,
		31164,
		32115,
		32647,
		32754,
		32434,
		31691,
		30535,
		28981,
		27049,
		24764,
		22156,
		19260,
		16113,
		12755,
		9231,
		5587,
		1870,
		-1870,
		-5587,
		-9231,
		-12755,
		-16113,
		-19260,
		-22156,
		-24764,
		-27049,
		-28981,
		-30535,
		-31691,
		-32434,
		-32754,
		-32647,
		-32115,
		-31164,
		-29806,
		-28060,
		-25949,
		-23498,
		-20742,
		-17715,
		-14457,
		-11011,
		-7421,
		-3735
};

const SYNTH_Wave SYNTH_TriangleWave[WaveTableLength]=
{
		0,
		2340,
		4680,
		7020,
		9360,
		11700,
		14040,
		16380,
		18720,
		21060,
		23400,
		25740,
		28080,
		30420,
		32760,
		30420,
		28080,
		25740,
		23400,
		21060,
		18720,
		16380,
		14040,
		11700,
		9360,
		7020,
		4680,
		2340,
		0,
		-2340,
		-4680,
		-7020,
		-9360,
		-11700,
		-14040,
		-16380,
		-18720,
		-21060,
		-23400,
		-25740,
		-28080,
		-32760,
		-30420,
		-28080,
		-25740,
		-23400,
		-21060,
		-18720,
		-16380,
		-14040,
		-11700,
		-9360,
		-7020,
		-4680,
		-2340
};

const SYNTH_Wave SYNTH_HalfTriangleWave[WaveTableLength]=
{
		0,
		2340,
		4680,
		7020,
		9360,
		11700,
		14040,
		16380,
		18720,
		21060,
		23400,
		25740,
		28080,
		30420,
		32760,
		30420,
		28080,
		25740,
		23400,
		21060,
		18720,
		16380,
		14040,
		11700,
		9360,
		7020,
		4680,
		2340,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
};

const SYNTH_Wave SYNTH_HalfSinWave[WaveTableLength]=
{
		0,
		3734,
		7420,
		11008,
		14454,
		17711,
		20737,
		23493,
		25942,
		28053,
		29799,
		31156,
		32107,
		32639,
		32746,
		32426,
		31683,
		30527,
		28974,
		27042,
		24758,
		22151,
		19255,
		16109,
		12752,
		9229,
		5586,
		1870,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0
};

const SYNTH_Wave SYNTH_QuarterSinWave[WaveTableLength]=
{
		0,
		3734,
		7420,
		11008,
		14454,
		17711,
		20737,
		23493,
		25942,
		28053,
		29799,
		31156,
		32107,
		32639,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		-1870,
		-5586,
		-9229,
		-12752,
		-16109,
		-19255,
		-22151,
		-24758,
		-27042,
		-28974,
		-30527,
		-31683,
		-32426,
		-32746,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0
};

const SYNTH_Wave SYNTH_SquareWave[WaveTableLength]=
{
		32760,
		32760,
		32760,
		32760,
		32760,
		32760,
		32760,
		32760,
		32760,
		32760,
		32760,
		32760,
		32760,
		32760,
		32760,
		32760,
		32760,
		32760,
		32760,
		32760,
		32760,
		32760,
		32760,
		32760,
		32760,
		32760,
		32760,
		32760,
		-32760,
		-32760,
		-32760,
		-32760,
		-32760,
		-32760,
		-32760,
		-32760,
		-32760,
		-32760,
		-32760,
		-32760,
		-32760,
		-32760,
		-32760,
		-32760,
		-32760,
		-32760,
		-32760,
		-32760,
		-32760,
		-32760,
		-32760,
		-32760,
		-32760,
		-32760,
		-32760
};

const SYNTH_Wave SYNTH_HalfSquareWave[WaveTableLength]=
{
		32760,
		32760,
		32760,
		32760,
		32760,
		32760,
		32760,
		32760,
		32760,
		32760,
		32760,
		32760,
		32760,
		32760,
		32760,
		32760,
		32760,
		32760,
		32760,
		32760,
		32760,
		32760,
		32760,
		32760,
		32760,
		32760,
		32760,
		32760,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0
};

const SYNTH_Wave SYNTH_SquareHachWave[WaveTableLength]=
{
		32760,
		0,
		32760,
		0,
		32760,
		0,
		32760,
		0,
		32760,
		0,
		32760,
		0,
		32760,
		0,
		32760,
		0,
		32760,
		0,
		32760,
		0,
		32760,
		0,
		32760,
		0,
		32760,
		0,
		32760,
		0,
		-32760,
		0,
		-32760,
		0,
		-32760,
		0,
		-32760,
		0,
		-32760,
		0,
		-32760,
		0,
		-32760,
		0,
		-32760,
		0,
		-32760,
		0,
		-32760,
		0,
		-32760,
		0,
		-32760,
		0,
		-32760,
		0,
		-32760,

};

const SYNTH_Wave SYNTH_NoiseWave[WaveTableLength]=
{
		3713,
		-2581,
		-22340,
		-12471,
		7346,
		31007,
		-7882,
		-32300,
		26080,
		-1478,
		21368,
		11834,
		-25766,
		11099,
		-19524,
		-10623,
		-4683,
		25367,
		-5207,
		28318,
		-1358,
		6363,
		-4106,
		9527,
		28312,
		23806,
		16789,
		-17214,
		-32284,
		30397,
		-7897,
		27748,
		-27614,
		-27574,
		-29005,
		-12052,
		-14686,
		-31223,
		18485,
		8715,
		3829,
		-1187,
		15907,
		18555,
		-31122,
		10645,
		-19611,
		-14926,
		32696,
		27430,
		-19222,
		19883,
		-26754,
		23295,
		19666
};

const SYNTH_Wave SYNTH_HalfNoiseWave[WaveTableLength]=
{
		26816,
		-32387,
		28278,
		-31512,
		1944,
		-14350,
		-26461,
		-16443,
		9046,
		-11391,
		-2852,
		-31731,
		-19904,
		-7348,
		-13703,
		-15452,
		-23853,
		29337,
		26365,
		-18880,
		1915,
		19209,
		-32568,
		-12154,
		-5016,
		-20263,
		-29404,
		21221,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0
};

const SYNTH_Wave SYNTH_SawWave[WaveTableLength]=
{
		0,
		2340,
		4680,
		7020,
		9360,
		11700,
		14040,
		16380,
		18720,
		21060,
		23400,
		25740,
		28080,
		30420,
		-585,
		-2925,
		-5265,
		-7605,
		-9945,
		-12285,
		-14625,
		-16965,
		-19305,
		-21645,
		-23985,
		-26325,
		-28665,
		-31005,
		1170,
		3510,
		5850,
		8190,
		10530,
		12870,
		15210,
		17550,
		19890,
		22230,
		24570,
		26910,
		29250,
		31590,
		-1755,
		-4095,
		-6435,
		-8775,
		-11115,
		-13455,
		-15795,
		-18135,
		-20475,
		-22815,
		-25155,
		-27495,
		-29835
};

const SYNTH_Wave SYNTH_HalfSawWave[WaveTableLength]=
{
		0,
		2340,
		4680,
		7020,
		9360,
		11700,
		14040,
		16380,
		18720,
		21060,
		23400,
		25740,
		28080,
		30420,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		-2340,
		-4680,
		-7020,
		-9360,
		-11700,
		-14040,
		-16380,
		-18720,
		-21060,
		-23400,
		-25740,
		-28080,
		-30420,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0
};

const SYNTH_Wave SYNTH_SinHachWave[WaveTableLength]=
{
		0,
		0,
		7420,
		0,
		14454,
		0,
		20737,
		0,
		25942,
		0,
		29799,
		0,
		32107,
		0,
		32746,
		0,
		31683,
		0,
		28974,
		0,
		24758,
		0,
		19255,
		0,
		12752,
		0,
		5586,
		0,
		-1870,
		0,
		-9229,
		0,
		-16109,
		0,
		-22151,
		0,
		-27042,
		0,
		-30527,
		0,
		-32426,
		0,
		-32639,
		0,
		-31156,
		0,
		-28053,
		0,
		-23493,
		0,
		-17711,
		0,
		-11008,
		0,
		-3734,
};

const SYNTH_Frequencies SYNTH_NoteFrequencies[NotesLength]=
{
		3270,3465,3671,3889,4120,4365,4625,4900,5191,5500,5827,6174,
		6541,6930,7342,7778,8241,8731,9250,9800,10383,11000,11654,12347,
		13081,13859,14683,15556,16481,17461,18500,19600,20765,22000,23308,24694,
		26163,27718,29366,31113,32963,34923,36999,39200,41530,44000,46616,49388,
		52325,55437,58733,62225,65926,69846,73999,78399,83061,88000,93233,98777,
		104650,110873,117466,124451,131851,139691,147998,156798,166122,176000,186466,197553,
		209300,221746,234932,248902,263702,279383,295996,313596,332244,352000,372931,395107,
		418601,443492,469864,497803,527404,558765,591991,627193,664488,704000,745862,790213
};

const SYNTH_Instrument SYNTH_Inst_Piano=
{
		0.15f/TickAudio,								// Pas de maintien
		0.05f/TickAudio,				// Sustain pendant 30 ms
		TickAudio/0.03f,				// 10ms d'attaque
		TickAudio/0.08f,				// 20 ms de descente (à 50% de volume, donc 40ms pour arriver à zero)
		0.8f,							// Sustain à 50%
		TickAudio/1.20f,				// Retrait pendant 400 ms

		(SYNTH_Wave*)SYNTH_SinWave,

};

const SYNTH_Instrument SYNTH_Inst_Guitar=
{
		0.15f/TickAudio,								// Pas de maintien
		0.05f/TickAudio,				// Sustain pendant 30 ms
		TickAudio/0.03f,				// 10ms d'attaque
		TickAudio/0.08f,				// 20 ms de descente (à 50% de volume, donc 40ms pour arriver à zero)
		0.8f,							// Sustain à 50%
		TickAudio/1.20f,				// Retrait pendant 400 ms

		(SYNTH_Wave*)SYNTH_SquareWave,

};


const SYNTH_Instrument SYNTH_Inst_Sin=
{
		0.15f/TickAudio,								// Pas de maintien
		0.05f/TickAudio,				// Sustain pendant 30 ms
		TickAudio/0.03f,				// 10ms d'attaque
		TickAudio/0.08f,				// 20 ms de descente (à 50% de volume, donc 40ms pour arriver à zero)
		0.8f,							// Sustain à 50%
		TickAudio/1.20f,				// Retrait pendant 400 ms

		(SYNTH_Wave*)SYNTH_SinWave,
};

const SYNTH_Instrument SYNTH_Inst_Triangle=
{
		0.15f/TickAudio,								// Pas de maintien
		0.05f/TickAudio,				// Sustain pendant 30 ms
		TickAudio/0.03f,				// 10ms d'attaque
		TickAudio/0.08f,				// 20 ms de descente (à 50% de volume, donc 40ms pour arriver à zero)
		0.8f,							// Sustain à 50%
		TickAudio/1.20f,				// Retrait pendant 400 ms

		(SYNTH_Wave*)SYNTH_TriangleWave,
};

const SYNTH_Instrument SYNTH_Inst_Square=
{
		0.15f/TickAudio,								// Pas de maintien
		0.05f/TickAudio,				// Sustain pendant 30 ms
		TickAudio/0.03f,				// 10ms d'attaque
		TickAudio/0.08f,				// 20 ms de descente (à 50% de volume, donc 40ms pour arriver à zero)
		0.8f,							// Sustain à 50%
		TickAudio/1.20f,				// Retrait pendant 400 ms

		(SYNTH_Wave*)SYNTH_SquareWave,
};

const SYNTH_Instrument SYNTH_Inst_Saw=
{
		0.15f/TickAudio,								// Pas de maintien
		0.05f/TickAudio,				// Sustain pendant 30 ms
		TickAudio/0.03f,				// 10ms d'attaque
		TickAudio/0.08f,				// 20 ms de descente (à 50% de volume, donc 40ms pour arriver à zero)
		0.8f,							// Sustain à 50%
		TickAudio/1.20f,				// Retrait pendant 400 ms

		(SYNTH_Wave*)SYNTH_SawWave,
};

const SYNTH_Instrument SYNTH_Inst_Noise=
{
		0.15f/TickAudio,								// Pas de maintien
		0.05f/TickAudio,				// Sustain pendant 30 ms
		TickAudio/0.03f,				// 10ms d'attaque
		TickAudio/0.08f,				// 20 ms de descente (à 50% de volume, donc 40ms pour arriver à zero)
		0.8f,							// Sustain à 50%
		TickAudio/1.20f,				// Retrait pendant 400 ms

		(SYNTH_Wave*)SYNTH_NoiseWave,
};

const SYNTH_Instrument SYNTH_Inst_HalfTriangle=
{
		0.15f/TickAudio,								// Pas de maintien
		0.05f/TickAudio,				// Sustain pendant 30 ms
		TickAudio/0.03f,				// 10ms d'attaque
		TickAudio/0.08f,				// 20 ms de descente (à 50% de volume, donc 40ms pour arriver à zero)
		0.8f,							// Sustain à 50%
		TickAudio/1.20f,				// Retrait pendant 400 ms

		(SYNTH_Wave*)SYNTH_HalfTriangleWave,
};

const SYNTH_Instrument SYNTH_Inst_HalfSquare=
{
		0.15f/TickAudio,								// Pas de maintien
		0.05f/TickAudio,				// Sustain pendant 30 ms
		TickAudio/0.03f,				// 10ms d'attaque
		TickAudio/0.08f,				// 20 ms de descente (à 50% de volume, donc 40ms pour arriver à zero)
		0.8f,							// Sustain à 50%
		TickAudio/1.20f,				// Retrait pendant 400 ms

		(SYNTH_Wave*)SYNTH_HalfSquareWave,
};

const SYNTH_Instrument SYNTH_Inst_HalfSin=
{
		0.15f/TickAudio,								// Pas de maintien
		0.05f/TickAudio,				// Sustain pendant 30 ms
		TickAudio/0.03f,				// 10ms d'attaque
		TickAudio/0.08f,				// 20 ms de descente (à 50% de volume, donc 40ms pour arriver à zero)
		0.8f,							// Sustain à 50%
		TickAudio/1.20f,				// Retrait pendant 400 ms

		(SYNTH_Wave*)SYNTH_HalfSinWave,
};

const SYNTH_Instrument SYNTH_Inst_HalfNoise=
{
		0.15f/TickAudio,								// Pas de maintien
		0.05f/TickAudio,				// Sustain pendant 30 ms
		TickAudio/0.03f,				// 10ms d'attaque
		TickAudio/0.08f,				// 20 ms de descente (à 50% de volume, donc 40ms pour arriver à zero)
		0.8f,							// Sustain à 50%
		TickAudio/1.20f,				// Retrait pendant 400 ms

		(SYNTH_Wave*)SYNTH_HalfNoiseWave,
};

const SYNTH_Instrument SYNTH_Inst_QuaterSin=
{
		0.15f/TickAudio,								// Pas de maintien
		0.05f/TickAudio,				// Sustain pendant 30 ms
		TickAudio/0.03f,				// 10ms d'attaque
		TickAudio/0.08f,				// 20 ms de descente (à 50% de volume, donc 40ms pour arriver à zero)
		0.8f,							// Sustain à 50%
		TickAudio/1.20f,				// Retrait pendant 400 ms

		(SYNTH_Wave*)SYNTH_QuarterSinWave,
};

const SYNTH_Instrument SYNTH_Inst_SquareHach=
{
		0.15f/TickAudio,								// Pas de maintien
		0.05f/TickAudio,				// Sustain pendant 30 ms
		TickAudio/0.03f,				// 10ms d'attaque
		TickAudio/0.08f,				// 20 ms de descente (à 50% de volume, donc 40ms pour arriver à zero)
		0.8f,							// Sustain à 50%
		TickAudio/1.20f,				// Retrait pendant 400 ms

		(SYNTH_Wave*)SYNTH_SquareHachWave,
};

const SYNTH_Instrument SYNTH_Inst_SinHach=
{
		0.15f/TickAudio,								// Pas de maintien
		0.05f/TickAudio,				// Sustain pendant 30 ms
		TickAudio/0.03f,				// 10ms d'attaque
		TickAudio/0.08f,				// 20 ms de descente (à 50% de volume, donc 40ms pour arriver à zero)
		0.8f,							// Sustain à 50%
		TickAudio/1.20f,				// Retrait pendant 400 ms

		(SYNTH_Wave*)SYNTH_SinHachWave,
};

const SYNTH_Instrument SYNTH_Inst_HalfSaw=
{
		0.15f/TickAudio,								// Pas de maintien
		0.05f/TickAudio,				// Sustain pendant 30 ms
		TickAudio/0.03f,				// 10ms d'attaque
		TickAudio/0.08f,				// 20 ms de descente (à 50% de volume, donc 40ms pour arriver à zero)
		0.8f,							// Sustain à 50%
		TickAudio/1.20f,				// Retrait pendant 400 ms

		(SYNTH_Wave*)SYNTH_HalfSawWave,
};

//const SYNTH_Instrument SYNTH_Inst_Piano=
//{
//		0,								// Pas de maintien
//		0.03f/TickAudio,					// Sustain pendant 30 ms
//	TickAudio/0.01f,				// 10ms d'attaque
//	TickAudio/0.04f,				// 20 ms de descente (à 50% de volume, donc 40ms pour arriver à zero)
//	0.5f,							// Sustain à 50%
//	TickAudio/0.40f,				// Retrait pendant 400 ms
//
//
//	(SYNTH_Wave*)SYNTH_SinHachWave,
//
//};
//
//const SYNTH_Instrument SYNTH_Inst_Guitar=
//{
//		0,								// Pas de maintien
//		0.08f/TickAudio,					// Sustain pendant 80 ms
//	TickAudio/0.005f,				// 5ms d'attaque
//	TickAudio/0.09f,				// 45 ms de descente (à 50% de volume, donc 90ms pour arriver à zero)
//	0.5f,							// Sustain à 50%
//	TickAudio/0.10f,				// Retrait pendant 100 ms
//
//
//	(SYNTH_Wave*)SYNTH_SquareWave,
//};



