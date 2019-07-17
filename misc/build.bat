@echo off

IF NOT EXIST ..\build mkdir ..\build

pushd ..\build

"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.21.27702\bin\Hostx64\x64\cl.exe" -DHANDMADE_INTERNAL=1 -FC -Zi "C:\game\handmadehero\code\win32_handmade.cpp" user32.lib gdi32.lib
popd