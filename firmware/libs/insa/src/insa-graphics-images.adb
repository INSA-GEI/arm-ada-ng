-- Package Insa.Graphics.Image
-- Functions for unpacking and drawing image bitmap on screen
--
with Ada;
with Ada.Unchecked_Deallocation;

package body Insa.Graphics.Images is
   pragma Warnings (Off);
   
   -- NewImage
   -- Create a new, empty image with a given width and height
   function NewImage(W: NATURAL; H: NATURAL) return IMAGE is
      Img: IMAGE;
   begin 
      Img.Data := new BITMAP(0..(W*H)-1);
      Img.Width := W;
      Img.Height := H;
      
      return Img;
   end NewImage;
   
   -- FreeImage
   -- Destroy an image and free memory used
   procedure FreeImage (Img: in out IMAGE) is
      procedure Free_BMP is new Ada.Unchecked_Deallocation (BITMAP, BITMAP_ACCESS);
      Bmp_Ptr: BITMAP_ACCESS := Img.Data;
   begin
      Free_BMP(BMP_Ptr);
      Img.Data :=null;
   end FreeImage; 
   
   -- DrawImage
   -- Draw an image at position (x,y) on screen
   procedure DrawImage(x: PIXEL_X; y: PIXEL_Y; Img: IMAGE) is
      procedure Wrapper_DrawImage(Bmp_ptr: BITMAP_ACCESS; x: NATURAL; y: NATURAL; W: NATURAL; H:NATURAL);
      pragma Import (C, Wrapper_DrawImage, "GLCD_DrawImage");
   begin
      Wrapper_DrawImage(Img.Data, NATURAL(x), NATURAL(y), Img.Width, Img.Height);
   end DrawImage;
   
   -- DrawImageFromSRAM
   -- Draw an image, stored in SRAM, at position (x,y) on screen
   procedure DrawImageFromSRAM(x: PIXEL_X; y: PIXEL_Y; W: NATURAL; H: NATURAL; addr: MEMORY_ADDRESS) is
      procedure Wrapper_DrawImageFromSRAM(addr: MEMORY_ADDRESS; x: NATURAL; y: NATURAL; W: NATURAL; H:NATURAL);
      pragma Import (C, Wrapper_DrawImageFromSRAM, "GLCD_DrawImagefromSRAM");
   begin
      Wrapper_DrawImageFromSRAM(addr, NATURAL(x), NATURAL(y), NATURAL(W), NATURAL(H));
   end DrawImageFromSRAM;

   -- UnpackImage
   -- Unpack a compressed image to an usable image
   function UnpackImage(Pack_Img: PACK_IMAGE) return IMAGE is
      Img: IMAGE;
      Index: NATURAL:=0;
   begin
      Img:=NewImage(Pack_Img.Width,Pack_Img.Height);
      
      for I in Pack_Img.Data'Range loop
	 for X in 0 .. Pack_Img.Data(I).Length-1 loop
	    Img.Data(Index+Natural(X)):=Pack_Img.Data(I).Pixel;
	 end loop;
	 
	 Index:=Index + NATURAL(Pack_Img.Data(I).Length);
      end loop;
      
      return Img;
   end UnpackImage;
   
   -- UnpackImageToSRAM
   -- Unpack a compressed image to an usable image directly into SRAM
   procedure UnpackImageToSRAM(Pack_Img: PACK_IMAGE; addr: MEMORY_ADDRESS) is
      Index: MEMORY_ADDRESS:=addr;
   begin
      for I in Pack_Img.Data'Range loop
	 for X in 0 .. Pack_Img.Data(I).Length-1 loop
	    --Img.Data(Index+Natural(X)):=Pack_Img.Data(I).Pixel;
	    WriteByte(Index+MEMORY_ADDRESS(X), MEMORY_BYTE(Pack_Img.Data(I).Pixel));
	 end loop;
	 
	 Index:=Index + MEMORY_ADDRESS(Pack_Img.Data(I).Length);
      end loop;
   end UnpackImageToSRAM;

end Insa.Graphics.Images;
