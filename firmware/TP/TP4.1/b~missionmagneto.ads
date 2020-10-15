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

   Ada_Main_Program_Name : constant String := "_ada_missionmagneto" & ASCII.NUL;
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
   u00001 : constant Version_32 := 16#85e3a6b3#;
   pragma Export (C, u00001, "missionmagnetoB");
   u00002 : constant Version_32 := 16#b6df930e#;
   pragma Export (C, u00002, "system__standard_libraryB");
   u00003 : constant Version_32 := 16#f90293f2#;
   pragma Export (C, u00003, "system__standard_libraryS");
   u00004 : constant Version_32 := 16#e054a89a#;
   pragma Export (C, u00004, "magnetoB");
   u00005 : constant Version_32 := 16#34f7f7f6#;
   pragma Export (C, u00005, "magnetoS");
   u00006 : constant Version_32 := 16#3ffc8e18#;
   pragma Export (C, u00006, "adaS");
   u00007 : constant Version_32 := 16#e18a47a0#;
   pragma Export (C, u00007, "ada__float_text_ioB");
   u00008 : constant Version_32 := 16#e61b3c6c#;
   pragma Export (C, u00008, "ada__float_text_ioS");
   u00009 : constant Version_32 := 16#d90b9106#;
   pragma Export (C, u00009, "ada__exceptionsB");
   u00010 : constant Version_32 := 16#687d7b36#;
   pragma Export (C, u00010, "ada__exceptionsS");
   u00011 : constant Version_32 := 16#e947e6a9#;
   pragma Export (C, u00011, "ada__exceptions__last_chance_handlerB");
   u00012 : constant Version_32 := 16#41e5552e#;
   pragma Export (C, u00012, "ada__exceptions__last_chance_handlerS");
   u00013 : constant Version_32 := 16#095425b4#;
   pragma Export (C, u00013, "systemS");
   u00014 : constant Version_32 := 16#465d427a#;
   pragma Export (C, u00014, "system__soft_linksB");
   u00015 : constant Version_32 := 16#97d0fde1#;
   pragma Export (C, u00015, "system__soft_linksS");
   u00016 : constant Version_32 := 16#b01dad17#;
   pragma Export (C, u00016, "system__parametersB");
   u00017 : constant Version_32 := 16#777e28cb#;
   pragma Export (C, u00017, "system__parametersS");
   u00018 : constant Version_32 := 16#0f0cb66d#;
   pragma Export (C, u00018, "system__secondary_stackB");
   u00019 : constant Version_32 := 16#a235eadd#;
   pragma Export (C, u00019, "system__secondary_stackS");
   u00020 : constant Version_32 := 16#39a03df9#;
   pragma Export (C, u00020, "system__storage_elementsB");
   u00021 : constant Version_32 := 16#24976fb0#;
   pragma Export (C, u00021, "system__storage_elementsS");
   u00022 : constant Version_32 := 16#41837d1e#;
   pragma Export (C, u00022, "system__stack_checkingB");
   u00023 : constant Version_32 := 16#87eb4e5c#;
   pragma Export (C, u00023, "system__stack_checkingS");
   u00024 : constant Version_32 := 16#87a448ff#;
   pragma Export (C, u00024, "system__exception_tableB");
   u00025 : constant Version_32 := 16#54fa4cf6#;
   pragma Export (C, u00025, "system__exception_tableS");
   u00026 : constant Version_32 := 16#ce4af020#;
   pragma Export (C, u00026, "system__exceptionsB");
   u00027 : constant Version_32 := 16#61374842#;
   pragma Export (C, u00027, "system__exceptionsS");
   u00028 : constant Version_32 := 16#aa0563fc#;
   pragma Export (C, u00028, "system__exceptions_debugB");
   u00029 : constant Version_32 := 16#77dedc70#;
   pragma Export (C, u00029, "system__exceptions_debugS");
   u00030 : constant Version_32 := 16#570325c8#;
   pragma Export (C, u00030, "system__img_intB");
   u00031 : constant Version_32 := 16#0b8fc576#;
   pragma Export (C, u00031, "system__img_intS");
   u00032 : constant Version_32 := 16#39df8c17#;
   pragma Export (C, u00032, "system__tracebackB");
   u00033 : constant Version_32 := 16#5776fb70#;
   pragma Export (C, u00033, "system__tracebackS");
   u00034 : constant Version_32 := 16#9ed49525#;
   pragma Export (C, u00034, "system__traceback_entriesB");
   u00035 : constant Version_32 := 16#090fd3c4#;
   pragma Export (C, u00035, "system__traceback_entriesS");
   u00036 : constant Version_32 := 16#6fd210f2#;
   pragma Export (C, u00036, "system__traceback__symbolicB");
   u00037 : constant Version_32 := 16#dd19f67a#;
   pragma Export (C, u00037, "system__traceback__symbolicS");
   u00038 : constant Version_32 := 16#701f9d88#;
   pragma Export (C, u00038, "ada__exceptions__tracebackB");
   u00039 : constant Version_32 := 16#20245e75#;
   pragma Export (C, u00039, "ada__exceptions__tracebackS");
   u00040 : constant Version_32 := 16#57a37a42#;
   pragma Export (C, u00040, "system__address_imageB");
   u00041 : constant Version_32 := 16#a8b8b88e#;
   pragma Export (C, u00041, "system__address_imageS");
   u00042 : constant Version_32 := 16#8c33a517#;
   pragma Export (C, u00042, "system__wch_conB");
   u00043 : constant Version_32 := 16#12290766#;
   pragma Export (C, u00043, "system__wch_conS");
   u00044 : constant Version_32 := 16#9721e840#;
   pragma Export (C, u00044, "system__wch_stwB");
   u00045 : constant Version_32 := 16#3f382b67#;
   pragma Export (C, u00045, "system__wch_stwS");
   u00046 : constant Version_32 := 16#b96cfbef#;
   pragma Export (C, u00046, "system__wch_cnvB");
   u00047 : constant Version_32 := 16#1d9ebd95#;
   pragma Export (C, u00047, "system__wch_cnvS");
   u00048 : constant Version_32 := 16#4be8ce1b#;
   pragma Export (C, u00048, "interfacesS");
   u00049 : constant Version_32 := 16#ece6fdb6#;
   pragma Export (C, u00049, "system__wch_jisB");
   u00050 : constant Version_32 := 16#9deea4b4#;
   pragma Export (C, u00050, "system__wch_jisS");
   u00051 : constant Version_32 := 16#920eada5#;
   pragma Export (C, u00051, "ada__tagsB");
   u00052 : constant Version_32 := 16#13ca27f3#;
   pragma Export (C, u00052, "ada__tagsS");
   u00053 : constant Version_32 := 16#c3335bfd#;
   pragma Export (C, u00053, "system__htableB");
   u00054 : constant Version_32 := 16#8d96965e#;
   pragma Export (C, u00054, "system__htableS");
   u00055 : constant Version_32 := 16#089f5cd0#;
   pragma Export (C, u00055, "system__string_hashB");
   u00056 : constant Version_32 := 16#2fc8fd20#;
   pragma Export (C, u00056, "system__string_hashS");
   u00057 : constant Version_32 := 16#940c8174#;
   pragma Export (C, u00057, "system__unsigned_typesS");
   u00058 : constant Version_32 := 16#b44f9ae7#;
   pragma Export (C, u00058, "system__val_unsB");
   u00059 : constant Version_32 := 16#84a46c4f#;
   pragma Export (C, u00059, "system__val_unsS");
   u00060 : constant Version_32 := 16#27b600b2#;
   pragma Export (C, u00060, "system__val_utilB");
   u00061 : constant Version_32 := 16#a5f4934a#;
   pragma Export (C, u00061, "system__val_utilS");
   u00062 : constant Version_32 := 16#d1060688#;
   pragma Export (C, u00062, "system__case_utilB");
   u00063 : constant Version_32 := 16#2d5d4c63#;
   pragma Export (C, u00063, "system__case_utilS");
   u00064 : constant Version_32 := 16#c1a106e2#;
   pragma Export (C, u00064, "ada__text_ioB");
   u00065 : constant Version_32 := 16#e701a999#;
   pragma Export (C, u00065, "ada__text_ioS");
   u00066 : constant Version_32 := 16#10558b11#;
   pragma Export (C, u00066, "ada__streamsB");
   u00067 : constant Version_32 := 16#2e6701ab#;
   pragma Export (C, u00067, "ada__streamsS");
   u00068 : constant Version_32 := 16#db5c917c#;
   pragma Export (C, u00068, "ada__io_exceptionsS");
   u00069 : constant Version_32 := 16#84a27f0d#;
   pragma Export (C, u00069, "interfaces__c_streamsB");
   u00070 : constant Version_32 := 16#a06e9ee4#;
   pragma Export (C, u00070, "interfaces__c_streamsS");
   u00071 : constant Version_32 := 16#79c5f3ba#;
   pragma Export (C, u00071, "system__crtlS");
   u00072 : constant Version_32 := 16#f1dc49a7#;
   pragma Export (C, u00072, "system__file_ioB");
   u00073 : constant Version_32 := 16#ae25c4d1#;
   pragma Export (C, u00073, "system__file_ioS");
   u00074 : constant Version_32 := 16#cf417de3#;
   pragma Export (C, u00074, "ada__finalizationS");
   u00075 : constant Version_32 := 16#95817ed8#;
   pragma Export (C, u00075, "system__finalization_rootB");
   u00076 : constant Version_32 := 16#46a65624#;
   pragma Export (C, u00076, "system__finalization_rootS");
   u00077 : constant Version_32 := 16#769e25e6#;
   pragma Export (C, u00077, "interfaces__cB");
   u00078 : constant Version_32 := 16#61e3d2ff#;
   pragma Export (C, u00078, "interfaces__cS");
   u00079 : constant Version_32 := 16#d301c7de#;
   pragma Export (C, u00079, "system__os_libB");
   u00080 : constant Version_32 := 16#dc0cac3f#;
   pragma Export (C, u00080, "system__os_libS");
   u00081 : constant Version_32 := 16#1a817b8e#;
   pragma Export (C, u00081, "system__stringsB");
   u00082 : constant Version_32 := 16#77eb34d2#;
   pragma Export (C, u00082, "system__stringsS");
   u00083 : constant Version_32 := 16#f4cbbf1c#;
   pragma Export (C, u00083, "system__file_control_blockS");
   u00084 : constant Version_32 := 16#d5f9759f#;
   pragma Export (C, u00084, "ada__text_io__float_auxB");
   u00085 : constant Version_32 := 16#f854caf5#;
   pragma Export (C, u00085, "ada__text_io__float_auxS");
   u00086 : constant Version_32 := 16#181dc502#;
   pragma Export (C, u00086, "ada__text_io__generic_auxB");
   u00087 : constant Version_32 := 16#a6c327d3#;
   pragma Export (C, u00087, "ada__text_io__generic_auxS");
   u00088 : constant Version_32 := 16#237a28d3#;
   pragma Export (C, u00088, "system__img_realB");
   u00089 : constant Version_32 := 16#cefc7456#;
   pragma Export (C, u00089, "system__img_realS");
   u00090 : constant Version_32 := 16#0dc39e47#;
   pragma Export (C, u00090, "system__fat_llfS");
   u00091 : constant Version_32 := 16#1b28662b#;
   pragma Export (C, u00091, "system__float_controlB");
   u00092 : constant Version_32 := 16#e9a86688#;
   pragma Export (C, u00092, "system__float_controlS");
   u00093 : constant Version_32 := 16#f1f88835#;
   pragma Export (C, u00093, "system__img_lluB");
   u00094 : constant Version_32 := 16#ddc581b7#;
   pragma Export (C, u00094, "system__img_lluS");
   u00095 : constant Version_32 := 16#eef535cd#;
   pragma Export (C, u00095, "system__img_unsB");
   u00096 : constant Version_32 := 16#0bf8bd83#;
   pragma Export (C, u00096, "system__img_unsS");
   u00097 : constant Version_32 := 16#592443c3#;
   pragma Export (C, u00097, "system__powten_tableS");
   u00098 : constant Version_32 := 16#faa9a7b2#;
   pragma Export (C, u00098, "system__val_realB");
   u00099 : constant Version_32 := 16#f77d52a5#;
   pragma Export (C, u00099, "system__val_realS");
   u00100 : constant Version_32 := 16#6c05c057#;
   pragma Export (C, u00100, "system__exn_llfB");
   u00101 : constant Version_32 := 16#b52a9e68#;
   pragma Export (C, u00101, "system__exn_llfS");
   u00102 : constant Version_32 := 16#512139a0#;
   pragma Export (C, u00102, "system__fat_fltS");
   u00103 : constant Version_32 := 16#f64b89a4#;
   pragma Export (C, u00103, "ada__integer_text_ioB");
   u00104 : constant Version_32 := 16#f1daf268#;
   pragma Export (C, u00104, "ada__integer_text_ioS");
   u00105 : constant Version_32 := 16#f6fdca1c#;
   pragma Export (C, u00105, "ada__text_io__integer_auxB");
   u00106 : constant Version_32 := 16#b9793d30#;
   pragma Export (C, u00106, "ada__text_io__integer_auxS");
   u00107 : constant Version_32 := 16#18d57884#;
   pragma Export (C, u00107, "system__img_biuB");
   u00108 : constant Version_32 := 16#522e0939#;
   pragma Export (C, u00108, "system__img_biuS");
   u00109 : constant Version_32 := 16#e7d8734f#;
   pragma Export (C, u00109, "system__img_llbB");
   u00110 : constant Version_32 := 16#13e919c7#;
   pragma Export (C, u00110, "system__img_llbS");
   u00111 : constant Version_32 := 16#9777733a#;
   pragma Export (C, u00111, "system__img_lliB");
   u00112 : constant Version_32 := 16#181b7065#;
   pragma Export (C, u00112, "system__img_lliS");
   u00113 : constant Version_32 := 16#0e8808d4#;
   pragma Export (C, u00113, "system__img_llwB");
   u00114 : constant Version_32 := 16#ba853a51#;
   pragma Export (C, u00114, "system__img_llwS");
   u00115 : constant Version_32 := 16#428b07f8#;
   pragma Export (C, u00115, "system__img_wiuB");
   u00116 : constant Version_32 := 16#3c6f8eab#;
   pragma Export (C, u00116, "system__img_wiuS");
   u00117 : constant Version_32 := 16#7ebd8839#;
   pragma Export (C, u00117, "system__val_intB");
   u00118 : constant Version_32 := 16#41f10f8b#;
   pragma Export (C, u00118, "system__val_intS");
   u00119 : constant Version_32 := 16#b3aa7b17#;
   pragma Export (C, u00119, "system__val_lliB");
   u00120 : constant Version_32 := 16#9370c314#;
   pragma Export (C, u00120, "system__val_lliS");
   u00121 : constant Version_32 := 16#06052bd0#;
   pragma Export (C, u00121, "system__val_lluB");
   u00122 : constant Version_32 := 16#eefed606#;
   pragma Export (C, u00122, "system__val_lluS");
   u00123 : constant Version_32 := 16#84ad4a42#;
   pragma Export (C, u00123, "ada__numericsS");
   u00124 : constant Version_32 := 16#03e83d1c#;
   pragma Export (C, u00124, "ada__numerics__elementary_functionsB");
   u00125 : constant Version_32 := 16#00443200#;
   pragma Export (C, u00125, "ada__numerics__elementary_functionsS");
   u00126 : constant Version_32 := 16#0cdfa324#;
   pragma Export (C, u00126, "ada__numerics__auxS");
   u00127 : constant Version_32 := 16#b0988e58#;
   pragma Export (C, u00127, "insaB");
   u00128 : constant Version_32 := 16#34488d3d#;
   pragma Export (C, u00128, "insaS");
   u00129 : constant Version_32 := 16#63b70ccf#;
   pragma Export (C, u00129, "insa__graphicsB");
   u00130 : constant Version_32 := 16#5c6222d3#;
   pragma Export (C, u00130, "insa__graphicsS");
   u00131 : constant Version_32 := 16#dba6bfea#;
   pragma Export (C, u00131, "insa__graphics__uiB");
   u00132 : constant Version_32 := 16#5d46fcf6#;
   pragma Export (C, u00132, "insa__graphics__uiS");
   u00133 : constant Version_32 := 16#f9ad2a59#;
   pragma Export (C, u00133, "insa__keysB");
   u00134 : constant Version_32 := 16#07fddcb9#;
   pragma Export (C, u00134, "insa__keysS");
   u00135 : constant Version_32 := 16#aa0aea3a#;
   pragma Export (C, u00135, "insa__sensorsB");
   u00136 : constant Version_32 := 16#476746fd#;
   pragma Export (C, u00136, "insa__sensorsS");
   u00137 : constant Version_32 := 16#2b70b149#;
   pragma Export (C, u00137, "system__concat_3B");
   u00138 : constant Version_32 := 16#02247911#;
   pragma Export (C, u00138, "system__concat_3S");
   u00139 : constant Version_32 := 16#fd83e873#;
   pragma Export (C, u00139, "system__concat_2B");
   u00140 : constant Version_32 := 16#0bf4f264#;
   pragma Export (C, u00140, "system__concat_2S");
   u00141 : constant Version_32 := 16#932a4690#;
   pragma Export (C, u00141, "system__concat_4B");
   u00142 : constant Version_32 := 16#77300e94#;
   pragma Export (C, u00142, "system__concat_4S");
   u00143 : constant Version_32 := 16#58e7cff7#;
   pragma Export (C, u00143, "system__memoryB");
   u00144 : constant Version_32 := 16#50294380#;
   pragma Export (C, u00144, "system__memoryS");
   --  BEGIN ELABORATION ORDER
   --  ada%s
   --  interfaces%s
   --  system%s
   --  system.case_util%s
   --  system.case_util%b
   --  system.exn_llf%s
   --  system.exn_llf%b
   --  system.float_control%s
   --  system.float_control%b
   --  system.htable%s
   --  system.img_int%s
   --  system.img_int%b
   --  system.img_lli%s
   --  system.img_lli%b
   --  system.img_real%s
   --  system.parameters%s
   --  system.parameters%b
   --  system.crtl%s
   --  interfaces.c_streams%s
   --  interfaces.c_streams%b
   --  system.powten_table%s
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
   --  system.fat_llf%s
   --  system.img_biu%s
   --  system.img_biu%b
   --  system.img_llb%s
   --  system.img_llb%b
   --  system.img_llu%s
   --  system.img_llu%b
   --  system.img_llw%s
   --  system.img_llw%b
   --  system.img_uns%s
   --  system.img_uns%b
   --  system.img_real%b
   --  system.img_wiu%s
   --  system.img_wiu%b
   --  system.val_int%s
   --  system.val_lli%s
   --  system.val_llu%s
   --  system.val_real%s
   --  system.val_uns%s
   --  system.val_util%s
   --  system.val_util%b
   --  system.val_uns%b
   --  system.val_real%b
   --  system.val_llu%b
   --  system.val_lli%b
   --  system.val_int%b
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
   --  system.concat_3%s
   --  system.concat_3%b
   --  system.concat_4%s
   --  system.concat_4%b
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
   --  ada.text_io.float_aux%s
   --  ada.float_text_io%s
   --  ada.float_text_io%b
   --  ada.text_io.generic_aux%s
   --  ada.text_io.generic_aux%b
   --  ada.text_io.float_aux%b
   --  ada.text_io.integer_aux%s
   --  ada.text_io.integer_aux%b
   --  ada.integer_text_io%s
   --  ada.integer_text_io%b
   --  insa%s
   --  insa%b
   --  insa.graphics%s
   --  insa.graphics%b
   --  insa.graphics.ui%s
   --  insa.graphics.ui%b
   --  insa.keys%s
   --  insa.keys%b
   --  insa.sensors%s
   --  insa.sensors%b
   --  magneto%s
   --  magneto%b
   --  missionmagneto%b
   --  END ELABORATION ORDER


end ada_main;
