import sounddevice as sd
import numpy as np
import serial

DEVICE = 7
ser = serial.Serial("COM4", 115200)

def callback(indata, frames, time, status):
    volume = np.sqrt(np.mean(indata**2))

    pwm = int(min(255, volume * 8000))

    ser.write(f"{pwm}\n".encode())

with sd.InputStream(
        device=DEVICE,
        channels=2,
        samplerate=48000,
        blocksize=1024,
        callback=callback):
    input("Press Enter to stop...\n")
