/*
 * audio-synth-const.c
 *
 *  Created on: 9 nov. 2017
 *      Author: dimercur
 */

#include "audio-synth.h"
#include "audio-synth-const.h"

#define TickAudio			(float)(1.0f/44100.0f)

const SYNTH_Wave SYNTH_SinHachWave[WaveTableLength];
const SYNTH_Wave SYNTH_SinWave[WaveTableLength];
const SYNTH_Wave SYNTH_HalfSinWave[WaveTableLength];
const SYNTH_Wave SYNTH_SquareWave[WaveTableLength];
const SYNTH_Wave SYNTH_TriangleWave[WaveTableLength];

const SYNTH_Wave SYNTH_SinHachWave[WaveTableLength]=
{
		128, 0, 156, 0, 184, 0, 209, 0, 229, 0, 244, 0, 253,
		0, 255, 0, 251, 0, 241, 0, 224, 0, 203, 0, 177, 0,
		149, 0, 121, 0, 92, 0, 66, 0, 42, 0, 23, 0, 9, 0, 2, 0,
		1, 0, 7, 0, 19, 0, 37, 0, 59, 0, 85, 0, 114
};

const SYNTH_Wave SYNTH_SinWave[WaveTableLength]=
{
		128, 142, 156, 171, 184, 197, 209, 219, 229, 237, 244, 249, 253,
		255, 255, 254, 251, 247, 241, 233, 224, 214, 203, 190, 177, 164,
		149, 135, 121, 107, 92, 79, 66, 53, 42, 32, 23, 15, 9, 5, 2, 1,
		1, 3, 7, 12, 19, 27, 37, 47, 59, 72, 85, 100, 114
};

const SYNTH_Wave SYNTH_HalfSinWave[WaveTableLength]=
{
		128, 142, 156, 171, 184, 197, 209, 219, 229, 237, 244, 249, 253,
		255, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0,
		0, 0, 121, 107, 92, 79, 66, 53, 42, 32, 23, 15, 9, 5, 2, 1,
		0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0
};

const SYNTH_Wave SYNTH_SquareWave[WaveTableLength]=
{
		255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
		255,255,255,255,255,255,255,255,255,255,255,255,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

/*const SYNTH_Wave SYNTH_TriangleWave[WaveTableLength]=
{
		128,137,146,155,164,173,182,191,200,209,218,227,236,245,255,245,
		236,227,218,209,200,191,182,173,164,155,146,137,128,118,109,100,
		91,82,73,64,55,46,37,28,19,10,1,9,19,29,39,48,58,68,78,87,97,107,117
};*/

const SYNTH_Wave SYNTH_TriangleWave[WaveTableLength]=
{
		128,137,146,155,164,173,182,191,200,209,218,227,236,245,255,245,
		236,227,218,209,200,191,182,173,164,155,146,137,128,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
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
		0,								// Pas de maintien
		0.03f/TickAudio,					// Sustain pendant 30 ms
	TickAudio/0.01f,				// 10ms d'attaque
	TickAudio/0.04f,				// 20 ms de descente (à 50% de volume, donc 40ms pour arriver à zero)
	0.5f,							// Sustain à 50%
	TickAudio/0.40f,				// Retrait pendant 400 ms


	(SYNTH_Wave*)SYNTH_SinHachWave,

};

const SYNTH_Instrument SYNTH_Inst_Guitar=
{
		0,								// Pas de maintien
		0.08f/TickAudio,					// Sustain pendant 80 ms
	TickAudio/0.005f,				// 5ms d'attaque
	TickAudio/0.09f,				// 45 ms de descente (à 50% de volume, donc 90ms pour arriver à zero)
	0.5f,							// Sustain à 50%
	TickAudio/0.10f,				// Retrait pendant 100 ms


	(SYNTH_Wave*)SYNTH_SquareWave,
};

/*
const SYNTH_Instrument SYNTH_Inst_Drum=
{

};*/

