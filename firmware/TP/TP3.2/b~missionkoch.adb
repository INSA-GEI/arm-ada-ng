pragma Ada_95;
pragma Warnings (Off);
pragma Source_File_Name (ada_main, Spec_File_Name => "b~missionkoch.ads");
pragma Source_File_Name (ada_main, Body_File_Name => "b~missionkoch.adb");
pragma Suppress (Overflow_Check);
with Ada.Exceptions;

package body ada_main is

   E097 : Short_Integer; pragma Import (Ada, E097, "system__os_lib_E");
   E019 : Short_Integer; pragma Import (Ada, E019, "system__soft_links_E");
   E029 : Short_Integer; pragma Import (Ada, E029, "system__exception_table_E");
   E073 : Short_Integer; pragma Import (Ada, E073, "ada__io_exceptions_E");
   E061 : Short_Integer; pragma Import (Ada, E061, "ada__numerics_E");
   E075 : Short_Integer; pragma Import (Ada, E075, "ada__tags_E");
   E072 : Short_Integer; pragma Import (Ada, E072, "ada__streams_E");
   E095 : Short_Integer; pragma Import (Ada, E095, "interfaces__c_E");
   E031 : Short_Integer; pragma Import (Ada, E031, "system__exceptions_E");
   E100 : Short_Integer; pragma Import (Ada, E100, "system__file_control_block_E");
   E090 : Short_Integer; pragma Import (Ada, E090, "system__file_io_E");
   E093 : Short_Integer; pragma Import (Ada, E093, "system__finalization_root_E");
   E091 : Short_Integer; pragma Import (Ada, E091, "ada__finalization_E");
   E023 : Short_Integer; pragma Import (Ada, E023, "system__secondary_stack_E");
   E070 : Short_Integer; pragma Import (Ada, E070, "ada__text_io_E");
   E007 : Short_Integer; pragma Import (Ada, E007, "insa_E");
   E009 : Short_Integer; pragma Import (Ada, E009, "insa__graphics_E");
   E011 : Short_Integer; pragma Import (Ada, E011, "insa__graphics__ui_E");
   E056 : Short_Integer; pragma Import (Ada, E056, "insa__keys_E");
   E005 : Short_Integer; pragma Import (Ada, E005, "nombre_E");
   E060 : Short_Integer; pragma Import (Ada, E060, "tortue_E");

   Local_Priority_Specific_Dispatching : constant String := "";
   Local_Interrupt_States : constant String := "";

   Is_Elaborated : Boolean := False;

   procedure finalize_library is
   begin
      E070 := E070 - 1;
      declare
         procedure F1;
         pragma Import (Ada, F1, "ada__text_io__finalize_spec");
      begin
         F1;
      end;
      declare
         procedure F2;
         pragma Import (Ada, F2, "system__file_io__finalize_body");
      begin
         E090 := E090 - 1;
         F2;
      end;
      declare
         procedure Reraise_Library_Exception_If_Any;
            pragma Import (Ada, Reraise_Library_Exception_If_Any, "__gnat_reraise_library_exception_if_any");
      begin
         Reraise_Library_Exception_If_Any;
      end;
   end finalize_library;

   procedure adafinal is
      procedure s_stalib_adafinal;
      pragma Import (C, s_stalib_adafinal, "system__standard_library__adafinal");

      procedure Runtime_Finalize;
      pragma Import (C, Runtime_Finalize, "__gnat_runtime_finalize");

   begin
      if not Is_Elaborated then
         return;
      end if;
      Is_Elaborated := False;
      Runtime_Finalize;
      s_stalib_adafinal;
   end adafinal;

   type No_Param_Proc is access procedure;

   procedure adainit is
      Main_Priority : Integer;
      pragma Import (C, Main_Priority, "__gl_main_priority");
      Time_Slice_Value : Integer;
      pragma Import (C, Time_Slice_Value, "__gl_time_slice_val");
      WC_Encoding : Character;
      pragma Import (C, WC_Encoding, "__gl_wc_encoding");
      Locking_Policy : Character;
      pragma Import (C, Locking_Policy, "__gl_locking_policy");
      Queuing_Policy : Character;
      pragma Import (C, Queuing_Policy, "__gl_queuing_policy");
      Task_Dispatching_Policy : Character;
      pragma Import (C, Task_Dispatching_Policy, "__gl_task_dispatching_policy");
      Priority_Specific_Dispatching : System.Address;
      pragma Import (C, Priority_Specific_Dispatching, "__gl_priority_specific_dispatching");
      Num_Specific_Dispatching : Integer;
      pragma Import (C, Num_Specific_Dispatching, "__gl_num_specific_dispatching");
      Main_CPU : Integer;
      pragma Import (C, Main_CPU, "__gl_main_cpu");
      Interrupt_States : System.Address;
      pragma Import (C, Interrupt_States, "__gl_interrupt_states");
      Num_Interrupt_States : Integer;
      pragma Import (C, Num_Interrupt_States, "__gl_num_interrupt_states");
      Unreserve_All_Interrupts : Integer;
      pragma Import (C, Unreserve_All_Interrupts, "__gl_unreserve_all_interrupts");
      Detect_Blocking : Integer;
      pragma Import (C, Detect_Blocking, "__gl_detect_blocking");
      Default_Stack_Size : Integer;
      pragma Import (C, Default_Stack_Size, "__gl_default_stack_size");
      Leap_Seconds_Support : Integer;
      pragma Import (C, Leap_Seconds_Support, "__gl_leap_seconds_support");
      Bind_Env_Addr : System.Address;
      pragma Import (C, Bind_Env_Addr, "__gl_bind_env_addr");

      procedure Runtime_Initialize (Install_Handler : Integer);
      pragma Import (C, Runtime_Initialize, "__gnat_runtime_initialize");

      Finalize_Library_Objects : No_Param_Proc;
      pragma Import (C, Finalize_Library_Objects, "__gnat_finalize_library_objects");
   begin
      if Is_Elaborated then
         return;
      end if;
      Is_Elaborated := True;
      Main_Priority := -1;
      Time_Slice_Value := -1;
      WC_Encoding := 'b';
      Locking_Policy := ' ';
      Queuing_Policy := ' ';
      Task_Dispatching_Policy := ' ';
      Priority_Specific_Dispatching :=
        Local_Priority_Specific_Dispatching'Address;
      Num_Specific_Dispatching := 0;
      Main_CPU := -1;
      Interrupt_States := Local_Interrupt_States'Address;
      Num_Interrupt_States := 0;
      Unreserve_All_Interrupts := 0;
      Detect_Blocking := 0;
      Default_Stack_Size := -1;
      Leap_Seconds_Support := 0;

      Runtime_Initialize (1);

      Finalize_Library_Objects := finalize_library'access;

      System.Soft_Links'Elab_Spec;
      System.Exception_Table'Elab_Body;
      E029 := E029 + 1;
      Ada.Io_Exceptions'Elab_Spec;
      E073 := E073 + 1;
      Ada.Numerics'Elab_Spec;
      E061 := E061 + 1;
      Ada.Tags'Elab_Spec;
      Ada.Streams'Elab_Spec;
      E072 := E072 + 1;
      Interfaces.C'Elab_Spec;
      System.Exceptions'Elab_Spec;
      E031 := E031 + 1;
      System.File_Control_Block'Elab_Spec;
      E100 := E100 + 1;
      System.Finalization_Root'Elab_Spec;
      E093 := E093 + 1;
      Ada.Finalization'Elab_Spec;
      E091 := E091 + 1;
      System.File_Io'Elab_Body;
      E090 := E090 + 1;
      E095 := E095 + 1;
      Ada.Tags'Elab_Body;
      E075 := E075 + 1;
      System.Soft_Links'Elab_Body;
      E019 := E019 + 1;
      System.Os_Lib'Elab_Body;
      E097 := E097 + 1;
      System.Secondary_Stack'Elab_Body;
      E023 := E023 + 1;
      Ada.Text_Io'Elab_Spec;
      Ada.Text_Io'Elab_Body;
      E070 := E070 + 1;
      E007 := E007 + 1;
      E009 := E009 + 1;
      Insa.Graphics.Ui'Elab_Spec;
      E011 := E011 + 1;
      E056 := E056 + 1;
      E005 := E005 + 1;
      Tortue'Elab_Spec;
      E060 := E060 + 1;
   end adainit;

   procedure Ada_Main_Program;
   pragma Import (Ada, Ada_Main_Program, "_ada_missionkoch");

   function main
     (argc : Integer;
      argv : System.Address;
      envp : System.Address)
      return Integer
   is
      procedure Initialize (Addr : System.Address);
      pragma Import (C, Initialize, "__gnat_initialize");

      procedure Finalize;
      pragma Import (C, Finalize, "__gnat_finalize");
      SEH : aliased array (1 .. 2) of Integer;

      Ensure_Reference : aliased System.Address := Ada_Main_Program_Name'Address;
      pragma Volatile (Ensure_Reference);

   begin
      gnat_argc := argc;
      gnat_argv := argv;
      gnat_envp := envp;

      Initialize (SEH'Address);
      adainit;
      Ada_Main_Program;
      adafinal;
      Finalize;
      return (gnat_exit_status);
   end;

--  BEGIN Object file/option list
   --   /home/dimercur/arm-ada/lib/lib-ada/insa.o
   --   /home/dimercur/arm-ada/lib/lib-ada/insa-graphics.o
   --   /home/dimercur/arm-ada/lib/lib-ada/insa-graphics-ui.o
   --   /home/dimercur/arm-ada/lib/lib-ada/insa-keys.o
   --   ./nombre.o
   --   ./tortue.o
   --   ./missionkoch.o
   --   -L./
   --   -L/home/dimercur/arm-ada/lib/lib-ada/
   --   -L/usr/local/insa/arm-ada/compilateur/gcc-arm-none-eabi-6-2017-q3-update/lib/gcc/arm-none-eabi/6.3.1/adalib/
   --   -static
   --   -lgnat
   --   -lm
--  END Object file/option list   

end ada_main;
