# S2DP_PIC12F509

S2DP_PIC12F509 is a simple serial data programmer which runs on PIC12F509.
It controls four system signals, DATA, CLOCK, WP_, and RESET_, on boot-time using GIPO as follows: \*1

1. Set direction of the GPIO into INPUT
2. Wait RESET_ turn into HIGH (disabled)
3. Set direction of the GPIO into OUTPUT
4. Set RESET_ into LOW (enabled) and WP_ into HIGH (unprotected)
5. Write data one bit by one bit using DATA and CLOCK
6. Set direction of the GPIO into INPUT again
7. Sleep

\*1 Expect that DATA, CLOCK, and WP_ are pull-downed and RESET_ is pull-upped

## PIC12F509 Pin Assign
- 1 VDD
- 2 GP5: DATA
  - Should be pull-downed
- 3 GP4: WP_
  - Should be pull-downed
- 4 GP3: Unused (INPUT)
- 5 GP2: RESET_
  - Should be pull-upped
- 6 GP1: CLOCK
  - Should be pull-downed
- 7 GP0: Unused (OUTPUT with LOW)
- 8 VSS

## How to Build
### Setup Toolchain
Download and install MPLAB X IDE.

https://www.microchip.com/mplab/mplab-x-ide

![MPLAB X IDE installer](https://github.com/tanahome/S2DP_PIC12F509/blob/images/images/xide_installer.png)

Download and install MPLAB XC8 Compiler.

https://www.microchip.com/mplab/compilers

![MPLAB XC8 Compiler installer](https://github.com/tanahome/S2DP_PIC12F509/blob/images/images/xc8_installer.png)

Startup MPLAB X IDE.

![MPLAB X IDE desktop icon](https://github.com/tanahome/S2DP_PIC12F509/blob/images/images/xide_icon.png)

### Create S2DP Project
Select `New Project...` from `File` menu.

![Select New Project](https://github.com/tanahome/S2DP_PIC12F509/blob/images/images/newproject1.png)

Select `Microchip Embedded` from `Categories:` and `Standalone Project` from `Projects:`.

![Choose Project](https://github.com/tanahome/S2DP_PIC12F509/blob/images/images/newproject2.png)

Select `PIC12F509` as `Device:`.

![Select Device](https://github.com/tanahome/S2DP_PIC12F509/blob/images/images/newproject3.png)

Do nothing.  Just press `Next >`.

![Select Header](https://github.com/tanahome/S2DP_PIC12F509/blob/images/images/newproject4.png)

Select using PIC writer if you have.  If you use universal programmer such as TL866CS, select
`PICKit3` or something.

![Select Tool](https://github.com/tanahome/S2DP_PIC12F509/blob/images/images/newproject5.png)

Select `XC8` as a compiler.

![Select Compiler](https://github.com/tanahome/S2DP_PIC12F509/blob/images/images/newproject6.png)

Enter project name, e.g, *S2DP*, in `Project Name:`

![Select Project Name and Folder](https://github.com/tanahome/S2DP_PIC12F509/blob/images/images/newproject7.png)

Project *S2DP* has been created.

![Projects](https://github.com/tanahome/S2DP_PIC12F509/blob/images/images/newproject8.png)

### Compile S2DP
Download main.c from [GitHub repository](https://github.com/tanahome/S2DP_PIC12F509/blob/master/main.c).

Import main.c into the project.  Right click `Source Files` of the project tree of *S2DP*, select `Add Existing Item...` and select downloaded main.c file.

![Add main.c](https://github.com/tanahome/S2DP_PIC12F509/blob/images/images/compile1.png)

If main.c is imported successfully, it would appear in `Source Files`.

![Imported main.c](https://github.com/tanahome/S2DP_PIC12F509/blob/images/images/compile2.png)

Double click main.c and show it in the right area.

![Show main.c](https://github.com/tanahome/S2DP_PIC12F509/blob/images/images/compile3.png)

Press the hammer icon to test the compiler.

![Build button](https://github.com/tanahome/S2DP_PIC12F509/blob/images/images/compile4.png)



If compiled successfully, the following message is shown in the right bottom area

    make -f nbproject/Makefile-default.mk SUBPROJECTS= .build-conf
    make[1]: Entering directory 'C:/Users/yourname/MPLABXProjects/S2DP.X'
    make  -f nbproject/Makefile-default.mk dist/default/production/S2DP.X.production.hex
    make[2]: Entering directory 'C:/Users/yourname/MPLABXProjects/S2DP.X'

    ....

    BUILD SUCCESSFUL (total time: 2s)
    Loading code from C:/Users/yourname/MPLABXProjects/S2DP.X/dist/default/production/S2DP.X.production.hex...
    Loading completed

_C:/Users/yourname/MPLABXProjects/S2DP.X/dist/default/production/S2DP.X.production.hex_ is a file to be programmed to PIC device.

Focus on main.c.  Replace both DATALEN and DATA macro with an appropriate value what you want to program.

Before:

    #define DATALEN 16
    #define DATA {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}

After (example with 12Byte data):

    #define DATALEN 12
    #define DATA {0x48,0x65,0x6C,0x6C,0x6F,0x20,0x57,0x6F,0x72,0x6C,0x64,0x00}

Build again.  Press the hammer icon.

![Build button](https://github.com/tanahome/S2DP_PIC12F509/blob/images/images/compile4.png)

If successfully built, a _hex_ file is appeared in the output directory after the following message is shown.

    make -f nbproject/Makefile-default.mk SUBPROJECTS= .build-conf
    make[1]: Entering directory 'C:/Users/yourname/MPLABXProjects/S2DP.X'
    make  -f nbproject/Makefile-default.mk dist/default/production/S2DP.X.production.hex
    make[2]: Entering directory 'C:/Users/yourname/MPLABXProjects/S2DP.X'

    ....

    BUILD SUCCESSFUL (total time: 2s)
    Loading code from C:/Users/yourname/MPLABXProjects/S2DP.X/dist/default/production/S2DP.X.production.hex...
    Loading completed

## How to Write Program to PIC Device

This document shows the way to write compiled program to PIC device with TL866CS as an  example.  If you are using another PIC writer, please follow its usage.

Startup MiniPro Programmer.

![MiniPro desktop icon](https://github.com/tanahome/S2DP_PIC12F509/blob/images/images/program1.png)

Select `Search and Select IC` from `Select IC` menu.

![Search and select IC](https://github.com/tanahome/S2DP_PIC12F509/blob/images/images/program2.png)

Select `PIC12F509` as device.

![Select PIC12F509](https://github.com/tanahome/S2DP_PIC12F509/blob/images/images/program3.png)

Open _hex_ file.  Select `Open` from `File` menu.

![Open file](https://github.com/tanahome/S2DP_PIC12F509/blob/images/images/program4.png)

Open _S2DP.X.production.hex_ file generated by MPLAB Toolchain.

![Select hex file](https://github.com/tanahome/S2DP_PIC12F509/blob/images/images/program5.png)

`File load Options` window is shown.  Just press `OK` button.

![File load options](https://github.com/tanahome/S2DP_PIC12F509/blob/images/images/program6.png)

Select `Program` from `Device` menu.

![Program](https://github.com/tanahome/S2DP_PIC12F509/blob/images/images/program7.png)

`Chip Program` window is shown.  Set PIC12F509 device on TL866CS and press `Program` button.

![Chip Program window](https://github.com/tanahome/S2DP_PIC12F509/blob/images/images/program8.png)


If successfully programmed, `Programming Successful!` message is shown.

![Programming successful](https://github.com/tanahome/S2DP_PIC12F509/blob/images/images/program9.png)
