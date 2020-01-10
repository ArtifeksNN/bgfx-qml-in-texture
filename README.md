# Bgfx-qml-in-texture
Port bgfx engine into qml item throw texture

git clone
cd project
git submodule init & git submodule update

Linux:
1) check your system and drivers sudo apt-get install libgl1-mesa-dev x11proto-core-dev libx11-dev
2) cd bgfx
3) make linux-release64

Windows:

MSVC
1) cd bgfx
2) open cmd
2) ..\bx\tools\bin\windows\genie --with-examples vs2017
3) make vs2017-release64

MINGW
1) cd bgfx
2) open cmd
3) set MINGW=*your mingw path*
2) ..\bx\tools\bin\windows\genie --with-examples --gcc=mingw-gcc gmake
3) mingw32-make mingw-gcc-release64