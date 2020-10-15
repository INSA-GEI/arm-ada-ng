-- Package Insa.Graphics
-- Functions for drawing primitives and character string on screen
--

-- pragma Ada_95;

package Insa.Graphics is
   pragma Warnings (Off);

   subtype COLOR is BYTE;
   subtype TEXT_X is INTEGER range 0 .. 39;
   subtype TEXT_Y is INTEGER range 0 .. 14;
   subtype PIXEL_X is INTEGER range 0 .. 319;
   subtype PIXEL_Y is INTEGER range 0 .. 239;
   
   Black: 	constant COLOR := 16#00#;
   Navy: 	constant COLOR := 16#01#;
   DarkGreen: 	constant COLOR := 16#0C#;
   DarkCyan: 	constant COLOR := 16#0D#;
   Maroon: 	constant COLOR := 16#60#;
   Purple: 	constant COLOR := 16#61#;
   Olive: 	constant COLOR := 16#6C#;
   LightGrey: 	constant COLOR := 16#B6#;
   DarkGrey: 	constant COLOR := 16#6D#;
   Blue: 	constant COLOR := 16#03#;
   Green: 	constant COLOR := 16#1C#;
   Cyan: 	constant COLOR := 16#1F#;
   Red: 	constant COLOR := 16#E0#;
   LightRed: 	constant COLOR := 16#EC#;
   Magenta: 	constant COLOR := 16#E3#;
   Yellow: 	constant COLOR := 16#FC#;
   White: 	constant COLOR := 16#FF#;
   
   -- SetTextColor
   -- Set the color used for drawing text (Black, Navy, DrakGreen ...)
   procedure SetTextColor(val: COLOR);
   
   -- SetBackColor
   -- Set the color used for drawing text background (Black, Navy, DrakGreen ...)
   procedure SetBackColor(val: COLOR);
   
   -- SetPenColor
   -- Set the color used for drawing graphic primitives like lines, circles, rectangles
   procedure SetPenColor(val: COLOR);
   
   -- ClearScreen
   -- Empty screen, with background defined 
   procedure ClearScreen(val: COLOR);
   
   -- PutPixel
   -- Draw a single pixel (dot) on screen
   procedure PutPixel (x: PIXEL_X; y: PIXEL_Y; c: COLOR);
   
   -- DrawString
   -- Draw a string on screen, like on a tty display
   procedure DrawString (x: TEXT_X; y: TEXT_Y; s: String);
   
   -- DrawChar
   -- Draw a character on screen, like on a tty display
   procedure DrawChar (x: TEXT_X; y: TEXT_Y; c: Character);
   
   -- DrawLine
   -- Draw a line on screen, from (x1,y1) to (x2,y2) using color defined with SetPenColor
   procedure DrawLine(x1: PIXEL_X; y1: PIXEL_Y; x2: PIXEL_X; y2: PIXEL_Y);
   
   -- DrawRectangle
   -- Draw an empty (only border) rectangle on screen, from (x1,y1) to (x2,y2) using color defined with SetPenColor
   procedure DrawRectangle(x1: PIXEL_X; y1: PIXEL_Y; x2: PIXEL_X; y2: PIXEL_Y);
   
   -- DrawRectangle
   -- Draw a solid filled rectangle on screen, from (x1,y1) to (x2,y2) using color defined with SetPenColor
   procedure DrawFillRectangle(x1: PIXEL_X; y1: PIXEL_Y; x2: PIXEL_X; y2: PIXEL_Y);
   
   -- DrawCircle
   -- Draw an empty (only border) circle on screen, center on (x,y), with radius and using color defined with SetPenColor
   procedure DrawCircle(x: PIXEL_X; y: PIXEL_Y; radius: INTEGER);
   
   -- DrawCircle
   -- Draw a solid filled circle on screen, center on (x,y), with radius and using color defined with SetPenColor
   procedure DrawFillCircle(x: PIXEL_X; y: PIXEL_Y; radius: INTEGER);

end Insa.Graphics;
