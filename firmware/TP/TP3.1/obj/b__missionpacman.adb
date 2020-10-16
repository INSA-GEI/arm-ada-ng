pragma Warnings (Off);
pragma Ada_95;
pragma Source_File_Name (ada_main, Spec_File_Name => "b__missionpacman.ads");
pragma Source_File_Name (ada_main, Body_File_Name => "b__missionpacman.adb");
pragma Suppress (Overflow_Check);

package body ada_main is

   E06 : Short_Integer; pragma Import (Ada, E06, "insa_E");
   E17 : Short_Integer; pragma Import (Ada, E17, "insa__graphics_E");
   E15 : Short_Integer; pragma Import (Ada, E15, "ecran_E");
   E08 : Short_Integer; pragma Import (Ada, E08, "insa__keys_E");
   E24 : Short_Integer; pragma Import (Ada, E24, "insa__memory_E");
   E22 : Short_Integer; pragma Import (Ada, E22, "insa__graphics__images_E");
   E10 : Short_Integer; pragma Import (Ada, E10, "insa__timer_E");
   E04 : Short_Integer; pragma Import (Ada, E04, "carte_E");
   E25 : Short_Integer; pragma Import (Ada, E25, "sprites_E");
   E20 : Short_Integer; pragma Import (Ada, E20, "lab_E");


   procedure adainit is
   begin
      null;

      E06 := E06 + 1;
      E17 := E17 + 1;
      E15 := E15 + 1;
      E08 := E08 + 1;
      E24 := E24 + 1;
      E22 := E22 + 1;
      E10 := E10 + 1;
      E04 := E04 + 1;
      sprites'elab_spec;
      E25 := E25 + 1;
      Lab'Elab_Body;
      E20 := E20 + 1;
   end adainit;

   procedure Ada_Main_Program;
   pragma Import (Ada, Ada_Main_Program, "_ada_missionpacman");

   procedure main is
      Ensure_Reference : aliased System.Address := Ada_Main_Program_Name'Address;
      pragma Volatile (Ensure_Reference);

   begin
      adainit;
      Ada_Main_Program;
   end;

--  BEGIN Object file/option list
   --   /home/dimercur/Travail/git/arm-ada-ng/firmware/TP/TP1/obj/ecran.o
   --   /home/dimercur/Travail/git/arm-ada-ng/firmware/TP/TP1/obj/carte.o
   --   /home/dimercur/Travail/git/arm-ada-ng/firmware/TP/TP1/obj/sprites.o
   --   /home/dimercur/Travail/git/arm-ada-ng/firmware/TP/TP1/obj/lab.o
   --   /home/dimercur/Travail/git/arm-ada-ng/firmware/TP/TP1/obj/missionpacman.o
   --   -L/home/dimercur/Travail/git/arm-ada-ng/firmware/TP/TP1/obj/
   --   -L/home/dimercur/Travail/git/arm-ada-ng/firmware/TP/TP1/obj/
   --   -L/home/dimercur/Travail/git/arm-ada-ng/firmware/libs/sys/lib/
   --   -L/home/dimercur/Travail/git/arm-ada-ng/firmware/libs/insa/lib/
   --   -L/home/dimercur/opt/GNAT/2020-arm-elf/arm-eabi/lib/gnat/zfp-armada/adalib/
   --   -static
   --   -lgnat
--  END Object file/option list   

end ada_main;
