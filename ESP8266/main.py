import urequests as req
import ov2640
import gc
import time
from machine import ADC
from machine import UART
from machine import reset

uart = UART(1, 115200)                         # init with given baudrate
uart.init(115200, bits=8, parity=None, stop=2) # init with given parameters
adc0 = ADC(0)
url = "http://6155cfaa.ngrok.io/identify"
url_command = "http://6155cfaa.ngrok.io/actCommand"

def take_photo():
    if adc0.read() > 500:
        try:
            res = req.post(url, json="START")
            print("initializing camera")
            cam = ov2640.ov2640(resolution=ov2640.OV2640_320x240_JPEG)
            print(gc.mem_free())

            clen = cam.capture_to_file('image.jpg', True)
            print("captured image is %d bytes" % clen)
            print("image is saved to image.jpg")
            res = req.post(url, json="END")

            time.sleep(2)
        except:
            print("exiting...")
        reset()

def receive_command():
    time.sleep(1)
    res = req.get(url_command)
    if res.text != '':
        uart.write(res.text)
        uart.write(res.text)
    time.sleep(1)


while True:
    take_photo()
    receive_command()

