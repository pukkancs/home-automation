import serial;
import paho.mqtt.client as mqtt
import time

broker_address="192.168.1.84" 
client = mqtt.Client("RPi-1") #create new instance
client.username_pw_set("mosquitto", password="pass");
client.connect(broker_address) #connect to broker

arduinoSerialData =serial.Serial('/dev/ttyACM1',9600)
while 1:
	if(arduinoSerialData.inWaiting()>0):
		myData = int(arduinoSerialData.readline())
                
                if (myData == 17990):
                    client.publish("home/test/led", 'OFF')
                    print "Publishing: OFF"
               
                if (myData == 20302):
                    client.publish("home/test/led", 'ON')
                    print "Publishing: ON"

