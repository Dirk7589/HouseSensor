from django.db import models

class SensorPacket(models.Model):
	address = models.IntegerField()
	time_stamp = models.DateTimeField(auto_now_add=True)
	data = models.DecimalField(max_digits=6, decimal_places=2)

class AveragedData(models.Model):
    address = models.IntegerField()
    time_stamp = models.DateTimeField(auto_now_add=True)
    data = models.DecimalField(max_digits=6, decimal_places=2)