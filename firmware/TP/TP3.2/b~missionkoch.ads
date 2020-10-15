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

   Ada_Main_Program_Name : constant String := "_ada_missionkoch" & ASCII.NUL;
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
   u00001 : constant Version_32 := 16#4f2219d1#;
   pragma Export (C, u00001, "missionkochB");
   u00002 : constant Version_32 := 16#b6df930e#;
   pragma Export (C, u00002, "system__standard_libraryB");
   u00003 : constant Version_32 := 16#f90293f2#;
   pragma Export (C, u00003, "system__standard_libraryS");
   u00004 : constant Version_32 := 16#09d61ec0#;
   pragma Export (C, u00004, "nombreB");
   u00005 : constant Version_32 := 16#115c374f#;
   pragma Export (C, u00005, "nombreS");
   u00006 : constant Version_32 := 16#b0988e58#;
   pragma Export (C, u00006, "insaB");
   u00007 : constant Version_32 := 16#34488d3d#;
   pragma Export (C, u00007, "insaS");
   u00008 : constant Version_32 := 16#63b70ccf#;
   pragma Export (C, u00008, "insa__graphicsB");
   u00009 : constant Version_32 := 16#5c6222d3#;
   pragma Export (C, u00009, "insa__graphicsS");
   u00010 : constant Version_32 := 16#dba6bfea#;
   pragma Export (C, u00010, "insa__graphics__uiB");
   u00011 : constant Version_32 := 16#5d46fcf6#;
   pragma Export (C, u00011, "insa__graphics__uiS");
   u00012 : constant Version_32 := 16#d90b9106#;
   pragma Export (C, u00012, "ada__exceptionsB");
   u00013 : constant Version_32 := 16#687d7b36#;
   pragma Export (C, u00013, "ada__exceptionsS");
   u00014 : constant Version_32 := 16#3ffc8e18#;
   pragma Export (C, u00014, "adaS");
   u00015 : constant Version_32 := 16#e947e6a9#;
   pragma Export (C, u00015, "ada__exceptions__last_chance_handlerB");
   u00016 : constant Version_32 := 16#41e5552e#;
   pragma Export (C, u00016, "ada__exceptions__last_chance_handlerS");
   u00017 : constant Version_32 := 16#095425b4#;
   pragma Export (C, u00017, "systemS");
   u00018 : constant Version_32 := 16#465d427a#;
   pragma Export (C, u00018, "system__soft_linksB");
   u00019 : constant Version_32 := 16#97d0fde1#;
   pragma Export (C, u00019, "system__soft_linksS");
   u00020 : constant Version_32 := 16#b01dad17#;
   pragma Export (C, u00020, "system__parametersB");
   u00021 : constant Version_32 := 16#777e28cb#;
   pragma Export (C, u00021, "system__parametersS");
   u00022 : constant Version_32 := 16#0f0cb66d#;
   pragma Export (C, u00022, "system__secondary_stackB");
   u00023 : constant Version_32 := 16#a235eadd#;
   pragma Export (C, u00023, "system__secondary_stackS");
   u00024 : constant Version_32 := 16#39a03df9#;
   pragma Export (C, u00024, "system__storage_elementsB");
   u00025 : constant Version_32 := 16#24976fb0#;
   pragma Export (C, u00025, "system__storage_elementsS");
   u00026 : constant Version_32 := 16#41837d1e#;
   pragma Export (C, u00026, "system__stack_checkingB");
   u00027 : constant Version_32 := 16#87eb4e5c#;
   pragma Export (C, u00027, "system__stack_checkingS");
   u00028 : constant Version_32 := 16#87a448ff#;
   pragma Export (C, u00028, "system__exception_tableB");
   u00029 : constant Version_32 := 16#54fa4cf6#;
   pragma Export (C, u00029, "system__exception_tableS");
   u00030 : constant Version_32 := 16#ce4af020#;
   pragma Export (C, u00030, "system__exceptionsB");
   u00031 : constant Version_32 := 16#61374842#;
   pragma Export (C, u00031, "system__exceptionsS");
   u00032 : constant Version_32 := 16#aa0563fc#;
   pragma Export (C, u00032, "system__exceptions_debugB");
   u00033 : constant Version_32 := 16#77dedc70#;
   pragma Export (C, u00033, "system__exceptions_debugS");
   u00034 : constant Version_32 := 16#570325c8#;
   pragma Export (C, u00034, "system__img_intB");
   u00035 : constant Version_32 := 16#0b8fc576#;
   pragma Export (C, u00035, "system__img_intS");
   u00036 : constant Version_32 := 16#39df8c17#;
   pragma Export (C, u00036, "system__tracebackB");
   u00037 : constant Version_32 := 16#5776fb70#;
   pragma Export (C, u00037, "system__tracebackS");
   u00038 : constant Version_32 := 16#9ed49525#;
   pragma Export (C, u00038, "system__traceback_entriesB");
   u00039 : constant Version_32 := 16#090fd3c4#;
   pragma Export (C, u00039, "system__traceback_entriesS");
   u00040 : constant Version_32 := 16#6fd210f2#;
   pragma Export (C, u00040, "system__traceback__symbolicB");
   u00041 : constant Version_32 := 16#dd19f67a#;
   pragma Export (C, u00041, "system__traceback__symbolicS");
   u00042 : constant Version_32 := 16#701f9d88#;
   pragma Export (C, u00042, "ada__exceptions__tracebackB");
   u00043 : constant Version_32 := 16#20245e75#;
   pragma Export (C, u00043, "ada__exceptions__tracebackS");
   u00044 : constant Version_32 := 16#57a37a42#;
   pragma Export (C, u00044, "system__address_imageB");
   u00045 : constant Version_32 := 16#a8b8b88e#;
   pragma Export (C, u00045, "system__address_imageS");
   u00046 : constant Version_32 := 16#8c33a517#;
   pragma Export (C, u00046, "system__wch_conB");
   u00047 : constant Version_32 := 16#12290766#;
   pragma Export (C, u00047, "system__wch_conS");
   u00048 : constant Version_32 := 16#9721e840#;
   pragma Export (C, u00048, "system__wch_stwB");
   u00049 : constant Version_32 := 16#3f382b67#;
   pragma Export (C, u00049, "system__wch_stwS");
   u00050 : constant Version_32 := 16#b96cfbef#;
   pragma Export (C, u00050, "system__wch_cnvB");
   u00051 : constant Version_32 := 16#1d9ebd95#;
   pragma Export (C, u00051, "system__wch_cnvS");
   u00052 : constant Version_32 := 16#4be8ce1b#;
   pragma Export (C, u00052, "interfacesS");
   u00053 : constant Version_32 := 16#ece6fdb6#;
   pragma Export (C, u00053, "system__wch_jisB");
   u00054 : constant Version_32 := 16#9deea4b4#;
   pragma Export (C, u00054, "system__wch_jisS");
   u00055 : constant Version_32 := 16#f9ad2a59#;
   pragma Export (C, u00055, "insa__keysB");
   u00056 : constant Version_32 := 16#07fddcb9#;
   pragma Export (C, u00056, "insa__keysS");
   u00057 : constant Version_32 := 16#fd83e873#;
   pragma Export (C, u00057, "system__concat_2B");
   u00058 : constant Version_32 := 16#0bf4f264#;
   pragma Export (C, u00058, "system__concat_2S");
   u00059 : constant Version_32 := 16#3d7bc4a0#;
   pragma Export (C, u00059, "tortueB");
   u00060 : constant Version_32 := 16#0919aee4#;
   pragma Export (C, u00060, "tortueS");
   u00061 : constant Version_32 := 16#84ad4a42#;
   pragma Export (C, u00061, "ada__numericsS");
   u00062 : constant Version_32 := 16#03e83d1c#;
   pragma Export (C, u00062, "ada__numerics__elementary_functionsB");
   u00063 : constant Version_32 := 16#00443200#;
   pragma Export (C, u00063, "ada__numerics__elementary_functionsS");
   u00064 : constant Version_32 := 16#0cdfa324#;
   pragma Export (C, u00064, "ada__numerics__auxS");
   u00065 : constant Version_32 := 16#6c05c057#;
   pragma Export (C, u00065, "system__exn_llfB");
   u00066 : constant Version_32 := 16#b52a9e68#;
   pragma Export (C, u00066, "system__exn_llfS");
   u00067 : constant Version_32 := 16#512139a0#;
   pragma Export (C, u00067, "system__fat_fltS");
   u00068 : constant Version_32 := 16#940c8174#;
   pragma Export (C, u00068, "system__unsigned_typesS");
   u00069 : constant Version_32 := 16#c1a106e2#;
   pragma Export (C, u00069, "ada__text_ioB");
   u00070 : constant Version_32 := 16#e701a999#;
   pragma Export (C, u00070, "ada__text_ioS");
   u00071 : constant Version_32 := 16#10558b11#;
   pragma Export (C, u00071, "ada__streamsB");
   u00072 : constant Version_32 := 16#2e6701ab#;
   pragma Export (C, u00072, "ada__streamsS");
   u00073 : constant Version_32 := 16#db5c917c#;
   pragma Export (C, u00073, "ada__io_exceptionsS");
   u00074 : constant Version_32 := 16#920eada5#;
   pragma Export (C, u00074, "ada__tagsB");
   u00075 : constant Version_32 := 16#13ca27f3#;
   pragma Export (C, u00075, "ada__tagsS");
   u00076 : constant Version_32 := 16#c3335bfd#;
   pragma Export (C, u00076, "system__htableB");
   u00077 : constant Version_32 := 16#8d96965e#;
   pragma Export (C, u00077, "system__htableS");
   u00078 : constant Version_32 := 16#089f5cd0#;
   pragma Export (C, u00078, "system__string_hashB");
   u00079 : constant Version_32 := 16#2fc8fd20#;
   pragma Export (C, u00079, "system__string_hashS");
   u00080 : constant Version_32 := 16#b44f9ae7#;
   pragma Export (C, u00080, "system__val_unsB");
   u00081 : constant Version_32 := 16#84a46c4f#;
   pragma Export (C, u00081, "system__val_unsS");
   u00082 : constant Version_32 := 16#27b600b2#;
   pragma Export (C, u00082, "system__val_utilB");
   u00083 : constant Version_32 := 16#a5f4934a#;
   pragma Export (C, u00083, "system__val_utilS");
   u00084 : constant Version_32 := 16#d1060688#;
   pragma Export (C, u00084, "system__case_utilB");
   u00085 : constant Version_32 := 16#2d5d4c63#;
   pragma Export (C, u00085, "system__case_utilS");
   u00086 : constant Version_32 := 16#84a27f0d#;
   pragma Export (C, u00086, "interfaces__c_streamsB");
   u00087 : constant Version_32 := 16#a06e9ee4#;
   pragma Export (C, u00087, "interfaces__c_streamsS");
   u00088 : constant Version_32 := 16#79c5f3ba#;
   pragma Export (C, u00088, "system__crtlS");
   u00089 : constant Version_32 := 16#f1dc49a7#;
   pragma Export (C, u00089, "system__file_ioB");
   u00090 : constant Version_32 := 16#ae25c4d1#;
   pragma Export (C, u00090, "system__file_ioS");
   u00091 : constant Version_32 := 16#cf417de3#;
   pragma Export (C, u00091, "ada__finalizationS");
   u00092 : constant Version_32 := 16#95817ed8#;
   pragma Export (C, u00092, "system__finalization_rootB");
   u00093 : constant Version_32 := 16#46a65624#;
   pragma Export (C, u00093, "system__finalization_rootS");
   u00094 : constant Version_32 := 16#769e25e6#;
   pragma Export (C, u00094, "interfaces__cB");
   u00095 : constant Version_32 := 16#61e3d2ff#;
   pragma Export (C, u00095, "interfaces__cS");
   u00096 : constant Version_32 := 16#d301c7de#;
   pragma Export (C, u00096, "system__os_libB");
   u00097 : constant Version_32 := 16#dc0cac3f#;
   pragma Export (C, u00097, "system__os_libS");
   u00098 : constant Version_32 := 16#1a817b8e#;
   pragma Export (C, u00098, "system__stringsB");
   u00099 : constant Version_32 := 16#77eb34d2#;
   pragma Export (C, u00099, "system__stringsS");
   u00100 : constant Version_32 := 16#f4cbbf1c#;
   pragma Export (C, u00100, "system__file_control_blockS");
   u00101 : constant Version_32 := 16#58e7cff7#;
   pragma Export (C, u00101, "system__memoryB");
   u00102 : constant Version_32 := 16#50294380#;
   pragma Export (C, u00102, "system__memoryS");
   --  BEGIN ELABORATION ORDER
   --  ada%s
   --  interfaces%s
   --  system%s
   --  system.case_util%s
   --  system.case_util%b
   --  system.exn_llf%s
   --  system.exn_llf%b
   --  system.htable%s
   --  system.img_int%s
   --  system.img_int%b
   --  system.parameters%s
   --  system.parameters%b
   --  system.crtl%s
   --  interfaces.c_streams%s
   --  interfaces.c_streams%b
   --  system.standard_library%s
   --  system.exceptions_debug%s
   --  system.exceptions_debug%b
   --  system.storage_elements%s
   --  system.storage_elements%b
   --  system.stack_checking%s
   --  system.stack_checking%b
   --  system.string_hash%s
   --  system.string_hash%b
   --  system.htable%b
   --  system.strings%s
   --  system.strings%b
   --  system.os_lib%s
   --  system.traceback_entries%s
   --  system.traceback_entries%b
   --  ada.exceptions%s
   --  system.soft_links%s
   --  system.unsigned_types%s
   --  system.fat_flt%s
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
   --  ada.io_exceptions%s
   --  ada.numerics%s
   --  ada.numerics.aux%s
   --  ada.numerics.elementary_functions%s
   --  ada.numerics.elementary_functions%b
   --  ada.tags%s
   --  ada.streams%s
   --  ada.streams%b
   --  interfaces.c%s
   --  system.exceptions%s
   --  system.exceptions%b
   --  system.file_control_block%s
   --  system.file_io%s
   --  system.finalization_root%s
   --  system.finalization_root%b
   --  ada.finalization%s
   --  system.memory%s
   --  system.memory%b
   --  system.standard_library%b
   --  system.secondary_stack%s
   --  system.file_io%b
   --  interfaces.c%b
   --  ada.tags%b
   --  system.soft_links%b
   --  system.os_lib%b
   --  system.secondary_stack%b
   --  system.address_image%b
   --  ada.exceptions.traceback%b
   --  system.traceback%s
   --  system.traceback%b
   --  system.traceback.symbolic%s
   --  system.traceback.symbolic%b
   --  ada.exceptions%b
   --  ada.text_io%s
   --  ada.text_io%b
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
   --  tortue%s
   --  tortue%b
   --  missionkoch%b
   --  END ELABORATION ORDER


end ada_main;
