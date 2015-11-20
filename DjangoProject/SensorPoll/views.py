from django.http import Http404
from django.shortcuts import render
from django.template import RequestContext, loader
from .models import SensorPacket
from django.core.paginator import Paginator, EmptyPage, PageNotAnInteger
from django.http import HttpResponse

def index(request):
	template = loader.get_template('SensorPoll/index.html')
	packets = SensorPacket.objects.all()
	context = RequestContext(request, {'packets':packets,})
	return HttpResponse(template.render(context))

def tables(request):
    template = loader.get_template('SensorPoll/tables.html')
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
    context = RequestContext(request, {'packets':packets,})
    return HttpResponse(template.render(context))

def charts(request):
    template = loader.get_template('SensorPoll/charts.html')
    packets = SensorPacket.objects.all()
    context = RequestContext(request, {'packets':packets,})
    return HttpResponse(template.render(context))


