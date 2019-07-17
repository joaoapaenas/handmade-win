@echo off

set CommonCompilerFlags=-MT -nologo -Gm- -GR- -EHa- -Od -Oi -W4 -wd4201 -wd4100 -wd4189 -DHANDMADE_INTERNAL=1 -DHANDMADE_SLOW=1 -DHANDMADE_WIN32=1 -FC -Z7 -Fmwin32_handmade.map
set CommonLinkerFlags=-opt:ref -subsystem:windows,5.02 user32.lib gdi32.lib winmm.lib

set File="C:\game\handmadehero\code\win32_handmade.cpp"

IF NOT EXIST ..\build mkdir ..\build

pushd ..\build

cl %CommonCompilerFlags% %File% /link %CommonLinkerFlags%
popd