import serial
import struct

def send( buf ):
	while True:
		if ser.out_waiting == 0: #送信待ちのデータが0になるのを確認
			break
	for b in buf:
		a = struct.pack("B", b) #符号なし8ビットのバイナリ形式にする
		ser.write(a) #1byte送信する
	ser.flush() #全て送信するまで待機

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
	startbyte=[250] #スタートバイトは250
	send(startbyte)
	x = [244, 42, 7, 21]
	send(x)
