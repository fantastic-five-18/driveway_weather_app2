class DriveStatusLog:
    instances = 0
    
    def __init__(self, timeStamp = str(),
                 currentWeather = str(),
                 water = str(),
                 distance = str(),
                 temp = str(),
                 snow = False):
        self.timeStamp = timeStamp
        self.currentWeather = currentWeather
        self.water = water
        self.distance = distance
        self.temp = temp
        self.snow = snow

    def writeToFile(self):
        with open("DriveWayStatus", "a+") as statusLog:
            statusLog.write(self.timeStamp + "\t")    
            statusLog.write(self.currentWeather + " ")
            statusLog.write(self.water + " ")
            statusLog.write(self.distance + " ")
            statusLog.write(self.temperature + " ")
            statusLog.write(str(self.snow) + '\n')

            DriveStatusLog.instances += 1

        statusLog.close()
