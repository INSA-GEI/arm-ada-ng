pragma Warnings (Off);
pragma Ada_95;
pragma Restrictions (No_Exception_Propagation);
with System;
package ada_main is


   GNAT_Version : constant String :=
                    "GNAT Version: Community 2020 (20200818-93)" & ASCII.NUL;
   pragma Export (C, GNAT_Version, "__gnat_version");

   Ada_Main_Program_Name : constant String := "_ada_missiondicho" & ASCII.NUL;
   pragma Export (C, Ada_Main_Program_Name, "__gnat_ada_main_program_name");

   procedure adainit;
   pragma Export (C, adainit, "adainit");

   procedure main;
   pragma Export (C, main, "main");

   --  BEGIN ELABORATION ORDER
   --  ada%s
   --  system%s
   --  ada.exceptions%s
   --  ada.exceptions%b
   --  system.img_int%s
   --  system.img_int%b
   --  insa%s
   --  insa%b
   --  insa.graphics%s
   --  insa.graphics%b
   --  insa.graphics.ui%s
   --  insa.graphics.ui%b
   --  insa.keys%s
   --  insa.keys%b
   --  nombre%s
   --  nombre%b
   --  missiondicho%b
   --  END ELABORATION ORDER

end ada_main;
