import pygame
from pygame.locals import *
import time
import math

class joyconState:
	def __init__(self):
		self.X=0
		self.Y=0
		self.A=0
		self.B=0
		self.posX=0
		self.posY=0

def main() :
	pygame.init()

	jstate=joyconState()

	print(f"ジョイスティック名: {joys.get_name()}")
	print(f"ボタンの数: {joys.get_numbuttons()}")
	print(f"軸の数: {joys.get_numaxes()}")

	# イベントループで入力を監視
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
				else:
					pass
			elif event.type == pygame.JOYAXISMOTION:
				# print(f"軸 {event.axis} が移動しました: {event.value}")
				if event.axis==0:
					jstate.posX=event.value
				elif event.axis==1:
					jstate.posY=event.value
		# print(f"X={jstate.X} Y={jstate.Y} A={jstate.A} B={jstate.B} posX={jstate.posX} posY={jstate.posY}")
		
		# ここから送信用の計算
		raw_rotate = 180/math.pi * math.atan2(jstate.posY, jstate.posX) +180
		raw_rotate = (raw_rotate-270) % 360
		raw_speed = math.sqrt(jstate.posX**2 + jstate.posY**2)
		# print(f"raw_rotate={raw_rotate} raw_speed={raw_speed}")

		# 0-255の範囲にスケーリング
		rotate = int(raw_rotate / 360 * 255)  # 回転角度を0-255にスケーリング
		speed = int(min(raw_speed, 1.0) * 255)  # スピードを0-1に収めた上で0-255にスケーリング
		if speed < 30:
			speed=0
			rotate=0
		if speed==250:
			speed=251
		if rotate==250:
			rotate=251
		print(f"rotate={rotate} speed={speed}")

		#ボタンの処理
		mode=0
		if jstate.X==1:
			mode=3

if __name__ == '__main__':
	pygame.init()
	pygame.joystick.init()
	try:
		joys = pygame.joystick.Joystick(0)
		joys.init()
		main()
	except pygame.error:
		print ('error has occured')

