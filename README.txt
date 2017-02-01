Video Transitions Spatio-Temporal Images
Authors: Curtis Matthias, Beau Grier

Used to create spatio-temporal images (STIs) of a video file. These images can identify video
scene transitions (cut, wipe, dissolve) of the video source.

Multiple type of spatio-temportal images are availble:
- Verticle STI using columns of video frames
- Horizonal STI using rows of video frames
- STI by histogram differences



DEMO VIDEO:
https://www.dropbox.com/s/ysf8sxm9xk5h92y/VTSTI_Demo.flv?dl=0



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