package wrap is

   function Get_Num return Integer;
   pragma Import (C, Get_Num, "get_num");
   
end wrap;
