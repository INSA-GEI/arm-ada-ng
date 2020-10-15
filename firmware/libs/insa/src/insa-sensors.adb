-- Package Insa.Sensors
-- Function for accessing sensor (accelerometer, magnetometer, gyroscope)
--

package body Insa.Sensors is
   
   type WRAPPER_VALUES is array(0..2) of FLOAT;
   type WRAPPER_ACCESS is access WRAPPER_VALUES;
   
   -- GetGyroscopicValues
   -- return an array of 3 uncalibrated float values (axis X, Y and Z) corresponding to gyroscopic sensor 
   -- gyroscope => speed of rotation around an axis
   -- values are from -256.0 to 256.0
   function GetGyroscopicValues return SENSOR_VALUES is
   
     function Wrapper_GetGyroscopicValues return WRAPPER_ACCESS;
     pragma Import (C, Wrapper_GetGyroscopicValues, "L3GD20_GetGyroscopicValues");
     
     Values: SENSOR_VALUES;
     Wrapper_Values: WRAPPER_ACCESS;
     
   begin 
      Wrapper_Values := Wrapper_GetGyroscopicValues;
      
      pragma Warnings (Off);
      Values(1) := Wrapper_Values(0);
      Values(2) := Wrapper_Values(1);
      Values(3) := Wrapper_Values(2);
      pragma Warnings (On);
      
      return Values;
   end GetGyroscopicValues;
   
   -- GetMagneticValues
   -- return an array of 3 uncalibrated float values (axis X, Y and Z) corresponding to magnetic sensor 
   -- magnetic sensor => sense the magnetic field seen by an axis
   -- values are from -512.0 to 512.0
   function GetMagneticValues return SENSOR_VALUES is
      
     function Wrapper_GetMagneticValues return WRAPPER_ACCESS;
     pragma Import (C, Wrapper_GetMagneticValues, "LSM303DLHC_GetMagneticValues");
     
     Values: SENSOR_VALUES;
     Wrapper_Values: WRAPPER_ACCESS;
   begin
      Wrapper_Values := Wrapper_GetMagneticValues;
      
      pragma Warnings (Off);
      Values(1) := Wrapper_Values(0);
      Values(2) := Wrapper_Values(1);
      Values(3) := Wrapper_Values(2);
      pragma Warnings (On);
      
      return Values;
   end GetMagneticValues;
   
   -- GetAccelerometerValues
   -- return an array of 3 uncalibrated float values (axis X, Y and Z) corresponding to accelerometer sensor 
   -- accelerometer sensor => sense the acceleration as seen by an axis
   -- values are from -1024.0 to 1024.0
   function GetAccelerometerValues return SENSOR_VALUES is
      
     function Wrapper_GetAccelerometerValues return WRAPPER_ACCESS;
     pragma Import (C, Wrapper_GetAccelerometerValues, "LSM303DLHC_GetAccelerometerValues");
     
     Values: SENSOR_VALUES;
     Wrapper_Values: WRAPPER_ACCESS;
   begin
      Wrapper_Values := Wrapper_GetAccelerometerValues;
      
      pragma Warnings (Off);
      Values(1) := Wrapper_Values(0);
      Values(2) := Wrapper_Values(1);
      Values(3) := Wrapper_Values(2);
      pragma Warnings (On);
      
      return Values;
   end GetAccelerometerValues;

end Insa.Sensors;
