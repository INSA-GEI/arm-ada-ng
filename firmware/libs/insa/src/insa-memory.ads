-- Package Insa.Memory
-- Define functions for reading or writing in external memory
--
-- External memory is 512 Kb long and is accessed byte by byte
--

package Insa.Memory is
   pragma Warnings (Off);
   
   subtype MEMORY_ADDRESS is INTEGER range 0 .. 512*1024-1;
   type MEMORY_BYTE is range 0 .. 255;
   for MEMORY_BYTE'Size use 8;  
   
   type MEMORY_BUFFER is array (MEMORY_ADDRESS range <>) of MEMORY_BYTE;
   
   -- StartAudio
   -- Lauch audio processing, which will call Event_Callback every half-audio buffer processed
   function ReadByte(Addr: MEMORY_ADDRESS) return MEMORY_BYTE;
   
   -- StopAudio
   -- Stop audio processing
   procedure WriteByte(Addr: MEMORY_ADDRESS; Data: MEMORY_BYTE);
   
   -- FillAudioBuffer
   -- Used to fill audio buffer. Audio buffer is 1024 elements long and split in 2
   -- each time half part is processed, an event is raised, indicating which part of buffer (buffer_nbr) must be filled
   procedure ReadByteBuffer(Addr: MEMORY_ADDRESS; Buffer: in out MEMORY_BUFFER);
   
   -- SetAudioCallback
   -- used to register an event callback
   -- callback is called every time half part of audio buffer
   procedure WriteByteBuffer(Addr: MEMORY_ADDRESS; Buffer: MEMORY_BUFFER);
   
end Insa.Memory;
