compiling instructions:
structure should look like this:

vlibc.h
vlibc_font.h
examples
-> fractals
-> -> main.c
-> -> vlibc_windows.h
-> -> README.txt

command for compilation:
gcc main.c -ffast-math -fno-math-errno -O3 -std=c99 -lgdi32 -mconsole


operating instructions:
+/-                       ---  change the real part of the Julia constant by 0.001
shift and +/-             ---  change the imaginary part of the Julia constant by 0.001
R                         ---  reset the scale
1/2/3                     ---  change the fractal to Mandelbrot/Julia/Julia cubic
Enter/F5                  ---  render button
hold left mouse and drag  ---  change the scale