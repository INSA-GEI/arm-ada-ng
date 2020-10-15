with Insa, Insa.Graphics, Insa.Graphics.UI, Insa.Keys;
use Insa, Insa.Graphics, Insa.Graphics.UI, Insa.Keys; 

package body Nombre is
   
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
   
   function SaisirTailleVecteur return Integer  is
      MyProgressBar : ProgressBar ;
      potValue: POTENTIOMETER_VALUE;
      Depth: Natural;
      
   begin
      EcrireEcran (2, 4, "Saisissez la taille du vecteur");
      EcrireEcran (2, 11, "Appuyer sur A pour valider");
      CreateProgressBar(myProgressBar, 50, 100, PIXEL_X'Last-100, 26);
      ProgressBarSetMaximum(myProgressBar,15);
      while GetKeyState(Key_A) /= Key_Pressed loop
	 potValue:=GetPotentiometerValue(Potentiometer_Left);
	 Depth := (Positive(Potvalue)*15/255);
	 ProgressBarChangeValue(myProgressBar, Depth);
	 EcrireEcran (2, 9, Positive'Image(Depth)&"  ");
	 Insa.SysDelay(50);
      end loop;   
       while GetKeyState(Key_A) = Key_Pressed loop
	 null ;
      end loop ;
      return Depth ;
   end SaisirTailleVecteur ;

   function SaisirValeurRecherchee return Integer  is
      MyProgressBar : ProgressBar ;
      potValue: POTENTIOMETER_VALUE;
      Depth: Natural;
   begin
      EcrireEcran (2, 8, "Saisissez la valeur recherchee");
      EcrireEcran (2, 14, "Appuyer sur A pour valider");
      CreateProgressBar(myProgressBar, 50, 160, PIXEL_X'Last-100, 18);
      ProgressBarSetMaximum(myProgressBar,15);
      while GetKeyState(Key_A) /= Key_Pressed loop
	 potValue:=GetPotentiometerValue(Potentiometer_Left);
	 Depth := (Positive(Potvalue)*15/255);
	 ProgressBarChangeValue(myProgressBar, Depth);	 
	 EcrireEcran (6, 12, Positive'Image(Depth)&"  ");	 
	 Insa.SysDelay(50);
      end loop;  
       while GetKeyState(Key_A) = Key_Pressed loop
	 null ;
      end loop ;
      return Depth ;
   end SaisirValeurRecherchee;
   
   function SaisirNombreCroissant (PlusPetiteValeur : Integer ) return Integer  is
      MyProgressBar : ProgressBar ;
      potValue: POTENTIOMETER_VALUE;
      Depth: Natural;
   begin
      EffacerEcran ;
      EcrireEcran (2, 4, "Saisissez votre valeur");
      EcrireEcran (2, 14, "Appuyer sur A pour valider");
      CreateProgressBar(myProgressBar, 50, 100, PIXEL_X'Last-100, 26);
      ProgressBarSetMaximum(myProgressBar,15);
      while GetKeyState(Key_A) /= Key_Pressed loop
	 potValue:=GetPotentiometerValue(Potentiometer_Left);
	 Depth := (Positive(Potvalue)*15/255)+PlusPetiteValeur;
	 ProgressBarChangeValue(myProgressBar, Depth);
	 EcrireEcran (2, 9, Positive'Image(Depth)&"  ");	 
	 Insa.SysDelay(50);
      end loop;   
       while GetKeyState(Key_A) = Key_Pressed loop
	 null ;
      end loop ;
      return Depth ;
   end SaisirNombreCroissant ;
   
   
     function SaisirFinesse return Integer  is
      MyProgressBar : ProgressBar ;
      potValue: POTENTIOMETER_VALUE;
      Depth: Positive;
      
   begin
      EcrireEcran (2, 4, "Saisissez la finesse de Koch");
      EcrireEcran (2, 14, "Appuyer sur A pour valider");
      CreateProgressBar(myProgressBar, 50, 100, PIXEL_X'Last-100, 26);
      ProgressBarSetMaximum(myProgressBar,11);
      while GetKeyState(Key_A) /= Key_Pressed loop
	 potValue:=GetPotentiometerValue(Potentiometer_Left);
	 Depth := (Positive(Potvalue)*10/255+1);
	 ProgressBarChangeValue(myProgressBar, Depth);
	 EcrireEcran (2, 9, Positive'Image(Depth)&"  ");
	 Insa.SysDelay(50);
      end loop;
       while GetKeyState(Key_A) = Key_Pressed loop
	 null ;
      end loop ;
      return Depth ;
   end SaisirFinesse ;
   
end Nombre;
