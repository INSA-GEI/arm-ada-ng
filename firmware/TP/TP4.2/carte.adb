with Insa , Insa.Keys , Insa.Timer , Insa.Graphics , Insa.Sensors ;
use  Insa , Insa.Keys , Insa.Timer , Insa.Graphics , Insa.Sensors ;

package body Carte is
   
   SeuilEstOuest : constant Integer := 30 ;
   SeuilNordSud : constant Integer := 30 ;
   
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
   
   type T_Valeur_Accelero is array (1..3) of Integer ;
   
   -- Retourne les valeurs des 3 axes de=u magnetometre
   function ObtenirValeursAccelero return T_Valeur_Accelero ;
    
   function ObtenirValeursAccelero return T_Valeur_Accelero is
       Valeurs_Accelero: SENSOR_VALUES;
       Resultat : T_Valeur_Accelero ;
    begin
       Valeurs_Accelero := GetAccelerometerValues;        
       REsultat(1):= Integer(Valeurs_Accelero(1));
       REsultat(2):= Integer(Valeurs_Accelero(2));
       REsultat(3):= Integer(Valeurs_Accelero(3));
       return Resultat ;
    end ObtenirValeursaccelero;
    
   function DetecterDirection return T_Direction is            
      Resultat : T_Direction := Immobile;
      TempsEntree : integer  := TempsEcoule ;
      EstOuest : Integer ;
      NordSud : Integer ;
      
   begin
      EstOuest := Obtenirvaleursaccelero(1);
      NordSud := Obtenirvaleursaccelero(2);
	
      --EcrireEcran(1,1,"X: " & Integer'Image(EstOuest) & "  ");
      --EcrireEcran(1,2,"Y: " & Integer'Image(NordSud) & "  ");

      if abs(EstOuest) > abs(NordSud) then
	 if EstOuest > SeuilEstOuest then
	    Resultat := Ouest ;
	 elsif EstOuest < -SeuilEstOuest then
	    Resultat := Est ;
	 end if;
      else
	 if NordSuD > SeuilNordSud then
	    Resultat := Nord ;
	 elsif NordSuD < -SeuilNordSud then
	    Resultat := Sud ;
	 end if;
      end if;
	 
       while  TempsEcoule - TempsEntree < 1 loop
	  null ;
       end loop ;

      --EcrireEcran(1,3,"R: " & T_Direction'Image(Resultat) & "     ");
      return Resultat ;
   end DetecterDirection ;
    
  
   procedure EffacerEcran is
   begin
      ClearScreen(Navy);
   end EffacerEcran;
   
   procedure EcrireEcran (C : in Integer;L : in Integer;S : in String) is
   begin
      Insa.Graphics.SetTextColor(White);
      Insa.Graphics.SetBackColor(Navy); 
      Insa.Graphics.DrawString(C,L,S);
   end EcrireEcran;
   
end carte ;
