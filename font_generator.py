from PIL import Image, ImageDraw, ImageFont
import numpy as np
import os

def main():
    try:
        font_size = int(input("Enter font size (pixels): "))
        if font_size <= 0:
            print("Font size must be positive")
            return
    except ValueError:
        print("Please enter a valid number")
        return
    
    chars = "0123456789qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM"
    
    font = ImageFont.load_default()
    
    with open(f"vlibc_font.h", "w") as f:
        f.write(f"// Generated bitmap font ({font_size}x{font_size})\n")
        f.write(f"// Characters: {chars}\n\n")
        f.write(f"#ifndef VLIBC_BITMAP_FONT_H\n")
        f.write(f"#define VLIBC_BITMAP_FONT_H\n\n")
        f.write(f"#define VLIBC_FONT_CHAR_COUNT 62\n")
        f.write(f"#define VLIBC_FONT_WIDTH {font_size}\n")
        f.write(f"#define VLIBC_FONT_HEIGHT {font_size}\n\n")
        f.write(f"#define VLIBC_FONT_SIZE {font_size}\n\n")
        f.write("#ifndef VLIBCDEF\n")
        f.write("#define VLIBCDEF static const\n")
        f.write("#endif\n\n")
        
        f.write(f"VLIBCDEF short __vlibc_font[VLIBC_FONT_CHAR_COUNT][VLIBC_FONT_HEIGHT][VLIBC_FONT_WIDTH] = {{\n")
        
        for char_idx, char in enumerate(chars):
            img = Image.new('L', (font_size, font_size), 255)
            draw = ImageDraw.Draw(img)
            
            left, top, right, bottom = draw.textbbox((0, 0), char, font=font)
            text_width = right - left
            text_height = bottom - top
            
            position = ((font_size - text_width) // 2 - left, (font_size - text_height) // 2 - top)

            draw.text(position, char, font=font, fill=0)
            
            bitmap = np.array(img)
            bitmap = (bitmap < 128).astype(int)
            
            f.write(f"    // Character '{char}' (ASCII: {ord(char)})\n")
            f.write(f"    {{\n")
            
            for row in range(font_size):
                f.write("        {")
                for col in range(font_size):
                    f.write(f"{bitmap[row][col]}")
                    if col < font_size - 1:
                        f.write(", ")
                f.write("}")
                if row < font_size - 1:
                    f.write(",")
                f.write("\n")
            
            f.write("    }")
            if char_idx < len(chars) - 1:
                f.write(",")
            f.write("\n\n")
        
        f.write("};\n\n")

        f.write(f"VLIBCDEF char VLIBC_FONT_CHARS[] = \"{chars}\";\n\n")

        f.write("VLIBCDEF int __vlibc_get_font(char c) {\n")
        f.write("    const char *ptr = VLIBC_FONT_CHARS;\n")
        f.write("    int index = 0;\n")
        f.write("    while (*ptr) {\n")
        f.write("        if (*ptr == c) {\n")
        f.write("            return index;\n")
        f.write("        }\n")
        f.write("        ptr++;\n")
        f.write("        index++;\n")
        f.write("    }\n")
        f.write("    return -1;\n")
        f.write("}\n\n")
        
        f.write("#endif // BITMAP_FONT_H\n")

    print(f"Font dimensions: {font_size}x{font_size} pixels")
    print(f"Total characters: {len(chars)}")

if __name__ == "__main__":
    main()
