-- Package Insa.Random_Number
-- Function for generating random number
--

package body Insa.Random_Number is
   
   -- GetValue
   -- return a random number from 0 to 65535
   function GetValue return RANDOM_VALUE is
      
      function Wrapper_GetValue return RANDOM_VALUE;
      pragma Import (C, Wrapper_GetValue, "RNG_GetValue");
      
   begin
      return Wrapper_GetValue;
   end GetValue; 
   
end Insa.Random_Number;
