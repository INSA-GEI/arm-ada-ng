pragma Warnings (Off);
pragma Ada_95;
pragma Source_File_Name (ada_main, Spec_File_Name => "b__missionsimon.ads");
pragma Source_File_Name (ada_main, Body_File_Name => "b__missionsimon.adb");
pragma Suppress (Overflow_Check);

package body ada_main is

   E07 : Short_Integer; pragma Import (Ada, E07, "insa_E");
   E09 : Short_Integer; pragma Import (Ada, E09, "insa__graphics_E");
   E16 : Short_Integer; pragma Import (Ada, E16, "insa__graphics__ui_E");
   E20 : Short_Integer; pragma Import (Ada, E20, "insa__keys_E");
   E14 : Short_Integer; pragma Import (Ada, E14, "insa__memory_E");
   E11 : Short_Integer; pragma Import (Ada, E11, "insa__graphics__images_E");
   E22 : Short_Integer; pragma Import (Ada, E22, "insa__random_number_E");
   E24 : Short_Integer; pragma Import (Ada, E24, "insa__timer_E");
   E25 : Short_Integer; pragma Import (Ada, E25, "ressources_E");
   E05 : Short_Integer; pragma Import (Ada, E05, "simon_E");


   procedure adainit is
   begin
      null;

      E07 := E07 + 1;
      E09 := E09 + 1;
      E16 := E16 + 1;
      E20 := E20 + 1;
      E14 := E14 + 1;
      E11 := E11 + 1;
      E22 := E22 + 1;
      E24 := E24 + 1;
      ressources'elab_spec;
      E25 := E25 + 1;
      Simon'Elab_Body;
      E05 := E05 + 1;
   end adainit;

   procedure Ada_Main_Program;
   pragma Import (Ada, Ada_Main_Program, "_ada_missionsimon");

   procedure main is
      Ensure_Reference : aliased System.Address := Ada_Main_Program_Name'Address;
      pragma Volatile (Ensure_Reference);

   begin
      adainit;
      Ada_Main_Program;
   end;

--  BEGIN Object file/option list
   --   /home/dimercur/Travail/git/arm-ada-ng/firmware/TP/TP2/obj/ressources.o
   --   /home/dimercur/Travail/git/arm-ada-ng/firmware/TP/TP2/obj/simon.o
   --   /home/dimercur/Travail/git/arm-ada-ng/firmware/TP/TP2/obj/missionsimon.o
   --   -L/home/dimercur/Travail/git/arm-ada-ng/firmware/TP/TP2/obj/
   --   -L/home/dimercur/Travail/git/arm-ada-ng/firmware/TP/TP2/obj/
   --   -L/home/dimercur/Travail/git/arm-ada-ng/firmware/libs/sys/lib/
   --   -L/home/dimercur/Travail/git/arm-ada-ng/firmware/libs/insa/lib/
   --   -L/home/dimercur/opt/GNAT/2020-arm-elf/arm-eabi/lib/gnat/zfp-armada/adalib/
   --   -static
   --   -lgnat
--  END Object file/option list   

end ada_main;
