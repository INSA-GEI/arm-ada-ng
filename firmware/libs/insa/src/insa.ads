-- Package Insa
-- Define several usefull types and generic functions
--

-- pragma Ada_95;

package Insa is
   pragma Warnings (Off);
   
   -- Definition of an unsigned byte (8 bit long)
   type BYTE is range 0 .. 255;
   for BYTE'Size use 8;  
   
   -- Definition of a signed byte (8 bit long)
   type SIGNED_BYTE is range -128 .. 127;
   for SIGNED_BYTE'Size use 8;
   
   -- Definition of an unsigned word (16 bit long)
   type WORD is range 0 .. 65535;
   for WORD'Size use 16;
   
   -- Definition of a signed word (16 bit long)
   type SIGNED_WORD is range -32768 .. 32767;
   for SIGNED_WORD'Size use 16;
   
   -- GetOSVersion
   -- Return current version as Major.Minor
   procedure GetOSVersion(Major: out INTEGER; Minor: out INTEGER);
   
   -- SysDelay
   -- Wait during 'Time' millisecondes
   procedure SysDelay(Time: Positive);

end Insa;
