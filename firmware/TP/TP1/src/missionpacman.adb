with Ecran ,  Lab , Carte ;
use  Ecran ,  Lab , Carte ;

pragma Warnings (Off, "pragma Restrictions (No_Exception_Propagation) in effect");
pragma Warnings (Off, "*may call Last_Chance_Handler");

procedure Missionpacman is
   
   DureeJeu : constant Integer := 600; 
   
   procedure AfficherGameOver is
   begin
      EffacerEcran;
      EcrireEcran(12,7,"GAME OVER");
      EcrireEcran(17,10,"Appuyez sur la touche A");
      AttendreToucheA;
      EffacerEcran;
   end AfficherGameOver ;
   
   procedure AfficherVictoire (S : in Integer ) is
   begin
      EffacerEcran;
      EcrireEcran(12,6,"Victoire !");
      EcrireEcran(12,8,"Score : " & Integer'Image(S*4));
      EcrireEcran(17,10,"Appuyez sur la touche A");
      AttendreToucheA;
      EffacerEcran;
   end AfficherVictoire ;
   
   procedure AfficherNombreVies (P : in T_Pacman ; L : in T_Lab) is
   begin
      SuspendreTimer ;
      EffacerEcran;
      EcrireEcran(12,2,"Plus que");
      EcrireEcran(17,5,Integer'Image(P.Nbrevies)&" vie(s)");
      EcrireEcran(17,10,"Appuyez sur la touche A");
      AttendreToucheA;
      EffacerEcran;
      DessinerLabyrinthe(L);
      ReprendreTimer ;
   end AfficherNombreVies ;
   
   function CompterCerise (L : in T_Lab) return Integer is
      Resultat : Integer := 0 ;
   begin
      for I in L'Range(1) loop
         for J in L'Range(2) loop
            if L(I,J) = Cerise then
               Resultat := Resultat +1 ;
            end if;
         end loop ;
      end loop ;
      return Resultat ;
   end CompterCerise ;
   
   procedure GererFinPartie (P : out T_Pacman ; L : out T_Lab) is
   begin
      InitialiserJeu(P,L); 
      Mettreazerotimer ;
   end GererFinPartie ;
   
   procedure GererContactMur (P : in out T_Pacman ; L : in T_Lab ) is
   begin
      P.NbreVies := P.NbreVies -1 ;
      if P.NbreVies > 0 then
         AfficherNombreVies(P,L);
      end if ;      
   end GererContactMur ;
   
   procedure GererDeplacement( P : in out T_Pacman ; L : in out T_Lab ; D : in T_Direction ; NbrC : in out Integer ) is
   begin
      DessinerBloc(P.PosX,P.PosY,Vide);
      L(P.PosX,P.PosY):=Vide;
      case D is
      when Sud =>
         P := (P.PosX,P.PosY+1,P.NbreVies);
      when Nord => 
         P := (P.PosX,P.PosY-1,P.NbreVies);
      when Est =>
         P := (P.PosX+1,P.PosY,P.NbreVies);
      when Ouest =>
         P := (P.PosX-1,P.PosY,P.NbreVies);
      when others =>
         null;
      end case ;
      if  L(P.PosX,P.PosY) = Cerise then
         NbrC := NbrC +1 ;
      end if;
      L(P.PosX,P.PosY):=Pacman;
      DessinerBloc(P.PosX,P.PosY,Pacman, D); 
   end GererDeplacement ;
   
   procedure AfficherTemps is
   begin
      EcrireEcran(32,4,"Decompte");
      --      if Float(DureeJeu-GetTempsEcoule) < 0.2 * Float(DureeJeu) then
      --	 Insa.Graphics.SetTextColor(Red);
      --      end if;
      EcrireEcran(35,6,Integer'Image(DureeJeu-GetTempsEcoule) & "  ");
   end AfficherTemps;
   
   function TesterMur (D: T_Direction ; L : T_Lab ; P : T_Pacman ) return Boolean is
      CestMur : Boolean := False ;
   begin
      if (D = Sud and L(P.PosX,P.PosY+1) = Mur) or
        (D = Nord and L(P.PosX,P.PosY-1) = Mur) or
        (D = Ouest and L(P.PosX-1,P.PosY) = Mur) or
        (D = Est and  L(P.PosX+1,P.PosY) = Mur) then
         CestMur := True ;
      end if;
      return  CestMur ;
   end TesterMur ;
   
   
   Mon_Lab : T_Lab ;
   Mon_PacMan : T_Pacman ;
   Ma_Direction : T_Direction ;
   Mon_Nbre_Cerises_Mangees,Mon_Nbre_Cerises_Depart : Integer := 0 ;
   
begin
   Lab.InitialiserJeu(Mon_PacMan,Mon_Lab);
   Carte.InitialiserCarte ;
   Mon_Nbre_Cerises_Depart := CompterCerise(Mon_Lab);
   while True loop
      while (GetTempsEcoule <= DureeJeu) and (Mon_Nbre_Cerises_Mangees < Mon_Nbre_Cerises_Depart) and  (Mon_PacMan.NbreVies > 0) loop
         AfficherTemps ;	 
         Ma_Direction := Carte.DetecterDirection ;
         if TesterMur(Ma_Direction,Mon_Lab,Mon_PacMan) then
            GererContactMur(Mon_PacMan,Mon_Lab);
         elsif Ma_Direction /= Immobile then
            GererDeplacement(Mon_PacMan,Mon_Lab,Ma_Direction,Mon_Nbre_Cerises_Mangees);
         end if;
      end loop;
      if (GetTempsEcoule > DureeJeu) or (Mon_PacMan.NbreVies <= 0) then
         AfficherGameOver ;
      else
         AfficherVictoire(DureeJeu - GetTempsEcoule) ; 
      end if;
      GererFinPartie(Mon_PacMan,Mon_Lab);
      Mon_Nbre_Cerises_Depart := CompterCerise(Mon_Lab);
      Mon_Nbre_Cerises_Mangees := 0 ;
   end loop ;
   
end Missionpacman ;

