# Textra Errestrial
Textra Errestrial is a game about decoding an alien language. You wake up on a ship with no recollection of how you got there, and must find out how to call for help in a language you do not understand. Made over the summer semester for Computer Programming I.

## Compile instructions
First, retrieve this repository via git.
```
git clone https://github.com/JmeJuniper/textra-errestrial.git
```
Then, create a build folder with CMake.
```
cd textra-errestrial
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
```
Build the project with the newly-generated build folder.
```
cd ..
cmake --build build --config Release --target all
```
The compiled project is now available in `textra-errestrial\build\bin`.