from django.contrib import admin

from .models import SensorPacket
from .models import AveragedData
from .models import ActiveSensors

admin.site.register(SensorPacket)
# Register your models here.
admin.site.register(AveragedData)
admin.site.register(ActiveSensors)