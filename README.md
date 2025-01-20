# FLTK-submodule

To create a simple C++ project with CMake that uses FLTK as a submodule, follow these steps:

---

### Step 1: Create the Project Directory Structure
```plaintext
MyFLTKProject/
+-- CMakeLists.txt
+-- src/
¦   +-- main.cpp
+-- third_party/
¦   +-- fltk/ (to be added as a submodule)
```

---

### Step 2: Initialize the Git Repository and Add FLTK as a Submodule
1. Initialize a new Git repository:
   ```bash
   git init
   ```
2. Add FLTK as a submodule:
   ```bash
   git submodule add https://github.com/fltk/fltk.git third_party/fltk
   ```
3. Update the submodule:
   ```bash
   git submodule update --init --recursive
   ```

---

### Step 3: Write the `CMakeLists.txt` File
Create the `CMakeLists.txt` file in the root directory with the following content:

```cmake
cmake_minimum_required(VERSION 3.16)
project(MyFLTKProject)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add FLTK as a subdirectory
add_subdirectory(third_party/fltk)

# Add the source files
add_executable(MyFLTKProject src/main.cpp)

# Link FLTK to the project
target_link_libraries(MyFLTKProject PRIVATE fltk fltk_images fltk_jpeg fltk_png fltk_z)
```

---

### Step 4: Create a Simple FLTK `main.cpp`
Write a minimal FLTK example in `src/main.cpp`:

```cpp
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>

int main() {
    Fl_Window window(400, 300, "Hello FLTK");
    Fl_Box box(100, 100, 200, 100, "Hello, World!");
    window.show();
    return Fl::run();
}
```

---

### Step 5: Build the Project
1. Create a `build` directory and navigate into it:
   ```bash
   mkdir build && cd build
   ```
2. Run CMake to configure the project:
   ```bash
   cmake .. -DCMAKE_BUILD_TYPE=Release
   ```
3. Build the project:
   ```bash
   cmake --build . --config Release  # or on dos: cmake -G "NMake Makefiles" ..
   ```
4. Run the application:
   ```bash
   ./MyPortableApp
   ```

---

### Notes
- FLTK includes its dependencies (like zlib and libpng), so linking `fltk_z`, `fltk_png`, etc., ensures proper functionality.
- You can customize the FLTK build options (like enabling OpenGL) by passing CMake options to `add_subdirectory`:
  ```cmake
  set(FLTK_USE_OPENGL ON CACHE BOOL "Enable OpenGL")
  add_subdirectory(third_party/fltk)
  ```
- To update FLTK in the future, run:
  ```bash
  git submodule update --remote
  ```

This approach ensures that FLTK is bundled and built as part of your project without requiring manual installation.

---

git clone --recurse-submodules git@github.com:tpanj/fltk-submodule.git
