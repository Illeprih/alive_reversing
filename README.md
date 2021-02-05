# R.E.L.I.V.E.
An Open-Source Engine Replacement for Oddworld: Abe's Oddysee and Oddworld: Abe's Exoddus.

R.E.L.I.V.E. is a fan-made, open-source project that intends to become a fully compatible engine replacement for Oddworld Inhabitants' iconic first two games. The project's goals include fixing the original games' bugs and also eventually providing a modding / level creation interface, alongside of course making it possible to study or use the engine for new projects.

For more details, please check the project's website: https://aliveteam.github.io/

## Contributing

Anyone who wishes to contribute is encouraged to join the project's [Discord](
https://discord.gg/khs6KKS), where most of the communication happens.

By contributing to this project, the contributor agrees and accepts that their code will be licensed under a GPL-compatible license in the future.

## Building R.E.L.I.V.E.

### Cloning

Since the project uses third-party repositories for some of its functions, you need to clone the project using the `--recursive` flag.

```
git clone --recursive https://github.com/AliveTeam/alive_reversing.git
```

#### **Regardless of your platform, you need to create a folder called `build` in your repository root! `.gitignore` is configured to ignore this folder. This helps to prevent polluting the commits with binaries.**

### Build on Windows using `msbuild`

[SDL](https://libsdl.org/download-2.0.php) and [CMake](https://cmake.org/) is required to build the project.

1. `cd build`
2. `cmake -S .. -B . -DSDL2_DIR=PATH_TO_YOUR_SDL2_DIRECTORY`
3. `msbuild /p:Configuration=Debug;Platform=Win32 ar.sln /m`

### Build on Windows using Visual Studio 2017

[SDL](https://libsdl.org/download-2.0.php) is required to build the project.

1. Launch VS2017.
2. Goto `File` -> `Open` -> `CMake`. Then choose the `CMakeLists.txt` from the root of this cloned git repository.
3. Select `CMake` -> `Change CMake settings` -> `CMakeLists.txt`.
4. Choose `x86-debug` and click `select`.
5. This will open `CMakeSettings.json`, edit the line `cmakeCommandArgs` to contain `-DSDL2_DIR=PATH_TO_YOUR_SDL2_DIRECTORY`, set your build directory to `build` and then click `generate` in the top yellow warning bar.
6. Invoke `CMake` -> `Build all` to build the project.

### Build on Linux

1. Install SDL2 using your package manager.
2. `cd build`
3. `cmake -S .. -B .`
4. `make -j$(nproc)`
5. You'll find your executables in the `Source` folder under `AliveExe`.
6. You can optionally install the package using `make install` or create a Debian-compatible package using `cpack -G DEB`.

## Testing

### Hook Manager

For testing we provide an application called Hook Manager, which lets you freely change whether specific functions use the original code or the rewritten one. This lets you figure out whether bugs are the result of errors in the rewrite or whether they are part of the original game.

The hook manager can be downloaded from [this](https://github.com/AliveTeam/AliveHookManager/releases/tag/1.0) link. You also need a patched executable for the game of your choice, which you can download [here](https://cdn.discordapp.com/attachments/505078398087987201/807014898717425674/patched_dlls.zip).

To use the manager you need to do the following:

You need to obtain the .map and .dll files for whichever game you want to debug. You can do this in one of two ways:

- Set the `AO_ROOT` and `AE_ROOT` environment variables to their respective game's install folders.
- Compile R.E.L.I.V.E. using the `msbuild` method
- Your .map and .dll files will be placed in the install folders.

OR:

- Download the .map and DLL files from AppVeyor:
  - [32 bits](https://ci.appveyor.com/api/projects/paulsapps/alive-reversing/artifacts/build/RELIVE_Binaries_Full_Debug_x86.zip?branch=master&job=Platform%3A%20x86&pr=false)
  - [64 bits](https://ci.appveyor.com/api/projects/paulsapps/alive-reversing/artifacts/build/RELIVE_Binaries_Full_Debug_x64.zip?branch=master&job=Platform%3A%20x64&pr=false)
- Drop the .map and DLL files from the build folder into the respective game's installation folder.

Regardless of which way you chose, this is how you finalize the process:
- Drop the respective game's patched exe into their installation folder.
- Launch the patched exe
- Start the hook manager
