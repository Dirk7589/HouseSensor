from django.contrib import admin

from .models import SensorPacket
from .models import AveragedData

admin.site.register(SensorPacket)
# Register your models here.
admin.site.register(AveragedData)