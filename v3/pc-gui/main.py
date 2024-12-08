import pygame
from pygame.locals import *
import time
import math
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

class joyconState:
	def __init__(self):
		self.X=0
		self.Y=0
		self.A=0
		self.B=0
		self.posX=0
		self.posY=0
		self.sr=0
		self.sl=0

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

def main() :
	pygame.init()

	jstate=joyconState()

	print(f"ジョイスティック名: {joys.get_name()}")
	print(f"ボタンの数: {joys.get_numbuttons()}")
	print(f"軸の数: {joys.get_numaxes()}")



	# イベントループで入力を監視
	Hue=0
	toggleA=0
	preA=0
	toggleB=0
	preB=0

	while True:
		for event in pygame.event.get():
			if event.type == pygame.JOYBUTTONDOWN:
				# print(f"ボタン {event.button} が押されました")
				if event.button==0:
					jstate.X=1
				elif event.button==1:
					jstate.A=1
				elif event.button==2:
					jstate.Y=1
				elif event.button==3:
					jstate.B=1
				elif event.button==9:
					jstate.sl=1
				elif event.button==10:
					jstate.sr=1
				else:
					pass
			elif event.type == pygame.JOYBUTTONUP:
				# print(f"ボタン {event.button} が離されました")
				if event.button==0:
					jstate.X=0
				elif event.button==1:
					jstate.A=0
				elif event.button==2:
					jstate.Y=0
				elif event.button==3:
					jstate.B=0
				elif event.button==9:
					jstate.sl=0
				elif event.button==10:
					jstate.sr=0
				else:
					pass
			elif event.type == pygame.JOYAXISMOTION:
				# print(f"軸 {event.axis} が移動しました: {event.value}")
				if event.axis==0:
					jstate.posX=event.value
				elif event.axis==1:
					jstate.posY=event.value
		if jstate.posX<0.1 and jstate.posX>-0.1:
			if jstate.posY<0.1 and jstate.posY>-0.1:
				jstate.posX=0
				jstate.posY=0
		# print(f"X={jstate.X} Y={jstate.Y} A={jstate.A} B={jstate.B} posX={jstate.posX} posY={jstate.posY} sr={jstate.sr} sl={jstate.sl}")
		
		# ここから送信用の計算
		raw_rotate = 180/math.pi * math.atan2(jstate.posY, jstate.posX) +180
		raw_rotate = (raw_rotate-270) % 360
		raw_speed = math.sqrt(jstate.posX**2 + jstate.posY**2)
		# print(f"raw_rotate={raw_rotate} raw_speed={raw_speed}")

		# 0-255の範囲にスケーリング
		rotate = int(raw_rotate / 360 * 255)  # 回転角度を0-255にスケーリング
		speed = int(min(raw_speed, 1.0) * 255)  # スピードを0-1に収めた上で0-255にスケーリング
		if speed < 50:
			speed=0
			rotate=0
		# print(f"rotate={rotate} speed={speed}")

		#---ボタンの処理---
		#toggle処理
		if jstate.A==1 and preA==0:
			toggleA=1-toggleA
			if toggleB==1:
				toggleB=0
		preA=jstate.A
		if jstate.B==1 and preB==0:
			toggleB=1-toggleB
			if toggleA==1:
				toggleA=0
		preB=jstate.B
		# print(f"toggleA={toggleA} toggleB={toggleB}")

		#modeの処理
		if jstate.X==1:
			mode=3
			toggleA=0
			toggleB=0
		elif toggleA==1:
			mode=0
		elif toggleB==1:
			mode=2
		else:
			mode=1

		#色の処理
		if jstate.sr==1:
			Hue+=1
			if Hue>255:
				Hue=0
		if jstate.sl==1:
			Hue-=1
			if Hue<0:
				Hue=255

		#送信
		startbyte=[250] #スタートバイトは250
		send(startbyte)
		# x = [125, rotate, speed, mode]
		x = [Hue, rotate, speed, mode]
		for i in range(4):
			if x[i]==250:
				x[i]=251
				# print("over-------------------------")
		send(x)
		print(f"Hue={Hue} rotate={rotate} speed={speed} mode={mode}")

		time.sleep(0.02)
		

if __name__ == '__main__':
	pygame.init()
	pygame.joystick.init()
	try:
		joys = pygame.joystick.Joystick(0)
		joys.init()
		main()
	except pygame.error:
		print ('error has occured')

