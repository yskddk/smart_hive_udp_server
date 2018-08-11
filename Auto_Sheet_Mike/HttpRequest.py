import requests
import socket
from threading import Thread

#YUSUKE# address=('192.168.68.35',9898)
address=('127.0.0.1', 50812)
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  
s.bind(address)


def HttpRequest(msg):
    if len(msg)<18:
        print("Msg Length Is Too Short (Need 17)")
    else:
        payload ={"method":msg[0],"WorkSheetName":msg[1],"Time":msg[2],"Lon":msg[3],
        "Lat":msg[4],
        "Tem1":msg[5],
        "Hum1":msg[6],
        "Vol1":msg[7],
         "Tem2":msg[8],
        "Hum2":msg[9],
        "Vol2":msg[10],
         "Tem3":msg[11],
        "Hum3":msg[12],
        "Vol3":msg[13],
         "Tem4":msg[14],
        "Hum4":msg[15],
        "Vol4":msg[16],
        "Weight":msg[17],}
        r=requests.post("https://script.google.com/macros/s/AKfycbw-3C_60Ua9ZrdB9ns_hilYOU70aqjISdaQfRV1V6sxsN50Zgnz/exec",payload)
        m =''
        for i in msg:
           m+=i+","
        print("Successful To Post Data\n" +m+" \n")
       


while True:
    data, addr = s.recvfrom(2048)
    stringdata =data.decode('utf-8')
    stringArray =stringdata.split(",")
    if stringdata =="close":
        print('Server Close')
        break
    if stringArray[0]=="write":
        print("Data Get")
        HttpRequest(stringArray)
        


#method ="write"
#payload ={"method":method,"WorkSheetName":"Hello"}

#r=requests.post("https://script.google.com/macros/s/AKfycbx2PXjWJAMQtkWSLasN1ta6eokuDm7lgmEjirN8Q9xUJEAGy_32/exec",payload)

#print(r.text)
#HttpRequest('1,2,3,4')


