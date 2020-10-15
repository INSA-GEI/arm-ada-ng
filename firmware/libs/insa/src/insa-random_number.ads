-- Package Insa.Random_Number
-- Function for generating random number
--

package Insa.Random_Number is
   pragma Warnings (Off);

   subtype RANDOM_VALUE is INTEGER range 0 .. 65535;
   
   -- GetValue
   -- return a random number from 0 to 65535
   function GetValue return RANDOM_VALUE;
   
end Insa.Random_Number;
