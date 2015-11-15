from django.http import Http404
from django.shortcuts import render
from django.template import RequestContext, loader
from .models import SensorPacket

from django.http import HttpResponse

def index(request):
	template = loader.get_template('SensorPoll/index.html')
	packets = SensorPacket.objects.all()
	context = RequestContext(request, {'packets':packets,})
	return HttpResponse(template.render(context))

def tables(request):
    template = loader.get_template('SensorPoll/tables.html')
    packets = SensorPacket.objects.all()
    context = RequestContext(request, {'packets':packets,})
    return HttpResponse(template.render(context))

def charts(request):
    template = loader.get_template('SensorPoll/charts.html')
    packets = SensorPacket.objects.all()
    context = RequestContext(request, {'packets':packets,})
    return HttpResponse(template.render(context))


