package Nombre is
   
   -- attend un appui sur la touche A
   procedure AttendreToucheA ;
   
   -- Efface un ecran et fixe un fond bleu fonce
   procedure EffacerEcran ;
   
   -- Ecrit la chaine S
   -- avec le 1er caractere a la colonne C et ligne L
   -- C appartient a [0..39] et L appartient a [0..14]
   procedure EcrireEcran (C : in Integer;L : in Integer;S : in String) ;
   
   
   -- Efface la ligne L de l'ecran
   procedure EffacerLigne (L : in Integer) ;
   
   -- Attend jusqu'a l'appui de la touche A
   -- que l'utilisateur saisisse la taille du vecteur
   -- a l'aide de la valeur du potentiometre de droite
   function SaisirTailleVecteur return Integer  ;
   
   -- Fonction identique a SaisirTailleVecteur
   -- seul le message d'invite change
   function SaisirValeurRecherchee return Integer  ; 
     
   -- Attend jusqu'a l'appui de la touche A
   -- que l'utilisateur saisisse une valeur 
   -- mais dont la plus petite valeur retournee est fixee par 
   -- PlusPetiteValeur 
   -- A vous de l'appeler intelligemment pour s'assurer que
   -- toutes les valeurs du vecteur sont croissantes
   function SaisirNombreCroissant (PlusPetiteValeur : Integer ) return Integer ;
   
   
   ------------------------------------------------------------------------------
   --############################################################################
   -- Complement pour la partie flocon de Koch
   --############################################################################
   
   -- Fonction identique a SaisirTailleVecteur
   -- et SaisirValeurRecherchee
   -- seul le message d'invite change
   function SaisirFinesse return Integer  ; 
   
   
end Nombre ;
