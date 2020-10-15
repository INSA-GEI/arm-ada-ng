with Plateau , Carte ;
use  Plateau , Carte ;

procedure missionsnake is
   
   PERDU : exception ;
   
   procedure AfficherFinPartie (L : in P_Element ) is
      function CompterElement (L : P_Element) return Integer is
	 Res : Integer :=0 ;
      begin
	 if L/=null then
	    Res :=  1 + CompterElement(L.all.Suiv);
	 end if;
	 return Res ;
      end CompterElement ;
      
   begin
      EffacerEcran ;
      EcrireEcran(2,5," PERDU!");
      EcrireEcran(2,6," Taille du serpent"&Integer'Image(CompterElement(L)));
   end AfficherFinPartie ;
   
   
   procedure EffacerFinListe (L : in P_Element;T : in out T_Table ) is
      Aux : P_Element := L ;
   begin
      if Aux/=null then
	 while Aux.all.Suiv /= null loop
	    Aux:=Aux.all.Suiv ;
	 end loop;
	 T(Aux.Serpent.PosX,Aux.Serpent.PosY):=Vide;
	 DessinerBloc(Aux.Serpent.PosX,Aux.Serpent.PosY,Vide);
      end if;
   end EffacerFinListe ;
   
   procedure AjouterElementEnTete (L: in out P_Element;tete : T_Snake ) is
   begin
      L := new Element'(tete,L);
   end AjouterElementEnTete ;
   
   procedure SupprimerQueue (L: in P_Element) is
      Aux : P_Element := L ;
   begin
      while Aux.all.Suiv.all.Suiv /= null loop
	 Aux:=Aux.all.Suiv;
      end loop;
      EffacerMemoireElement(Aux.all.Suiv);	 
   end SupprimerQueue ;   
   
   procedure GererDeplacement( S : in out P_Element ; T : in out T_Table ; D : in T_Direction ) is
      NouvelleTete : T_Snake ;
   begin
      case D is
	 when Sud =>
	    Nouvelletete :=((S.Serpent.PosX+1) mod 12, S.Serpent.PosY);
	 when Nord =>  
	    Nouvelletete :=((S.Serpent.PosX-1) mod 12,S.Serpent.PosY);
	 when Est => 
	    Nouvelletete :=(S.Serpent.PosX,(S.Serpent.PosY+1) mod 16);
	 when Ouest => 
	    Nouvelletete :=(S.Serpent.PosX,(S.Serpent.PosY-1) mod 16);
	 when others =>
	    null;
      end case ;
      if T(Nouvelletete.PosX,Nouvelletete.PosY) = Snake then
	 raise PERDU ;
      else
	 AjouterElementEnTete(S,Nouvelletete);
      end if;
      if  T(S.Serpent.PosX,S.Serpent.PosY) /= Cerise then
	 EffacerFinListe(S,T);
	 SupprimerQueue(S);
      end if;
     
      T(S.Serpent.PosX,S.Serpent.PosY):=Snake;
      DessinerBloc(S.Serpent.PosX,S.Serpent.PosY,Snake);  
     
   end GererDeplacement ;
   
   Ma_Table : T_Table ;
   Mon_Serpent : P_Element ;
   Ma_Direction : T_Direction ;
   
begin   
   InitialiserCarte ;
   Mon_Serpent := new Element ;
   InitialiserJeu(Ma_Table,Mon_Serpent.Serpent) ;      
   while True loop	 
      Ma_Direction := Carte.DetecterDirection ;
      if Ma_Direction /= Immobile then 
    	 GererDeplacement(Mon_Serpent,Ma_Table,Ma_Direction);	 
      end if;
      Placercerise(Ma_Table);
   end loop;
exception
   when PERDU =>
      AfficherFinPartie(Mon_Serpent);
end missionsnake ;
 
