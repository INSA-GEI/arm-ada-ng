-- Package Insa.Graphics.Advanced
-- Functions for drawing primitives and character string on screen
--

-- pragma Ada_95;

-- with Insa.Graphics;
-- use Insa.Graphics;

package body Insa.Graphics.Advanced is
   
   -- SetScrollMode
   -- Set scrolling mode for layer 1 and 2
   procedure SetScrollMode(mode: SCROLL_MODE) is
      procedure Wrapper_SetScrollMode(mode: SCROLL_MODE);
      pragma Import (C, Wrapper_SetScrollMode, "GLCD_LayerScrollMode");
   begin
      Wrapper_SetScrollMode(mode);
   end SetScrollMode;
   
   -- SetScrollWindow
   -- Define window area for scrolling current layer
   procedure SetScrollWindow(x: PIXEL_X; y: PIXEL_Y; width: PIXEL_X; height: PIXEL_Y) is
      procedure Wrapper_SetScrollWindow(x: PIXEL_X; y: PIXEL_Y; width: PIXEL_X; height: PIXEL_Y);
      pragma Import (C, Wrapper_SetScrollWindow, "GLCD_SetScrollWindow");
   begin
      Wrapper_SetScrollWindow(x, y, width, height);
   end SetScrollWindow;
   
   -- ScrollVertical
   -- Scroll current layer in defined window (see SetScrollWindow) for a delta number of pixel
   procedure ScrollVertical(d: PIXEL_Y) is
      procedure Wrapper_ScrollVertical(d: PIXEL_Y);
      pragma Import (C, Wrapper_ScrollVertical, "GLCD_ScrollVertical");
   begin
      Wrapper_ScrollVertical(d);
   end ScrollVertical;
   
   -- ScrollHorizontal
   -- Scroll current layer in defined window (see SetScrollWindow) for a delta number of pixel
   procedure ScrollHorizontal(d: PIXEL_X) is
      procedure Wrapper_ScrollHorizontal(d: PIXEL_X);
      pragma Import (C, Wrapper_ScrollHorizontal, "GLCD_ScrollHorizontal");
   begin
      Wrapper_ScrollHorizontal(d);
   end ScrollHorizontal;
   
   -- SetLayerDisplayMode
   -- Set display mode between layer 1 and layer 2
   procedure SetLayerDisplayMode(mode: DISPLAY_MODE) is
      procedure Wrapper_SetLayerDisplayMode(mode: DISPLAY_MODE);
      pragma Import (C, Wrapper_SetLayerDisplayMode, "GLCD_LayerDisplayMode");
   begin
      Wrapper_SetLayerDisplayMode(mode);
   end SetLayerDisplayMode;
   
   -- SetLayerTransparency
   -- Define amount of transparency for each layer, Disable means black and no transparency, 100% mean no transparency at all
   -- lower value means more transaprency
   procedure SetLayerTransparency(layer1: TRANSPARENCY; layer2: TRANSPARENCY) is
      procedure Wrapper_SetLayerTransparency(layer1: TRANSPARENCY; layer2: TRANSPARENCY);
      pragma Import (C, Wrapper_SetLayerTransparency, "GLCD_LayerTransparency");
   begin
      Wrapper_SetLayerTransparency(layer1, layer2);
   end SetLayerTransparency;
   
   -- SetLayer
   -- Define which layer to draw to
   procedure SetLayer(layer: LAYER_ID) is
      procedure Wrapper_SetLayer(layer: LAYER_ID);
      pragma Import (C, Wrapper_SetLayer, "GLCD_SetLayer");
   begin
      Wrapper_SetLayer(layer);
   end SetLayer;
   
   -- Under this line, functions are about BTE (Block Transfert Engine), a way of copying block of pixel for layer to layer
   -- In graphic programming, it is related to BitBlt (Bit Blitting)
   
   -- SetBTESource
   -- Set source coordinates for a block transfert 
   procedure SetBTESource(x: PIXEL_X; y: PIXEL_Y; layer: LAYER_ID) is
      procedure Wrapper_SetBTESource(x: PIXEL_X; y: PIXEL_Y; layer: LAYER_ID);
      pragma Import (C, Wrapper_SetBTESource, "GLCD_BTESetSource");
   begin
      Wrapper_SetBTESource(x, y, layer);
   end SetBTESource;
   
   -- SetBTEDestination
   -- Set destination coordinates for a block transfert
   procedure SetBTEDestination (x: PIXEL_X; y: PIXEL_Y; layer: LAYER_ID) is
      procedure Wrapper_SetBTEDestination(x: PIXEL_X; y: PIXEL_Y; layer: LAYER_ID);
      pragma Import (C, Wrapper_SetBTEDestination, "GLCD_BTESetDestination");
   begin
      Wrapper_SetBTEDestination(x, y, layer);
   end SetBTEDestination;
   
   -- SetBTESize
   -- Set block size
   procedure SetBTESize (width: PIXEL_X; height: PIXEL_Y) is
      procedure Wrapper_SetBTESize(width: PIXEL_X; height: PIXEL_Y);
      pragma Import (C, Wrapper_SetBTESize, "GLCD_BTESetSize");
   begin
      Wrapper_SetBTESize(width, height);
   end SetBTESize;
   
   -- SetBackgroundColorforBTE
   -- Define background color used in certain BTE operations
   procedure SetBackgroundColorforBTE (red: INTEGER; green: INTEGER; blue: INTEGER) is
      procedure Wrapper_SetBackgroundColorforBTE(red: INTEGER; green: INTEGER; blue: INTEGER);
      pragma Import (C, Wrapper_SetBackgroundColorforBTE, "GLCD_BTESetBackgroundColor");
   begin
      Wrapper_SetBackgroundColorforBTE(red, green, blue);
   end SetBackgroundColorforBTE;
   
   -- SetForegroundColorforBTE
   -- Define foreground color used in certain BTE operations
   procedure SetForegroundColorforBTE (red: INTEGER; green: INTEGER; blue: INTEGER) is
      procedure Wrapper_SetForegroundColorforBTE(red: INTEGER; green: INTEGER; blue: INTEGER);
      pragma Import (C, Wrapper_SetForegroundColorforBTE, "GLCD_BTESetForegroundColor");
   begin
      Wrapper_SetForegroundColorforBTE(red, green, blue);
   end SetForegroundColorforBTE;
   
   -- SetPatternNumberforBTE
   -- Define which pattern to use during a block transfert (only for certain BTE operation)
   procedure SetPatternNumberforBTE(pattern: BYTE) is
      procedure Wrapper_SetPatternNumberforBTE(pattern: BYTE);
      pragma Import (C, Wrapper_SetPatternNumberforBTE, "GLCD_BTESetPatternNumber");
   begin
      Wrapper_SetPatternNumberforBTE(pattern);
   end SetPatternNumberforBTE;
   
   -- SetTransparentColorforBTE
   -- define which color must be used as transparent during a block transfert (only for certain BTE operation)
   procedure SetTransparentColorforBTE(c: COLOR) is
      procedure Wrapper_SetTransparentColorforBTE(c: COLOR);
      pragma Import (C, Wrapper_SetTransparentColorforBTE, "GLCD_SetTransparentColor");
   begin
      Wrapper_SetTransparentColorforBTE(c);
   end SetTransparentColorforBTE;
   
   -- StartBTE
   -- Start a block transfert, using source and destination coordinates and color or pattern already defined
   -- source_mode and dest_mode allow to select between a linear presentation of data or a block presentation
   -- rop is used to select ROP function to be applied when copying block (see documentation for rop functions, page 85)
   -- operation is used to select BTE operation for block transfert (see documentation page 84)
   procedure StartBTE(source_mode: DATA_MODE; dest_mode: DATA_MODE; rop: ROP_FUNCTION; operation: BTE_OPERATION) is
      procedure Wrapper_StartBTE(source_mode: DATA_MODE; dest_mode: DATA_MODE; rop: ROP_FUNCTION; operation: BTE_OPERATION);
      pragma Import (C, Wrapper_StartBTE, "GLCD_BTEStart");
   begin
      Wrapper_StartBTE(source_mode, dest_mode, rop, operation);
   end StartBTE;
   
   -- StartBTEAndFillFromSRAM
   -- Start a block transfert, using source and destination coordinates and color or pattern already defined
   -- dest_mode allow to select between a linear presentation of data or a block presentation
   -- rop is used to select ROP function to be applied when copying block (see documentation for rop functions, page 85)
   -- operation is used to select BTE operation for block transfert (see documentation page 84)
   -- Then provide data from external RAM (SRAM)
   procedure StartBTEAndFillFromSRAM(dest_mode: DATA_MODE; rop: ROP_FUNCTION; operation: BTE_OPERATION; addr: MEMORY_ADDRESS; size: INTEGER) is
      procedure Wrapper_StartBTEAndFillFromSRAM(dest_mode: DATA_MODE; rop: ROP_FUNCTION; operation: BTE_OPERATION; addr: MEMORY_ADDRESS; size: INTEGER);
      pragma Import (C, Wrapper_StartBTEAndFillFromSRAM, "GLCD_BTEStartAndFillFromSRAM");
   begin
      Wrapper_StartBTEAndFillFromSRAM(dest_mode, rop, operation, addr, size);
   end StartBTEAndFillFromSRAM;   
end Insa.Graphics.Advanced;
