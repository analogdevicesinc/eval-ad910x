# EVAL-AD910x
[Analog Devices Inc.](http://www.analog.com/en/index.html) Software driver for AD9102 or AD9106 evaluation board.

## Evaluation Boards/Products Supported
  * EVAL-AD9102 (AD9102)
  * EVAL-AD9106 (AD9106)

## Overview
These code files provide drivers to interface with AD9102 or AD9106 and communicate with EVAL-AD9102 or EVAL-AD9106 board. 
Also, it supported both single board, and multi-board synchronization.
This code was developed and tested on [SDP-K1 controller board](https://www.analog.com/en/resources/evaluation-hardware-and-software/evaluation-boards-kits/SDP-K1.html).

### Product details:
  * [AD9102](https://www.analog.com/en/products/ad9102.html)
  * [AD9106](https://www.analog.com/en/products/ad9106.html)

### Eval board details:
  * [EVAL-AD9102](https://www.analog.com/en/design-center/evaluation-hardware-and-software/evaluation-boards-kits/eval-ad9102.html)
  * [EVAL-AD9106](https://www.analog.com/en/design-center/evaluation-hardware-and-software/evaluation-boards-kits/eval-ad9106.html)

## How to Get Started
For more information about on how to evaluate AD9102/AD9106 evaluation board using mbed, please visit our Wiki User Guide below:
  * [AD9106 & AD9102 Evaluation Boards](https://wiki.analog.com/resources/eval/dpg/eval-ad9106)
  * [Evaluating the AD9106/AD9102 Digital-to-Analog and Waveform Generator Converter using MBED](https://wiki.analog.com/resources/eval/dpg/eval-ad9106-mbed)

### Hardware Setup
  * **Required Hardware:**
      * SDP-K1
      * EVAL-AD910x
      * USB cable (USB-A to USB-C)
    
  * **Optional Hardware:**
      * 9-12 V power supply
      * High-frequency continuous wave generator
    
  * Plug in the EVAL-AD910x board on SDP-K1 board (or any other Mbed enabled controller board) using the SDP connector and screws.
  * Connect SDP-K1 board to the PC using the USB cable.


### Software Setup
  * **Compiler/Builder IDE:** [Arm Keil Studio Cloud IDE](https://studio.keil.arm.com/)
  
  * **Driver:** [ADI Github EVAL-AD910x Repository](https://github.com/analogdevicesinc/eval-ad910x.git)
  * From the repository, import the source files by copying the repository HTTPS web URL and clone it to Keil Studio Cloud.
  * Select specific build target, SDP-K1. (SDP-K1 must be detected as connected device)
  * User has two method to load the driver into SDP-K1 controller board.
      * Using **Keil Studio Cloud Run Terminal**:
          * Open Preferences>Open UI Settings>Extensions>Run and configure the following:
              * Flash Mode: cmsis
              * Verify Flash: Unchecked
          * Click Open Serial Monitor and set-up baud rate to 115200.
          * Click Run to build the source code file and load to SDP-K1 controller board.
      
      * Using separate **Terminal Emulator (TeraTerm, Putty)**:
          * Build the source code thru Keil Studio Cloud.
          * Drag and drop binary (.bin) into SDP-K1 controller board.
          * Open any terminal emulator, and configure the following:
              * Port Number
              * Baud Rate
          * After setting up, click Connect.
  * Refer to wiki user guide for different configuration set-up.

A detailed user guide on how to use SDP-K1 board on Mbed platform is available 
here: https://wiki.analog.com/resources/tools-software/mbed


## Helpful Links
  * [Additional detailes on SDP-K1 controller board](https://os.mbed.com/platforms/SDP_K1/)
  * [Arm Mbed OS 6](https://os.mbed.com/docs/mbed-os/v6.5/introduction/index.html)
  * [Arm Keil Studio Cloud User Guide](https://developer.arm.com/documentation/102497/1-7/Introduction?lang=en)

## License
For licenses, please read the following:
  * Main License: LICENSE
  * Other Licenses: NOTICE

## Support
For any further questions, feel free to ask at [EngineerZone](https://ez.analog.com/data_converters/high-speed_dacs/). Also, for common questions, please visit [FAQ](https://ez.analog.com/data_converters/high-speed_dacs/w/documents/15701/ad9106-ad9102-low-power-dac-and-waveform-generator-faqs).
