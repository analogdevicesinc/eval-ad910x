/******************************************************************************
    @file:  ad910x.h
 
    @brief: Defines digital pins and functions for the devices' SPI interface
            and printing data from SPI read to text-based user interface
-------------------------------------------------------------------------------
    Copyright (c) 2024 Analog Devices, Inc. All Rights Reserved.
    This software is proprietary to Analog Devices, Inc. and its licensors.

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License. 
******************************************************************************/

#ifndef __ad910x_h__
#define __ad910x_h__
#include "mbed.h"

class AD910x_SINGLE {
    public:
        #pragma region (Single-Board Code)
        SPI( spi );             // SPI instance of AD910x
        DigitalOut( csb );      // DigitalOut instance for AD910x chip select pin
        DigitalOut( resetb );   // DigitalOut instance for AD910x reset pin
        DigitalOut( triggerb ); // DigitalOut instance for AD910x trigger pin
 
        /*** 4-Wire SPI, Reset, and Trigger configuration & constructor ***/
        AD910x_SINGLE( PinName CSB = PA_15, PinName MOSI = PA_7, PinName MISO = PB_4, PinName SCK = PB_3,
                PinName RESETB = PG_11, PinName TRIGGERB = PG_10 );
     
        /*** SPI register addresses ***/
        uint16_t reg_add[66] = {0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007, 0x0008, 0x0009, 0x000a, 0x000b, 0x000c, 0x000d, 0x000e, 0x001f, 0x0020, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027, 0x0028, 0x0029, 0x002a, 0x002b, 0x002c, 0x002d, 0x002e, 0x002f, 0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037, 0x003e, 0x003f, 0x0040, 0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0047, 0x0050, 0x0051, 0x0052, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057, 0x0058, 0x0059, 0x005a, 0x005b, 0x005c, 0x005d, 0x005e, 0x005f, 0x001e, 0x001d};
    
        // Function to set up SPI
        void spi_init( uint8_t reg_len, uint8_t mode, uint32_t hz);
    
        // SPI write function
        void spi_write( uint16_t addr, int16_t data );
    
        // SPI read function
        int16_t spi_read( uint16_t addr );

        // Function to reset SPI register values
        void AD910x_reg_reset();
        
        // Function to display register data
        void print_data( uint16_t addr, uint16_t data );
    
        // Function to write to SRAM
        void AD910x_update_sram( int16_t data[] );
    
        // Function to display n SRAM data
        void AD910x_print_sram( uint16_t n );
    
        // Function to write to device SPI registers and display updated register values
        void AD910x_update_regs( uint16_t data[] );
          
        // Function to start pattern generation
        void AD910x_start_pattern();
        
        // Function to stop pattern generation
        void AD910x_stop_pattern();
        #pragma endregion
};

class AD910x_MULTI {
    public:
        #pragma region (Multi-Board Code)
        SPI( spi );             // SPI instance of AD910x
        DigitalOut( csb1 );     // DigitalOut instance for AD910x device 1 chip select pin
        DigitalOut( csb2 );     // DigitalOut instance for AD910x device 2 chip select pin
        DigitalOut( resetb );   // DigitalOut instance for AD910x reset pin
        DigitalOut( triggerb ); // DigitalOut instance for AD910x trigger pin
 
        /*** 4-Wire SPI, Reset, and Trigger configuration & constructor ***/
        AD910x_MULTI( PinName CSB1 = PA_15, PinName CSB2 = PB_15, PinName MOSI = PA_7, PinName MISO = PB_4, PinName SCK = PB_3,
                PinName RESETB = PG_11, PinName TRIGGERB = PG_10 );
     
        /*** SPI register addresses ***/
        uint16_t reg_add[66] = {0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007, 0x0008, 0x0009, 0x000a, 0x000b, 0x000c, 0x000d, 0x000e, 0x001f, 0x0020, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027, 0x0028, 0x0029, 0x002a, 0x002b, 0x002c, 0x002d, 0x002e, 0x002f, 0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037, 0x003e, 0x003f, 0x0040, 0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0047, 0x0050, 0x0051, 0x0052, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057, 0x0058, 0x0059, 0x005a, 0x005b, 0x005c, 0x005d, 0x005e, 0x005f, 0x001e, 0x001d};
    
        // Function to set up SPI
        void spi_init( uint8_t reg_len, uint8_t mode, uint32_t hz);
    
        // Enable SPI device
        void spi_en_dev( bool dev_id );
        
        // Disable SPI devices
        void spi_disable_dev();
        
        // SPI write function
        void spi_write( bool dev_id, uint16_t addr, int16_t data );
    
        // SPI read function
        int16_t spi_read( bool dev_id, uint16_t addr );

        // Function to reset SPI register values
        void AD910x_reg_reset();
        
        // Function to display register data
        void print_data( uint16_t addr, uint16_t data );
    
        // Function to write to SRAM
        void AD910x_update_sram( bool devnum, int16_t data[] );
    
        // Function to display n SRAM data
        void AD910x_print_sram( bool devnum, uint16_t n );
    
        // Function to write to device SPI registers and display updated register values
        void AD910x_update_regs( bool devnum, uint16_t data[] );
          
        // Function to start pattern generation
        void AD910x_start_pattern();
        
        // Function to stop pattern generation
        void AD910x_stop_pattern();
        #pragma endregion
};
#endif
