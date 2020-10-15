-- TP pointeurs (3 séances)
-- DAMERY JC 2015

with Insa;
with Insa.Graphics;
with Insa.Graphics.UI;
with Insa.Sensors;
with Insa.Keys;

with Ada.Numerics.Elementary_Functions;
with Ada.Text_Io , Ada.Float_Text_Io , Ada.Integer_Text_Io;
use Ada.Text_Io , Ada.Float_Text_Io , Ada.Integer_Text_Io;

use Insa;
use Insa.Graphics;
use Insa.Graphics.UI;
use Insa.Sensors;
use Insa.Keys;
use Ada.Numerics.Elementary_Functions;


package body Magneto is   
   
    function ObtenirValeursMagneto return T_Valeur_Magneto is
       Valeurs_Magnetometre: SENSOR_VALUES;
       Resultat : T_Valeur_Magneto ;
    begin
       Valeurs_Magnetometre := GetMagneticValues;        
       REsultat(1):= Integer(Valeurs_Magnetometre(1));
       REsultat(2):= Integer(Valeurs_Magnetometre(2));
       REsultat(3):= Integer(Valeurs_Magnetometre(3));
       return Resultat ;
    end ObtenirValeursMagneto;
    
    function CalculerRacineCarre (N: Integer) return Integer is
    begin
       return Integer(Sqrt(float(N)));
    end CalculerRacineCarre ;
    
    function Attendre2secondesOuB return Boolean is
       Compteur : Natural := 0;
    begin
       while (GetKeyState(KEY_B) /= Key_Pressed) and Compteur < 4 loop
	  DrawString(10, 7, "Enregistrement -");
	  Insa.SysDelay(100); -- Attente
	  DrawString(10, 7, "Enregistrement \");
	  Insa.SysDelay(100); -- Attente
	  DrawString(10, 7, "Enregistrement |");
	  Insa.SysDelay(100); -- Attente
	  DrawString(10, 7, "Enregistrement /");
	  Insa.SysDelay(100); -- Attente
	  Compteur := Compteur +1 ;
       end loop ;
       return GetKeyState(KEY_B) = Key_Pressed ;
    end Attendre2secondesOuB ;
    
    procedure EffacerEcran is
   begin
      ClearScreen(white);
   end EffacerEcran;
   
   procedure EcrireEcran (C : in Integer;L : in Integer;S : in String) is
   begin
      SetTextColor(BLack);
      SetBackColor(white); 
      DrawString(C,L,S);
   end EcrireEcran;
   
   procedure DessinerEcran (C : in Integer;L : in Integer;Coul : in Integer ) is
      Coul_Loc : Integer;
   begin
      Coul_Loc := Coul;
      
      if Coul_Loc > 255 then
	 Coul_Loc := 255;
      end if;
      
      if Coul_Loc <0 then
	 Coul_Loc := 0;
      end if;
      
      SetPenColor(Color(Coul_Loc));
      DrawFillRectangle(C*8,L*16,C*8+8,L*16+16);
      SetTextColor(Black);
   end DessinerEcran ;
   
    procedure AttendreToucheA is
   begin
      EcrireEcran(2,Text_Y'LAST,"Appuyer sur A pour continuer");
      while GetKeyState(Key_A) /= Key_Pressed loop
	 null ;
      end loop ;
      while GetKeyState(Key_A) = Key_Pressed loop
	 null ;
      end loop ;
   end AttendreToucheA;
   
   procedure AttendreToucheB is
   begin
      while GetKeyState(Key_B) /= Key_Pressed loop
	 null ;
      end loop ;
      while GetKeyState(Key_B) = Key_Pressed loop
	 null ;
      end loop ;
   end AttendreToucheB;
       
end Magneto ;
