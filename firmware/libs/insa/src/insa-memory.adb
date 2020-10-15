-- Package Insa.Memory
-- Define functions for reading or writing in external memory
--
-- External memory is 512 KBytes long and is accessed byte by byte
--

package body Insa.Memory is
   
   -- ReadByte
   -- Read a byte from external memory at given address
   function ReadByte(Addr: MEMORY_ADDRESS) return MEMORY_BYTE is
      function Wrapper_ReadByte(Addr: MEMORY_ADDRESS) return MEMORY_BYTE;
      pragma Import (C, Wrapper_ReadByte, "SRAM_ReadByte");
   begin
      return Wrapper_ReadByte(Addr);
   end ReadByte;
   
   -- WriteByte
   -- Stop audio processing
   procedure WriteByte(Addr: MEMORY_ADDRESS; Data: MEMORY_BYTE) is
      procedure Wrapper_WriteByte(Addr: MEMORY_ADDRESS; Data: MEMORY_BYTE);
      pragma Import (C, Wrapper_WriteByte, "SRAM_WriteByte");
   begin
      Wrapper_WriteByte(Addr, Data);
   end WriteByte;
   
   -- ReadByteBuffer
   -- Read a buffer of data from SRAM
   procedure ReadByteBuffer(Addr: MEMORY_ADDRESS; Buffer: in out MEMORY_BUFFER) is
      Local_Addr: MEMORY_ADDRESS;
   begin
      Local_Addr:=Addr;
      
      for Counter in Buffer'Range loop
         Buffer(Counter):=ReadByte(Local_Addr);
	 
         if Local_Addr/=MEMORY_ADDRESS'Last then
            pragma Warnings (Off);
            Local_Addr:=Local_Addr+1;
            pragma Warnings (On);
         else
            Local_Addr:=MEMORY_ADDRESS'First;
         end if; 
      end loop;
      
   end ReadByteBuffer;
      
   -- WriteByteBuffer
   -- Write a buffer of data into SRAM
   procedure WriteByteBuffer(Addr: MEMORY_ADDRESS; Buffer: MEMORY_BUFFER) is 
      Local_Addr: MEMORY_ADDRESS;
   begin
      Local_Addr:=Addr;
      
      for Counter in Buffer'Range loop
         WriteByte(Local_Addr, Buffer(Counter));
	 
         if Local_Addr/=MEMORY_ADDRESS'Last then
            pragma Warnings (Off);
            Local_Addr:=Local_Addr+1;
            pragma Warnings (Off);
         else
            Local_Addr:=MEMORY_ADDRESS'First;
         end if; 
      end loop;
   
   end WriteByteBuffer;
   
end Insa.Memory;
