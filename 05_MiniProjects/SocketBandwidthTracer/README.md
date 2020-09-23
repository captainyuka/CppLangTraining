# Socket Bandwidth Tracer

Socket Bandwidth Tracer consists of a server and multiple clients.
  
  * Each client can add sockets and listen socket bandwidth
  
  * The server will inform the client at specified intervals about the bandwidth data of each socket the client listens.

## Example Client Commands

* Commands consists of
  * `CMD:IP:PORT:MS`

```
ADD:192.168.1.1:1923:500
DEL:192.168.1.1:1923:500
```

## Server Setup Instructions

0- Download [PcapPlusPlus Latest Source Code](https://github.com/seladb/PcapPlusPlus/releases/tag/v20.08) and move to into the 'C:' drive. 

1- Download and run mingw-w64 installer [from here](https://sourceforge.net/projects/mingw-w64/files/mingw-w64/mingw-w64-release/), Also [Direct Link](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/installer/mingw-w64-install.exe/download): 

  * Make sure the installation path doesn’t contain spaces (otherwise PcapPlusPlus compilation may fail)
	
  * Make sure to choose the i686 (32-bit) and POSIX threads (and not win32 threads) options. 
  
    * for example: `i686-8.1.0-posix-dwarf-rt_v6-rev0`. PcapPlusPlus doesn’t support MinGW-w64 64-bit (x86_64)

2- Install MSYS2 [from here](https://www.msys2.org/): 

3- Add the following folders to your `PATH` environment variable:
	
  * The MinGW-w64 folder that contains `g++.exe`, `mingw32-make`, etc. 
  
	  * It should be under `[MinGW-w64_install_folder]\mingw32\bin`, for example: `C:\i686-8.1.0-posix-dwarf-rt_v6-rev0\mingw32\bin`
    
  * The MSYS2 `usr\bin` folder, for example: `C:\msys32\usr\bin`

4- Download [Npcap SDK](https://nmap.org/npcap/#download): 

  * Make sure Npcap SDK path has no space, move to C drive if possible

5- Install [Npcap latest version](https://nmap.org/npcap/#download): 

6- Run the `configure-windows-mingw.bat` batch file from PcapPlusPlus main directory. 

```powershell
C:\PcapPlusPlus>configure-windows-mingw.bat

******************************************
PcapPlusPlus Windows configuration script
******************************************

MinGW32 or MinGW-w64 are required for compiling PcapPlusPlus. Please specify
the type you want to use (can be either "mingw32" or "mingw-w64")

Please specify mingw32 or mingw-w64: mingw-w64


If mingw-w64 is not installed, please download and install it
mingw-w64 can be downloaded from: sourceforge.net/projects/mingw-w64/

Please specify mingw-w64 installed path (for example: C:\MinGW or C:\i686-8.1.0-posix-dwarf-rt_v6-rev0): C:\i686-8.1.0-posix-dwarf-rt_v6-rev0  


MSYS2 is required for compiling PcapPlusPlus.
If MSYS2 are not installed, please download and install it from: https://www.msys2.org/

Please specify MSYS2 installed path: C:\msys64


WinPcap or Npcap SDK is required for compiling PcapPlusPlus.
For downloading WinPcap SDK (developer's pack) please go to https://www.winpcap.org/devel.htm
For downloading Npcap SDK please go to https://nmap.org/npcap/#download

Please specify WinPcap/Npcap SDK path: C:\Npcap-SDK

PcapPlusPlus configuration is complete. Files created (or modified): mk\platform.mk, mk\PcapPlusPlus.mk

```

7- Build the code

  * Run `mingw32-make.exe all` from PcapPlusPlus main directory


## References

* Our Server installation guide is an enhanced version of the [PcapPlusPlus installation guide](https://pcapplusplus.github.io/docs/install/build-source/mingw#prerequisites-for-building-with-mingw-w64).
