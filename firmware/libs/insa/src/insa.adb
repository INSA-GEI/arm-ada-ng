-- Package Insa
-- Define several usefull types and generic functions
--

-- pragma Ada_95;
-- with Interfaces;

package body Insa is
   pragma Warnings (Off);
   
   type VERSION is access INTEGER;
   
   -- GetOSVersion
   -- Return current version as Major.Minor
   procedure GetOSVersion(Major: out INTEGER; Minor: out INTEGER) is
      procedure Wrapper_GetOSVersion(Major_Ver: VERSION; Minor_Ver: VERSION);
      pragma Import (C, Wrapper_GetOSVersion, "API_GetOSVersion");
      
      Maj,Min: Version;
   begin
      Wrapper_GetOSVersion(Maj, Min);
      
      Major:=Maj.all;
      Minor:=Min.all;
   end GetOSVersion;
   
   -- SysDelay
   -- Wait during 'Time' millisecondes
   procedure SysDelay(Time: Positive) is
      procedure Wrapper_SysDelay(Time: Positive);
      pragma Import (C, Wrapper_SysDelay, "C_Delay");
   begin
      Wrapper_SysDelay(Time);
   end SysDelay;
   
end Insa;
