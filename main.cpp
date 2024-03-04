/*******************************************************************************
    @file:   main.cpp
    
    @brief:  Main module for EVAL-AD910x application interface
--------------------------------------------------------------------------------
    Copyright (c) 2024 Analog Devices, Inc. All Rights Reserved.
    This software is proprietary to Analog Devices, Inc. and its licensors.

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License. 
*******************************************************************************/

/*******************************************************************************
    About AD910x
        * Product Page: https://www.analog.com/AD9102, https://www.analog.com/AD9106
        * Eval Page:    https://www.analog.com/eval-ad9102, https://www.analog.com/eval-ad9106
        * Wiki Guide:   https://wiki.analog.com/resources/eval/dpg/eval-ad9106-mbed

    User Instructions
        * To use the code for single-board evaluation: Remove / * in Line 84 and * / in Line 144
        * To use the code for multi-board evaluation: Remove / * in Line 145 and * / in Line 202
*******************************************************************************/

// *** Libraries *** //
#include "mbed.h"
#include "platform/mbed_thread.h"
#include "config.h"
#include "ad910x.h"

// *** Defines for UART Protocol *** //
#define BAUD_RATE       115200

AD910x_SINGLE device_single;                        // Board variable definition for single-board use case (see ad910x.h)          
AD910x_MULTI device_multi;                          // Board variable definition for multi-board use case (see ad910x.h)

DigitalOut en_cvddx( PG_7, 0 );                     // DigitalOut instance for enable pin of on-board oscillator supply
DigitalOut shdn_n_lt3472( PG_9, 0 );                // DigitalOut instance for shutdown/enable pin of on-board amplifier supply

// * Configure and instantiate UART protocol and baud rate * //
UnbufferedSerial pc( USBTX, USBRX, BAUD_RATE );

#pragma region: Function Declarations
/*** Single-Board ***/
void setup_device_single( void );
void print_menu_single( void );
void print_prompt1_single( void );
void print_prompt2_single( void );
void print_title_single( void );
void sel_example_single( char example );
void prog_example1_single( void );
void prog_example2_single( void );
void prog_example3_single( void );
void prog_example4_single( void );
void prog_example5_single( void );
void prog_example6_single( void );
void stop_example_single( void );

/*** Multi-Board ***/
void setup_device_multi( void );
void print_menu_multi( void );
void print_menu_ext( void );
void print_prompt1_multi( void );
void print_prompt2_multi( void );
void print_prompt2_ext( void );
void print_title_multi( void );	
void sel_example_multi( bool dev_num, char example );	
void prog_example1_multi( bool dev_num );	
void prog_example2_multi( bool dev_num );	
void prog_example3_multi( bool dev_num );	
void prog_example4_multi( bool dev_num );	
void prog_example5_multi( bool dev_num );	
void prog_example6_multi( bool dev_num );
void stop_example_multi( void );

/*** Common Functions ***/
void print_prompt3( void );
void print_prompt4( void );
#pragma endregion

