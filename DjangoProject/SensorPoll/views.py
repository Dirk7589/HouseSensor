from django.http import Http404
from django.shortcuts import render
from .models import SensorPacket
from .models import AveragedData, ActiveSensors, HourlySensorData
from django.core.paginator import Paginator, EmptyPage, PageNotAnInteger
from django.http import HttpResponse
from .forms import ActiveSensorsForm

def index(request):
    form = ActiveSensorsForm()
    packets = SensorPacket.objects.all()
    activeSensors = ActiveSensors.objects.all().order_by('Sensor_number')
    polledSensors = SensorPacket.objects.values('address').distinct().order_by('address')
    context = {'packets':packets, 'activeSensors':activeSensors, 'polledSensors':polledSensors,'form':form}

    if request.method == "POST":
        if request.POST['submit']=='removeSensor':
            try:
                sensorId = request.POST['Sensor_selected'].split(":")
                toDelete = ActiveSensors.objects.get(Sensor_number=sensorId[0])
                toDelete.delete()
            except:
                raise Http404("Could not delete sensor")

        elif request.POST['submit']=='addSensor':
            try:
                activeSensor = ActiveSensors.objects.get(Sensor_number=request.POST['Sensor_number'])
                activeSensor.Sensor_name=request.POST['Sensor_name']
                activeSensor.save()
            except:
                newSensor = ActiveSensorsForm(request.POST)
                if newSensor.is_valid():
                    newSensor.save()
    else:
        form = ActiveSensorsForm()

    return render(request, 'SensorPoll/index.html', context)

def tables(request):

    packets_list = SensorPacket.objects.all()
    paginator = Paginator(packets_list, 25)
    page = request.GET.get('page')
    try:
        packets = paginator.page(page)
    except PageNotAnInteger:
        # If page is not an integer, deliver first page.
        packets = paginator.page(1)
    except EmptyPage:
        # If page is out of range (e.g. 9999), deliver last page of results.
        packets = paginator.page(paginator.num_pages)

    context = {'packets':packets,}
    return render(request, 'SensorPoll/tables.html', context)

def charts(request):
    
    hourly_packs = HourlySensorData.objects.all()
    averaged_packs = AveragedData.objects.all()
    context = {'averaged_packs':averaged_packs,'hourly_packs':hourly_packs,}
    return render(request, 'SensorPoll/charts.html', context)


