import FaBo9Axis_MPU9250 as m
import time
mpu = m.MPU9250()
print("up")
thing = 0
with open("logpy.csv", "w") as file:
    print("reading...")
    while True:
        time.sleep(0.01)
        data = mpu.readMagnet()
        if str(data['x']) != '0':
            file.write(str(data['x']) + "," + str(data['y']) + "," + str(data['z']) + "\n")
            thing +=1
        if thing == 1920:
            break
