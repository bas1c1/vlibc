# vlibc
Header-only no-std crossplatform simple graphics library in C

# license
This project is distributed under the **GNU AGPLv3** license. If you plan to use vlibc in your own (closed) software, embedded devices, or SaaS products without opening the source code, you need a commercial license.

To buy one, contact me here: vlibc_development@internet.ru

# building

build command for sdl_impl:
```
gcc test.c -lSDL2 -O3 -ffast-math -fno-math-errno -std=c99
```

build command for console_impl:
```
gcc test.c -O3 -ffast-math -fno-math-errno -std=c99
```

# examples

3d rotating gradient cube

![изображение](https://github.com/user-attachments/assets/e1b749b0-74a0-4c06-b739-2f2e12801030)