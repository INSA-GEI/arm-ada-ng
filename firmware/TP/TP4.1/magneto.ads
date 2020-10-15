with Insa;
use Insa;

package  Magneto is
   
   type COULEUR is range 0 .. 255;
   for COULEUR'Size use 8; 
   
   type T_Valeur_Magneto is array (1..3) of Integer ;
   
   -- Retourne les valeurs des 3 axes de=u magnetometre
   function ObtenirValeursMagneto return T_Valeur_Magneto ;
   
   -- Retourne la partie entiere de la racine carree de N
   function CalculerRacineCarre (N: Integer) return Integer ;
   
   -- fonction bloquante qui attend le 1er evenement entre
   -- soit que 2 secondes se soient ecoulees
   -- soit que l'utilisateur ait appuye sur la touche B
   -- un message s'affiche sur la ligne 10
   -- le boolean est vrai si la touche B a ete appuyee
   function Attendre2secondesOuB return Boolean ;
   
   
   -- efface l'ecran
   procedure EffacerEcran ;
   
   -- ecris sur l'ecran la chaine de caractere S a la ligne L, colonne C 
   procedure EcrireEcran(C : in Integer;L : in Integer;S : in String) ;
   
   -- dessine un rectangle plein de taille d'un caractere de couleur Col
   -- a la ligne L, colonne C
   procedure DessinerEcran (C : in Integer;L : in Integer;Coul : in Integer ) ;
   
   
   -- affiche a l'ecran un message d'attente
   -- blocante jusu'a l'appui de la touche A
   procedure AttendreToucheA ;
   
   -- affiche a l'ecran un message d'attente
   -- blocante jusu'a l'appui de la touche B
   procedure AttendreToucheB;
   
end Magneto ;
