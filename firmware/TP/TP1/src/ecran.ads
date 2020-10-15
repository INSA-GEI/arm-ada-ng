with Insa , Insa.Graphics  ;
use  Insa , Insa.Graphics  ;

package Ecran is
   
   -- Efface un ecran et fixe un fond bleu fonce
   procedure EffacerEcran ;
   
   -- Ecrit la chaine S en blan sur fond bleu fonce
   -- avec le 1er caractere a la colonne C et ligne L
   -- C appartient a [0..39] et L appartient a [0..14]
   procedure EcrireEcran (C : in Integer;L : in Integer;S : in String) ;
   
end Ecran;
