pragma Warnings (Off);
pragma Ada_95;
pragma Restrictions (No_Exception_Propagation);
with System;
package ada_main is


   GNAT_Version : constant String :=
                    "GNAT Version: Community 2020 (20200818-93)" & ASCII.NUL;
   pragma Export (C, GNAT_Version, "__gnat_version");

   Ada_Main_Program_Name : constant String := "_ada_main" & ASCII.NUL;
   pragma Export (C, Ada_Main_Program_Name, "__gnat_ada_main_program_name");

   procedure adainit;
   pragma Export (C, adainit, "adainit");

   procedure main;
   pragma Export (C, main, "main");

   --  BEGIN ELABORATION ORDER
   --  ada%s
   --  system%s
   --  system.img_int%s
   --  system.img_int%b
   --  system.storage_elements%s
   --  system.storage_elements%b
   --  insa%s
   --  insa%b
   --  insa.graphics%s
   --  insa.graphics%b
   --  last_chance_handler%s
   --  last_chance_handler%b
   --  main%b
   --  END ELABORATION ORDER

end ada_main;
