with Carte;
use Carte;

package Lab is
   
   MaxNbreVies : constant Integer := 4 ;
   
   type T_Bloc is (Mur,Vide,Pacman,Cerise) ;
  
   type T_Lab is array (1..10,1..10) of T_Bloc ;
   
   type T_Pacman is record
      PosX :     Integer ;
      PosY :     Integer ;
      NbreVies : Integer ;
   end record ;   
   
   Invalid_Bloc: exception;
   
   -- Efface l'ecran, genere et dessine un labyrinthe
   -- Positionne Pacman avec MaxNbreVies vies au milieu du labyrinthe
   procedure InitialiserJeu (P : out T_Pacman ; L : out T_Lab)  ;
   
   -- Retourne une variable de type T_Lab initialisee avec un labyrinthe
   -- dans lequel un T_Pacman P est place 
   function GenererLabyrinthe(P : T_Pacman) return T_Lab ;
   
   -- Dessine a la Ieme ligne Jeme colonne du labyrinthe un T_Bloc defini par TypeBloc
   procedure DessinerBloc (I,J : Integer ; TypeBloc : T_Bloc) ;
   
   -- Dessine a la Ieme ligne Jeme colonne du labyrinthe un bloc pacman (Pacman_Haut, Pacman_Droit, Pacman_Gauche, Pacman_Bas) 
   -- en fonction de la direction.
   -- Si le bloc n'est pas un bloc pacman, une exception Invalid_Bloc est levée
   procedure DessinerBloc (I,J : Integer ; TypeBloc : T_Bloc; Direction: T_Direction );
   
   -- Dessine un labyrinthe T_Lab defini par L
   procedure DessinerLabyrinthe (L : T_Lab) ;
   
end Lab;



