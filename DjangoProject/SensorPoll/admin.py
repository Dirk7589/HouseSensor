from django.contrib import admin

from .models import SensorPacket
from .models import AveragedData
from .models import ActiveSensors
from .models import HourlySensorData
from .models import DailyAverageSensorData

# Register your models here.
admin.site.register(SensorPacket)
admin.site.register(AveragedData)
admin.site.register(ActiveSensors)
admin.site.register(HourlySensorData)
admin.site.register(DailyAverageSensorData)