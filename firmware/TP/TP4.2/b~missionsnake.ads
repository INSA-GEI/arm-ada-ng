pragma Ada_95;
pragma Warnings (Off);
with System;
package ada_main is

   gnat_argc : Integer;
   gnat_argv : System.Address;
   gnat_envp : System.Address;

   pragma Import (C, gnat_argc);
   pragma Import (C, gnat_argv);
   pragma Import (C, gnat_envp);

   gnat_exit_status : Integer;
   pragma Import (C, gnat_exit_status);

   GNAT_Version : constant String :=
                    "GNAT Version: 6.3.1 20170620 (release) [ARM/embedded-6-branch revision 249437]" & ASCII.NUL;
   pragma Export (C, GNAT_Version, "__gnat_version");

   Ada_Main_Program_Name : constant String := "_ada_missionsnake" & ASCII.NUL;
   pragma Export (C, Ada_Main_Program_Name, "__gnat_ada_main_program_name");

   procedure adainit;
   pragma Export (C, adainit, "adainit");

   procedure adafinal;
   pragma Export (C, adafinal, "adafinal");

   function main
     (argc : Integer;
      argv : System.Address;
      envp : System.Address)
      return Integer;
   pragma Export (C, main, "main");

   type Version_32 is mod 2 ** 32;
   u00001 : constant Version_32 := 16#a143757b#;
   pragma Export (C, u00001, "missionsnakeB");
   u00002 : constant Version_32 := 16#b6df930e#;
   pragma Export (C, u00002, "system__standard_libraryB");
   u00003 : constant Version_32 := 16#f90293f2#;
   pragma Export (C, u00003, "system__standard_libraryS");
   u00004 : constant Version_32 := 16#d90b9106#;
   pragma Export (C, u00004, "ada__exceptionsB");
   u00005 : constant Version_32 := 16#687d7b36#;
   pragma Export (C, u00005, "ada__exceptionsS");
   u00006 : constant Version_32 := 16#3ffc8e18#;
   pragma Export (C, u00006, "adaS");
   u00007 : constant Version_32 := 16#e947e6a9#;
   pragma Export (C, u00007, "ada__exceptions__last_chance_handlerB");
   u00008 : constant Version_32 := 16#41e5552e#;
   pragma Export (C, u00008, "ada__exceptions__last_chance_handlerS");
   u00009 : constant Version_32 := 16#095425b4#;
   pragma Export (C, u00009, "systemS");
   u00010 : constant Version_32 := 16#465d427a#;
   pragma Export (C, u00010, "system__soft_linksB");
   u00011 : constant Version_32 := 16#97d0fde1#;
   pragma Export (C, u00011, "system__soft_linksS");
   u00012 : constant Version_32 := 16#b01dad17#;
   pragma Export (C, u00012, "system__parametersB");
   u00013 : constant Version_32 := 16#777e28cb#;
   pragma Export (C, u00013, "system__parametersS");
   u00014 : constant Version_32 := 16#0f0cb66d#;
   pragma Export (C, u00014, "system__secondary_stackB");
   u00015 : constant Version_32 := 16#a235eadd#;
   pragma Export (C, u00015, "system__secondary_stackS");
   u00016 : constant Version_32 := 16#39a03df9#;
   pragma Export (C, u00016, "system__storage_elementsB");
   u00017 : constant Version_32 := 16#24976fb0#;
   pragma Export (C, u00017, "system__storage_elementsS");
   u00018 : constant Version_32 := 16#41837d1e#;
   pragma Export (C, u00018, "system__stack_checkingB");
   u00019 : constant Version_32 := 16#87eb4e5c#;
   pragma Export (C, u00019, "system__stack_checkingS");
   u00020 : constant Version_32 := 16#87a448ff#;
   pragma Export (C, u00020, "system__exception_tableB");
   u00021 : constant Version_32 := 16#54fa4cf6#;
   pragma Export (C, u00021, "system__exception_tableS");
   u00022 : constant Version_32 := 16#ce4af020#;
   pragma Export (C, u00022, "system__exceptionsB");
   u00023 : constant Version_32 := 16#61374842#;
   pragma Export (C, u00023, "system__exceptionsS");
   u00024 : constant Version_32 := 16#aa0563fc#;
   pragma Export (C, u00024, "system__exceptions_debugB");
   u00025 : constant Version_32 := 16#77dedc70#;
   pragma Export (C, u00025, "system__exceptions_debugS");
   u00026 : constant Version_32 := 16#570325c8#;
   pragma Export (C, u00026, "system__img_intB");
   u00027 : constant Version_32 := 16#0b8fc576#;
   pragma Export (C, u00027, "system__img_intS");
   u00028 : constant Version_32 := 16#39df8c17#;
   pragma Export (C, u00028, "system__tracebackB");
   u00029 : constant Version_32 := 16#5776fb70#;
   pragma Export (C, u00029, "system__tracebackS");
   u00030 : constant Version_32 := 16#9ed49525#;
   pragma Export (C, u00030, "system__traceback_entriesB");
   u00031 : constant Version_32 := 16#090fd3c4#;
   pragma Export (C, u00031, "system__traceback_entriesS");
   u00032 : constant Version_32 := 16#6fd210f2#;
   pragma Export (C, u00032, "system__traceback__symbolicB");
   u00033 : constant Version_32 := 16#dd19f67a#;
   pragma Export (C, u00033, "system__traceback__symbolicS");
   u00034 : constant Version_32 := 16#701f9d88#;
   pragma Export (C, u00034, "ada__exceptions__tracebackB");
   u00035 : constant Version_32 := 16#20245e75#;
   pragma Export (C, u00035, "ada__exceptions__tracebackS");
   u00036 : constant Version_32 := 16#57a37a42#;
   pragma Export (C, u00036, "system__address_imageB");
   u00037 : constant Version_32 := 16#a8b8b88e#;
   pragma Export (C, u00037, "system__address_imageS");
   u00038 : constant Version_32 := 16#8c33a517#;
   pragma Export (C, u00038, "system__wch_conB");
   u00039 : constant Version_32 := 16#12290766#;
   pragma Export (C, u00039, "system__wch_conS");
   u00040 : constant Version_32 := 16#9721e840#;
   pragma Export (C, u00040, "system__wch_stwB");
   u00041 : constant Version_32 := 16#3f382b67#;
   pragma Export (C, u00041, "system__wch_stwS");
   u00042 : constant Version_32 := 16#b96cfbef#;
   pragma Export (C, u00042, "system__wch_cnvB");
   u00043 : constant Version_32 := 16#1d9ebd95#;
   pragma Export (C, u00043, "system__wch_cnvS");
   u00044 : constant Version_32 := 16#4be8ce1b#;
   pragma Export (C, u00044, "interfacesS");
   u00045 : constant Version_32 := 16#ece6fdb6#;
   pragma Export (C, u00045, "system__wch_jisB");
   u00046 : constant Version_32 := 16#9deea4b4#;
   pragma Export (C, u00046, "system__wch_jisS");
   u00047 : constant Version_32 := 16#e66ca570#;
   pragma Export (C, u00047, "carteB");
   u00048 : constant Version_32 := 16#77916842#;
   pragma Export (C, u00048, "carteS");
   u00049 : constant Version_32 := 16#b0988e58#;
   pragma Export (C, u00049, "insaB");
   u00050 : constant Version_32 := 16#34488d3d#;
   pragma Export (C, u00050, "insaS");
   u00051 : constant Version_32 := 16#63b70ccf#;
   pragma Export (C, u00051, "insa__graphicsB");
   u00052 : constant Version_32 := 16#5c6222d3#;
   pragma Export (C, u00052, "insa__graphicsS");
   u00053 : constant Version_32 := 16#f9ad2a59#;
   pragma Export (C, u00053, "insa__keysB");
   u00054 : constant Version_32 := 16#07fddcb9#;
   pragma Export (C, u00054, "insa__keysS");
   u00055 : constant Version_32 := 16#aa0aea3a#;
   pragma Export (C, u00055, "insa__sensorsB");
   u00056 : constant Version_32 := 16#476746fd#;
   pragma Export (C, u00056, "insa__sensorsS");
   u00057 : constant Version_32 := 16#14eb63fd#;
   pragma Export (C, u00057, "insa__timerB");
   u00058 : constant Version_32 := 16#973ffe06#;
   pragma Export (C, u00058, "insa__timerS");
   u00059 : constant Version_32 := 16#4b10a56b#;
   pragma Export (C, u00059, "plateauB");
   u00060 : constant Version_32 := 16#890adae7#;
   pragma Export (C, u00060, "plateauS");
   u00061 : constant Version_32 := 16#84ad4a42#;
   pragma Export (C, u00061, "ada__numericsS");
   u00062 : constant Version_32 := 16#4a9efeb7#;
   pragma Export (C, u00062, "insa__random_numberB");
   u00063 : constant Version_32 := 16#f33621ae#;
   pragma Export (C, u00063, "insa__random_numberS");
   u00064 : constant Version_32 := 16#0ab1cacb#;
   pragma Export (C, u00064, "system__random_numbersB");
   u00065 : constant Version_32 := 16#db11095d#;
   pragma Export (C, u00065, "system__random_numbersS");
   u00066 : constant Version_32 := 16#eef535cd#;
   pragma Export (C, u00066, "system__img_unsB");
   u00067 : constant Version_32 := 16#0bf8bd83#;
   pragma Export (C, u00067, "system__img_unsS");
   u00068 : constant Version_32 := 16#940c8174#;
   pragma Export (C, u00068, "system__unsigned_typesS");
   u00069 : constant Version_32 := 16#7cd2c459#;
   pragma Export (C, u00069, "system__random_seedB");
   u00070 : constant Version_32 := 16#4319909c#;
   pragma Export (C, u00070, "system__random_seedS");
   u00071 : constant Version_32 := 16#5ec405a9#;
   pragma Export (C, u00071, "ada__calendarB");
   u00072 : constant Version_32 := 16#e67a5d0a#;
   pragma Export (C, u00072, "ada__calendarS");
   u00073 : constant Version_32 := 16#769e25e6#;
   pragma Export (C, u00073, "interfaces__cB");
   u00074 : constant Version_32 := 16#61e3d2ff#;
   pragma Export (C, u00074, "interfaces__cS");
   u00075 : constant Version_32 := 16#1d7754d3#;
   pragma Export (C, u00075, "system__arith_64B");
   u00076 : constant Version_32 := 16#02f14e5d#;
   pragma Export (C, u00076, "system__arith_64S");
   u00077 : constant Version_32 := 16#d083f760#;
   pragma Export (C, u00077, "system__os_primitivesB");
   u00078 : constant Version_32 := 16#83db34c2#;
   pragma Export (C, u00078, "system__os_primitivesS");
   u00079 : constant Version_32 := 16#b44f9ae7#;
   pragma Export (C, u00079, "system__val_unsB");
   u00080 : constant Version_32 := 16#84a46c4f#;
   pragma Export (C, u00080, "system__val_unsS");
   u00081 : constant Version_32 := 16#27b600b2#;
   pragma Export (C, u00081, "system__val_utilB");
   u00082 : constant Version_32 := 16#a5f4934a#;
   pragma Export (C, u00082, "system__val_utilS");
   u00083 : constant Version_32 := 16#d1060688#;
   pragma Export (C, u00083, "system__case_utilB");
   u00084 : constant Version_32 := 16#2d5d4c63#;
   pragma Export (C, u00084, "system__case_utilS");
   u00085 : constant Version_32 := 16#fd83e873#;
   pragma Export (C, u00085, "system__concat_2B");
   u00086 : constant Version_32 := 16#0bf4f264#;
   pragma Export (C, u00086, "system__concat_2S");
   u00087 : constant Version_32 := 16#58e7cff7#;
   pragma Export (C, u00087, "system__memoryB");
   u00088 : constant Version_32 := 16#50294380#;
   pragma Export (C, u00088, "system__memoryS");
   u00089 : constant Version_32 := 16#79c5f3ba#;
   pragma Export (C, u00089, "system__crtlS");
   --  BEGIN ELABORATION ORDER
   --  ada%s
   --  interfaces%s
   --  system%s
   --  system.arith_64%s
   --  system.case_util%s
   --  system.case_util%b
   --  system.img_int%s
   --  system.img_int%b
   --  system.os_primitives%s
   --  system.os_primitives%b
   --  system.parameters%s
   --  system.parameters%b
   --  system.crtl%s
   --  system.standard_library%s
   --  system.exceptions_debug%s
   --  system.exceptions_debug%b
   --  system.storage_elements%s
   --  system.storage_elements%b
   --  system.stack_checking%s
   --  system.stack_checking%b
   --  system.traceback_entries%s
   --  system.traceback_entries%b
   --  ada.exceptions%s
   --  system.arith_64%b
   --  system.soft_links%s
   --  system.unsigned_types%s
   --  system.img_uns%s
   --  system.img_uns%b
   --  system.val_uns%s
   --  system.val_util%s
   --  system.val_util%b
   --  system.val_uns%b
   --  system.wch_con%s
   --  system.wch_con%b
   --  system.wch_cnv%s
   --  system.wch_jis%s
   --  system.wch_jis%b
   --  system.wch_cnv%b
   --  system.wch_stw%s
   --  system.wch_stw%b
   --  ada.exceptions.last_chance_handler%s
   --  ada.exceptions.last_chance_handler%b
   --  ada.exceptions.traceback%s
   --  system.address_image%s
   --  system.concat_2%s
   --  system.concat_2%b
   --  system.exception_table%s
   --  system.exception_table%b
   --  ada.numerics%s
   --  interfaces.c%s
   --  system.exceptions%s
   --  system.exceptions%b
   --  ada.calendar%s
   --  ada.calendar%b
   --  system.memory%s
   --  system.memory%b
   --  system.standard_library%b
   --  system.random_numbers%s
   --  system.random_seed%s
   --  system.random_seed%b
   --  system.secondary_stack%s
   --  interfaces.c%b
   --  system.soft_links%b
   --  system.secondary_stack%b
   --  system.random_numbers%b
   --  system.address_image%b
   --  ada.exceptions.traceback%b
   --  system.traceback%s
   --  system.traceback%b
   --  system.traceback.symbolic%s
   --  system.traceback.symbolic%b
   --  ada.exceptions%b
   --  carte%s
   --  insa%s
   --  insa%b
   --  insa.graphics%s
   --  insa.graphics%b
   --  insa.keys%s
   --  insa.keys%b
   --  insa.random_number%s
   --  insa.random_number%b
   --  insa.sensors%s
   --  insa.sensors%b
   --  insa.timer%s
   --  insa.timer%b
   --  carte%b
   --  plateau%s
   --  plateau%b
   --  missionsnake%b
   --  END ELABORATION ORDER


end ada_main;
