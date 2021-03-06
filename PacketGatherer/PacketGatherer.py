#!usr/bin/env python

import serial
import sys
import os
import time
sys.path.append(os.path.join(os.path.dirname(__file__), '/home/pi/HouseSensor/DjangoProject'))
os.environ.setdefault('DJANGO_SETTINGS_MODULE', 'DjangoProject.settings')
from django.conf import settings

#import Django models:

from SensorPoll.models import SensorPacket


#Set read port 
port = serial.Serial("/dev/ttyAMA0", baudrate=300)

#define a predetermined packet size
packetSize = 5

class ReceivedPacket:
	def __init__(self,packet):

		self.address = packet[0]
		self.data = packet[1]
		self.creationTime = time.time()

	def displayPacket(self):
		print(str(self.address))
		print(str(self.data))
		
	def getAddress(self):
		return self.address
		
	def getData(self):
		return self.data
		
	def getCorrectedData(self):
		correctedData = float(self.data)/10.0
		return correctedData
		
	def getTime(self):
		return self.creationTime

	def isDifferentThan(self, olderPacket):
		if (olderPacket is None):
			return True
		elif (self.address != olderPacket.address):
			return True
		elif self.creationTime > (olderPacket.creationTime + 15):
			return True
		else:
			return False


			
#initialize a last packet
lastPacket = None

#Main function, always running
try:
	while True:
		received = port.read()
			
		value = ord(received)
		syncChar = 40 #The synchronizing character is '('
		#check for synchronizing character
		if value == syncChar:
			#print('accepted sync')
			buffer = port.read(packetSize)
			packet = []
			
			#create the packet in proper format 'address'+'data'+'checksum'
			for i in xrange(packetSize):
				packet.append(ord(buffer[i]))
				
			address = packet[0]					
			#reform data from low and high 8bit numbers
			data = (packet[2] << 8) | packet[1]
			#reform checksum from low and high 8bit numbers
			checksum = (packet[4] << 8) | packet[3]
			
			computedChecksum = address+data
			
			#compare computed checksum to received checksum
			if computedChecksum == checksum and checksum != 0:
				#print('checksum passed')
				#print(str(packet))
				computedPacket = [address, data, checksum];
				#instantiate Packet object
				currentPacket = ReceivedPacket(computedPacket)
				#check for packet duplicity
				if currentPacket.isDifferentThan(lastPacket):
					#print('packet is different than the last')
					#create packet to write to django DB
					pack = SensorPacket(address= currentPacket.getAddress(),  data= currentPacket.getCorrectedData())
					pack.save()
					#print('saved packet')
					#save packet for next cycle check
					lastPacket = currentPacket
				
				
except:
	sys.exit(1)
				
sys.exit(0)
