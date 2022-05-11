<!-- Written by Mohammad Ishrak Abedin-->
# Circular Array
---
### A simple data structure in C++ to serve as a stack allocated circular array of size ***n***, where any amount of item can be added or pushed, and only the last ***n*** items will be preserved.
---
### The project relies on **[PREMAKE](https://premake.github.io/)** meta build system and can be compiled in Windows or Linux using preferred build system (Expected to use MSVC for Windows and GCC for Linux).

## *Tools Used*
---
- [Premake 5.0 Alpha](https://premake.github.io/)

*Premake5 is already provided for Windows in the `premake` folder.*


## *Packages Required for Linux*
---
+ GCC
+ Make
+ Premake 5.0 alpha

---
## *Building for Windows (MSVC/ Visual Studio)*
---
*Powershell scripts are provided to make the build process faster. One might need to change **Execution Policy** to execute ps1 scripts. Alternatively the scripts can be converted to **bat** or **com** files to execute in **cmd**. The Windows version is targeted towards **MSVC** using **Microsoft Visual Studio**. Visual Studio version **2019 or Higher** recommended.*

Run the following commands in step to generate project files and build the project.
```powershell
.\makedir.ps1 # Generates output directories

.\premake\premake5.exe vs2022 # Pass respective Visual Studio version
```
*At this point, a **Visual Studio Solution (.sln)** will be generated. Use it to build the project.*

---
## *Building for Linux (GCC/ Make)*
---
*Shell Scripts are provided to make the build process faster. Install the aforementioned required packages before building.*

Run the following commands in step to generate project files and build the project.
```bash
#-- Project Generation --
sh ./makedir.sh # Generates output directories

premake5 gmake2 # Generates Makefile

#-- Building ---
# For building in Debug Mode
make config=debug
# or
# For building in Release Mode
make config=release
```
---
## Using the Circular Array
---
The data structure is distributed as a *header only* file, where you just need to copy the [CircularArray.h](./CircularArray/CircularArray.h) file into your include directory.

A new circular array of maximum capacity of `capacity` can be created as (stack allocated):

```C++
ish::CircularArray<type, capacity> ArrayName;
```

Other functionalities like *adding* a new item or others can be found in the header file and the provided test file as well; they are pretty straight forward.
