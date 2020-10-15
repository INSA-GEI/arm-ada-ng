-- Package Insa.Keys
-- Functions to read keys state and potentiometer values
--

package body Insa.Keys is
   
   -- GetKeyState
   -- Return the current state (Key_Pressed or Key_Released) of a given key (Key_A, Key_B, ...)
   -- Incorrect key id will raise CONSTRAINT_ERROR  
   function GetKeyState(key: KEY_ID) return KEY_STATE is
      
      -- Wrapper to corresponding OS function
      function Wrapper_GetKeyState (key: KEY_ID) return KEY_STATE;
      pragma Import (C, Wrapper_GetKeyState, "KEYS_GetState");
      
   begin
      return Wrapper_GetKeyState(Key);
   end GetKeyState;
   
   -- GetAllKeys
   -- Return all keys state in a single structure
   function GetAllKeys return KEY_LIST is
      Keys: KEY_LIST;
   begin
      Keys.A:=GetKeyState(KEY_A);
      Keys.B:=GetKeyState(KEY_B);
      Keys.Center:=GetKeyState(KEY_CENTER);
      Keys.Up:=GetKeyState(KEY_UP);
      Keys.Down:=GetKeyState(KEY_DOWN);
      Keys.Left:=GetKeyState(KEY_LEFT);
      Keys.Right:=GetKeyState(KEY_RIGHT);
      
      return Keys;
   end GetAllKeys;
   
   -- GetPotentiometerValue
   -- Return the current value (range 0 to 255) of a given potentiometer (Potentiometer_Left or Potentiometer_Right)
   -- Incorrect potentiometer id will raise CONSTRAINT_ERROR  
   function GetPotentiometerValue(pot: POTENTIOMETER_ID) return POTENTIOMETER_VALUE is
      
      -- Wrapper to corresponding OS function
      function Wrapper_GetPotentiometerValue(pot: POTENTIOMETER_ID) return POTENTIOMETER_VALUE;
      pragma Import (C, Wrapper_GetPotentiometerValue, "POT_GetValue");
      
   begin
      return Wrapper_GetPotentiometerValue(Pot);
   end GetPotentiometerValue;
   
end Insa.Keys;
