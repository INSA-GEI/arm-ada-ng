pragma Warnings (Off);
pragma Ada_95;
pragma Source_File_Name (ada_main, Spec_File_Name => "b__main.ads");
pragma Source_File_Name (ada_main, Body_File_Name => "b__main.adb");
pragma Suppress (Overflow_Check);

package body ada_main is

   E04 : Short_Integer; pragma Import (Ada, E04, "insa_E");
   E06 : Short_Integer; pragma Import (Ada, E06, "insa__graphics_E");
   E08 : Short_Integer; pragma Import (Ada, E08, "last_chance_handler_E");


   procedure adainit is
   begin
      null;

      E04 := E04 + 1;
      E06 := E06 + 1;
      E08 := E08 + 1;
   end adainit;

   procedure Ada_Main_Program;
   pragma Import (Ada, Ada_Main_Program, "_ada_main");

   procedure main is
      Ensure_Reference : aliased System.Address := Ada_Main_Program_Name'Address;
      pragma Volatile (Ensure_Reference);

   begin
      adainit;
      Ada_Main_Program;
   end;

--  BEGIN Object file/option list
   --   /home/dimercur/arm-ada/gnatstudio/proj_1/obj/last_chance_handler.o
   --   /home/dimercur/arm-ada/gnatstudio/proj_1/obj/main.o
   --   -L/home/dimercur/arm-ada/gnatstudio/proj_1/obj/
   --   -L/home/dimercur/arm-ada/gnatstudio/proj_1/obj/
   --   -L/home/dimercur/arm-ada/gnatstudio/sys/lib/
   --   -L/home/dimercur/arm-ada/gnatstudio/insa/lib/
   --   -L/home/dimercur/opt/GNAT/2020-arm-elf/arm-eabi/lib/gnat/zfp-armada/adalib/
   --   -static
   --   -lgnat
--  END Object file/option list   

end ada_main;
