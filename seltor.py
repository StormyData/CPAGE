from selenium import webdriver
import datetime
from pyvirtualdisplay import Display
from time import sleep
from tbselenium.tbdriver import TorBrowserDriver
from random import randint
from tbselenium.utils import start_xvfb, stop_xvfb
import tbselenium.common as cm
import sys
if len(sys.argv) == 1:
	n = 10
	print "No number argument. Used default - 10\n"
else:
	if len(sys.argv) == 2:
		n = int(sys.argv[1])
	else:
		print "Error: Too many arguments.\n"
log = open("log.txt","a")
log.write("\n"+"startTorHeadless"+"\n")
data_out = open("data.txt","a")
start_time = datetime.datetime.now()
log.write(start_time.strftime("%x")+"\n")
log.write(str(n))
tbpath = "path_to_tor_browser"
for x in range(0,n):
	sleep(randint(1,10))
	print "{}: Running...".format(x)
	display = Display(visible = 0, size = (800,600))
	display.start()
	xvfb_display = start_xvfb()
	with TorBrowserDriver(tbpath, tor_cfg=cm.USE_RUNNING_TOR) as driver:
		driver.get("adress")
		element = driver.find_element_by_id("name")
		while element.get_attribute("src") == None:
			sleep(3)
			element = driver.find_element_by_id("name")
		data_out.write("\n"+element.get_attribute("src")["num":])
	print "Done"
	stop_xvfb(xvfb_display)
	display.stop()
x = str(datetime.datetime.now()-start_time).split('.')[0]
print "Time: " + x
log.write("\n"+x)
log.close()
data_out.close()
