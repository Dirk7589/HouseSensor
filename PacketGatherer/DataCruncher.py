#usr/bin/env python

import serial
import sys
import os
import time
sys.path.append(os.path.join(os.path.dirname(__file__), '/home/pi/HouseSensor/DjangoProject'))
os.environ.setdefault('DJANGO_SETTINGS_MODULE', 'DjangoProject.settings')
from django.conf import settings

#import Django models:

from SensorPoll.models import SensorPacket
#from SensorPoll.models import AveragedData





numberOfSensors = 1
#Main function

#uncomment the try function when done playing around
#try:
	
for i in xrange(1,numberOfSensors+1):
	entries_to_avg = SensorPacket.objects.filter(address=i).values('data')
	
	#average the data only if a sensor has data to average
	if len(entries_to_avg) != 0:
		data_avg = sum(d['data'] for d in entries_to_avg)/ float(len(entries_to_avg))
		
		#calculatedAverage = AveragedData(address = i, data = data_avg)
		#calculatedAverage.save()
		
	#still need to create a method that will delete all the data that was just used to get an average point
	
	
	
				
#except:
#	sys.exit(1)
				
#sys.exit(0)
