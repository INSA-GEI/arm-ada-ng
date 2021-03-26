with Insa;
with Insa.Graphics;

pragma Warnings (Off, "pragma Restrictions (No_Exception_Propagation) in effect");
pragma Warnings (Off, "*may call Last_Chance_Handler");

procedure Main is

   procedure TrowException is
      I: Natural:=10;
   begin
      loop
         I:=I-1;
      end loop;
   exception
         when others => Insa.Graphics.DrawString(1,2, "exception in TrowException");
            raise Constraint_Error;
   end TrowException;


   I: Integer:=0;
   Str: constant String:="Ada rules !!";
begin

   Insa.Graphics.DrawString(1,1, Str);

   loop

      begin
         TrowException;
      exception
         when others => Insa.Graphics.DrawString(1,3, "Caught exception!");
            raise Constraint_Error;
      end;

      I:=I+1;

      if I >100 then
         raise Constraint_Error;
      end if;

   end loop;

end Main;
