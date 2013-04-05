#!/usr/bin/python
# source of color picker: https://gist.github.com/keitheis/2986210


import gtk, sys, getopt
import serial

class myRGB:
   
   ## translate a color to int between 0-255
   # @param x the color (R, G or B) from gtk.ColorSelection (0-65535)
   def todec(self,x):
      #convert to int 0-255
      return int(round((x/65536.0)*255))

   def myExit(self):
      self.ser.close()
      sys.exit()

   ## callback for changing color
   def color_changed_cb(self,widget):
      c = widget.get_current_color()
      self.sendArduino(c)

   ## send the serial command to the arduino
   # @param c the gtk.gdk.Color to send
   def sendArduino(self,c):
      cmd = "c %d %d %d\n" % (self.todec(c.red),self.todec(c.green),self.todec(c.blue))
      print (cmd)
      self.ser.write (cmd)
      #s = self.ser.read(100)
      #print s

   ## constructor, (almost) never ends
   # @param port the serial port to connect to
   def __init__(self,port):
      self.port = port
      
      self.ser = serial.Serial(port, 9600, timeout=1)

      #s = self.ser.read(10)
      #print s

      # display color picker and get values
      csd = gtk.ColorSelectionDialog('LED Color Chooser')
      cs = csd.colorsel
      cs.set_has_opacity_control(False)
      cs.set_current_alpha(0)
      cs.set_current_color(gtk.gdk.color_from_hsv(0,1,1))
      cs.connect("color_changed", self.color_changed_cb)
   
      while True:
         csd.show()
         if csd.run() != gtk.RESPONSE_OK:
            print 'No color selected.'
            self.myExit()
         c = cs.get_current_color()
         self.sendArduino (c)

      self.myExit()

   
def usage():
   print "test.py [-h] [-p /dev/ttyUSB1]"
   
if __name__ == "__main__":
   port = '/dev/ttyUSB1'
   
   try:
      opts, args = getopt.getopt(sys.argv[1:], "hp:")
   except getopt.GetoptError:
      usage()
      sys.exit(2)
   for opt, arg in opts:
      if opt == "-h":
         usage()
         sys.exit(2)
      elif opt == "-p":
         port = arg

   myRGB(port)
