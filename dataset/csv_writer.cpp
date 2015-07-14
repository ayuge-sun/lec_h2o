#include <cv.h>
#include <highgui.h>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <dirent.h>

#include "hira_label.h"

#define IMAGE_X 95
#define IMAGE_Y 95

/* 8 ビット，グレースケール */
#define CV_LOAD_IMAGE_GRAYSCALE 0

using namespace std;

int
main (int argc, char *argv[])
{
  IplImage *color_img, *gray_img;
  CvRect roi;
  CvFileStorage *fs;
  int number = 0;
  int x = 0, y = 0, size = 0;
  const char* path= "./out/pgm";
  DIR *dp;       // ディレクトリへのポインタ
  dirent* entry; // readdir() で返されるエントリーポイント
  int label;
  stringstream file_init;
  
  dp = opendir(path);
  if (dp==NULL) exit(1);
  do {
	//初期化
	file_init.str("");
	file_init.clear();
    entry = readdir(dp);
	if (entry != NULL){
	  
	  //inital
	  file_init << entry->d_name[1] << entry->d_name[2] << entry->d_name[3] << entry->d_name[4];
	  if (entry->d_name[0] == 'u')
		{
		  cout << "inital: " << file_init.str() << endl;
		  //label付
		  label = labeling(file_init.str());
		  cout << "label:" << label << endl;

		  //画像読み込み
		  gray_img = cvLoadImage (entry->d_name, CV_LOAD_IMAGE_GRAYSCALE);
		  cout << "file mane: " << entry->d_name << endl;
	 
		  //csv書き出し
		  if(gray_img != NULL){
			if(size == 0){
			  for(y = 0; y < gray_img->height; y++){
				for(x = 0; x < gray_img->width; x++){
				  cout << (char*)gray_img->imageData << endl;
				  cout << "表示した？" << endl;
				}
			  }
			}
		  }
		  //number of times
		  size ++;
		}	
	}

  } while (entry != NULL);  

  // (1)画像を読み込む


  cout << "size: " << size << endl;  
  cout << "MA hit: " << number << endl;

}
