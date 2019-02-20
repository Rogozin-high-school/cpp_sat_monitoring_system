import FaBo9Axis_MPU9250 as m

mpu = m.MPU9250()
with open("logpy.csv", "w") as file:
    while True:
        data = mpu.readMagnet()
        file.write(str(data['x']) + "," + str(data['y']) + "," + str(data['z']) + "," + "\n")
