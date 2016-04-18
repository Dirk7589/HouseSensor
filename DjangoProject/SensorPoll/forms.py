from django import forms

from models import *

class ActiveSensorsForm(forms.ModelForm):
    class Meta:
        model = ActiveSensors
        fields = ('Sensor_number', 'Sensor_name')
           


