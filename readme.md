# Toolchain and Codebase Setup for The MbedOS + VS Code
Document how to set up a MbedOS toolchain to develop embedded firmware with Visual Studio Code. A lot of this information was taken from Mbed Official Website, 
then adjusted to fit Hukseflux needs.

This will allow you to develop firmware using either a NUCLEO development board, or a ST-Link programmer. For this description, the use of a STM32F446RE NUCLEO board is assumed. 
The intended audience for this page will know what to adjust to get another type of target device up-and-running.

### Contents

- Pre-requisite Setup
    - Environment Variables
    - Configuration of Visual Studio Code
- Project Setup
    - Download Sourcode
    - Update Settings Variables
- Post-requisite Setup
- Compile And Test

### Pre-requisite Setup

The following software is needed. Before all installations, create the folder `C:\VSARM` and then start the installations:

| Tables         | Version | Installation Path | Description |
| :------------- | -------:| -----------------:| -----------:|
| [GNU Arm Embedded Toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads) | v8.2.1 | `C:\VSARM\armgcc` | Download the Windows 32-bit installer for Windows 7 and later. |
| [OpenOCD](https://freddiechopin.info/en/download/category/4-openocd) | v0.10.0 | `C:\VSARM\openocd` | `NA` |
| [Git](https://git-scm.com/download/win) | v2.28.0 | `C:\VSARM\git` | `NA` |
| [Python 2](https://www.python.org/downloads/windows/) | v1.10.4 | `C:\VSARM\python27` | `NA` |
| [STMicroelectronics STlink Tools](https://github.com/stlink-org/stlink/releases/tag/v1.6.1) | v1.6.1 | `C:\VSARM\stlink` | Download the binaries. |
| [Mbed-CLI](https://pypi.org/project/mbed-cli/#:~:text=Mbed%20CLI%20is%20a%20Python,to%20install%20Mercurial%20and%20Git.) | v2.7.18 | `NA` | Run `pip install mbed-cli` in command prompt. |
| [ST-LINK USB driver](https://my.st.com/content/my_st_com/en/products/development-tools/software-development-tools/stm32-software-development-tools/stm32-utilities/stsw-link009.html) | v2.0.1 | `NA` | `NA` |
| [Visual Studio Code](https://code.visualstudio.com/) | v1.50.0 | `NA` |  Download the system installer, not the user installer. |

#### Environment Variables

1. Open Windows **Control Panel** and navigate to **System** (Control Panel->System and Security->System).
2. After the **System** screen appears, select **Advanced system settings**.
3. This will open the **System Properties** window. Select the **Advanced** tab and then the **Environment Variables** button.
4. Under the **System variables** section, scroll down and highlight the **Path** variable. Click the **Edit** button.
5. In the Edit screen, click **New** and add the path to:

    - `C:\VSARM\stlink\bin`
    - `C:\VSARM\openocd\bin`
    - `C:\VSARM\armcc\bin`

#### Configuration of Visual Studio Code

1. Open Visual Studio Code.
2. `Press Ctrl-Shift-X` to open the Extension tab and install the following extensions:

    - `C/C++`
    - `Cortex Debug`

3. Press `F1` and type `Open Settings (JSON)`. Open the user settings .JSON file and add the following:
    - `"cortex-debug.armToolchainPath": "${env:VSARM}\\armcc\\bin\\",`
