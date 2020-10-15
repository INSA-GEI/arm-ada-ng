-- Package Insa.Graphics.UI
-- Provide several widgets for creating GUI
--

with Insa.Graphics;

package body Insa.Graphics.UI is
   pragma Warnings (Off);
   
   procedure DrawProgressBar(X: PIXEL_X; Y: PIXEL_Y; W: PIXEL_X; H: PIXEL_Y; Val: PROGRESS_BAR_RANGE; Maxval: PROGRESS_BAR_RANGE) is
      Length: INTEGER;
      Local_Value : PROGRESS_BAR_RANGE;
   begin
      -- Dessin du cadre 
      Insa.Graphics.SetTextColor(Insa.Graphics.Black);
      Insa.Graphics.DrawLine(X,Y,X+W,Y);
      Insa.Graphics.DrawLine(X,Y,X,Y+H);
      Insa.Graphics.DrawLine(X+W,Y,X+W,Y+H);
      Insa.Graphics.DrawLine(X,Y+H,X+W,Y+H);
      
      Local_Value := Val;
      
      if (Local_Value>Maxval) then
         Local_Value := Maxval;
      end if;
      
      -- Dessin du remplissage 
      Length := (Local_Value * (W-4)) / Maxval;
      
      Insa.Graphics.SetTextColor(Insa.Graphics.Blue);
      Insa.Graphics.DrawFillRectangle(X+2, Y+2, (X+2)+Length , (Y+2)+H-4);
      
      Insa.Graphics.SetTextColor(Insa.Graphics.White);
      Insa.Graphics.DrawFillRectangle(X+2+Length+1, Y+2, (X+2+Length)+(W-4)-Length, (Y+2)+ H-4);
   end DrawProgressBar;
   
   procedure DrawCenterBar(X: PIXEL_X; Y: PIXEL_Y; W: PIXEL_X; H: PIXEL_Y; Val: INTEGER; Maxval: POSITIVE);
   pragma Import (C, DrawCenterBar, "GUI_CenterBar");
   
   --  procedure DrawCenterBar(x: PIXEL_X; y: PIXEL_Y; w: PIXEL_X; h: PIXEL_Y; val: INTEGER; maxval: POSITIVE) is
   --     Length1: INTEGER;
   --     Length2: INTEGER;
   --     Length: INTEGER;
   --     Local_Value : INTEGER;
   --  begin
   --     -- Dessin du cadre
   --     Insa.Graphics.SetTextColor(Insa.Graphics.Black);
   --     Insa.Graphics.DrawLine(x,y,x+w,y);
   --     Insa.Graphics.DrawLine(x,y,x,y+h);
   --     Insa.Graphics.DrawLine(x+w,y,x+w,y+h);
   --     Insa.Graphics.DrawLine(x,y+h,x+w,y+h);
      
   --     if Val >= 0 and val >= Maxval then
   --  	Local_Value := maxval-1;
   --     end if;
	  
   --     if Val < 0 and (-val) >= maxval then
   --  	Local_Value := -(maxval-1);
   --     end if;
	  
   --     -- Dessin du remplissage
   --     length1 := (w-4)/2;
   --     length2 := (Local_Value * (w-4)) / maxval;
   --     length2 := length2/2;
   --     length := length1 + length2;
      
   --     Insa.Graphics.SetTextColor(Insa.Graphics.Blue);
   --     Insa.Graphics.DrawFillRectangle(x+2, y+2, (x+2)+ length, (y+2) + h-4);
      
   --     Insa.Graphics.SetTextColor(Insa.Graphics.White);
   --     Insa.Graphics.DrawFillRectangle(x+2+length+1, y+2, (x+2+length+1)+(w-4)-length, (y+2)+h-4);
   --  end DrawCenterBar;
   
   procedure CreateProgressBar(Bar: in out ProgressBar; X: PIXEL_X; Y: PIXEL_Y; W: PIXEL_X; H: PIXEL_Y) is
   begin
      Bar.X :=X;
      Bar.Y :=Y;
      Bar.W :=W;
      Bar.H :=H;

      Bar.Val:=0;
      Bar.Maxval:=PROGRESS_BAR_RANGE'LAST;

      DrawProgressBar(Bar.X, Bar.Y, Bar.W, Bar.H, Bar.Val, Bar.Maxval);
   end CreateProgressBar;

   procedure ProgressBarSetMaximum(Bar: in out ProgressBar; Maxval: PROGRESS_BAR_RANGE) is
   begin
      if Bar.W=0 then
         -- progress bar non initialisée
         raise OBJECT_NOT_INITIALIZED;
      end if;

      Bar.Maxval:=Maxval;
      if Bar.Val > Bar.Maxval then
         Bar.Val := Bar.Maxval;
      end if;

      DrawProgressBar(Bar.X, Bar.Y, Bar.W, Bar.H, Bar.Val, Bar.Maxval);
   end ProgressBarSetMaximum;

   procedure ProgressBarChangeValue(Bar: in out ProgressBar; Val: PROGRESS_BAR_RANGE) is
   begin
      if Bar.W=0 then
         -- progress bar non initialisée
         raise OBJECT_NOT_INITIALIZED;
      end if;
	
      if Bar.Val /= Val then
         Bar.Val:=Val;
         if Bar.Val > Bar.Maxval then
            Bar.Val := Bar.Maxval;
         end if;

         DrawProgressBar(Bar.X, Bar.Y, Bar.W, Bar.H, Bar.Val, Bar.Maxval);
      end if;
	
   end ProgressBarChangeValue;

   -- procedures pour les center bars
   procedure CreateCenterBar(Bar: in out CenterBar; X: PIXEL_X; Y: PIXEL_Y; W: PIXEL_X; H: PIXEL_Y) is
   begin
      Bar.X :=X;
      Bar.Y :=Y;
      Bar.W :=W;
      Bar.H :=H;

      Bar.Val:=0;
      Bar.Maxval:=CENTER_BAR_RANGE'LAST;

      DrawCenterBar(Bar.X, Bar.Y, Bar.W, Bar.H, Bar.Val, Bar.Maxval);
   end CreateCenterBar;

   procedure CenterBarSetMaximum(Bar: in out CenterBar; Maxval: CENTER_BAR_RANGE) is
   begin
      if Bar.W=0 then
         -- progress bar non initialisée
         raise OBJECT_NOT_INITIALIZED;
      end if;

      Bar.Maxval:=Maxval;
      if Bar.Val > Bar.Maxval then
         Bar.Val := Bar.Maxval;
      end if;

      if Bar.Val < -Bar.Maxval then
         Bar.Val := -Bar.Maxval;
      end if;

      DrawCenterBar(Bar.X, Bar.Y, Bar.W, Bar.H, Bar.Val, Bar.Maxval);
   end CenterBarSetMaximum;

   procedure CenterBarChangeValue(Bar: in out CenterBar; Val: INTEGER) is
   begin
      if Bar.W=0 then
         -- progress bar non initialisée
         raise OBJECT_NOT_INITIALIZED;
      end if;
	
      if Bar.Val /= Val then
         Bar.Val:=Val;
         if Bar.Val > Bar.Maxval then
            Bar.Val := Bar.Maxval;
         end if;

         if Bar.Val < -Bar.Maxval then
            Bar.Val := -Bar.Maxval;
         end if;

         DrawCenterBar(Bar.X, Bar.Y, Bar.W, Bar.H, Bar.Val, Bar.Maxval);
      end if;
   end CenterBarChangeValue;
      
   procedure CreateWindow(Title: String; Background: COLOR; TitlebarText: COLOR; TitlebarBgnd: COLOR) is
      Blackbkg: constant String := "                                        ";
   begin
      Insa.Graphics.ClearScreen(Background);
      Insa.Graphics.SetTextColor(TitlebarText);
      Insa.Graphics.SetBackColor(TitlebarBgnd);
      Insa.Graphics.DrawString(0,0,Blackbkg);
      Insa.Graphics.DrawString((40-Title'Length)/2, 0, Title);
   end CreateWindow;
      
end Insa.Graphics.UI;
