/************************************************************
■Macでメモリーカードをフォーマット。ファイルタイプをFAT32形式にする方法。
	https://blog.websandbag.com/entry/2018/02/15/040004
	
	contents
		元々、FAT16であったが、改めてmac上でディスクユーティリティを使い、FATでformatする(結果は、FAT16なのだが)必要があった。
		そうしないと、なぜかfileを書き込めなかったので。
		★★★ くれぐれも、HDDを消してしまわないよう、細心の注意を払うこと ★★★

■Seeed-Studio/ Music_Shield
	query = arduino MusicPlayer seeed api
	
		https://github.com/Seeed-Studio/Music_Shield
************************************************************/
#include <MusicPlayer.h>
#include <SD.h>
#include <SPI.h>

/************************************************************
************************************************************/
// #define AUTO_SCAN

const int SD_SS = 10;


/************************************************************
************************************************************/
/******************************
******************************/
void setup() {
	/********************
	********************/
	Serial.begin(9600);
	
	pinMode(SS, OUTPUT);
	SD.begin(SD_SS); // need this to use SD class like "SD.exists()".
	
	/********************
	********************/
	player.begin();
	
#ifdef 	AUTO_SCAN
	// file nameの順番が狂ってしまった
	player.scanAndPlayAll();
	
#else
	// 決め打ち
	enum { NUM_MUSICS = 22, };
	enum { BUF_SIZE = 100, };
	for(int i = 0; i < NUM_MUSICS; i++){
		char buf[BUF_SIZE];
		sprintf(buf, "music%02d.mp3", i + 1);
		Serial.print("> ");
		Serial.println(buf);
		
		if(SD.exists(buf) == true){
			player.addToPlaylist(buf);
		}else{
			Serial.print("[");
			Serial.print(buf);
			Serial.println("] not exist.");
		}
	}
#endif
}

/******************************
******************************/
void loop() {
	/********************
	Music Shueldの制御関数を呼び出す
	player.update()の方が良かったのでは？？
	********************/
	player.play();
}
