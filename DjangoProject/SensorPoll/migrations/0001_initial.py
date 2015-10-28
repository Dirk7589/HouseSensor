# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
    ]

    operations = [
        migrations.CreateModel(
            name='SensorPacket',
            fields=[
                ('id', models.AutoField(verbose_name='ID', serialize=False, auto_created=True, primary_key=True)),
                ('address', models.IntegerField()),
                ('time_stamp', models.DateTimeField(verbose_name=b'date received')),
                ('data', models.IntegerField()),
            ],
        ),
    ]
