-- Package Insa.Timer
-- Management of periodic timer
--
-- Periodic timer generate an event every 100ms
--

package Insa.Timer is
   pragma Warnings (Off);
   
   type TIMER_CALLBACK is access procedure;
      
   TIMER_CALLBACK_NOT_SET: exception;
   
   -- StartTimer
   -- Start periodic timer (period = 100 ms)
   -- Return TIMER_CALLBACK_NOT_SET if not callback was previously registered using SetEventCallBack
   procedure StartTimer;
   
   -- StopTimer
   -- Stop event timer
   procedure StopTimer;
   
   -- SetEventCallBack
   -- register a callback that will be called by periodic timer (period = 100 ms)
   procedure SetEventCallBack(Callback: TIMER_CALLBACK);

end Insa.Timer;
