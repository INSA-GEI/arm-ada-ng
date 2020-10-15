with Insa , Carte, Insa.Graphics, Ada.Unchecked_Deallocation, Ada.Numerics.Discrete_Random, insa.Random_Number ;
use  Insa , Insa.Graphics ;

package body plateau is
   
    TailleSymbole : constant Integer := 20 ;
       
    X_Origine_Lab : constant Integer := 0 ;--20
    Y_Origine_Lab : constant Integer := 0 ;--20
        
    type T_Tableau_Couleur is array (0..14) of COLOR ;
    
    Les_CouleursSnake : constant T_Tableau_Couleur := 
      (Black,Navy,DarkGreen,DarkCyan,Maroon,
       Purple,Olive,LightGrey,DarkGrey,Blue,
       Green,Cyan,Red,Magenta,Yellow);
        
    CouleurMur1 : constant COLOR     := Green;
    CouleurMur2 : constant COLOR     := Darkgreen;
    CouleurVide : constant COLOR     :=  white ;
    CouleurCerise : constant COLOR   := Red ;
    IndexCouleurSnake : Integer := Les_CouleursSnake'First ;
    --CouleurSnake : constant COLOR  := Les_Couleurs(15) ;
   
   procedure DessinerBlocVide(X,Y : Integer) is
   begin
      SetPenColor(CouleurVide) ;
      DrawFillRectangle(X,Y,X+TailleSymbole-1,Y+TailleSymbole-1);
   end DessinerBlocVide ;
      
   procedure DessinerBlocSnake(X,Y : Integer) is
   begin
      DessinerBlocVide(X,Y);
      IndexCouleurSnake := IndexCouleurSnake +1 ;
      SetPenColor(Les_CouleursSnake(IndexCouleurSnake  mod 14)) ;
      DrawFillCircle(X+TailleSymbole/2,Y+TailleSymbole/2,TailleSymbole/2-1);
   end DessinerBlocSnake ;
   
   procedure DessinerBlocCerise(X,Y : Integer) is
   begin
      DessinerBlocVide(X,Y);
      SetPenColor(CouleurCerise) ;
      DrawFillCircle(X+TailleSymbole*2/3,Y+TailleSymbole/3,TailleSymbole/6);
      DrawFillCircle(X+TailleSymbole*2/3,Y+TailleSymbole*2/3,TailleSymbole/6);
   end DessinerBlocCerise ;
   
   
   procedure DessinerMur (X,Y : Integer) is
   begin
      SetPenColor(CouleurMur1) ; 
      DrawFillRectangle(X,Y,X+TailleSymbole,Y+TailleSymbole/2);
      SetPenColor(CouleurMur2) ; 
      DrawFillRectangle(X,Y+TailleSymbole/2,X+TailleSymbole,Y+TailleSymbole);
      
   end DessinerMur;
         
   procedure DessinerBloc (I,J : Integer ; TypeBloc : T_Bloc) is
      X,Y : Integer ;
   begin
      X:= X_Origine_Lab+(J)*TailleSymbole ;
      Y:= Y_Origine_Lab+(I)*TailleSymbole ;
      case TypeBloc is
	 when Mur    => DessinerMur(X,Y);
	 when Vide   => DessinerBlocVide(X,Y);
	 when Cerise => DessinerBlocCerise(X,Y) ;
	 when Snake  => DessinerBlocSnake(X,Y) ;
      end case;
   end DessinerBloc;
   
   procedure DessinerTable (T : T_Table) is
   begin
      for I in T'Range(1) loop
	 for J in T'Range(2) loop
	    DessinerBloc(I,J,T(I,J)) ; 
	 end loop;
      end loop;
   end DessinerTable ;
    
   procedure InitialiserJeu (T: out T_Table ; S: out T_Snake) is 
     
   begin 
      T:= (others => (others => Vide));
      S.Posx := T'First(1)+T'Length(1)/2 ;
      S.PosY := T'First(2)+T'Length(2)/2 ;
      T(S.Posx,S.PosY) := Snake ;
      ClearScreen(White);
      DessinerTable(T);
   end InitialiserJeu ;
   
   procedure EffacerMemoireElement (L : in out P_Element) is
      procedure Liberer_Element is 
          new Ada.Unchecked_Deallocation(Element,P_Element);
   begin
      Liberer_Element(L);
   end EffacerMemoireElement ;
   
   -- Generateur aleatoire entre 0 et 11 :
   subtype Small_Int_Range is Integer range 0..11 ;
   package My_Small_Int_Random is new Ada.Numerics.Discrete_Random( Small_Int_Range ) ;
   use My_Small_Int_Random ;
   
   -- Generateur aleatoire entre 0 et 15 :
   subtype Large_Int_Range is Integer range 0..15 ;
   package My_Large_Int_Random is new Ada.Numerics.Discrete_Random( Large_Int_Range ) ;
   use My_Large_Int_Random ;
   
   --CeriseX : My_Small_Int_Random.Generator ;    
   --CeriseY : My_Large_Int_Random.Generator ;
   -- CeriseX : RANDOM_VALUE;
   -- CeriseY : RANDOM_VALUE;
   procedure PlacerCerise (T:in out T_Table) is
      LocalX,LocalY : Integer ;
   begin
      if Carte.TempsEcoule mod 50 = 0 then
	 --Reset(CeriseX) ;
	 --Reset(CeriseY) ;
	 --Localx:=Random(CeriseX);
	 --LocalY:=Random(CeriseY);
	 Localx := Insa.Random_Number.GetValue*12/65536;
	 if Localx > 11 then Localx :=11;
	 end if;
 
	 Localy := Insa.Random_Number.GetValue*16/65536;
	 if Localy > 15 then Localy :=15;
	 end if;

	 if T(LocalX,LocalY) = Vide then 
	    T(LocalX,LocalY) := Cerise ;	    
	    DessinerBloc(LocalX,LocalY,Cerise) ;
	 end if;
      end if;
   end PlacerCerise ;
  
 end plateau;  
