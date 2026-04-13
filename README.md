# vlibc
Header-only no-std crossplatform simple graphics library in C

# license
This project is distributed under the **GNU AGPLv3** license. If you plan to use vlibc in your own (closed) software, embedded devices, or SaaS products without opening the source code, you need a commercial license.

To buy one, contact me here: vlibc_development@internet.ru

# building

build command for windows_impl:
```
gcc test.c -lgdi32 -O3 -ffast-math -fno-math-errno -std=c99
```

build command for sdl_impl:
```
gcc test.c -lSDL2 -O3 -ffast-math -fno-math-errno -std=c99
```

build command for console_impl:
```
gcc test.c -O3 -ffast-math -fno-math-errno -std=c99
```

how to build arduino_impl:

1. Open ArduinoIDE
2. Create new project
3. Copy all the files you need in project folder (sketch_test.ino, vlibc_arduino_serial.h, vlibc.h, vlibc_font.h)
4. Fix the imports (just change the 10th line of vlibc_arduino_serial.h from `#include "../vlibc.h"` to `#include "vlibc.h"`)
5. Click "Upload" button

how to test arduino_impl:

1. Open the listener.py
2. Change serial port to your port
3. Run the listener.py
4. Enjoy :)

# examples

3d rotating gradient cube

![изображение](https://github.com/user-attachments/assets/e1b749b0-74a0-4c06-b739-2f2e12801030)