-- Package Insa.Timer
-- Management of periodic timer
--
-- Periodic timer generate an event every 100ms
--

package body Insa.Timer is
   type CtoADA_TIMER_CALLBACK is access procedure;
   pragma Convention(C, CtoADA_TIMER_CALLBACK);
   
   Event_Callback: TIMER_CALLBACK:=null;
   procedure CtoADATimerCallback;
   pragma Convention(C, CtoADATimerCallback);
   
   procedure CtoADATimerCallback is
   begin
      pragma Warnings (Off);
      Event_Callback.all;
      pragma Warnings (On);
   end CtoADATimerCallback;
   
   -- StartTimer
   -- Start periodic timer (period = 100 ms)
   -- Return TIMER_CALLBACK_NOT_SET if not callback was previously registered using SetEventCallBack
   procedure StartTimer is
      
     function Wrapper_StartTimer return Integer;
     pragma Import (C, Wrapper_StartTimer, "TIMER_Start");
      
   begin
      if Wrapper_StartTimer = 0 then -- timer non demarré / callback pas initialisé
         pragma Warnings (Off);
         raise TIMER_CALLBACK_NOT_SET;
         pragma Warnings (On);
      end if;
   end StartTimer;
   
   -- StopTimer
   -- Stop event timer
   procedure StopTimer is
      
     procedure Wrapper_StopTimer;
     pragma Import (C, Wrapper_StopTimer, "TIMER_Stop");
     
   begin
      Wrapper_StopTimer;
   end StopTimer;
   
   -- SetEventCallBack
   -- register a callback that will be called by periodic timer (period = 100 ms)
   procedure SetEventCallBack(Callback: TIMER_CALLBACK) is
      
     procedure Wrapper_SetEventCallBack(SysCallback: CtoADA_TIMER_CALLBACK);
     pragma Import (C, Wrapper_SetEventCallBack, "TIMER_SetEventCallback");
     
   begin
      Wrapper_SetEventCallBack(CtoADATimerCallback'access);
      Event_Callback := Callback;
   end SetEventCallBack;
   
end Insa.Timer;
