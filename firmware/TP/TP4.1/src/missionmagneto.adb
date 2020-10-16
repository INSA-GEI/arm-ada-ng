with Magneto ;
use Magneto  ;

pragma Warnings (Off, "pragma Restrictions (No_Exception_Propagation) in effect");
pragma Warnings (Off, "*may call Last_Chance_Handler");

procedure Missionmagneto is
   
   type Element ;
   type P_Element is access Element;

   type Element is 
      record
         Norme : Integer;
         Num : Natural;
         Suiv : P_Element;
      end record;
   
   procedure Ajouter_Fin(L : in out P_Element; CM : in Integer ; Num : Integer) is
      Aux, P : P_Element;
   begin
      -- si la liste est vide alors
      -- la creer avec cet element
      if L = null then
         L := new Element'(CM, Num, null);
         -- sinon : il faut se placer a la fin
         -- et ajouter le nouvel element
      else
         -- se placer sur le dernier element
         Aux := L; -- Aux contient au moins 1 element
         while Aux.all.Suiv /= null loop
            Aux := Aux.all.Suiv;
         end loop;
         -- ajouter l element en fin
         P:=new Element'(CM, Num, null);
         Aux.all.Suiv := P;
      end if;
   end Ajouter_Fin;
      
   procedure Ajouter_Croissant_Rec(L : in out P_Element; CM : in Integer; Num : in Natural) is

   begin
      if L = null then
         L := new Element'(CM, Num, null);
      else
         -- si insertion en tete
         if CM <= L.all.Norme then
            L := new Element'(CM, Num, L);
         else 
            Ajouter_Croissant_Rec(L.all.Suiv, CM, Num); 
         end if;
      end if;
   end Ajouter_Croissant_Rec;
   
   procedure Filtrer(L : in P_Element ;  Nb_Val_Filtrees : out Integer ) is
      Aux : P_Element := L;
     
   begin
      Nb_Val_Filtrees := 0 ;
      while Aux /= null loop
         if Aux.all.Suiv /= null then
            if Aux.all.Norme = Aux.all.Suiv.Norme then
               Aux.all.Suiv := Aux.all.Suiv.all.Suiv;
               Nb_Val_Filtrees := Nb_Val_Filtrees + 1;
            else 
               Aux := Aux.all.Suiv; 
            end if;
         else 
            Aux := null;
         end if;	
      end loop;
   end Filtrer;
   
   procedure Enregistrer(L : out P_Element) is
      Val: Integer;
      Valeurs_Magnetometre: T_Valeur_Magneto;
      Num : Natural := 0;
      Continuer : Boolean := True ;
   begin 
      EcrireEcran(1, 10, "Appuyer sur B ");
      EcrireEcran(1, 11, "pour arreter l'enregistrement ");
      L := null; 
      while Continuer loop      
         if Attendre2secondesOuB then
            Continuer := False ;
         else	    
            Valeurs_Magnetometre := ObtenirValeursMagneto;         
            Val := CalculerRacineCarre(Valeurs_Magnetometre(1)**2 + Valeurs_Magnetometre(2)**2 + Valeurs_Magnetometre(3)**2);
            --Ajouter_Fin(L, Val, Num);
            Ajouter_Croissant_Rec(L, Val, Num);
            Num := Num + 1; 
            EcrireEcran(5, 5, "Dernier enregistrement :  " & Integer'Image(Integer(Val))&"    ");
         end if;
      end loop;
   end Enregistrer;
   
   procedure AfficherNPremiers(L : in P_Element; N : in Integer) is
      Aux : P_Element := L;
      Ligne : Integer :=1;      
   begin
      if Aux /=null then
         while Ligne <= N loop	 
            Ligne := Ligne +1 ;
            if Aux/= null then
               EcrireEcran(1 ,Ligne, "Nbr: " & Integer'Image(Aux.all.Num) & ":" &Integer'Image(Aux.all.Norme));
    
               DessinerEcran(15,Ligne,((Aux.all.Norme-L.all.Norme)/4)*4);
               Aux:=Aux.all.Suiv;
            else 
               EcrireEcran(1 ,Ligne,"- - - -");	   
            end if;
         end loop;
      end if;
   end AfficherNPremiers;
   
   procedure AfficherNDerniers(L : in P_Element; N : in out Integer ; Max : in out Integer) is
   begin      	 
      if L /= null then	    
         AfficherNDerniers(L.all.Suiv,N,Max);
         if N= 5 then
            Max := L.all.Norme ;
         end if;
         if N /=0 then	    
            EcrireEcran(1 , 13-(5-N),"Nbr: " & Integer'Image(L.all.Num) & ":" &Integer'Image(L.all.Norme));
            DessinerEcran(15,13-(5-N),((Max-L.all.Norme)/64)*64);
            N:=N-1;
         end if;
      end if;
      if L = null and N <= 0 then
         EcrireEcran(1 , 13-(5-N),"- - - -");
         N := N - 1 ;
      end if;
   end AfficherNDerniers;
   
   procedure Afficher(L : in P_Element) is
      NbreLignesAffichees,Max : Integer :=5 ;
   begin
      EcrireEcran(1,1, "Les 5 premieres valeurs sont ");
      AfficherNPremiers(L,NbreLignesAffichees);
      EcrireEcran(1,8, "Les 5 dernieres valeurs sont ");
      AfficherNDerniers(L,NbreLignesAffichees,Max);
   end Afficher;
   
   La_Liste : P_Element := null;
   Nombre_Valeurs_Supprimees : Integer ;
begin
   EffacerEcran;
   EcrireEcran(2,1,"Enregistreur de champ magnetique");  
   AttendreToucheA;
   loop     
      EffacerEcran;
      EcrireEcran(5, 1, "Appuyer sur B");
      EcrireEcran(5, 2, "pour demarrer l'enregistrement"); 
      AttendreToucheB;
      EffacerEcran;
      Enregistrer(La_Liste);
      EffacerEcran;
      EcrireEcran(2,0,"Liste brute");
      Afficher(La_Liste);
      AttendreToucheA;
      Filtrer(La_Liste,Nombre_Valeurs_Supprimees); 
      EffacerEcran;
      EcrireEcran(2,0,"Liste filtree" &Integer'Image(Nombre_Valeurs_Supprimees)& " valeurs supprimees");
      Afficher(La_Liste);
      AttendreToucheA;
   end loop;
   
end Missionmagneto;
