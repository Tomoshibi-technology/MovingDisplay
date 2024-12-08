import serial
import struct

def send( buf ):
	while True:
		if ser.out_waiting == 0:
			break
	for b in buf:
		a = struct.pack( "B", b )
		ser.write(a)
	ser.flush()

ser = serial.Serial(
		port = "/dev/cu.wchusbserial110",
		baudrate = 115200,
		parity = serial.PARITY_NONE,
		bytesize = serial.EIGHTBITS,
		stopbits = serial.STOPBITS_ONE,
		#timeout = None,
		#xonxoff = 0,
		#rtscts = 0,
	)

while True:
	x = [0xFA, 0xFF, 0x02, 0xFE, 0x03]
	send(x)
