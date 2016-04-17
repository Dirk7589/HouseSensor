#!usr/bin/env python

import sys
import os
sys.path.append(os.path.join(os.path.dirname(__file__), '/home/pi/HouseSensor/DjangoProject'))
os.environ.setdefault('DJANGO_SETTINGS_MODULE', 'DjangoProject.settings')
from django.conf import settings
from django.core.wsgi import get_wsgi_application
application = get_wsgi_application()

#import Django models:
from SensorPoll.models import AveragedData
from SensorPoll.models import HourlySensorData


activeSensorsList = AveragedData.objects.values_list('address', flat=True).distinct().order_by('address')
#Main function

#uncomment the try function when done playing around
#try:
	
for sensorAddress in activeSensorsList:
	sensor_entries = AveragedData.objects.filter(address = sensorAddress)
	entries_to_avg = sensor_entries.values('data')
	
	#average the data only if a sensor has data to average
	if len(entries_to_avg) != 0:
		data_avg = sum(d['data'] for d in entries_to_avg)/ len(entries_to_avg)
		
		#form the data into the django model and save it as such
		calculatedAverage = HourlySensorData(address = sensorAddress, data = data_avg)
		calculatedAverage.save()
		
				
#except:
#	sys.exit(1)
				
sys.exit(0)