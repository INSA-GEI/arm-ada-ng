-- Package Insa.Graphics.UI
-- Provide several widgets for creating GUI
--

package Insa.Graphics.UI is
   pragma Warnings (Off);

   subtype PROGRESS_BAR_RANGE is INTEGER range 0 .. 255;
   subtype CENTER_BAR_RANGE is POSITIVE;

   type ProgressBar is 
      record
         x: PIXEL_X:=0; 
         y: PIXEL_Y:=0; 
         w: PIXEL_X:=0; 
         h: PIXEL_Y:=0;
         val: PROGRESS_BAR_RANGE :=PROGRESS_BAR_RANGE'FIRST; 
         maxval: PROGRESS_BAR_RANGE:=PROGRESS_BAR_RANGE'LAST;
      end record; 
	   
   type CenterBar is 
      record
         x: PIXEL_X:=0; 
         y: PIXEL_Y:=0; 
         w: PIXEL_X:=0; 
         h: PIXEL_Y:=0;
         val: INTEGER :=0; 
         maxval: CENTER_BAR_RANGE:=CENTER_BAR_RANGE'LAST;
      end record; 

   OBJECT_NOT_INITIALIZED: exception;

   -- procedures pour les progress bars
   procedure CreateProgressBar(bar: in out ProgressBar; x: PIXEL_X; y: PIXEL_Y; w: PIXEL_X; h: PIXEL_Y);
   procedure ProgressBarSetMaximum(bar: in out ProgressBar; maxval: PROGRESS_BAR_RANGE);
   procedure ProgressBarChangeValue(bar: in out ProgressBar; val: PROGRESS_BAR_RANGE);

   -- procedures pour les center bars
   procedure CreateCenterBar(bar: in out CenterBar; x: PIXEL_X; y: PIXEL_Y; w: PIXEL_X; h: PIXEL_Y);
   procedure CenterBarSetMaximum(bar: in out CenterBar; maxval: CENTER_BAR_RANGE);
   procedure CenterBarChangeValue(bar: in out CenterBar; val: INTEGER);
   
   -- Creation de fenetres
   procedure CreateWindow(Title: String; Background: COLOR; TitlebarText: COLOR; TitlebarBgnd: COLOR);
end Insa.Graphics.UI;
