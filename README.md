## Android "Hello World", "close to the metal" version

A good-for-nothing test to explore the hardship and quirks of native Android development.

The aim of this little project is to understand:

- if it's possible to develop an application using almost only C/C++
- how difficult that would be
- how hard it is to cross-compile external libraries and their dependencies, specifically Guile
- how Guile would perform
- what are the limitations of using C/C++ when a Java functionality is required, like the `MediaStore` class or intents

And is the natural continuation of my previous https://github.com/R1ck77/guile-python-interop-test

## Current state

There is the most basic form of integration with Lua.

Lua is, in turn, the lowest possible bar for an external software integration I can think of: an easy to compile ANSI C code with no external dependencies.

The app uses a standard activity to present a C++ string, the string is stored and then loaded into a Lua interpreter before being sent to Java.

## Desiderata

Getting Guile to compile somehow.


## Disclaimer 

This project uses and most importantly contains most of the Lua-5.4.0 distribution in source form: I don't own that code, I am in no way affiliated with Lua or Lua.org and all lua code and material is covered by Lua's own license (https://www.lua.org/license.html).

The latest Lua distribution can be obtained at this URL:

https://www.lua.org/download.html

Also, do learn Lua if you can: it's an **awesome** language!
