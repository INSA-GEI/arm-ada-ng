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
const SYNTH_Instrument SYNTH_Inst_Drum;

#endif /* AUDIO_SYNTH_CONST_H_ */
