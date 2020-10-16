with Insa;
with Insa.Graphics;

package Tortue is

   -- Utilisation des couleurs du paquetage AdagraphX :
   -- Black, Blue, Green, Cyan, Red, Magenta, Brown,
   -- Light_Gray, Dark_Gray, Light_Blue, Light_Green,
   -- Light_Cyan, Light_Red, Light_Magenta, Yellow, White

   -- Définition d'une exception levée lorsque la tortue sort de l'écran
   Liberte : exception;

   -- procédure permettant l'ouverture d'une fenêtre graphique
   -- => PREMIERE PROCEDURE A UTILISER AVANT DE FAIRE APPEL AUX SUIVANTES DANS LE PROGRAMME DE DESSIN
   -- La tortue est positionnée en haut à gauche, coordonnées (0, 0), la tête vers le bas (orientation = 180°),
   -- plume baissée et prête à dessiner en blanc

   procedure Ouvrir_Page;

   -- procédure permettant la fermeture d'une fenêtre graphique
   -- => DERNIERE PROCEDURE A APPELER AVANT DE QUITTER LE PROGRAMME DE DESSIN
   procedure Fermer_Page;

   -- procédure permettant d'avancer de X unités dans la direction courante et depuis la position actuelle de la tortue
   procedure Avancer(X: in Float);

   -- procédure permettant de reculer de X unités dans la direction courante et depuis la position actuelle de la tortue
   procedure Reculer(X: in Float);

   -- procédure permettant de faire pivoter la position angulaire de la tortue de X degré dans le sens inverse des aiguilles d'une montre
   procedure Tourner_Gauche(X: in Float);

   -- procédure permettant de faire pivoter la position angulaire de la tortue de X degré dans le sens des aiguilles d'une montre
   procedure Tourner_Droite(X: in Float);

   -- procédure permettant de positionner la tortue sur une position angulaire spécifique (valeur X)
   -- X=0 : la tortue est orientée vers le haut
   -- X=90 : la tortue est orientée vers la droite
   -- X=180 : la tortue est orientée vers le bas
   -- X=270 : la tortue est orientée vers la gauche
   procedure Orienter(X: in Float);

   -- procédure permettant de lever la plume de la tortue
   -- => DANS CETTE ETAT AUCUN DEPLACEMENT NE SERA VISIBLE A L'ECRAN
   procedure Lever_Plume;

   -- procédure permettant de lever la plume de la tortue
   -- => DANS CETTE ETAT TOUT DEPLACEMENT LAISSERA UNE TRACE A L'ECRAN
   procedure Baisser_Plume;

   -- procédure permettant de choisir la couleur du tracé
   procedure Choix_Couleur(pen_color: in Insa.Graphics.COLOR);

   -- function retournant l'abscisse (= le numéro de colonne) de la position courante de la tortue
   function Coordonnee_X return Float;

   -- function retournant l'ordonnee (= le numéro de ligne) de la position courante de la tortue
   function Coordonnee_Y return Float;

   -- function retournant la valeur de la position angulaire courante de la tortue
   function Coordonnee_Direction return Float;

   -- function retournant le nombre maximum de lignes qui peut être affiché dans la fenêtre
   function Hauteur_Page return Float;

   -- function retournant le nombre maximum de colonnes qui peut être affiché dans la fenêtre
   function Largeur_Page return Float;

   -- procédure permettant un déplacement de la position courante vers le point (X, Y)
   procedure Absolue(X: in Insa.Graphics.PIXEL_X; Y: in Insa.Graphics.PIXEL_Y);

   -- procédure permettant un déplacement depuis la position courante (point A) vers un point B tel que abscisse(B)-abscisse(A) = X et ordonnee(B)-ordonnee(A) = Y
   procedure Deplacement(X: in Float; Y: in Float);
   
end Tortue;


