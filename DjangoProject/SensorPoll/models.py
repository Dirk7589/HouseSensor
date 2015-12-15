from django.db import models

class SensorPacket(models.Model):

    address = models.IntegerField()
    time_stamp = models.DateTimeField(auto_now_add=True)
    data = models.DecimalField(max_digits=6, decimal_places=2)

    def __str__(self):
        return ('address: ' + str(self.address) + ', Time: ' + str(self.time_stamp) + ', Data: '+ str(self.data))





class AveragedData(models.Model):

    address = models.IntegerField()
    time_stamp = models.DateTimeField(auto_now_add=True)
    data = models.DecimalField(max_digits=6, decimal_places=2)

    def __str__(self):
        return ('address: ' + str(self.address) + ',    Time: ' + str(self.time_stamp) + ',    Data: '+ str(self.data))