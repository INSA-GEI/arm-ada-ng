-- Package Insa.Led
-- Led PWR management
--

package Insa.Led is
   pragma Warnings (Off);

   subtype LED_STATE is INTEGER range 0 .. 1;

   -- Declaration of LED State
   Led_On:	constant LED_STATE := 1;
   Led_Off:	constant LED_STATE := 0;
   
   -- SetLed
   -- Change PWR led depending of provided state (Led_On or Led_Off)
   procedure SetLed(state: LED_STATE);
   
end Insa.Led;
