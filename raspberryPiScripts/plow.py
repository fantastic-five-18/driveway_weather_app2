import serial
import time
import string
import datetime
from DriveStatusLog import DriveStatusLog
from weather import Weather, Unit

ser = serial.Serial('/dev/ttyACM3', 9600)
msg = "a".encode('utf-8')
weather = Weather(unit=Unit.FAHRENHEIT)
logs = DriveStatusLog()
readCount = 0


while True:
    currentWeather = weather.lookup_by_location("detroit").condition.text
    sensorRead = ser.readline()

    if readCount == 0:
        logs.timeStamp = str(datetime.datetime.now())
        print("Timestamp: \t", logs.timeStamp)

        logs.currentWeather = currentWeather
        print("Weather: \t " + logs.currentWeather)
            
        water = sensorRead.decode('utf-8')
        logs.water = water[:len(water)-2]
        readCount += 1

        print("Water: \t\t", logs.water)
            
    elif readCount == 1:
        distance = sensorRead.decode('utf-8')
        logs.distance = distance[:len(distance)-2]
        readCount += 1

        print("Distance: \t", logs.distance)
            
    else:
        temperature = sensorRead.decode('utf-8')
        logs.temperature = temperature[:len(temperature)-2]
        readCount = 0

        print("Temperature: \t", logs.temperature)

        print("Snow: \t\t " + str(logs.snow) + '\n')

        logs.writeToFile()

        if int(logs.distance) < 300 and float(logs.temperature) <20 and int(logs.water)==1 and logs.currentWeather == "Mostly Cloudy":
            logs.snow = True
            ser.write(msg)
        else
            logs.snow = False
                




