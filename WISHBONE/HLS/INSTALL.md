## Installation Guide
The following commands only serve as an compile example. Please change the path according to your own PC settings if you want to implement the `HLS`.

```powershell
C:\Users\DLQ\AppData\Local\Programs\CLion\bin\cmake\win\x64\bin\cmake.exe -DCMAKE_BUILD_TYPE=Debug -DCMAKE_MAKE_PROGRAM=C:/Users/DLQ/AppData/Local/Programs/CLion/bin/ninja/win/x64/ninja.exe -G Ninja -S E:\SJTU\2024Fall\ECE4810J\Final_Project\ECE4810J_2024FALL\WISHBONE\HLS -B E:\SJTU\2024Fall\ECE4810J\Final_Project\ECE4810J_2024FALL\WISHBONE\HLS\cmake-build-debug

C:\Users\DLQ\AppData\Local\Programs\CLion\bin\cmake\win\x64\bin\cmake.exe --build E:\SJTU\2024Fall\ECE4810J\Final_Project\ECE4810J_2024FALL\WISHBONE\HLS\cmake-build-debug --target HLS -j 18

# assume pwd is the root directory of the repository
cd .\WISHBONE\HLS\

.\cmake-build-debug\HLS.exe
```