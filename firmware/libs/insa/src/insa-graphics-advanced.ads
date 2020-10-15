-- Package Insa.Graphics.Advanced
-- Functions for advanced operations on screen like transparency, scroll, ROP and Block Transfert Engine (BTE)
--

-- pragma Ada_95;

with Insa.Memory;
use Insa.Memory;

package Insa.Graphics.Advanced is
   pragma Warnings (Off);

   subtype SCROLL_MODE  is BYTE range 0 .. 2;
   subtype DISPLAY_MODE is BYTE range 0 .. 5;
   subtype TRANSPARENCY is BYTE range 0 .. 8;
   subtype BTE_OPERATION is BYTE range 0 .. 12;
   subtype ROP_FUNCTION is BYTE range 0 .. 15;
   subtype LAYER_ID is BYTE range 0 .. 1;
   subtype DATA_MODE is BYTE range 0 .. 1;
   
   Scroll_Mode_Both:   constant SCROLL_MODE := 0;
   Scroll_Mode_Layer1: constant SCROLL_MODE := 1;
   Scroll_Mode_Layer2: constant SCROLL_MODE := 2;
   
   Display_Mode_Only_Layer1:  constant DISPLAY_MODE := 0;
   Display_Mode_Only_Layer2:  constant DISPLAY_MODE := 1;
   Display_Mode_Lighten:      constant DISPLAY_MODE := 2;
   Display_Mode_Transparency: constant DISPLAY_MODE := 3;
   Display_Mode_Or:           constant DISPLAY_MODE := 4;
   Display_Mode_And:          constant DISPLAY_MODE := 5;
   
   Layer_1:			 constant LAYER_ID := 0;
   Layer_2:			 constant LAYER_ID := 1;
   
   Transparency_100: constant TRANSPARENCY := 0;
   Transparency_88:  constant TRANSPARENCY := 1;
   Transparency_75:  constant TRANSPARENCY := 2;
   Transparency_63:  constant TRANSPARENCY := 3;
   Transparency_50:  constant TRANSPARENCY := 4;
   Transparency_38:  constant TRANSPARENCY := 5;
   Transparency_25:  constant TRANSPARENCY := 6;
   Transparency_12:  constant TRANSPARENCY := 7;
   Transparency_0:   constant TRANSPARENCY := 8;
   
   BTE_Operation_0: constant BTE_OPERATION := 0;
   BTE_Operation_1: constant BTE_OPERATION := 1;
   BTE_Operation_2: constant BTE_OPERATION := 2;
   BTE_Operation_3: constant BTE_OPERATION := 3;
   BTE_Operation_4: constant BTE_OPERATION := 4;
   BTE_Operation_5: constant BTE_OPERATION := 5;
   BTE_Operation_6: constant BTE_OPERATION := 6;
   BTE_Operation_7: constant BTE_OPERATION := 7;
   BTE_Operation_8: constant BTE_OPERATION := 8;
   BTE_Operation_9: constant BTE_OPERATION := 9;
   BTE_Operation_10: constant BTE_OPERATION := 10;
   BTE_Operation_11: constant BTE_OPERATION := 11;
   BTE_Operation_12: constant BTE_OPERATION := 12;
   
   ROP_Function_0: constant ROP_FUNCTION := 0;
   ROP_Function_1: constant ROP_FUNCTION := 1;
   ROP_Function_2: constant ROP_FUNCTION := 2;
   ROP_Function_3: constant ROP_FUNCTION := 3;
   ROP_Function_4: constant ROP_FUNCTION := 4;
   ROP_Function_5: constant ROP_FUNCTION := 5;
   ROP_Function_6: constant ROP_FUNCTION := 6;
   ROP_Function_7: constant ROP_FUNCTION := 7;
   ROP_Function_8: constant ROP_FUNCTION := 8;
   ROP_Function_9: constant ROP_FUNCTION := 9;
   ROP_Function_10: constant ROP_FUNCTION := 10;
   ROP_Function_11: constant ROP_FUNCTION := 11;
   ROP_Function_12: constant ROP_FUNCTION := 12;
   ROP_Function_13: constant ROP_FUNCTION := 13;
   ROP_Function_14: constant ROP_FUNCTION := 14;
   ROP_Function_15: constant ROP_FUNCTION := 15;
   
   Linear_Mode: constant DATA_MODE := 1;
   Block_Mode: constant DATA_MODE := 0;
   
   -- SetScrollMode
   -- Set scrolling mode for layer 1 and 2
   procedure SetScrollMode(mode: SCROLL_MODE);
   
   -- SetScrollWindow
   -- Define window area for scrolling current layer
   procedure SetScrollWindow(x: PIXEL_X; y: PIXEL_Y; width: PIXEL_X; height: PIXEL_Y);
   
   -- ScrollVertical
   -- Scroll current layer in defined window (see SetScrollWindow) for a delta number of pixel
   procedure ScrollVertical(d: PIXEL_Y);
   
   -- ScrollHorizontal
   -- Scroll current layer in defined window (see SetScrollWindow) for a delta number of pixel
   procedure ScrollHorizontal(d: PIXEL_X);
   
   -- SetLayerDisplayMode
   -- Set display mode between layer 1 and layer 2
   procedure SetLayerDisplayMode(mode: DISPLAY_MODE);
   
   -- SetLayerTransparency
   -- Define amount of transparency for each layer, Disable means black and no transparency, 100% mean no transparency at all
   -- lower value means more transaprency
   procedure SetLayerTransparency(layer1: TRANSPARENCY; Layer2: TRANSPARENCY);
   
   -- SetLayer
   -- Define which layer to draw to
   procedure SetLayer(layer: LAYER_ID);
   
   -- Under this line, functions are about BTE (Block Transfert Engine), a way of copying block of pixel for layer to layer
   -- In graphic programming, it is related to BitBlt (Bit Blitting)
   
   -- SetBTESource
   -- Set source coordinates for a block transfert 
   procedure SetBTESource(x: PIXEL_X; y: PIXEL_Y; layer: LAYER_ID);
   
   -- SetBTEDestination
   -- Set destination coordinates for a block transfert
   procedure SetBTEDestination (x: PIXEL_X; y: PIXEL_Y; layer: LAYER_ID);
   
   -- SetBTESize
   -- Set block size
   procedure SetBTESize (width: PIXEL_X; height: PIXEL_Y);
   
   -- SetBackgroundColorforBTE
   -- Define background color used in certain BTE operations
   procedure SetBackgroundColorforBTE (red: INTEGER; green: INTEGER; blue: INTEGER);
   
   -- SetForegroundColorforBTE
   -- Define foreground color used in certain BTE operations
   procedure SetForegroundColorforBTE (red: INTEGER; green: INTEGER; blue: INTEGER);
   
   -- SetPatternNumberforBTE
   -- Define which pattern to use during a block transfert (only for certain BTE operation)
   procedure SetPatternNumberforBTE(pattern: BYTE);
   
   -- SetTransparentColorforBTE
   -- define which color must be used as transparent during a block transfert (only for certain BTE operation)
   procedure SetTransparentColorforBTE(c: COLOR);
   
   -- StartBTE
   -- Start a block transfert, using source and destination coordinates and color or pattern already defined
   -- source_mode and dest_mode allow to select between a linear presentation of data or a block presentation
   -- rop is used to select ROP function to be applied when copying block (see documentation for rop functions, page 85)
   -- operation is used to select BTE operation for block transfert (see documentation page 84)
   procedure StartBTE(source_mode: DATA_MODE; dest_mode: DATA_MODE; rop: ROP_FUNCTION; operation: BTE_OPERATION);

   -- StartBTEAndFillFromSRAM
   -- Start a block transfert, using source and destination coordinates and color or pattern already defined
   -- dest_mode allow to select between a linear presentation of data or a block presentation
   -- rop is used to select ROP function to be applied when copying block (see documentation for rop functions, page 85)
   -- operation is used to select BTE operation for block transfert (see documentation page 84)
   -- Then provide data from external RAM (SRAM)
   procedure StartBTEAndFillFromSRAM(dest_mode: DATA_MODE; rop: ROP_FUNCTION; operation: BTE_OPERATION; addr: MEMORY_ADDRESS; size: INTEGER);
end Insa.Graphics.Advanced;
