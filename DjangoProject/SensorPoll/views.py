from django.http import Http404
from django.shortcuts import render
from .models import SensorPacket
from .models import AveragedData
from django.core.paginator import Paginator, EmptyPage, PageNotAnInteger
from django.http import HttpResponse

def index(request):
	packets = SensorPacket.objects.all()
	context = {'packets':packets,}
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
    
    averaged_packs = AveragedData.objects.all()
    context = {'averaged_packs':averaged_packs,}
    return render(request, 'SensorPoll/charts.html', context)


