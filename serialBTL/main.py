import serial
import time
import bluetooth
 
def search():
    devices = bluetooth.discover_devices(duration=20, lookup_names = True)
    return devices

while True:
    print("[SCAN] Scan BLE sendo realizado. Aguarde...")
    results = search()
    print("[SCAN] Fim do scan BLE.")
    if (results!=None):
        for addr, name in results:
            print("Dispositivo encontrado: {0} - {1}".format(addr, name))
    time.sleep(1)
    print(" ")