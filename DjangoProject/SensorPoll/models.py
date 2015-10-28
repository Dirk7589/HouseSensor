from django.db import models

class SensorPacket(models.Model):
	address = models.IntegerField()
	time_stamp = models.DateTimeField('date received')
	data = models.IntegerField()