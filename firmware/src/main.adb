with Last_Chance_Handler;  pragma Unreferenced (Last_Chance_Handler);
with Wrap;

procedure Main is
   I: Integer:=0;
   Str: constant String:="Ada rules !!";
   Str2: constant String:="Do not print";
begin
   I:=Wrap.Get_Num;

   Wrap.DrawString(1,1, Str);

   loop
      I:=I+1;

      if I >100 then
         I:=0;
      end if;

   end loop;

end Main;
