PacketGatherer setup info:

example can be found at http://blog.scphillips.com/posts/2013/07/getting-a-python-script-to-run-in-the-background-as-a-service-on-boot/


Using the init script

To actually use this script, put your Python script where you want and make sure it is executable (e.g. chmod 755 myservice.py) and also starts with the line that tells the computer to use the Python interpreter (e.g. #!/usr/bin/env python). Edit the init script accordingly. Copy the init script into /etc/init.d using e.g. sudo cp myservice.sh /etc/init.d. Make sure the script is executable (chmod again) and make sure that it has UNIX line-endings. At this point you should be able to start your Python script using the command sudo /etc/init.d/myservice.sh start, check its status with the /etc/init.d/myservice.sh status argument and stop it with sudo /etc/init.d/myservice.sh stop.

To make the Raspberry Pi use your init script at the right time, one more step is required: running the command sudo update-rc.d myservice.sh defaults. This command adds in symbolic links to the /etc/rc.x directories so that the init script is run at the default times. you can see these links if you do ls -l /etc/rc?.d/*myservice.sh


------------------------------------
PacketGatherer.sh can be found at /etc/init.d/PacketGather.sh

PacketGatherer.py can be found at /home/pi/bin/PacketGatherer.py 
