-- with Insa.Audio.Synthesizer;
-- use Insa.Audio.Synthesizer;

package Simon is
   
   -- ###############################
   -- GESTION SEQUENCE
   -- ###############################
 
   type T_Direction is (Haut_Droit, Haut_Gauche, Bas_Droit, Bas_Gauche, Immobile); 

   type T_Sequence is array (Positive range <>) of T_Direction;
   
   -- Dessine ou Efface un pave 
   procedure DessinerPave (P : T_Direction ; Efface : Boolean);
   
   -- Efface tous les paves
   procedure EffaceTout ;
   
   -- Attend jusqu'a l'appui de la touche A
   -- que l'utilisateur saisisse la taille du vecteur
   -- a l'aide de la valeur du potentiometre de droite
   function SaisirLongueurSequence return Integer;  
      
   -- Genere une sequence aleatoire de la taille de S'Length
   procedure GenererSequence(S : in out T_Sequence);
   
   -- Affiche la sequence S
   procedure AfficherSequence (S : T_Sequence);
   
   -- Faire une petite pause entre 2 séquences (par ex.)
   procedure PetitePause ;
   
   -- ###############################
   -- GESTION TOUCHE 
   -- ###############################   
   
   -- renvoie la derniere touche de direction appuyee de type T_Direction
   function  DetecterDirection return T_Direction;
   
   -- ###############################
   -- GESTION MESSAGES LIBRES ECRAN
   -- ###############################
   
   -- attend un appui sur la touche A
   procedure AttendreToucheA ;
   
   -- Efface un ecran 
   procedure EffacerEcran ;
   
   -- Ecrit la chaine S
   -- avec le 1er caractere a la colonne C et ligne L
   -- C appartient a [0..39] et L appartient a [0..14]
   procedure EcrireEcran (C : in Integer; L : in Integer; S : in String) ;
      
   -- Efface la ligne L de l'ecran
   procedure EffacerLigne (L : in Integer) ;
   

   -- Affiche l'image du simon a l'écran
   procedure AfficherSimon;

   -- Affiche l'ecran "perdu"
   procedure AfficherGameOver;

   -- Affiche l'ecran "gagné"
   procedure AfficherGagne;

   -- effacement de l'ecran à la fin du jeu
   procedure EffaceEcranFinDuJeu;

end Simon ;

