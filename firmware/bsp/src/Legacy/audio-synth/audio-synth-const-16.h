/*
 * audio-synth-const.h
 *
 *  Created on: 9 nov. 2017
 *      Author: dimercur
 */

#ifndef AUDIO_SYNTH_CONST_H_
#define AUDIO_SYNTH_CONST_H_

#define WaveTableLength		55
#define NotesLength			12*8

const SYNTH_Frequencies SYNTH_NoteFrequencies[NotesLength];

const SYNTH_Instrument SYNTH_Inst_Piano;
const SYNTH_Instrument SYNTH_Inst_Guitar;

const SYNTH_Instrument SYNTH_Inst_Sin;
const SYNTH_Instrument SYNTH_Inst_Triangle;
const SYNTH_Instrument SYNTH_Inst_Square;
const SYNTH_Instrument SYNTH_Inst_Saw;
const SYNTH_Instrument SYNTH_Inst_Noise;
const SYNTH_Instrument SYNTH_Inst_HalfTriangle;
const SYNTH_Instrument SYNTH_Inst_HalfSquare;
const SYNTH_Instrument SYNTH_Inst_HalfSin;
const SYNTH_Instrument SYNTH_Inst_HalfNoise;
const SYNTH_Instrument SYNTH_Inst_QuaterSin;
const SYNTH_Instrument SYNTH_Inst_SquareHach;
const SYNTH_Instrument SYNTH_Inst_SinHach;
const SYNTH_Instrument SYNTH_Inst_HalfSaw;

#endif /* AUDIO_SYNTH_CONST_H_ */
