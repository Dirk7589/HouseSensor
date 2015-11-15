#!usr/bin/env python

import serial
import sys
import os
sys.path.append(os.path.join(os.path.dirname(__file__), '/home/pi/HouseSensor/DjangoProject'))
os.environ.setdefault('DJANGO_SETTINGS_MODULE', 'DjangoProject.settings')
from django.conf import settings

#import Django models:

from SensorPoll.models import SensorPacket


#Set read port 
port = serial.Serial("/dev/ttyAMA0", baudrate=300)

#define a predetermined packet size
packetSize = 3

class ReceivedPacket:
	def __init__(self,packet):

		self.address = packet[0]
		self.data = packet[1]

	def displayPacket(self):
		print(str(self.address))
		print(str(self.data))
		
	def getAddress(self):
		return self.address
		
	def getData(self):
		return self.data


#Main function, always running
try:
	while True:

		received = port.read()
			
		value = ord(received)
		syncChar = 40 #The synchronizing character is '('
		if value == syncChar:
			buffer = port.read(packetSize)
			packet = []

			for i in xrange(packetSize):
				packet.append(ord(buffer[i]))
					
			checksum = 0
			for i in xrange(len(packet)-1):
				checksum += packet[i]

			if packet[len(packet)-1] == checksum:
				currentPacket = ReceivedPacket(packet)
				pack = SensorPacket(address= currentPacket.getAddress(),  data= currentPacket.getData())
				pack.save()
except:
	sys.exit(1)
				
sys.exit(0)
