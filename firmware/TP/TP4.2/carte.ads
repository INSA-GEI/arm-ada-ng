package carte is
   
   type T_Direction is (Nord,Sud,Est,Ouest,Immobile) ;
  
   
   -- fonction devant etre appelee imperativement 
   -- au debut de votre programme
   procedure InitialiserCarte ;
   
   -- renvoie la derniere  direction observee par les accelerometres
   function  DetecterDirection return T_Direction ;         
   
    -- Efface un ecran et fixe un fond bleu fonce
   procedure EffacerEcran ;
   
   -- Ecrit la chaine S en blan sur fond bleu fonce
   -- avec le 1er caractere a la colonne C et ligne L
   -- C appartient a [0..39] et L appartient a [0..14]
   procedure EcrireEcran (C : in Integer;L : in Integer;S : in String) ;
   
   TempsEcoule : integer ;
end carte ;
