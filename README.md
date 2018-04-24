# Raw Modern OpenGL 3.3+ on macOS

A setup to unit test / learn *raw* modern OpenGL ([3.3 / 4.1](https://support.apple.com/en-us/HT202823)) on macOS and Xcode.

### Purposes

* As requested by those who want to follow those online tuts in order to learn OpenGL first / parallel to exploring creative coding frameworks. But have issues setting up the combination of Xcode and modern OpenGL.
* We love *oF* and *Cinder*, but sometimes testing / refreshing / learning some feature is hard as frameworks are opinionated by definition - having bootstrapping layer in front also means that when stuff does not work it's hard to know whose fault is it - yours or framework's (going step by step in *raw mode* will show it's yours ^_^). Btw, don't forget *p5* if all you need is vert + frag test.

## Building

### Intro

* Using [GLEW](http://glew.sourceforge.net) for OpenGL [extension loading](https://www.khronos.org/opengl/wiki/OpenGL_Loading_Library) 
* Using [GLFW](http://www.glfw.org) for windowing and eventing ([SDL](https://www.libsdl.org) and [SFML](https://www.sfml-dev.org) are alternatives, but unnecessary for the purpose. And please do not use *GLUT* (and *FreeGLUT* is unavailable on macOS).  

These dependencies are built on demand as dynamic dylibs and are automatically included in the app bundle due to Xcode project settings. Just `bash dependencies/build_dependencies.sh`.

If you wonder how this compares to frameworks

* *openFrameworks* uses *GLEW* and *GLFW* on macOS.
* *Cinder* uses [*GL Load*](http://glsdk.sourceforge.net/docs/html/group__module__glload.html) and native windowing and eventing (btw, it uses the same *GLFW* for *nix).


### Prerequisites

```sh
brew install cmake
```

### Action

* Clone this repo.
* Run `bash dependencies/build_dependencies.sh` first. It will download *GLM* as well as *GLEW* and *GLFW* sources, build the latter and thus generate libraries in `dependencies/`.
* Open *Xcode* project, build & run.
* One raw *main.cpp* file.
* Atomise and RAII it.
* Profit.

## Building GLEW and GLFW explained `build_dependencies.sh`

### Building GLEW on macOS

* Download latest GLEW release from Github.
* `make` it with supplying `GLEW_DEST` flag so that the resulting product is cleanly put here, not in `/usr/*`.
* On par with [GLEW docs](http://glew.sourceforge.net/build.html)
* Using `install_name_tool` change `LC_ID_DYLIB` for dylib to `@executable_path/../Frameworks/libGLEW.<version>.dylib` as this has to be the run path later for app bundle.

### Building GLFW on macOS

* Download latest GLFW release from Github.
* `cmake` it with supplying `CMAKE_INSTALL_PREFIX` flag so that the resulting product is cleanly put here, not in `/usr/*`.
* Add `BUILD_SHARED_LIBS` option to make dylib (or ignore that to make static lib).
* `make & make install`
* On par with [GLFW docs](http://www.glfw.org/docs/latest/compile.html#compile_options)
* Using `install_name_tool` change `LC_ID_DYLIB` for dylib to `@executable_path/../Frameworks/libglfw.<version>.dylib` as this has to be the run path later for app bundle.

### Linking GLEW and GLFW in Xcode

* Add both lib `include` to header search paths.
* Add both lib dylibs in *Link Binary With Libraries* phase.
* Add new *Copy Files Phase* to target and set destination to *Frameworks*. Set both dylibs to be copied over to app bundle.
* *Optionally* add new *Run Script Phase* to target. Use `install_name_tool` to fix runpath for just in place copied dylibs if you did not change `LC_ID_DYLIB` right after building those dylibs. 

```sh
# Change install directory for GLEW to run
install_name_tool -change <what to change> @executable_path/../Frameworks/libGLEW.<version>.dylib "$TARGET_BUILD_DIR/$PRODUCT_NAME.app/Contents/MacOS/$EXECUTABLE_NAME";
# Change install directory for GLFW to run
install_name_tool -change <what to change> @executable_path/../Frameworks/libglfw.<version>.dylib "$TARGET_BUILD_DIR/$PRODUCT_NAME.app/Contents/MacOS/$EXECUTABLE_NAME";
```

* You can reuse the built libraries in other projects too, as it will work when put into bundle *Frameworks*.

## Static linking instead of dynamic

If needed, you can switch to static lib type, just test both project build and run times and choose what's better.  
*GLEW* OOB builds both, see `dependencies/glew/lib/*.a`.  
For *GLFW* remove `-DBUILD_SHARED_LIBS=ON` to get static in `dependencies/glfw/lib`.  
And of course then you'll need to change *Link Binary With Libraries* phase to use static libs as well as remove unneeded copy script phase.

## Tested

* macOS 10.13
* Xcode 9.2 (project file set 6.3 compatible)
* C++11 / C++14

## Todo

PR welcome to add some more stuff to this barebones boilerplate.
