pragma Warnings (Off);
pragma Ada_95;
pragma Source_File_Name (ada_main, Spec_File_Name => "b__main.ads");
pragma Source_File_Name (ada_main, Body_File_Name => "b__main.adb");
pragma Suppress (Overflow_Check);

package body ada_main is

   E4 : Short_Integer; pragma Import (Ada, E4, "insa_E");
   E6 : Short_Integer; pragma Import (Ada, E6, "insa__graphics_E");


   procedure adainit is
   begin
      null;

      E4 := E4 + 1;
      E6 := E6 + 1;
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
   --   /home/dimercur/Travail/git/arm-ada-ng/firmware/exemples/exceptions/obj/main.o
   --   -L/home/dimercur/Travail/git/arm-ada-ng/firmware/exemples/exceptions/obj/
   --   -L/home/dimercur/Travail/git/arm-ada-ng/firmware/exemples/exceptions/obj/
   --   -L/home/dimercur/Travail/git/arm-ada-ng/firmware/libs/sys/lib/
   --   -L/home/dimercur/Travail/git/arm-ada-ng/firmware/libs/insa/lib/
   --   -L/home/dimercur/opt/GNAT/2020-arm-elf/arm-eabi/lib/gnat/zfp-armada/adalib/
   --   -static
   --   -lgnat
--  END Object file/option list   

end ada_main;
