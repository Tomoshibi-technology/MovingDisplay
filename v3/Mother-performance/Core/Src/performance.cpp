
#include "performance.h"

PERFORMANCE::PERFORMANCE(uint16_t* ptr_perform_array, uint8_t* ptr_display_send_array, int16_t* ptr_circle_relative_position_array, int16_t* ptr_fish_relative_position_array, int16_t* ptr_now_position_array){
	perform_array = ptr_perform_array;//TweLiteからのデータ
	display_send_array = ptr_display_send_array;//displayに送るデータ
	circle_relative_position_array = ptr_circle_relative_position_array;//円の相対座標
	fish_relative_position_array = ptr_fish_relative_position_array;//おさかなの相対座標
	now_position_array = ptr_now_position_array;//ロボットの絶対座標 {x, y, speed}

	circle_position_array[0] = now_position_array[0];
	circle_position_array[1] = 24 * 10;
	circle_position_array[2] = r_standard * 10;//r

}

void PERFORMANCE::set_display_send_array(){
//円
	display_send_array[1] = circle_relative_position_array[0]+100;//左右、送信用に100たす
	display_send_array[2] = circle_relative_position_array[1]+100;//上下、送信用に100たす
	display_send_array[3] = circle_relative_position_array[2];//半径

//光の設定
//	for(int i=0; i<9; i++){
//		display_send_array[i+4] = light_status_array[i];//光のステータスの設定
//	}
	display_send_array[4] = light_status_array[0];
	display_send_array[5] = light_status_array[1];
	display_send_array[6] = light_status_array[2];
	display_send_array[7] = light_status_array[3];
	display_send_array[8] = light_status_array[4];
	display_send_array[9] = light_status_array[5];
	display_send_array[10] = light_status_array[6];
	display_send_array[11] = light_status_array[7];
	display_send_array[12] = light_status_array[8];



//おさかなさん
	for(int i=0; i<6; i++){
		display_send_array[3*i+13] = fish_relative_position_array[3*i];//モード設定
		display_send_array[3*i+14] = fish_relative_position_array[3*i+1] + 100;//左右、送信用に100たす
		display_send_array[3*i+15] = fish_relative_position_array[3*i+2] + 100;//上下、送信用に100たす
	}

//250チェック
	for(int i=0; i<30; i++){
		if(display_send_array[i+1] == 250){display_send_array[i+1]++;}
		else{}
	}
}

void PERFORMANCE::get_drawing_status_performance(){
//円
	circle_relative_position_array[0] = circle_position_array[0] - now_position_array[0];//円との相対距離
	circle_relative_position_array[0] /= 10;//cmになおす
	circle_relative_position_array[0] += 24;//原点を左下にした値にする

	circle_relative_position_array[1] = circle_position_array[1] / 10;//上下方向、cmになおす
	circle_relative_position_array[2] = circle_position_array[2] / 10;//半径、cmになおす

//おさかなさん
	for(int i=0; i<6; i++){
		fish_relative_position_array[3*i] = fish_position_array[3*i];//モード

		fish_relative_position_array[3*i+1] = fish_position_array[3*i+1] - now_position_array[0];//さかなとの相対距離
		fish_relative_position_array[3*i+1] /= 10;//cmになおす
		fish_relative_position_array[3*i+1] += 24;//原点を左下にした値にする

		fish_relative_position_array[3*i+2] = fish_position_array[3*i+2] / 10;//上下方向、cmになおす
	}
}