// *** Main Functions *** //
/*
#pragma region: Main function for single-board use case
int main() {
    char ext_clk = 'y';
    char amp_out = 'n';
    char stop = 'n';
    char exit = 'n';
    char example = 1;
    uint8_t connected = 1;
    
    device_single.resetb = 1;
    device_single.triggerb = 1;
    
    setup_device_single();
    print_title_single();
    
    while( connected == 1 ) {
        print_prompt1_single();
        while( pc.readable() == 0 );
        ext_clk = getchar();
        if ( ext_clk == 'y' ) {
            en_cvddx = 0;
            printf("\nPlease connect external clock source to J10.\n");
        } else {
            en_cvddx = 1;
            printf("\nOn-board oscillator supply is enabled.\n");
        }
        
        thread_sleep_for(500);
        print_prompt2_single();
        while( pc.readable() == 0 );
        amp_out = getchar();
        if ( amp_out == 'y' ) {
            shdn_n_lt3472 = 1;
            printf("\nOn-board amplifier supply is enabled.\n");
        } else {
            shdn_n_lt3472 = 0;
        }
        
        print_menu_single();
        while( pc.readable() == 0 );
        example = getchar();
        sel_example_single( example );
        
        print_prompt3();
        while( pc.readable() == 0 );
        stop = getchar();		
        if ( stop == 'y' ) {	
            stop_example_single();	
            stop = 'n';	
        } else {	
            stop_example_single();
            connected = 0;	
            print_prompt4();		
        }	
    }
    
    return 0;
}
#pragma endregion
*/
/*
#pragma region: Main function for multi-board use case
int main() {
    char amp_out = 'n';	
    char stop = 'n';	
    char exit = 'n';	
    char example_b1 = 3;	
    char example_b2 = 3;	
    uint8_t connected = 1;
    bool device2;
    	
    device_multi.resetb = 1;	
    device_multi.triggerb = 1;
    
    setup_device_multi();	
    print_title_multi();	
    
    while( connected == 1 ) {
        print_prompt1_multi();		
        print_prompt2_multi();	
        while( pc.readable() == 0 );	
        amp_out = getchar();		
        if ( amp_out == 'y' ) {	
            shdn_n_lt3472 = 1;	
            print_prompt2_ext();	
        } else {	
            shdn_n_lt3472 = 0;	
        }

        device2 = false;                            // Board 1 selection
        print_menu_multi();	
        while( pc.readable() == 0 );
        example_b1 = getchar();
        sel_example_multi( device2, example_b1 );
        
        device2 = true;                             // Board 2 selection
        print_menu_ext();
        while( pc.readable() == 0 );		
        example_b2 = getchar();	
        sel_example_multi( device2, example_b2 );
        
        print_prompt3();	
        while( pc.readable() == 0 );
        stop = getchar();		
        if ( stop == 'y' ) {	
            stop_example_multi();	
            stop = 'n';	
        } else {	
            stop_example_multi();
            connected = 0;	
            print_prompt4();		
        }	
    }
    
    return 0;
}
#pragma endregion
*/

