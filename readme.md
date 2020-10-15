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
  * [Automatic Setup: GitHub](#Automatic-Setup-GitHub)
  * [Automatic Setup: Hukseflux Terminal Server](#Automatic-Setup-Hukseflux-Terminal-Server)
  * [Manual Setup](#Manual-Setup)
- [Post-requisite Setup](#Post-requisite-Setup)
- [Compile And Test](#Compile-And-Test)
- [Troubleshooting](#Troubleshooting)
  * [Version Check](#Version-Check)
  * [Usage Directory Error (GDBDebugger)](#Usage-Directory-Error-GDBDebugger)
  * [Configs (Mbed-CLI)](#Configs-Mbed-CLI)
  * [Hotfix for The Linux File Formats](#Hotfix-for-The-Linux-File-Formats)
  * [Extracting The 'mbed-os.zip' File](#Extracting-The-mbed-oszip-File)
- [Resources](#Resources)
- [License](#License)

## Pre-requisite Setup

The following software is needed. Before all installations, create the folder **`C:/VSARM`** and then start the installations:

| Software       | Version | Installation Path | Description |
| :------------- | :-------| :-----------------| :-----------|
| [GNU Arm Embedded Toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads) | v8.2.1 | `C:/VSARM/armgcc` | Download the Windows 32-bit installer for Windows 7 and later. |
| [OpenOCD](https://freddiechopin.info/en/download/category/4-openocd) | v0.10.0 | `C:/VSARM/openocd` | `NA` |
| [Git](https://git-scm.com/download/win) | v2.28.0 | `C:/VSARM/git` | `NA` |
| [Python 2](https://www.python.org/downloads/windows/) | v2.7.18 | `C:/VSARM/python27` | `NA` |
| [STMicroelectronics STlink Tools](https://github.com/stlink-org/stlink/releases/tag/v1.6.1) | v1.6.1 | `C:/VSARM/stlink` | Download the binaries. |
| [Mbed-CLI](https://pypi.org/project/mbed-cli/#:~:text=Mbed%20CLI%20is%20a%20Python,to%20install%20Mercurial%20and%20Git.) | v1.10.4 | `NA` | Run `pip install mbed-cli` in command prompt. |
| [ST-LINK USB driver](https://my.st.com/content/my_st_com/en/products/development-tools/software-development-tools/stm32-software-development-tools/stm32-utilities/stsw-link009.html) | v2.0.1 | `NA` | `NA` |
| [Visual Studio Code](https://code.visualstudio.com/) | v1.50.0 | `NA` |  Download the system installer, not the user installer. |

### Environment Variables

1. Open Windows **Control Panel** and navigate to **System** (Control Panel->System and Security->System).
2. After the **System** screen appears, select **Advanced system settings**.
3. This will open the **System Properties** window. Select the **Advanced** tab and then the **Environment Variables** button.
4. Under the **System variables** section, scroll down and highlight the **Path** variable. Click the **Edit** button.
5. In the Edit screen, click **New** and add the path to:

    - `C:/VSARM/stlink/bin`
    - `C:/VSARM/openocd/bin`
    - `C:/VSARM/armcc/bin`

### Configuration of Visual Studio Code

1. Open Visual Studio Code.
2. Press **`Ctrl-Shift-X`** to open the Extension tab and install the following extensions:

    - `C/C++`
    - `Cortex Debug`

3. Press **`F1`** and type **`Open Settings (JSON)`**. Open the user settings .JSON file and add the following codes:

```json
// Place your key bindings in this file to override the defaults
{
    "cortex-debug.armToolchainPath": "${env:VSARM}/armcc/bin/"
}
```

4. Press **`F1`** and type **`Open Keyboard Shortcuts (JSON)`**. Open the keyboard shortcuts .JSON file and add the following keyboard shortcut codes:

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

The project can be set up in two different ways: automatic (GitHub and Hukseflux Terminal Server) and manual. In both ways, your machine has to be connected to the internet at least one time. In this period, all dependencies are collected in your machine for the current project. Then, you can easily disconnect your machine from the internet and work on your project locally.

### Automatic Setup: GitHub

1. Open a command prompt.
2. Type **`git clone https://github.com/vberkaltun/mbedCore.git`** and run.

After these steps, all dependencies will be downloaded to your current directory.

### Automatic Setup: Hukseflux Terminal Server

The Hukseflux Terminal Server includes all the project templates that you may need for the MbedOS + VS Code developments. In case of this automatic setup option, please get in touch with your administration to find out how to download **`sing_mbed_template`** project path. After all these steps, you may have to check out these two topics as well:

- The [Hotfix for The Linux File Formats](#Hotfix-for-The-Linux-File-Formats) topic in the [Troubleshooting](#Troubleshooting) section
- The [Extracting The 'mbed-os.zip' File](#Extracting-The-mbed-oszip-File) topic in the [Troubleshooting](#Troubleshooting) section

### Manual Setup

1. Open a command prompt.
2. Type **`mbed new THIS_IS_YOUR_APP_NAME`** and run.
4. Create a **`main.cpp file`** in the root of your application. Open the file and add the following codes:

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

4. Open **`mbed_app.json`** in the root of your application and replace it with the following content:

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

5. Create a **`.vscode`** folder in the root of your application and then create these three files in this folder:

    - `.vscode/launch.json`
    - `.vscode/settings.json`
    - `.vscode/tasks.json`
    
6. Add the following content to the **`.vscode/launch.json`** file:

```json
{
    "version": "0.1.0",
    "configurations": [
        {
            "name": "Mbed Launch",
            "type": "cppdbg",
            "request": "launch",
            "program": "${config:COMPILE_DEBUG_PATH}/${config:PROJECT_NAME}.elf",
            "args": [],
            "stopAtEntry": true,
            "cwd": "${config:PROJECT_PATH}",
            "environment": [],
            "externalConsole": false,
            "serverLaunchTimeout": 20000,
            "filterStderr": true,
            "filterStdout": false,
            "serverStarted": "target halted due to debug-request, current mode: Thread",
            "logging": {
                "moduleLoad": true,
                "trace": true,
                "engineLogging": true,
                "programOutput": true,
                "exceptions": true
            },
            "windows": {
                "preLaunchTask": "Load Firmware (Debug)",
                "MIMode": "gdb",
                "MIDebuggerPath": "${config:ARM_PATH_EXEC_FILENAME}",
                "debugServerArgs": "-f ${config:OPENOCD_CONFIG_FILENAME} -f ${config:OPENOCD_INTERFACE_FILENAME} -c init -c \"reset init\"",
                "debugServerPath": "${config:OPENOCD_EXEC_FILENAME}",
                "setupCommands": [
                    { "text": "-target-select remote localhost:3333", "description": "connect to target", "ignoreFailures": false },
                    { "text": "-file-exec-and-symbols ${config:COMPILE_DEBUG_PATH}/${config:PROJECT_NAME}.elf", "description": "load file", "ignoreFailures": false},
                    { "text": "-interpreter-exec console \"monitor endian little\"", "ignoreFailures": false },
                    { "text": "-interpreter-exec console \"monitor reset\"", "ignoreFailures": false },
                    { "text": "-interpreter-exec console \"monitor halt\"", "ignoreFailures": false },
                    { "text": "-interpreter-exec console \"monitor arm semihosting enable\"", "ignoreFailures": false },
                    { "text": "-target-download", "description": "flash target", "ignoreFailures": false }
                ]
            }
        }
    ]
}
```

7. Add the following content to the **`.vscode/settings.json`** file:

```json
// Place your settings in this file to overwrite default and user settings.
{
    "C_Cpp.addWorkspaceRootToIncludePath": false,
    "C_Cpp.intelliSenseEngine": "Tag Parser",
    "git.ignoreLimitWarning": true,
    
    "PROJECT_PATH": "C:/Users/Dekimo/Documents/GitHub/mbedCore",
    "PROJECT_NAME": "${workspaceFolderBasename}",

    "DEVELOPMENT_BOARD_BAUDRATE": "115200",
    "DEVELOPMENT_BOARD_NAME": "NUCLEO_F446RE",
    "DEVELOPMENT_TOOLCHAIN": "GCC_ARM",
    
    "COMPILE_MEMORY_ADDRESS": "0x08000000",
    "COMPILE_RELEASE_PATH": "${config:PROJECT_PATH}/BUILD/${config:DEVELOPMENT_BOARD_NAME}/GCC_ARM-RELEASE",
    "COMPILE_DEBUG_PATH": "${config:PROJECT_PATH}/BUILD/${config:DEVELOPMENT_BOARD_NAME}/GCC_ARM-DEBUG",

    "ARM_PATH": "C:/VSARM/armgcc",
    "ARM_PATH_EXEC_FILENAME": "${config:ARM_PATH}/bin/arm-none-eabi-gdb.exe",

    "OPENOCD_PATH": "C:/VSARM/openocd",
    "OPENOCD_EXEC_FILENAME": "${config:OPENOCD_PATH}/bin/openocd.exe",
    "OPENOCD_CONFIG_FILENAME": "${config:OPENOCD_PATH}/scripts/board/st_nucleo_f4.cfg",
    "OPENOCD_INTERFACE_FILENAME": "${config:OPENOCD_PATH}/scripts/interface/stlink-v2-1.cfg",
    
    "files.exclude": {
        "**/BUILD": true,
        "**/mbed-os": true
    },
}
```

8. Add the following content to the **`.vscode/tasks.json`** file:

```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "Compile Firmware (Debug)",
            "type": "shell",
            "command": "mbed compile --target ${config:DEVELOPMENT_BOARD_NAME} --toolchain ${config:DEVELOPMENT_TOOLCHAIN} --profile debug",
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "problemMatcher": {
                "owner": "cpp",
                "fileLocation": [
                    "relative",
                    "${workspaceFolder}"
                ],
                "pattern": {
                    "regexp": "^(.*):(\\d+):(\\d+):\\s+(warning|error):\\s+(.*)$",
                    "file": 1,
                    "line": 2,
                    "column": 3,
                    "severity": 4,
                    "message": 5
                }
            }
        },
        {
            "label": "Compile Firmware (Release)",
            "type": "shell",
            "command": "mbed compile --target ${config:DEVELOPMENT_BOARD_NAME} --toolchain ${config:DEVELOPMENT_TOOLCHAIN} --profile release",
            "problemMatcher": {
                "owner": "cpp",
                "fileLocation": [
                    "relative",
                    "${workspaceFolder}"
                ],
                "pattern": {
                    "regexp": "^(.*):(\\d+):(\\d+):\\s+(warning|error):\\s+(.*)$",
                    "file": 1,
                    "line": 2,
                    "column": 3,
                    "severity": 4,
                    "message": 5
                }
            }
        },
        {
            "label": "Load Firmware (Debug)",
            "type": "shell",
            "command": "st-flash --reset write ${config:COMPILE_DEBUG_PATH}/${config:PROJECT_NAME}.bin ${config:COMPILE_MEMORY_ADDRESS}",
            "group": {
                "kind": "test",
                "isDefault": true
            },
            "problemMatcher": [],
            "dependsOn": [
                "Compile Firmware (Debug)"
            ]
        },
        {
            "label": "Load Firmware (Release)",
            "type": "shell",
            "command": "st-flash --reset write ${config:COMPILE_RELEASE_PATH}/${config:PROJECT_NAME}.bin ${config:COMPILE_MEMORY_ADDRESS}",
            "problemMatcher": [],
            "dependsOn": [
                "Compile Firmware (Release)"
            ]
        },
        {
            "label": "Clean Firmware (Debug)",
            "type": "shell",
            "command": "Remove-Item -Recurse -Force ${config:COMPILE_DEBUG_PATH}",
        },
        {
            "label": "Clean Firmware (Release)",
            "type": "shell",
            "command": "Remove-Item -Recurse -Force ${config:COMPILE_RELEASE_PATH}",
        },
        {
            "label": "Open Serial Monitor",
            "type": "shell",
            "command": "mbed sterm -b ${config:DEVELOPMENT_BOARD_BAUDRATE}",
        }
    ]
}
```

## Post-requisite Setup

1. Open the **`.vscode/settings.json`** file in the application folder.
2. Update the values of given parameters based on your software installations:

| Tables         | Description  |
| :------------- | :----------- |
| `PROJECT_PATH` | The root path of your application, for example **`C:/Users/Dekimo/Documents/GitHub/mbedCore`**. |
| `DEVELOPMENT_BOARD_BAUDRATE` | The baud rate of the serial communication port, for example: **`115200`**. |
| `DEVELOPMENT_BOARD_NAME` | The development board name, for example: **`NUCLEO_F446RE`**. For more information, check out the [Configs (Mbed-CLI)](#Configs-Mbed-CLI) topic in the [Troubleshooting](#Troubleshooting) section. |
| `DEVELOPMENT_TOOLCHAIN` | The compiler toolchain, for example: **`GCC_ARM`**. This documentation is totaly based on **`GCC_ARM`** compiler. For more information, check out the [Configs (Mbed-CLI)](#Configs-Mbed-CLI) topic in the [Troubleshooting](#Troubleshooting) section. |
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

### Version Check

If you already have an installed version of the required software, you can check out the versions of them with the given commands. Open a command prompt and run each of them one-by-one:

| Software       | Command |
| :------------- | ------: |
| GNU Arm Embedded Toolchain | `arm-none-eabi-gcc --version` |
| OpenOCD | `openocd --version` |
| Git | `git --version`|
| Python 2 | `python --version` |
| STMicroelectronics STlink Tools | `st-flash --version` |
| Mbed-CLI | `mbed --version` |
| ST-LINK USB driver | `NA` |
| Visual Studio Code | `code --version` |

### Usage Directory Error (GDBDebugger)

```
kdevelop(4806)/kdevelop (gdb debugger) GDBDebugger::GDB::processLine: GDB output:
"^error,msg="-environment-cd: Usage DIRECTORY""
```

This error occurs when you use Unicode in your project path. The only workaround is to not include Unicode in your path. For more information, check out the [Working directory and debug mode (11)](#Resources).

### Configs (Mbed-CLI)

You can check out the MbedOS configurations of your application with the given commands. Before running each of them, open a command prompt and redirect your command prompt to your application path with the **`cd YOUR_FULL_APPLICATION_PATH`** command. Then, run each of them one-by-one:

| Command        | Description |
| :------------- | :-----------|
| `mbed toolchain --supported` | Shows all supported toolchains by MbedOS. |
| `mbed target --supported` | Shows all supported development boards by MbedOS. |
| `mbed export --supported ides` | Shows all supported IDE by MbedOS. |
| `mbed config --list` | Shows the configured settings for the current project. |

### Hotfix for The Linux File Formats

If you have got some restrictions for the Linux data types in your machine, you can fix this problem by using the PowerShell commands located in the root path. This problem especially occurs if you would like to push or fetch anything in your TortoiseSVN repository. The given data types are the most common data types for this problem:

- `.gitattributes`
- `.gitignore`
- `.gitmodules`
- `.mbed`
- `.mbedignore`

The solution is changing Linux bases data types to the Windows supported data types or the other way around. Before pushing anything to the repository, you may have to run the **`mbed_prefix_add.ps1`** PowerShell command. Then, a 'hukseflux' will be added all your relevant data types. For the opposite way around, just run **`mbed_prefix_remove.ps1`** in the root path. You can also change this prefix name by editing the **`.PS1`** file with an editor.

### Extracting The 'mbed-os.zip' File

If you have used the **Hukseflux Terminal Server** for the installation, you will find out a **`mbed-os.zip`** file in the root path of the project. This ZIP file includes all MbedOS related libraries and configurations.

After the installation of the project files to your machine, you may have to extract this folder to the same path with the **`mbed-os`** name. After that, you can easily delete the **`mbed-os.zip`** file from the root path of the project.

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
10. [CWD is badly encoded to GDB and fails to find directory if it has a diacritic.](https://github.com/microsoft/vscode-cpptools/issues/3444)
11. [Working directory and debug mode](https://forum.kde.org/viewtopic.php?f=218&t=122931)

## License

```
Copyright 2020 Berk Altun, on behalf of Hukseflux

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

   http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
```
