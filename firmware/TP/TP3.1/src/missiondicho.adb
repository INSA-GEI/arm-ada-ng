with Nombre ;
use Nombre ;

pragma Warnings (Off, "pragma Restrictions (No_Exception_Propagation) in effect");
pragma Warnings (Off, "*may call Last_Chance_Handler");

procedure Missiondicho is
   
   type T_Vecteur is array (Integer range <>) of Natural ;
     
   procedure RechercherValeur (T : in T_Vecteur ; V : in Integer ; Indice : out Positive ;Trouve : out Boolean) is
      Milieu : constant Natural := (T'First+T'Last) / 2 ;
   begin
      if T'Length = 0 then
         Trouve := False ;
      elsif T(Milieu) = V then
         Trouve := True ;
         Indice := Milieu ;
      else
         if V> T(Milieu) then
            RechercherValeur(T(Milieu+1..T'Last),V,Indice,Trouve);
         else
            RechercherValeur(T(T'First..Milieu-1),V,Indice,Trouve);
         end if;
      end if;	 
   end RechercherValeur ;
   
   procedure SaisirVecteur(T: out T_Vecteur) is
     
   begin
      T(T'First) := SaisirNombreCroissant (0) ;
      for I in T'First+1..T'Last loop
         T(I):=SaisirNombreCroissant (T(I-1));
      end loop ;
   end SaisirVecteur ;
   
   procedure AfficherVecteur (T : in T_Vecteur) is
      
   begin
      EcrireEcran(2,4,"Les valeurs sont :");
      EffacerLigne(6);
      for I in T'Range loop
         EcrireEcran(3*I,6,Integer'Image(T(I)));
      end loop;
   end AfficherVecteur;
   
   procedure TesterUnitaire is
      Val       : constant Integer := 8 ;
      
      PasVal    : constant T_Vecteur (1..9) := (1,2,3,4,5,6,7,9,10) ;
      Valbord1  : constant T_Vecteur (1..9) := (0,1,2,3,4,5,6,7,8) ;
      Valbord2  : constant T_Vecteur (1..9) := (8,9,10,11,12,13,14,15,16) ;
      Valmilieu : constant T_Vecteur (1..9) := (4,5,6,7,8,9,10,11,12) ;
      Valbidon  : constant T_Vecteur (1..9) := (6,7,8,9,10,11,12,13,14) ;
      
      type T_Test is array (1..5) of T_Vecteur(1..9) ;
      
      Test : constant T_Test := (1=>PasVal,
                        2=>Valbord1,
                        3=>Valbord2,
                        4=>Valmilieu,
                        5=>Valbidon);
      
      Position : Integer ;
      Present  : Boolean ;   
      
   begin
      EcrireEcran(2,2,"Tests unitaires");
      for I in Test'Range loop
         AfficherVecteur(Test(I));
         RechercherValeur(Test(I),Val,Position,Present);
         if Present then
            EcrireEcran(2,8,"8 se trouve a la position"&Integer'Image(Position));
         else
            EcrireEcran(2,8,"8 n'est pas present");
         end if;
         EcrireEcran(2,10,"Appuyer sur A pour continuer");
         AttendreToucheA;
      end loop;
   end TesterUnitaire ;
      
   procedure TesterLibre is
   
      Position,TailleVecteur,ValeurRecherchee : Integer ;
      Present,Continuer : Boolean ;
      
   begin
      Continuer:=True; 
      while Continuer loop
         EffacerEcran;
         EcrireEcran(2,2,"Test libre : 0 pour arreter");
         TailleVecteur := SaisirTailleVecteur ;
         if TailleVecteur = 0 then
            Continuer := False;
         else
            declare
               Mon_Vecteur : T_Vecteur (1..TailleVecteur);
            begin
               EffacerEcran;
               SaisirVecteur(Mon_Vecteur);
               EffacerEcran;
               EcrireEcran(2,2,"Votre vecteur est :");
               AfficherVecteur(Mon_Vecteur);
               AttendreToucheA;
               ValeurRecherchee := SaisirValeurRecherchee ;
               EffacerEcran;
               AfficherVecteur(Mon_Vecteur);
               RechercherValeur(Mon_Vecteur,ValeurRecherchee,Position,Present);
               if Present then
                  EcrireEcran(2,8,Integer'Image(ValeurRecherchee)& " trouvee a la position "&Integer'Image(Position));
               else
                  EcrireEcran(2,8,Integer'Image(ValeurRecherchee)& " pas trouvee");
               end if;
            end ;
         end if;	 
         AttendreToucheA;
      end loop;   
   end TesterLibre ;
   
   
begin
   EffacerEcran;
   TesterUnitaire ;
   Testerlibre ;   
end Missiondicho;
