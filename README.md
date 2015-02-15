WinPEFix
========

Since Windows XP is no longer supported, Microsoft has updated its default
linking settings. Unless one is able to relink executable file, there is no
simple way to run application compiled by new MSVC on old Windows versions.
The reason why such programs should not be run on old OS versions is very
simple - there is no maintenance support any more (it is not 100% true).
Nonetheless, if one desires to run newly build application on an old box,
then basically there are three options:

- get executable for your OS version
- recompile from source using proper linking options
- modify [PE header](https://en.wikipedia.org/wiki/Portable_Executable) using
  hex editor

If the first two are not possible (they are recommended, though), then one
can use this tool - WinPEFix.

It will do the dirty job of overwriting the PE file's header, in order
to allow to run any application on Windows XP (bare metal version 5.01).
I mean "to allow", not "to run" - there might be incompatibilities
beyond targeting issue.


Compilation
-----------

In order to compile this tool, one has to have access to a box with Qt build
tools installed (e.g. Qt Creator for Windows). On Windows system, there are
no external dependencies required (Qt is used for building purpose only), so
once program is compiled, it should run from anywhere.


Usage
-----

1. Run WinPEFix tool
2. Select EXE file along with all required DDLs
3. Process...
4. ????
5. Profit!!!


Further reading
---------------

1. [Windows XP Targeting with C++ in Visual Studio 2012](http://blogs.msdn.com/b/vcblog/archive/2012/10/08/windows-xp-targeting-with-c-in-visual-studio-2012.aspx)
2. [Deploying Qt on XP and getting "not a valid Win32 application"](http://www.tripleboot.org/?p=423)
