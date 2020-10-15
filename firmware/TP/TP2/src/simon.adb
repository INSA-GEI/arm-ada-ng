with Insa, Insa.Graphics, Insa.Graphics.UI, Insa.Keys,Insa.Timer ,Insa.Random_Number; 
use Insa, Insa.Graphics, Insa.Graphics.UI, Insa.Keys, Insa.Timer ,Insa.Random_Number; 

--  with Insa.Graphics.Advanced;
--  use Insa.Graphics.Advanced;

with Insa.Graphics.Images;
use Insa.Graphics.Images;

--  with Insa.Audio.Synthesizer;
--  use Insa.Audio.Synthesizer;

with Ressources;
use Ressources;

pragma Warnings (Off, "pragma Restrictions (No_Exception_Propagation) in effect");
pragma Warnings (Off, "*may call Last_Chance_Handler");

package body Simon is
   
   --  TaillePave : constant Integer := 40 ;
   --  type T_Coord is record
   --     X : Integer ;
   --     Y : Integer ;
   --  end record;
   
   --  CouleurFond     : constant COLOR := White   ;
   --  CouleurHaut     : constant COLOR := Blue  ;
   --  CouleurBas      : constant COLOR := Green  ;
   --  CouleurDroite   : constant COLOR := Red    ;
   --  CouleurGauche   : constant COLOR := Yellow ;
   
   --  PositionCentre  : constant T_Coord := (PIXEL_X'Last/2,PIXEL_Y'Last/2) ;
   --  PositionHaut    : constant T_Coord := (PositionCentre.X + TaillePave,PositionCentre.Y) ;
   --  PositionBas     : constant T_Coord := (PositionCentre.X - TaillePave,PositionCentre.Y) ;
   --  PositionDroite  : constant T_Coord := (PositionCentre.X,PositionCentre.Y + TaillePave) ;
   --  PositionGauche  : constant T_Coord := (PositionCentre.X,PositionCentre.Y - TaillePave) ;
   --  
   T_Bleue : constant INTEGER :=1;
   T_Rouge : constant INTEGER :=2;
   T_Verte : constant INTEGER :=3;
   T_Jaune : constant INTEGER :=4;

   Simon_BG: Image;
   Touches: array (1..4) of IMAGE;
   
   procedure DessinerBlocHautDroit (Efface : Boolean) is
      --  Status: SYNTH_STATUS;

   begin
      if Efface then
         --SetPenColor(White);
         --DrawFillRectangle(0, 0, 
         --		   319,239);
         Drawimage((320-SimonBg.Width)/2, 
                   (240-SimonBg.Height)/2, 
                   Simon_BG);
      else	 
         --  Status:= SYNTH_SetInstrument(0, Guitar_Access);
         --  Status:=SYNTH_NoteOn(0, C3);
         Drawimage(165, 35, 
                   Touches(T_Bleue));
      end if;
   end DessinerBlocHautDroit ;
   
   procedure DessinerBlocBasGauche (Efface : Boolean) is
      --  Status: SYNTH_STATUS;
   begin
      if Efface then
         --SetPenColor(White);
         --DrawFillRectangle(0, 0, 
         --		   319,239);
         Drawimage((320-SimonBg.Width)/2, 
                   (240-SimonBg.Height)/2, 
                   Simon_BG);
      else	 
         --  Status:= SYNTH_SetInstrument(0, Guitar_Access);
         --  Status:=SYNTH_NoteOn(0, A3);
         Drawimage(72, 127, 
                   Touches(T_Rouge));
      end if;
   end DessinerBlocBasGauche ;
   
   procedure DessinerBlocBasDroit (Efface : Boolean) is
      --  Status: SYNTH_STATUS;
   begin
      if Efface then
         --SetPenColor(White);
         --DrawFillRectangle(0, 0, 
         --		   319,239);
         Drawimage((320-SimonBg.Width)/2, 
                   (240-SimonBg.Height)/2, 
                   Simon_BG);
      else	 
         --  Status:= SYNTH_SetInstrument(0, Guitar_Access);
         --  Status:=SYNTH_NoteOn(0, C4);
         Drawimage(165, 127, 
                   Touches(T_Verte));
      end if;
   end DessinerBlocBasDroit ;
   
   procedure DessinerBlocHautGauche (Efface : Boolean) is
      --  Status: SYNTH_STATUS;
   begin
      if Efface then
         --SetPenColor(White);
         --DrawFillRectangle(0, 0, 
         --		   319,239);
         Drawimage((320-SimonBg.Width)/2, 
                   (240-SimonBg.Height)/2, 
                   Simon_BG);
      else	 
         --  Status:= SYNTH_SetInstrument(0, Guitar_Access);
         --  Status:=SYNTH_NoteOn(0, A4);
         Drawimage(74, 35, 
                   Touches(T_Jaune));
      end if;
   end DessinerBlocHautGauche ;
   
   procedure EffacerEcran is
   begin
      ClearScreen(White);
   end EffacerEcran;
   
   procedure EcrireEcran (C : in Integer; L : in Integer; S : in String) is
   begin
      SetTextColor(BLack);
      SetBackColor(White); 
      DrawString(C,L,S);
   end EcrireEcran;
   
   procedure EffacerLigne (L : in Integer) is
   begin
      for I in 0..Text_X'Last loop
         EcrireEcran(I,L," ");
      end loop;
   end EffacerLigne ;   
   
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
   
   function SaisirLongueurSequence return Integer  is
      MyProgressBar : ProgressBar ;
      PotValue: POTENTIOMETER_VALUE;
      Depth: Natural;
      
   begin
      EcrireEcran (2, 4, "Saisissez la taille de la sequence");
      EcrireEcran (2, 11, "Appuyer sur A pour valider");
      CreateProgressBar(MyProgressBar, 50, 100, PIXEL_X'Last-100, 26);
      ProgressBarSetMaximum(MyProgressBar,15);
      
      while GetKeyState(Key_A) /= Key_Pressed loop
         PotValue:=GetPotentiometerValue(Potentiometer_Left);
         Depth := (Integer(PotValue)*15/255);
         ProgressBarChangeValue(MyProgressBar, Depth);
         EcrireEcran (2, 9, Positive'Image(Depth)&"  ");
         Insa.SysDelay(50);
      end loop;   
      
      while GetKeyState(Key_A) = Key_Pressed loop
         null ;
      end loop ;
      
      EffacerEcran;
      return Depth ;
   end SaisirLongueurSequence ;
   
   procedure GenererSequence(S : in out T_Sequence) is
      Pave : Integer ;
   begin 
      for I in S'Range loop
         Pave := GetValue;
	 
         if Pave < Random_Value'Last / 4 then 
            S(I):= Haut_Droit;
         elsif Pave < Random_Value'Last / 2 then
            S(I):= Haut_Gauche;   
         elsif Pave < Random_Value'Last * 3 / 4  then
            S(I):= Bas_Droit; 
         else
            S(I):= Bas_Gauche;    
         end if ;
      end loop;
   end GenererSequence ;
   
   TempsEcoule : Integer := 0;
   AttenteAffichage : constant Integer := 5 ;
   
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
      StopTimer;
   end SuspendreTimer ;
   
   procedure ReprendreTimer is
   begin
      StartTimer;
   end ReprendreTimer ;
   
   procedure Mettreazerotimer is
   begin
      TempsEcoule := 0;
   end Mettreazerotimer ;
   
   function DetecterDirection return T_Direction is
      Resultat : T_Direction ;
      --  TempsEntree : Integer  := TempsEcoule ;
      Valide : Boolean := False ;
      
   begin
      while not Valide loop
         if GetKeyState(Key_Up) = Key_Pressed and GetKeyState(Key_Right) = Key_Pressed then
            Resultat := Haut_Droit ;
            Valide := True ;
         end if; 
	 
         if GetKeyState(Key_Up) = Key_Pressed and GetKeyState(Key_Left) = Key_Pressed then
            Resultat := Haut_Gauche ;
            Valide := True ;
         end if;
	 
         if GetKeyState(Key_Down) = Key_Pressed and GetKeyState(Key_Right) = Key_Pressed then
            Resultat := Bas_Droit ;
            Valide := True ;
         end if;
	 
         if GetKeyState(Key_Down) = Key_Pressed and GetKeyState(Key_Left) = Key_Pressed then
            Resultat := Bas_Gauche ;
            Valide := True ;
         end if;
	 
         if GetKeyState(Key_Down) /= Key_Pressed and GetKeyState(Key_Left) /= Key_Pressed and
           GetKeyState(Key_Up) /= Key_Pressed and GetKeyState(Key_Right) /= Key_Pressed then
            Resultat := Immobile;
            Valide := True ;
         end if;
      end loop;
      
      Mettreazerotimer;
      
      while GetTempsEcoule /= 1 loop
         null;
      end loop;
      
      return Resultat ;
   end DetecterDirection ;
      
   procedure DessinerPave (P: T_Direction; Efface : Boolean) is
   begin
      case P is
      when Haut_Droit   => DessinerBlocHautDroit(Efface);	    
      when Haut_Gauche  => DessinerBlocHautGauche(Efface);
      when Bas_Droit    => DessinerBlocBasDroit(Efface) ;
      when Bas_Gauche   => DessinerBlocBasGauche(Efface) ;
      when others       => null;
      end case;  
   end DessinerPave;   
   
   
   procedure EffaceTout is
   begin
      DessinerPave (Haut_Gauche, True) ;
      DessinerPave (Bas_Gauche, True) ;
      DessinerPave (Haut_Droit, True) ;
      DessinerPave (Bas_Droit, True) ;
   end EffaceTout;
   
   procedure AfficherSequence (S : T_Sequence) is
   begin    
      for I in S'Range loop 
         DessinerPave (S(I),False);
         Mettreazerotimer;
	 
         while  TempsEcoule < AttenteAffichage loop
            null;
         end loop;
	 
         DessinerPave (S(I),True);
         Mettreazerotimer;
	 
         while  TempsEcoule < AttenteAffichage loop
            null;
         end loop;	 
      end loop;
   end AfficherSequence ;
   
   procedure PetitePause is
   begin
      Mettreazerotimer;
      while  TempsEcoule < 2*AttenteAffichage loop
         null ;
      end loop ;
   end PetitePause ;
   
   procedure InitialiserSonetImage is
      --Status: SYNTH_Status;
      --I: INTEGER;
   begin 
      -- Demarrage du synthe
      --  if SYNTH_Start /=SYNTH_SUCCESS then
      --     raise CONSTRAINT_ERROR;
      --  end if;
      --  
      --  Status:=SYNTH_SetMainVolume(200);
      --  I:=0;
      --  
      --  while I<4 loop
      --     Status:=SYNTH_SetVolume(I, 255);
      --     Status:=SYNTH_SetInstrument(I, Guitar_Access);
      --     I:=I+1;
      --  end loop;
      
      null;
   end InitialiserSonetImage;

   procedure AfficherSimon is
   begin     
      --SetLayerDisplayMode(Display_Mode_Transparency);
      --SetLayer(Layer_2);
      
      ClearScreen(White);

      Simon_BG:=Unpackimage(SimonBg);
      Drawimage((320-SimonBg.Width)/2, 
                (240-SimonBg.Height)/2, 

                Simon_BG);

      --SetLayer(Layer_1);
      --SetLayerTransparency(Transparency_100,Transparency_100);
      --SetTransparentColorforBTE(White);
      --ClearScreen (White);

      Touches(T_Bleue):=Unpackimage(Touche_Bleue);
      Touches(T_Rouge):=Unpackimage(Touche_Rouge);
      Touches(T_Verte):=Unpackimage(Touche_Verte);
      Touches(T_Jaune):=Unpackimage(Touche_Jaune);
   end AfficherSimon;

   procedure EffaceEcranFinDuJeu is
   begin
      --SetLayer(Layer_2);
      --ClearScreen(White);
      --SetLayer(Layer_1);
      ClearScreen(White);
   end EffaceEcranFinDuJeu;

   procedure AfficherGameOver is
      --  Status: SYNTH_STATUS;
      --  Stat_MELODY: MELODY_STATUS;

      --  I: INTEGER;
      Gameover_Bg: IMAGE;
      
   begin
      --SetLayer(Layer_1);
      --ClearScreen(Black);

      Gameover_Bg:=Unpackimage(GameOver);
      Drawimage((320-GameOver.Width)/2, 
                (240-GameOver.Height)/2, 
                Gameover_Bg);

      --  if SYNTH_Start =SYNTH_SUCCESS then
      --     Status:=SYNTH_SetMainVolume(200);

      --  I:=0;
      --  while (I<4) loop
      --     Status:= SYNTH_SetVolume(I, 255);               -- Reglage du volume par canal
      --     Status:= SYNTH_SetInstrument(I, Guitar_Access);	-- Parametrage de l'instrument à utiliser par canal
      --  
      --     I:=I+1;
      --  end loop;
      --  
      --  Stat_MELODY:=MELODY_Start(Rip_Melody,Rip.Music_Length);   -- Demarrage de la musique
      --  
      while GetKeyState(Key_A) /= Key_Pressed loop
         null ;
      end loop ;
	 
      while GetKeyState(Key_A) = Key_Pressed loop
         null ;
      end loop;

      --  Stat_MELODY:=MELODY_Stop;
      --  end if;
   end  AfficherGameOver;

   procedure AfficherGagne is
      I: Integer;
      Temps: Integer;

      --  Status: SYNTH_STATUS;
      --  Stat_MELODY: MELODY_STATUS;
      Sprites: array(1..4) of IMAGE;
      
   begin
      --SetLayer(Layer_1);
      
      Sprites(1):=Unpackimage(Fire1);
      Sprites(2):=Unpackimage(Fire2);
      Sprites(3):=Unpackimage(Fire3);
      Sprites(4):=Unpackimage(Fire4);

      Mettreazerotimer;
      ReprendreTimer;

      --  if SYNTH_Start =SYNTH_SUCCESS then
      --     Status:=SYNTH_SetMainVolume(200);
      --  
      --     I:=0;
      --     while (I<4) loop
      --        Status:= SYNTH_SetVolume(I, 255);               -- Reglage du volume par canal
      --        Status:= SYNTH_SetInstrument(I, Sinus_Instr_Access);	-- Parametrage de l'instrument à utiliser par canal
      --  
      --        I:=I+1;
      --     end loop;
      --  
      --     Stat_MELODY:=MELODY_Start(Ymca_Melody,Ymca.Music_Length);   -- Demarrage de la musique
      --  end if;

      I:=1;
      while (GetKeyState(Key_A) /= Key_Pressed) loop
         ClearScreen(Black);

         Temps:= GetTempsEcoule;

         case I is
         when 1 => Drawimage((320-Fire1.Width)/2, 
                             (240-Fire1.Height)/2+50, 
                             Sprites(1));
         when 2 => Drawimage((320-Fire2.Width)/2, 
                             (240-Fire2.Height)/2, 
                             Sprites(2));
         when 3 => Drawimage((320-Fire3.Width)/2, 
                             (240-Fire3.Height)/2, 
                             Sprites(3));
         when others => Drawimage((320-Fire4.Width)/2, 
                                  (240-Fire4.Height)/2,  
                                  Sprites(4));
         end case;

         I:= I+1;
         if I>=5 then
            I:=1;
         end if;

         while Temps+GetTempsEcoule<Temps+6 loop
            null;
         end loop;

         Mettreazerotimer;
         ReprendreTimer;
      end loop;

      SuspendreTimer;
      Mettreazerotimer;
      ReprendreTimer;

      EffaceEcranFinDuJeu;

      --  Stat_MELODY:=MELODY_Stop;

      while GetKeyState(Key_A) = Key_Pressed loop
         null ;
      end loop;
   end AfficherGagne;

begin
   InitialiserCarte ;
   InitialiserSonetImage;
end Simon;
