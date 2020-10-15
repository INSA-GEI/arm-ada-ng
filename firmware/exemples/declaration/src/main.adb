with Insa;
with Insa.Graphics;

pragma Warnings (Off, "pragma Restrictions (No_Exception_Propagation) in effect");
pragma Warnings (Off, "*may call Last_Chance_Handler");

procedure Main is

   type Vector is array (Integer range <>) of Integer;
   Size: Integer;
   I: Integer;
begin

   Size:= 10;
   I:=1;

   declare
      MyArray: Vector(1..Size);
   begin

      while I<11 loop
         MyArray(I):=I*I;
         Insa.Graphics.DrawString(10,I,Integer'Image(I) & " => " & Integer'Image(MyArray(I)));

         I:=I+1;

      end loop;
   end;

end Main;
