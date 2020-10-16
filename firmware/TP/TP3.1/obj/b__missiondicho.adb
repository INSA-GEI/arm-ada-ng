pragma Warnings (Off);
pragma Ada_95;
pragma Source_File_Name (ada_main, Spec_File_Name => "b__missiondicho.ads");
pragma Source_File_Name (ada_main, Body_File_Name => "b__missiondicho.adb");
pragma Suppress (Overflow_Check);

package body ada_main is

   E06 : Short_Integer; pragma Import (Ada, E06, "insa_E");
   E08 : Short_Integer; pragma Import (Ada, E08, "insa__graphics_E");
   E10 : Short_Integer; pragma Import (Ada, E10, "insa__graphics__ui_E");
   E15 : Short_Integer; pragma Import (Ada, E15, "insa__keys_E");
   E04 : Short_Integer; pragma Import (Ada, E04, "nombre_E");


   procedure adainit is
   begin
      null;

      E06 := E06 + 1;
      E08 := E08 + 1;
      E10 := E10 + 1;
      E15 := E15 + 1;
      E04 := E04 + 1;
   end adainit;

   procedure Ada_Main_Program;
   pragma Import (Ada, Ada_Main_Program, "_ada_missiondicho");

   procedure main is
      Ensure_Reference : aliased System.Address := Ada_Main_Program_Name'Address;
      pragma Volatile (Ensure_Reference);

   begin
      adainit;
      Ada_Main_Program;
   end;

--  BEGIN Object file/option list
   --   /home/dimercur/Travail/git/arm-ada-ng/firmware/TP/TP3.1/obj/nombre.o
   --   /home/dimercur/Travail/git/arm-ada-ng/firmware/TP/TP3.1/obj/missiondicho.o
   --   -L/home/dimercur/Travail/git/arm-ada-ng/firmware/TP/TP3.1/obj/
   --   -L/home/dimercur/Travail/git/arm-ada-ng/firmware/TP/TP3.1/obj/
   --   -L/home/dimercur/Travail/git/arm-ada-ng/firmware/libs/sys/lib/
   --   -L/home/dimercur/Travail/git/arm-ada-ng/firmware/libs/insa/lib/
   --   -L/home/dimercur/opt/GNAT/2020-arm-elf/arm-eabi/lib/gnat/zfp-armada/adalib/
   --   -static
   --   -lgnat
--  END Object file/option list   

end ada_main;
