-- Package Insa.Led
-- Led PWR management
--

package body Insa.Led is
   
   -- SetLed
   -- Change PWR led depending of provided state (Led_On or Led_Off)
   procedure SetLed(state: LED_STATE) is
      
      procedure Wrapper_SetLed(state: LED_STATE);
      pragma Import (C, Wrapper_SetLed, "LED_Set");
      
   begin
      Wrapper_SetLed(State);
   end SetLed; 
   
end Insa.Led;
