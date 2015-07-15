#include <cv.h>
#include <highgui.h>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <dirent.h>
#include <fstream>

#include "hira_label.h"

#define IMAGE_X 95
#define IMAGE_Y 95

/* 8 ビット，グレースケール */
//#define CV_LOAD_IMAGE_GRAYSCALE 0

using namespace std;

int
main (int argc, char *argv[])
{
  fstream file;
  cv::Mat img(95, 95, CV_16UC1);
  vector<int> data;
  int number = 0;
  int x = 0, y = 0, size = 0;
  const char* path= "./out/pgm";
  DIR *dp;       // ディレクトリへのポインタ
  dirent* entry; // readdir() で返されるエントリーポイント
  int label;
  stringstream file_init;
  
  //ファイルの読み込み
  file.open("train_data/test.csv", ios::out);
  if(! file.is_open()) {
	return  EXIT_FAILURE;
  }
  
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
		  cout << "inital: " << file_init.str();
		  //label付
		  label = labeling(file_init.str());
		  cout << ",label:" << label << endl;

		  //画像読み込み
		  stringstream file_path;
		  file_path << path << "/" << entry->d_name;
		  img = cv::imread (file_path.str(), 0);
		  cout << "file name: " << file_path.str() << endl;
	 
		  //csv書き出し
		  data.push_back(label);
		  for(y = 0; y < IMAGE_Y; y++){
			for(x = 0; x < IMAGE_X; x++){
			  //cout << "(" << y << "," << x << ")" <<  (int)img.at<unsigned char>(y,x) << endl;
			  //dataを格納
			  data.push_back( (int)img.at<unsigned char>(y,x) );
			}
		  }
		  //number of times
		  size ++;

		  cout << "data size : " << data.size() << endl;
		  //write csv file
		  for (int i = 0; i < data.size()-1; i++){
			file << data[i] << ",";
		  } file << data[data.size()-1] << endl;

		  //clear
		  data.clear();

		}	
	}

	// cout << "data size : " << data.size() << endl;
	// //write csv file
	// for (int i = 0; i < data.size()-1; i++){
	//   file << data[i] << ",";
	// } //file << data[data.size()-1] << endl;

	//clear
	data.clear();

  } while (entry != NULL);
    
  cout << "size: " << size << endl;  

}
