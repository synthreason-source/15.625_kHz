import serial
from pynput import mouse

# Replace with your Arduino port
ser = serial.Serial('COM4', 115200)

def on_move(x, y):
    # Convert X position to 0-255 range
    value = max(0, min(255, x // 5))

    ser.write(f"{value}\n".encode())

listener = mouse.Listener(on_move=on_move)
listener.start()
listener.join()
