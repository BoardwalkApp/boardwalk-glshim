This is a fork of lunixbochs' and ptitSeb's glshim library used in Boardwalk.

See the [main Boardwalk repo](https://github.com/zhuowei/Boardwalk) for details and build instructions.

## Building

For Boardwalk 1.0,

```
cd build/android
ndk-build
```

then copy `glshim/build/android/libs` to `lwjgl/platform_build/android_wrapper/libs`

The original README of glshim is included below:

----


glshim
====

This is a shim providing OpenGL 1.x functionality to OpenGL ES accelerated cards.

----

Compiling
----

    cmake .; make GL

*or for the Raspberry Pi*

    cmake . -DBCMHOST=1; make GL

----

GLU
----

You probably want the glu branch from https://github.com/lunixbochs/glues

    git clone git@github.com:lunixbochs/glues.git; git checkout glu; cmake .; make

----

Installation
----

Put lib/libGL.so.1 in your `LD_LIBRARY_PATH`. If you need GLU, build libGLU.so.1 from the glues repo and do likewise.
