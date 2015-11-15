from django.db import models

class SensorPacket(models.Model):
	address = models.IntegerField()
	time_stamp = models.DateTimeField(auto_now_add=True)
	data = models.IntegerField()