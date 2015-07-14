#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <cv.h>
#include <highgui.h>
#include <boost/thread/thread.hpp>
#include <boost/algorithm/string.hpp>

using namespace std;

#define IMAGE_X 28
#define IMAGE_Y 28

void loadValueFromCSV(const char file_path[]) {

  vector<vector<int> >  data;
  data.resize(10000);

  cout << "file_path:" << file_path << endl;
  ifstream ifs(file_path, ios::in);

  if (! ifs){
    cout << "no file exists!" << endl;
    exit(1);
  }

  std::string buf;  
 
  //終わりが来るまで一行読む
  int counter=0;
  while(ifs && std::getline(ifs, buf)) {
    std::vector<std::string> v;
	boost::algorithm::split(v, buf, boost::is_any_of(",")); //一行を要素ごとに区切る
	cv::Mat image = cv::Mat::zeros(IMAGE_X, IMAGE_Y, CV_32SC1); //cv::Mat作成
	int i = 0;
	for(int y = 0; y < IMAGE_Y; y++){ 
	  for(int x = 0 ; x < IMAGE_X; x++){
		image.at<int>( y, x ) = std::atoi(v[i].c_str());
		i++;
	  }
	}
	stringstream filename;
	filename << "./data_set/output_" << counter << ".jpg";
	cv::imwrite(filename.str(), image);
	cout << "保存したお！(" << counter << "回目)" << endl;
	//cv::releaseImage (&image);
	image.release();
	counter++;
  }
}


int
main (int argc, char **argv)
{
  string buf;
  int x, y;
  
  vector<vector<int> > data_;
  if (argc != 2) // || (img = cvLoadImage (argv[1], CV_LOAD_IMAGE_COLOR)) == 0)
    return -1;

  buf = argv[1];
  loadValueFromCSV(buf.c_str());

  // cv::Mat image = cv::Mat::zeros(IMAGE_X, IMAGE_Y, CV_32SC1);

  // // グレースケール画像（8bit）画像
  // for(int y = 0 ; y < IMAGE_Y; y++){
  // for(int x = 0 ; x < IMAGE_X; x++){
  //   image.at<int>( y, x ) = 0;
  //   }
  // }

  // cv::namedWindow ("Image", CV_WINDOW_AUTOSIZE);
  // cv::imshow ("Image", image);
  // cv::waitKey (0);
  // cv::imwrite("output.jpg", image);
  // cvDestroyWindow ("Image");
  // cvReleaseImage (&image);

  return 0;
}
