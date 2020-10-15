with Tortue, nombre;
use Tortue, nombre;

procedure missionkoch is
   
   procedure Courbe_Koch(Finesse : in Positive; Lg : in Float) is
   begin
      
      if Finesse = 1                 -- cas trivial
      then Avancer(Lg);
      else                           -- cas general
	 Courbe_Koch(Finesse-1, Lg/3.0);
	 Tourner_Gauche(60.0);                
	 
	 Courbe_Koch(Finesse-1, Lg/3.0);
	 Tourner_Droite(120.0);
	 
	 Courbe_Koch(Finesse-1, Lg/3.0);
	 Tourner_Gauche(60.0);
	 
	 Courbe_Koch(Finesse-1, Lg/3.0);
      end if;
   end Courbe_Koch;
   
   procedure Flocon_Koch(Finesse : in Positive; Lg : in Float := 120.0) is
   begin
      
      for Cote in 1..3 loop
	 Courbe_Koch(Finesse, Lg);
	 Tourner_Droite(120.0);      --dans le sens des aiguilles d'une montre
      end loop;
   end Flocon_Koch;
   
   
   Ma_Finesse : Positive ;
begin
	Ma_Finesse := SaisirFinesse ;
		
	Ouvrir_Page;

	Lever_plume;
	Absolue(80, 70);            
	Tourner_Gauche(90.0);      

	Baisser_Plume;

	Flocon_Koch(Ma_Finesse,150.0);

end missionkoch;
