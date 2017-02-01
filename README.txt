CMPT 365 - Project
Video Transitions Spatio-Temporal Images
Authors: Beau Grier, Curtis Matthias


TO RUN:
- Verify OpenCV 3.1.0 and Visual Studio 2012 are installed (CSIL recommended)
- Verify dependent dlls are included
- Naviagate to 'VTSTI\x64\Debug'
- Run 'VTSTI.exe'
- Follow UI instructions


TO BUILD:
- Install OpenCV 3.1.0
- Install Visual Studio 2012
- In Visual Studio project configuration menu:
	* Include Directories: 'opencv/build/include'
	* Linker Libraries: 'opencv/build/x64/vc11/lib'
	* Properties->General->Character Set: 'Not Set'
- Copy 'opencv_worldd.dll' from 'opencv/build/x64/vc11/bin' to 'VTSTI\x64\Debug'
- Copy 'opencv_ffmpeg300_64.dll' from 'opencv/build/x64/vc11/bin' to 'VTSTI\x64\Debug'
- If compiling in 64-bit, change Configuration Manager in Visual Studio to 'x64'