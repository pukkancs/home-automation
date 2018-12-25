import serial;
import paho.mqtt.client as mqtt
import time
import json

broker_address="192.168.1.84" 
client = mqtt.Client("RPi-1") #create new instance
client.username_pw_set("mosquitto", password="pass");
client.connect(broker_address) #connect to broker

arduinoSerialData =serial.Serial('/dev/ttyACM0',9600)
while 1:
	if(arduinoSerialData.inWaiting()>0):
            try:
		myData = json.loads(arduinoSerialData.readline())
                
                print json.dumps(myData)
                client.publish("home/test/sensor/array/1", json.dumps(myData))
            except ValueError:
                print 'Try again...'
