with Interfaces;

package wrap is

   function Get_Num return Integer;
   pragma Import (C, Get_Num, "get_num");
   
   procedure DrawString (X: Interfaces.Unsigned_32; Y: Interfaces.Unsigned_32; Str: String);

end wrap;
