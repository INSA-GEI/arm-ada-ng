with Insa , Insa.Keys , Insa.Timer;
use  Insa , Insa.Keys , Insa.Timer;

pragma Warnings (Off, "pragma Restrictions (No_Exception_Propagation) in effect");
pragma Warnings (Off, "*may call Last_Chance_Handler");

package body Carte is
   
   TempsEcoule : Integer := 0;
   pragma Volatile (TempsEcoule);

   function GetTempsEcoule return Integer is
   begin
      return TempsEcoule ;
   end GetTempsEcoule ;
   
   procedure TraiterPeriodique is
   begin 
      TempsEcoule := TempsEcoule + 1 ;
   end TraiterPeriodique ;
   
   procedure InitialiserCarte is
   begin      
      TempsEcoule := 0 ;
      SetEventCallBack(TraiterPeriodique'Access);
      StartTimer;
   end InitialiserCarte ;
   
   procedure SuspendreTimer is
   begin
      StopTimer ;
   end SuspendreTimer ;
   
   procedure ReprendreTimer is
   begin
      StartTimer ;
   end ReprendreTimer ;
   
   procedure Mettreazerotimer is
   begin
      TempsEcoule := 0 ;
   end Mettreazerotimer ;
   
   procedure AttendreToucheA is
   begin
      while GetKeyState(Key_A) /= Key_Pressed loop
         null ;
      end loop ;
      while GetKeyState(Key_A) = Key_Pressed loop
         null ;
      end loop ;
   end AttendreToucheA;
   
   function DetecterDirection return T_Direction is
      Resultat : T_Direction := Immobile;
      Compteurtemps : Integer;
   begin
      Compteurtemps := GetTempsEcoule;

      if GetKeyState(Key_Down) = Key_Pressed then
         Resultat := Sud ;
      end if ; 
      if GetKeyState(Key_Up) = Key_Pressed then
         Resultat := Nord ;
      end if ;
      if GetKeyState(Key_Left) = Key_Pressed then
         Resultat := Ouest ;
      end if ;
      if GetKeyState(Key_Right) = Key_Pressed then
         Resultat := Est ;
      end if ;
      
      if Resultat /= Immobile then Compteurtemps := Compteurtemps+2;
      else Compteurtemps := Compteurtemps+1;
      end if;
      --Compteurtemps := Compteurtemps+1;

      while Compteurtemps > GetTempsEcoule loop
         null;
      end loop;
      
      return Resultat ;
   end DetecterDirection ;
   
end Carte ;
