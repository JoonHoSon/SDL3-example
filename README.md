# macOS build

```bash
➜  mkdir build && cd $_ && cmake ../ && cd ..
➜  cmake --build build
```

# Windows (w/ VCPackage)

## VCPackage 설치

```cmd
C:\> git clone https://github.com/microsoft/vcpkg.git
C:\> cd vcpkg
C:\vcpkg> .\bootstrap-vcpkg.bat
```

## SDL3 설치

```cmd
C:\vcpkg> .\vcpkg install sdl3
C:\vcpkg> .\vcpkg integrate install # 중요
C:\vcpkg> .\vcpkg install sdl3-image[jpeg,png,tiff,webp]
```

## CMake 빌드

```cmd
C:\> cd tetris
C:\tetris> cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=C:\vcpkg\scripts\buildsystems\vcpkg.cmake
C:\tetris> cmake --build build
C:\tetris> .\build\Debug\tetris.exe # 실행
```

```cmd
C:\> cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=C:\vcpkg\scripts\buildsystems\vcpkg.cmake -DSDLMIXER_VENDORED=OFF -DSDLMIXER_SAMPLES=OFF
```