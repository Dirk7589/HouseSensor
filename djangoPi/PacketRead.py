import serial
import sys

port = serial.Serial("/dev/ttyAMA0", baudrate=300)


def readlineCR(port):
	rphrase = ""
	while True:
                rcv = port.read()
                rphrase += rcv

                if rcv == '\r' or rcv == '':
                       return  rphrase



class SensorPacket:
	def __init__(self,packet):

		self.address = packet[0]
		self.data = packet[1]

	def displayPacket(self):
		print(str(self.address))
		print(str(self.data))

packetSize = 3

while True:

	received = port.read()
		
	value = ord(received)
	if value == 40:
		buffer = port.read(packetSize)
		packet = []

		for i in xrange(packetSize):
			packet.append(ord(buffer[i]))
				
		checksum = 0
		for i in xrange(len(packet)-1):
			checksum += packet[i]

		if packet[len(packet)-1] == checksum:
			sensorPacket = SensorPacket(packet)
			sensorPacket.displayPacket()
				

sys.exit()
