pragma Warnings (Off);
pragma Ada_95;
pragma Source_File_Name (ada_main, Spec_File_Name => "b__missionsnake.ads");
pragma Source_File_Name (ada_main, Body_File_Name => "b__missionsnake.adb");
pragma Suppress (Overflow_Check);

package body ada_main is

   E09 : Short_Integer; pragma Import (Ada, E09, "insa_E");
   E11 : Short_Integer; pragma Import (Ada, E11, "insa__graphics_E");
   E20 : Short_Integer; pragma Import (Ada, E20, "insa__random_number_E");
   E13 : Short_Integer; pragma Import (Ada, E13, "insa__sensors_E");
   E15 : Short_Integer; pragma Import (Ada, E15, "insa__timer_E");
   E07 : Short_Integer; pragma Import (Ada, E07, "carte_E");
   E18 : Short_Integer; pragma Import (Ada, E18, "plateau_E");


   procedure adainit is
   begin
      null;

      E09 := E09 + 1;
      E11 := E11 + 1;
      E20 := E20 + 1;
      E13 := E13 + 1;
      E15 := E15 + 1;
      E07 := E07 + 1;
      E18 := E18 + 1;
   end adainit;

   procedure Ada_Main_Program;
   pragma Import (Ada, Ada_Main_Program, "_ada_missionsnake");

   procedure main is
      Ensure_Reference : aliased System.Address := Ada_Main_Program_Name'Address;
      pragma Volatile (Ensure_Reference);

   begin
      adainit;
      Ada_Main_Program;
   end;

--  BEGIN Object file/option list
   --   /home/dimercur/Travail/git/arm-ada-ng/firmware/TP/TP4.2/obj/carte.o
   --   /home/dimercur/Travail/git/arm-ada-ng/firmware/TP/TP4.2/obj/plateau.o
   --   /home/dimercur/Travail/git/arm-ada-ng/firmware/TP/TP4.2/obj/missionsnake.o
   --   -L/home/dimercur/Travail/git/arm-ada-ng/firmware/TP/TP4.2/obj/
   --   -L/home/dimercur/Travail/git/arm-ada-ng/firmware/TP/TP4.2/obj/
   --   -L/home/dimercur/Travail/git/arm-ada-ng/firmware/libs/sys/lib/
   --   -L/home/dimercur/Travail/git/arm-ada-ng/firmware/libs/insa/lib/
   --   -L/home/dimercur/opt/GNAT/2020-arm-elf/arm-eabi/lib/gnat/zfp-armada/adalib/
   --   -static
   --   -lgnat
--  END Object file/option list   

end ada_main;
