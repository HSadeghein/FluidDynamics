echo off
git clone https://github.com/google/googletest
cd .\googletest\googletest

type CMakeLists.txt > newFile.txt
echo set_target_properties(gtest_main gtest PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreadedDebug") >> newFile.txt
type newFile.txt > CMakeLists.txt

del .\newFile.txt
mkdir build
cd .\build
cmake ..
cmake --build .
cd ..
cd ..
cd ..
call vendors\premake\premake5.exe vs2019
pause