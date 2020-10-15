-- Package Insa.Sensors
-- Function for accessing sensor (accelerometer, magnetometer, gyroscope)
--

package Insa.Sensors is
   pragma Warnings (Off);
   
   type SENSOR_VALUES is array(1 .. 3) of Float;
   
   -- GetGyroscopicValues
   -- return an array of 3 uncalibrated float values (axis X, Y and Z) corresponding to gyroscopic sensor 
   -- gyroscope => speed of rotation around an axis
   -- values are from -256.0 to 256.0
   function GetGyroscopicValues return SENSOR_VALUES;
   
   -- GetMagneticValues
   -- return an array of 3 uncalibrated float values (axis X, Y and Z) corresponding to magnetic sensor 
   -- magnetic sensor => sense the magnetic field seen by an axis
   -- values are from -512.0 to 512.0
   function GetMagneticValues return SENSOR_VALUES;
   
   -- GetAccelerometerValues
   -- return an array of 3 uncalibrated float values (axis X, Y and Z) corresponding to accelerometer sensor 
   -- accelerometer sensor => sense the acceleration as seen by an axis
   -- values are from -1024.0 to 1024.0
   function GetAccelerometerValues return SENSOR_VALUES;

end Insa.Sensors;
