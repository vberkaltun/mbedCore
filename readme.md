# Toolchain and Codebase Setup for The MbedOS + VS Code
Document how to set up a MbedOS toolchain to develop embedded firmware with Visual Studio Code. A lot of this information was taken from Mbed Official Website, 
then adjusted to fit Hukseflux needs.

This will allow you to develop firmware using either a NUCLEO development board, or a ST-Link programmer. For this description, the use of a STM32F446RE NUCLEO board is assumed. 
The intended audience for this page will know what to adjust to get another type of target device up-and-running.

### Contents

- Pre-requisite Setup
    - Environment Variables
    - Extension Setup
    - Keyboard Shortcuts Setup
- Project Setup
- Post-requisite Setup
- Compile And Test

### Pre-requisite Setup

The following software is needed:
| Tables         | Version |
| :------------- | -------:|
| [Visual Studio Code](https://code.visualstudio.com/) (get the system installer, not the user installer) | v1.50.0 |
| [GNU Arm Embedded Toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads) | v8.2.1.20181213 |
| [OpenOCD](https://freddiechopin.info/en/download/category/4-openocd) | v0.10.0 |
| [STMicroelectronics STlink Tools](https://github.com/stlink-org/stlink/releases/tag/v1.6.1) (get the binaries) | v1.6.1 |
| [ST-LINK, ST-LINK/V2, ST-LINK/V2-1 USB driver](https://my.st.com/content/my_st_com/en/products/development-tools/software-development-tools/stm32-software-development-tools/stm32-utilities/stsw-link009.html) | v2.0.1 |
| [Git](https://git-scm.com/download/win) | v2.28.0 |
| [Mbed-CLI](https://pypi.org/project/mbed-cli/#:~:text=Mbed%20CLI%20is%20a%20Python,to%20install%20Mercurial%20and%20Git.) | v2.7.18 |
| [Python 2](https://www.python.org/downloads/windows/) | v1.10.4 |

#### Environment Variables

1. Create the folder `C:\VSARM`.
1. Install Visual Studio Code.
