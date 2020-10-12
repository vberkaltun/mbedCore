# Toolchain and Codebase Setup for The MbedOS + VS Code
Document how to set up a MbedOS toolchain to develop embedded firmware with Visual Studio Code. A lot of this information was taken from Mbed Official Website, 
then adjusted to fit Hukseflux needs.

This will allow you to develop firmware using either a NUCLEO development board, or a ST-Link programmer. For this description, the use of a STM32F446RE NUCLEO board is assumed. 
The intended audience for this page will know what to adjust to get another type of target device up-and-running.

<!-- toc -->

## Contents

- [Pre-requisite Setup](#Pre-requisite-Setup)
  * [Environment Variables](#Environment-Variables)
  * [Configuration of Visual Studio Code](#Configuration-of-Visual-Studio-Code)
- [Project Setup](#Project-Setup)
  * [Automatic Setup](#Automatic-Setup)
  * [Manual Setup](#Manual-Setup)
- [Post-requisite Setup](#Post-requisite-Setup)
- [Compile And Test](#Compile-And-Test)
- [Troubleshooting](#Troubleshooting)
- [Resources](#Resources)

## Pre-requisite Setup

The following software is needed. Before all installations, create the folder `C:\VSARM` and then start the installations:

| Tables         | Version | Installation Path | Description |
| :------------- | -------:| -----------------:| -----------:|
| [GNU Arm Embedded Toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads) | v8.2.1 | `C:\VSARM\armgcc` | Download the Windows 32-bit installer for Windows 7 and later. |
| [OpenOCD](https://freddiechopin.info/en/download/category/4-openocd) | v0.10.0 | `C:\VSARM\openocd` | `NA` |
| [Git](https://git-scm.com/download/win) | v2.28.0 | `C:\VSARM\git` | `NA` |
| [Python 2](https://www.python.org/downloads/windows/) | v2.7.18 | `C:\VSARM\python27` | `NA` |
| [STMicroelectronics STlink Tools](https://github.com/stlink-org/stlink/releases/tag/v1.6.1) | v1.6.1 | `C:\VSARM\stlink` | Download the binaries. |
| [Mbed-CLI](https://pypi.org/project/mbed-cli/#:~:text=Mbed%20CLI%20is%20a%20Python,to%20install%20Mercurial%20and%20Git.) | v1.10.4 | `NA` | Run `pip install mbed-cli` in command prompt. |
| [ST-LINK USB driver](https://my.st.com/content/my_st_com/en/products/development-tools/software-development-tools/stm32-software-development-tools/stm32-utilities/stsw-link009.html) | v2.0.1 | `NA` | `NA` |
| [Visual Studio Code](https://code.visualstudio.com/) | v1.50.0 | `NA` |  Download the system installer, not the user installer. |

### Environment Variables

1. Open Windows **Control Panel** and navigate to **System** (Control Panel->System and Security->System).
2. After the **System** screen appears, select **Advanced system settings**.
3. This will open the **System Properties** window. Select the **Advanced** tab and then the **Environment Variables** button.
4. Under the **System variables** section, scroll down and highlight the **Path** variable. Click the **Edit** button.
5. In the Edit screen, click **New** and add the path to:

    - `C:\VSARM\stlink\bin`
    - `C:\VSARM\openocd\bin`
    - `C:\VSARM\armcc\bin`

### Configuration of Visual Studio Code

1. Open Visual Studio Code.
2. Press **`Ctrl-Shift-X`** to open the Extension tab and install the following extensions:

    - `C/C++`
    - `Cortex Debug`

3. Press **`F1`** and type **`Open Settings (JSON)`**. Open the user settings .JSON file and add the following codes:

```json
// Place your key bindings in this file to override the defaults
{
    "cortex-debug.armToolchainPath": "${env:VSARM}\\armcc\\bin\\"
}
```

Next, add keyboard shortcuts to the **`Compile Firmware (Debug)`** and **`Load Firmware (Debug)`** commands. Press **`F1`** and type **`Open Keyboard Shortcuts (JSON)`**. Open the keyboard shortcuts .JSON file and add the following codes:

```json
// Place your key bindings in this file to override the defaults
[
    {
        "key": "f5",
        "command": "workbench.action.tasks.runTask",
        "args": "Compile Firmware (Debug)"
    },
    {
        "key": "f6",
        "command": "workbench.action.tasks.runTask",
        "args": "Load Firmware (Debug)"
    }
]
```

## Project Setup

The project can be set up in two different ways: automatic and manual. In both ways, your machine has to be connected to the internet at least one time. In this period, all dependencies are collected in your pc for the current project. Then, you can easily disconnect your machine from the internet.

### Automatic Setup

1. Open a command prompt.
2. Type **`git clone https://github.com/vberkaltun/mbedCore.git`**.

After these steps, all dependencies will be downloaded to your current directory.

### Manual Setup

1. Open a command prompt.
2. Type **`mbed new THIS_IS_YOUR_APP_NAME`** and run.
4. Create a **`main.cpp file`** in your root of the application. Open the file and add the following codes:

```cpp
#include "mbed.h"

int main()
{
    // Initialise the digital pin LED1 as an output
    DigitalOut led(LED1);

    while (true)
    {
        led = !led;
        wait_us(1000000);
    }
}
```

4. Open **`mbed_app.json`** in the root of the application and replace it with the following content:

```json
{
    "requires": ["bare-metal"],
    "target_overrides": {
        "*": {
            "target.c_lib": "small"
        }
    }
}
```

## Post-requisite Setup

1. Open the **`.vscode/settings.json`** file in the application folder.
2. Update the values of given parameters based on your installations:

| Tables         | Description  |
| :------------- | :----------- |
| `PROJECT_PATH` | The root path of your application, for example **`C:/Users/Dekimo/Documents/GitHub/mbedCore`**. |
| `DEVELOPMENT_BOARD_NAME` |The development board name, for example: **`NUCLEO_F446RE`**. For the full list of supported the devices, run the **`mbed target --supported`** in the root of the application. |
| `DEVELOPMENT_TOOLCHAIN` | The compiler toolchain, for example: **`GCC_ARM`**. This documentation is totaly based on **`GCC_ARM`** compiler. For the full list of supported the devices, run the **`mbed target --supported`** in the root of the application. |
| `COMPILE_MEMORY_ADDRESS` | The starting address of the firmware file, for example: **`0x08000000`**. |
| `ARM_PATH` | The root path of the ARM compiler, for example: **`C:/VSARM/armgcc`**. |
| `ARM_PATH_EXEC_FILENAME` | The executable filepath of the ARM compiler, for example: **`${config:ARM_PATH}/bin/arm-none-eabi-gdb.exe`**. |
| `OPENOCD_PATH` | The root path of the OpenOCD compiler, for example: **`C:/VSARM/openocd`**. |
| `OPENOCD_EXEC_FILENAME` | The executable filepath of the OpenOCD compiler, for example: **`${config:OPENOCD_PATH}/bin/openocd.exe`**. |
| `OPENOCD_CONFIG_FILENAME` | The config filepath of the OpenOCD compiler, for example: **`${config:OPENOCD_PATH}/scripts/board/st_nucleo_f4.cfg`**. |
| `OPENOCD_INTERFACE_FILENAME` | The interface filepath of the OpenOCD compiler, for example: **`${config:OPENOCD_PATH}/scripts/interface/stlink-v2-1.cfg`**. |

## Compile And Test

Press **`F5`** to build the code and **`F6`** to program the target device (don't forget to connect your development board). If all went well, the on-board LED should now be blinking, sometimes slow, sometimes fast.

## Troubleshooting

## Resources

1. [Exporting to Makefile fails to build on Windows](https://github.com/ARMmbed/mbed-os/issues/6335)
2. [Questions › Mbed-CLI export Simplicity Studio](https://os.mbed.com/questions/83006/Mbed-CLI-export-Simplicity-Studio/)
3. [Handbook › Exporting to GCC ARM Embedded](https://os.mbed.com/handbook/Exporting-to-GCC-ARM-Embedded)
4. [Docs › Build tools › Third-party build tools › Exporting](https://os.mbed.com/docs/mbed-os/v6.3/build-tools/third-party-build-tools.html#exporting-from-arm-mbed-cli)
5. [Docs › Tools › Developing: Mbed CLI › Installation and setup › After installation - configuring Mbed CLI](https://os.mbed.com/docs/mbed-os/v5.12/tools/after-installation-configuring-mbed-cli.html)
6. [Docs › Build tools › Third-party build tools › Exporting](https://os.mbed.com/docs/mbed-os/v6.3/build-tools/third-party-build-tools.html)
7. [Docs › Tutorials › Debugging › Visual Studio Code](https://os.mbed.com/docs/mbed-os/v5.12/tutorials/visual-studio-code.html)
8. [Docs › Tools › Debugging › Setting up a local debug toolchain](https://os.mbed.com/docs/mbed-os/v5.12/tools/setting-up-a-local-debug-toolchain.html)
9. [DISCO_F413ZH debugging with OpenOCD and Visual Studio Code](https://gist.github.com/janjongboom/51f2edbee8c965741465fa5feefe4cf1)
