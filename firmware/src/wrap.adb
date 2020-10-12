package body wrap is

   procedure DrawString (X: Interfaces.Unsigned_32; Y: Interfaces.Unsigned_32; Str: String) is

      procedure DrawADAString(x: Interfaces.Unsigned_32; y: Interfaces.Unsigned_32; len: Natural; s: String);
      pragma Import (C, DrawADAString, "GLCD_DrawADAString");
      
   begin
      DrawADAString(X, Y, Str'Length, Str);
   end DrawString;

end wrap;
