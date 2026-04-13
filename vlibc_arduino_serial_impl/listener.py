import serial
import os
os.system('') #magic thing that makes print work good

# --- SETTINGS ---
# Change 'COM3' to your port (e.g., '/dev/ttyUSB0' on Linux/Mac)
SERIAL_PORT = 'COM5' 
BAUD_RATE = 115200
# ----------------

try:
    ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
    print(f"Connected to {SERIAL_PORT} at {BAUD_RATE} baud.")
    print("Press Ctrl+C to stop.")
    c=0
    f=0

    print("\033[2J", end="")
    while True:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').rstrip()
            print(line)
            c+=1
            if c == 23:
                print("\033[H", end="")
                if f == 0:
                    print("\033[2J", end="")
                    f=1
                c=0

except:
    pass

finally:
    if 'ser' in locals() and ser.is_open:
        ser.close()
        print("Port closed.")