void PERFORMANCE::cal_drawing_status_performance(uint32_t count){

//	perform_array[0] = hue
//	perform_array[1] = θ
//	perform_array[2] = r
//	perform_array[3] = mode

	//描画モードを選択する
	//停止、まる固定、おさかな固定,まる運び


//ラインポジション
	line_position_array[0] = now_position_array[0] - 220;
	line_position_array[1] = now_position_array[0] + 220;

//サークルポジション
	//circle_position_array[0]は基本前の値と同じ

	circle_position_array[1] = 24 * 10;

	circle_position_array[2] = r_standard * 10;//r
	circle_position_array[2] = circle_position_array[2] - now_position_array[1] * circle_position_array[2] / shrink_const;//前後
//	if(perform_array[3] == 0){
//		circle_position_array[2] = circle_position_array[2] + circle_position_array[2] * sin() / 8;
//	}else{}

	if(perform_array[3] == 3){
		if(circle_position_array[0] - circle_position_array[2] <= line_position_array[0]){
			circle_position_array[0] = line_position_array[0] + circle_position_array[2];
//		}else if((circle_position_array[0] - circle_position_array[2] > line_position_array[0]) || (circle_position_array[0] + circle_position_array[2] > line_position_array[1])){
//
		}else if(circle_position_array[0] + circle_position_array[2] >= line_position_array[1]){
			circle_position_array[0] = line_position_array[1] - circle_position_array[2];
		}else{}
	}else{}


//光の設定
	if(perform_array[3] == 0){//フリー移動
		light_status_array[0] = perform_array[0] + 80;//circle_H
		light_status_array[1] = S_standard;//circle_S
		light_status_array[2] = V_standard;//circle_V
		light_status_array[3] = perform_array[0];//background_H
		light_status_array[4] = S_standard;//background_S
		light_status_array[5] = V_standard;//background_V
		light_status_array[6] = perform_array[0];//frame_H
		light_status_array[7] = S_standard;//frame_S
		light_status_array[8] = V_standard;//frame_V

	}else if(perform_array[3] == 1){//固定移動
		light_status_array[0] = perform_array[0] + 80;//circle_H
			light_status_array[0] %= 256;
		light_status_array[1] = S_standard;//circle_S
		light_status_array[2] = V_standard;//circle_V
		light_status_array[3] = perform_array[0];//background_H
		light_status_array[4] = S_standard;//background_S
		light_status_array[5] = V_standard;//background_V
		light_status_array[6] = perform_array[0];//frame_H
		light_status_array[7] = S_standard;//frame_S
		light_status_array[8] = V_standard;//frame_V

	}else if(perform_array[3] == 2){//おさかな
		light_status_array[0] = perform_array[0];//circle_H
		light_status_array[1] = S_standard;//circle_S
		light_status_array[2] = V_standard;//circle_V
		light_status_array[3] = perform_array[0];//background_H
		light_status_array[4] = S_standard;//background_S
		light_status_array[5] = V_standard;//background_V
		light_status_array[6] = perform_array[0];//frame_H
		light_status_array[7] = S_standard;//frame_S
		light_status_array[8] = V_standard;//frame_V

	}else if(perform_array[3] == 3){//枠
		light_status_array[0] = perform_array[0] + 80;//circle_H
			light_status_array[0] %= 256;
		light_status_array[1] = S_standard;//circle_S
		light_status_array[2] = V_standard;//circle_V
		light_status_array[3] = perform_array[0];//background_H
		light_status_array[4] = S_standard;//background_S
		light_status_array[5] = V_standard;//background_V
		light_status_array[6] = perform_array[0] + 160;//枠表示
			light_status_array[6] %= 256;
		light_status_array[7] = S_standard;//frame_S
		light_status_array[8] = V_standard;//frame_V

	}else{//例外処理
		light_status_array[0] = perform_array[0] + 80;//circle_H
		light_status_array[1] = S_standard;//circle_S
		light_status_array[2] = V_standard;//circle_V
		light_status_array[3] = perform_array[0];//background_H
		light_status_array[4] = S_standard;//background_S
		light_status_array[5] = V_standard;//background_V
		light_status_array[6] = perform_array[0];//frame_H
		light_status_array[7] = S_standard;//frame_S
		light_status_array[8] = V_standard;//frame_V
	}


//おさかなの設定
	if(perform_array[3] == 2){
		fish_position_array[0] = 2;//ID
		fish_position_array[1] = circle_position_array[0];//X
		fish_position_array[2] = 150;//Z

		fish_position_array[3] = 2;//ID
		fish_position_array[4] = circle_position_array[0] + 150;//X
		fish_position_array[5] = 300;//Z

		fish_position_array[6] = 2;//ID
		fish_position_array[7] = circle_position_array[0] - 170;//X
		fish_position_array[8] = 200;//Z

		fish_position_array[9] = 2;//ID
		fish_position_array[10] = circle_position_array[0] + 250;//X
		fish_position_array[11] = 75;//Z

		fish_position_array[12] = 2;//ID
		fish_position_array[13] = circle_position_array[0] - 400;//X
		fish_position_array[14] = 250;//Z

		fish_position_array[15] = 2;//ID
		fish_position_array[16] = circle_position_array[0] - 550;//X
		fish_position_array[17] = 100;//Z

	}else{
		fish_position_array[0] = 0;//ID
		fish_position_array[1] = 1500;//X
		fish_position_array[2] = 150;//Z

		fish_position_array[3] = 0;//ID
		fish_position_array[4] = 1900;//X
		fish_position_array[5] = 300;//Z

		fish_position_array[6] = 0;//ID
		fish_position_array[7] = 2300;//X
		fish_position_array[8] = 150;//Z

		fish_position_array[9] = 0;//ID
		fish_position_array[10] = 2700;//X
		fish_position_array[11] = 300;//Z

		fish_position_array[12] = 0;//ID
		fish_position_array[13] = 3100;//X
		fish_position_array[14] = 150;//Z

		fish_position_array[15] = 0;//ID
		fish_position_array[16] = 3500;//X
		fish_position_array[17] = 300;//Z
	}


}
