-- Package Insa.Keys
-- Functions to read keys state and potentiometer values
--

package Insa.Keys is
   pragma Warnings (Off);

   subtype KEY_STATE is INTEGER range 0 .. 1;
   subtype KEY_ID is INTEGER range 0 .. 7;
   subtype POTENTIOMETER_ID is INTEGER range 0 .. 1;
   subtype POTENTIOMETER_VALUE is BYTE;
   
   type KEY_LIST is record
      A: KEY_STATE;
      B: KEY_STATE;
      Down: KEY_STATE;
      Up: KEY_STATE;
      Center: KEY_STATE;
      Right: KEY_STATE;
      Left: KEY_STATE;
   end record;
   
   -- Declaration of keys ID
   Key_A:	constant KEY_ID := 0; 
   Key_B:       constant KEY_ID := 1; 
   Key_Up:	constant KEY_ID := 2; 
   Key_Down:	constant KEY_ID := 3; 
   Key_Left:	constant KEY_ID := 4; 
   Key_Center:	constant KEY_ID := 5; 
   Key_Right:	constant KEY_ID := 6; 
   Key_System:	constant KEY_ID := 7; 
   
   -- Declaration of keys states
   Key_Released:constant KEY_STATE := 0; 
   Key_Pressed:	constant KEY_STATE := 1; 
   
   -- Declaration of potentiometer ID
   Potentiometer_Left:	constant POTENTIOMETER_ID := 0; 
   Potentiometer_Right:	constant POTENTIOMETER_ID := 1; 
   
   -- GetKeyState
   -- Return the current state (Key_Pressed or Key_Released) of a given key (Key_A, Key_B, ...)
   -- Incorrect key id will raise CONSTRAINT_ERROR
   function GetKeyState(key: KEY_ID) return KEY_STATE;
   
   -- GetAllKeys
   -- Return all keys state in a single structure
   function GetAllKeys return KEY_LIST;
   
   -- GetPotentiometerValue
   -- Return the current value (range 0 to 255) of a given potentiometer (Potentiometer_Left or Potentiometer_Right)
   -- Incorrect potentiometer id will raise CONSTRAINT_ERROR
   function GetPotentiometerValue(pot: POTENTIOMETER_ID) return POTENTIOMETER_VALUE;

end Insa.Keys;
