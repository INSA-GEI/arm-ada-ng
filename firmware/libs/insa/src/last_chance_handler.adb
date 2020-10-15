------------------------------------------------------------------------------
--                                                                          --
--                             GNAT EXAMPLE                                 --
--                                                                          --
--             Copyright (C) 2014, Free Software Foundation, Inc.           --
--                                                                          --
-- GNAT is free software;  you can  redistribute it  and/or modify it under --
-- terms of the  GNU General Public License as published  by the Free Soft- --
-- ware  Foundation;  either version 3,  or (at your option) any later ver- --
-- sion.  GNAT is distributed in the hope that it will be useful, but WITH- --
-- OUT ANY WARRANTY;  without even the  implied warranty of MERCHANTABILITY --
-- or FITNESS FOR A PARTICULAR PURPOSE.                                     --
--                                                                          --
-- As a special exception under Section 7 of GPL version 3, you are granted --
-- additional permissions described in the GCC Runtime Library Exception,   --
-- version 3.1, as published by the Free Software Foundation.               --
--                                                                          --
-- You should have received a copy of the GNU General Public License and    --
-- a copy of the GCC Runtime Library Exception along with this program;     --
-- see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see    --
-- <http://www.gnu.org/licenses/>.                                          --
--                                                                          --
-- GNAT was originally developed  by the GNAT team at  New York University. --
-- Extensive contributions were provided by Ada Core Technologies Inc.      --
--                                                                          --
------------------------------------------------------------------------------
with Insa;
with Insa.Graphics;
with System.Storage_Elements; use System.Storage_Elements;

package body Last_Chance_Handler is

   -------------------------
   -- Last_Chance_Handler --
   -------------------------

   procedure Last_Chance_Handler (Msg : System.Address; Line : Integer) is

      procedure PrintInfo(Addr : System.Address; Line: Integer) is

         function Peek (Addr : System.Address) return Character is
            pragma Warnings (Off);
            C : Character with Address => Addr;
            pragma Warnings (On);
         begin
            return C;
         end Peek;

         Index:Integer:=0;
         A : System.Address := Addr;
      begin
         Insa.Graphics.SetPenColor(Insa.Graphics.LightRed);
         Insa.Graphics.DrawFillRectangle(15,60,305,180);
         Insa.Graphics.SetTextColor(Insa.Graphics.Black);
         Insa.Graphics.SetBackColor(Insa.Graphics.LightRed);
         Insa.Graphics.DrawRectangle(15,60,305,180);
         Insa.Graphics.DrawRectangle(16,61,304,179);
         Insa.Graphics.DrawRectangle(17,62,303,178);

         Insa.Graphics.DrawString(5,5, "-= Uncaught exception raised =-");
         Insa.Graphics.DrawString (10,7, "File : ");

         pragma Warnings (Off);
         while Peek(A) /= ASCII.NUL loop
            Insa.Graphics.DrawChar(18+Index,7,Peek(A));
            A := A + 1;
            Index:=Index+1;
         end loop;
         pragma Warnings (On);

         Insa.Graphics.DrawString (10,8, "Line : " & Integer'Image(Line));
      end PrintInfo;

   begin
      PrintInfo(Msg,Line);
      --  No return procedure.
      pragma Warnings (Off, "*rewritten as loop");
      <<spin>> goto spin;   -- yes, a goto!
      pragma Warnings (On, "*rewritten as loop");
   end Last_Chance_Handler;

end Last_Chance_Handler;