#pragma region (Function Definitions)
#pragma region: Functions to set up SPI communication
void setup_device_single() {
    device_single.spi_init( WORD_LEN, POL, FREQ );
    device_single.AD910x_reg_reset();
}
void setup_device_multi() {
    device_multi.spi_init( WORD_LEN, POL, FREQ );
    device_multi.AD910x_reg_reset();
}
#pragma endregion
#pragma region: Functions to print the title block when program first starts
void print_title_single() {
    printf("\n***********************************************************************\n");
    printf("* EVAL-%s Demonstration Program                                   *\n", ACTIVE_DEVICE);
    printf("*                                                                     *\n");
    printf("* This program demonstrates how to generate waveforms with the %s *\n", ACTIVE_DEVICE);
    printf("* using example register configurations in the datasheet.             *\n");
    printf("* This program is developed on Mbed OS version 6.                     *\n");
    printf("***********************************************************************\n");   
}
void print_title_multi() {	
    printf("\n***********************************************************************\n");	
    printf("* EVAL-%s Demonstration Program                                   *\n", ACTIVE_DEVICE);	
    printf("*                                                                     *\n");	
    printf("* This program demonstrates multi-chip synchronization using two %ss *\n", ACTIVE_DEVICE);	
    printf("* using example register configurations in the datasheet.             *\n");	
    printf("* This program is developed on Mbed OS version 6.                     *\n");	
    printf("***********************************************************************\n");   	
}
#pragma endregion
#pragma region: Functions to print the first prompt/question on whether to set up the on-board oscillator/s
void print_prompt1_single() {
    printf( "\nUsing external clock source?\n" );
    printf( "If yes, press y. If no, press any other key.\n" );
}
void print_prompt1_multi() {
    printf( "\nPlease connect clock inputs of both evaluation boards to a common clock source.\n" );	
    printf( "Configure JP1 and JP2 accordingly.\n" );	
    printf( "Make sure connector cables for both clock inputs are of same length.\n" );
}
#pragma endregion
#pragma region: Functions to print the next prompt/question on whether to set up the on-board amplifier/s
void print_prompt2_single() {
    printf( "\nConnected DAC outputs to on-board amplifiers?\n" );
    printf( "If yes, press y. If no, press any other key.\n" );
}
void print_prompt2_multi() {	
    printf( "\nConnected DAC outputs to on-board amplifiers?\n" );	
    printf( "(To ensure synchronization between the two devices, output configuration in both boards should be the same.)\n" );	
    printf( "If yes, connect a 7V to 12V 30W wall wart to SDP-K1 then press 'y'. If no, press any other key.\n" );	
}	
void print_prompt2_ext() {	
    printf("\nOn-board amplifiers are enabled for both boards.\n");	
}
#pragma endregion
#pragma region: Functions to print the summary of and select playable AD910x waveform configuration examples
void print_menu_single() {
    printf("\nExample Summary\n");
    if ( ACTIVE_DEVICE == "AD9106" ) {
        printf("   1 - 4 Gaussian Pulses with Different Start Delays and Digital Gain Settings\n");
        printf("   2 - 4 Pulses Generated from an SRAM Vector\n");
        printf("   3 - 4 Pulsed DDS-Generated Sine Waves with Different Start Delays and Digital Gain Settings\n");
        printf("   4 - Pulsed DDS-Generated Sine Wave and 3 Sawtooth Generator Waveforms\n");
        printf("   5 - Pulsed DDS-Generated Sine Waves Amplitude-Modulated by an SRAM Vector\n");
        printf("   6 - DDS-Generated Sine Wave and 3 Sawtooth Waveforms\n");
    } else if( ACTIVE_DEVICE == "AD9102" ) {
        printf("   1 - Gaussian Pulse\n");
        printf("   2 - Pulse Generated from an SRAM Vector\n");
        printf("   3 - Pulsed DDS-Generated Sine Wave\n");
        printf("   4 - Sawtooth Waveform\n");
        printf("   5 - Pulsed DDS-Generated Sine Wave Amplitude-Modulated by an SRAM Vector\n");
        printf("   6 - DDS-Generated Sine Wave\n");
    }
    printf("Select an option: \n");
}
void print_menu_multi() {	
    printf("\nExample Summary\n");	
    if ( ACTIVE_DEVICE == "AD9106" ) {	
        printf("   1 - 4 Gaussian Pulses with Different Start Delays and Digital Gain Settings\n");	
        printf("   2 - 4 Pulses Generated from an SRAM Vector\n");	
        printf("   3 - 4 Pulsed DDS-Generated Sine Waves with Different Start Delays and Digital Gain Settings\n");	
        printf("   4 - Pulsed DDS-Generated Sine Wave and 3 Sawtooth Generator Waveforms\n");	
        printf("   5 - Pulsed DDS-Generated Sine Waves Amplitude-Modulated by an SRAM Vector\n");	
        printf("   6 - DDS-Generated Sine Wave and 3 Sawtooth Waveforms\n");	
    } else if( ACTIVE_DEVICE == "AD9102" ) {	
        printf("   1 - Gaussian Pulse\n");	
        printf("   2 - Pulse Generated from an SRAM Vector\n");	
        printf("   3 - Pulsed DDS-Generated Sine Wave\n");	
        printf("   4 - Sawtooth Waveform\n");	
        printf("   5 - Pulsed DDS-Generated Sine Wave Amplitude-Modulated by an SRAM Vector\n");	
        printf("   6 - DDS-Generated Sine Wave\n");	
    }	
    printf("Select an option for board 1: \n");	
}	
void print_menu_ext() {	
    printf("\nSelect an option for board 2: \n");	
}
void sel_example_single( char example ) {
    switch ( example ) {
            case '1':
                prog_example1_single();
                break;
            case '2':
                prog_example2_single();
                break;
            case '3':
                prog_example3_single();
                break;
            case '4':
                prog_example4_single();
                break;
            case '5':    
                prog_example5_single();
                break;
            case '6':
                prog_example6_single();
                break;
            default:
                printf("\n****Invalid Entry****\n\n");
                break;
        }
    device_single.AD910x_start_pattern();
}
void sel_example_multi( bool dev_num, char example ) {	
    switch ( example ) {	
        case '1':	
            prog_example1_multi( dev_num );	
            break;	
        case '2':	
            prog_example2_multi( dev_num );	
            break;	
        case '3':	
            prog_example3_multi( dev_num );	
            break;	
        case '4':	
            prog_example4_multi( dev_num );	
            break;
        case '5':    	
            prog_example5_multi( dev_num );	
            break;	
        case '6':	
            prog_example6_multi( dev_num );	
            break;	
        default:	
            printf( "\n****Invalid Entry****\n\n" );	
            break;
    }
    if ( dev_num ) {
        device_multi.AD910x_start_pattern();
    }
}
#pragma endregion
#pragma region: Functions to play Example 1
void prog_example1_single() {
    if ( ACTIVE_DEVICE == "AD9106" ) {
        printf("\n4 Gaussian Pulses with Different Start Delays and Digital Gain Settings\n");
        thread_sleep_for(500);
        device_single.AD910x_update_sram( example1_RAM_gaussian );
        device_single.AD910x_update_regs( AD9106_example1_regval );
    } else if( ACTIVE_DEVICE == "AD9102" ) {
        printf("\nGaussian Pulse\n");
        thread_sleep_for(500);
        device_single.AD910x_update_sram( example1_RAM_gaussian );
        device_single.AD910x_update_regs( AD9102_example1_regval );
    }
}
void prog_example1_multi( bool dev_num ) {	
    if ( ACTIVE_DEVICE == "AD9106" ) {	
        printf("\n4 Gaussian Pulses with Different Start Delays and Digital Gain Settings\n");	
        thread_sleep_for(500);	
        device_multi.AD910x_update_sram( dev_num, example1_RAM_gaussian );	
        device_multi.AD910x_update_regs( dev_num, AD9106_example1_regval );	
    } else if( ACTIVE_DEVICE == "AD9102" ) {	
        printf("\nGaussian Pulse\n");	
        thread_sleep_for(500);	
        device_multi.AD910x_update_sram( dev_num, example1_RAM_gaussian );	
        device_multi.AD910x_update_regs( dev_num, AD9102_example1_regval );	
    }	
}
#pragma endregion
#pragma region: Functions to play Example 2
void prog_example2_single() {
    if ( ACTIVE_DEVICE == "AD9106" ) {
        printf("\n4 Pulses Generated from an SRAM Vector\n");
        thread_sleep_for(500);
        device_single.AD910x_update_sram( example2_4096_ramp );
        device_single.AD910x_update_regs( AD9106_example2_regval );
    } else if( ACTIVE_DEVICE == "AD9102" ) {
        printf("\nPulse Generated from an SRAM Vector\n");
        thread_sleep_for(500);
        device_single.AD910x_update_sram( example2_4096_ramp );
        device_single.AD910x_update_regs( AD9102_example2_regval );
    }
}
void prog_example2_multi( bool dev_num ) {	
    if ( ACTIVE_DEVICE == "AD9106" ) {	
        printf("\n4 Pulses Generated from an SRAM Vector\n");	
        thread_sleep_for(500);	
        device_multi.AD910x_update_sram( dev_num, example2_4096_ramp );	
        device_multi.AD910x_update_regs( dev_num, AD9106_example2_regval );	
    } else if( ACTIVE_DEVICE == "AD9102" ) {	
        printf("\nPulse Generated from an SRAM Vector\n");	
        thread_sleep_for(500);	
        device_multi.AD910x_update_sram( dev_num, example2_4096_ramp );	
        device_multi.AD910x_update_regs( dev_num, AD9102_example2_regval );	
    }	
}
#pragma endregion
#pragma region: Functions to play Example 3
void prog_example3_single() {
    if ( ACTIVE_DEVICE == "AD9106" ) {
        printf("\n4 Pulsed DDS-Generated Sine Waves with Different Start Delays and Digital Gain Settings\n");
        thread_sleep_for(500);
        device_single.AD910x_update_regs( AD9106_example3_regval );
    } else if( ACTIVE_DEVICE == "AD9102" ) {
        printf("\nPulsed DDS-Generated Sine Wave\n");
        thread_sleep_for(500);
        device_single.AD910x_update_regs( AD9102_example3_regval );
    }       
}
void prog_example3_multi( bool dev_num ) {	
    if ( ACTIVE_DEVICE == "AD9106" ) {	
        printf("\n4 Pulsed DDS-Generated Sine Waves with Different Start Delays and Digital Gain Settings\n");	
        thread_sleep_for(500);	
        device_multi.AD910x_update_regs( dev_num, AD9106_example3_regval );	
    } else if( ACTIVE_DEVICE == "AD9102" ) {	
        printf("\nPulsed DDS-Generated Sine Wave\n");	
        thread_sleep_for(500);	
        device_multi.AD910x_update_regs( dev_num, AD9102_example3_regval );	
    }     	
}
#pragma endregion
#pragma region: Functions to play Example 4
void prog_example4_single() {
    if ( ACTIVE_DEVICE == "AD9106" ) {
        printf("\nPulsed DDS-Generated Sine Wave and 3 Sawtooth Generator Waveforms\n");
        thread_sleep_for(500);
        device_single.AD910x_update_regs( AD9106_example4_regval );
    } else if( ACTIVE_DEVICE == "AD9102" ) {
        printf("\nSawtooth Waveform\n");
        thread_sleep_for(500);
        device_single.AD910x_update_regs( AD9102_example4_regval );
    }       
}
void prog_example4_multi( bool dev_num ) {	
    if ( ACTIVE_DEVICE == "AD9106" ) {	
        printf("\nPulsed DDS-Generated Sine Wave and 3 Sawtooth Generator Waveforms\n");	
        thread_sleep_for(500);	
        device_multi.AD910x_update_regs( dev_num, AD9106_example4_regval );	
    } else if( ACTIVE_DEVICE == "AD9102" ) {	
        printf("\nSawtooth Waveform\n");	
        thread_sleep_for(500);	
        device_multi.AD910x_update_regs( dev_num, AD9102_example4_regval );	
    }     	
}
#pragma endregion
#pragma region: Functions to play Example 5
void prog_example5_single() {
    if ( ACTIVE_DEVICE == "AD9106" ) {
        printf("\n4 Pulses Generated from an SRAM Vector\n");
        thread_sleep_for(500);
        device_single.AD910x_update_sram( example5_RAM_gaussian );
        device_single.AD910x_update_regs( AD9106_example5_regval );
    } else if ( ACTIVE_DEVICE == "AD9102" ) {
        printf("\nPulse Generated from an SRAM Vector\n");
        thread_sleep_for(500);
        device_single.AD910x_update_sram( example5_RAM_gaussian );
        device_single.AD910x_update_regs( AD9102_example5_regval );
    }  
}
void prog_example5_multi( bool dev_num ) {	
    if ( ACTIVE_DEVICE == "AD9106" ) {	
        printf("\n4 Pulses Generated from an SRAM Vector\n");	
        thread_sleep_for(500);	
        device_multi.AD910x_update_sram( dev_num, example5_RAM_gaussian );	
        device_multi.AD910x_update_regs( dev_num, AD9106_example5_regval );	
    } else if ( ACTIVE_DEVICE == "AD9102" ) {	
        printf("\nPulse Generated from an SRAM Vector\n");	
        thread_sleep_for(500);	
        device_multi.AD910x_update_sram( dev_num, example5_RAM_gaussian );	
        device_multi.AD910x_update_regs( dev_num, AD9102_example5_regval );	
    }	
}
#pragma endregion
#pragma region: Functions to play Example 6
void prog_example6_single() {
    if ( ACTIVE_DEVICE == "AD9106" ) {
        printf("\nDDS-Generated Sine Wave and 3 Sawtooth Waveforms\n");
        thread_sleep_for(500);
        device_single.AD910x_update_regs( AD9106_example6_regval );
    } else if( ACTIVE_DEVICE == "AD9102" ) {
        printf("\nDDS-Generated Sine Wave\n");
        thread_sleep_for(500);
        device_single.AD910x_update_regs( AD9102_example6_regval );
    }      
}
void prog_example6_multi( bool dev_num ) {	
    if ( ACTIVE_DEVICE == "AD9106" ) {	
        printf("\nDDS-Generated Sine Wave and 3 Sawtooth Waveforms\n");	
        thread_sleep_for(500);	
        device_multi.AD910x_update_regs( dev_num, AD9106_example6_regval );	
    } else if( ACTIVE_DEVICE == "AD9102" ) {	
        printf("\nDDS-Generated Sine Wave\n");	
        thread_sleep_for(500);	
        device_multi.AD910x_update_regs( dev_num, AD9102_example6_regval );	
    }   	
}
#pragma endregion
#pragma region: Function to print prompt/question on whether to choose another pattern
void print_prompt3() {
    printf( "\nChoose another pattern?\n" );
    printf( "y       -  Select new pattern.\n" );
    printf( "Any key -  Exit program.\n" );
}
#pragma endregion
#pragma region: Function to stop pattern generation
void stop_example_single() {
    device_single.AD910x_stop_pattern();
    printf( "\nPattern stopped.\n" );
}
void stop_example_multi() {
    device_multi.AD910x_stop_pattern();
    printf( "\nPattern stopped.\n" );
}
#pragma endregion
#pragma region: Function to print prompt/question on whether to exit the program
void print_prompt4() {
    printf("\nExiting program...\n");
}
#pragma endregion
#pragma endregion
