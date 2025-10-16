#include <chrono>
#include <gettermsize.h>
#include <iostream>
#include <iterator>
#include <opencv4/opencv2/core/mat.hpp>
#include <opencv4/opencv2/core/matx.hpp>
#include <opencv4/opencv2/core/types.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/videoio.hpp>
#include <thread>
using namespace cv;
using namespace std;
int main() {
  int width, height = 0;
  get_terminal_size(width, height);
  int orgwidth = width;
  int orgheight = height;
  VideoCapture vid("usr/test.mp4");
  bool validvid = false;
  cout << endl << "enter path of video" << endl;

  if (vid.isOpened())
    validvid = true;
  while (true) {
    string path;
    cin >> path;
    VideoCapture temp(path);
    if (temp.isOpened()) {
      vid = temp;
      break;
    }
  }

  // VideoCapture vid("/home/archy/Videos/opensourcemickey.mp4");
  double mspf = 1000 / vid.get(CAP_PROP_FPS);
  Mat image;
  int processtime = 10;
  // imread("/home/archy/Pictures/Screenshots/swappy-20250704-173449.png", 1);
  while (true) {
    auto t1 = chrono::high_resolution_clock::now();
    get_terminal_size(width, height);
    printf("\033[H\033[J");
    bool frame = vid.read(image);
    if (!frame)
      break;
    Mat resized;
    resize(image, resized, Size(width, height));
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        // int v = (int)resized.at<uchar>(i, j);
        int r = (int)resized.at<Vec3b>(i, j)[2];
        int g = (int)resized.at<Vec3b>(i, j)[1];
        int b = (int)resized.at<Vec3b>(i, j)[0];
        // cout << j << "\t" << i << endl;
        if ((i == 0 && j == 0)) {
          cout << processtime + 10;
          continue;
        } else if ((i == 0 && j == 1))
          continue;
        printf("\033[38;2;%d;%d;%dm\033[48;2;%d;%d;%dmt\033[m", r, g, b, r, g,
               b);
      }
    }
    auto t2 = chrono::high_resolution_clock::now();
    processtime =
        (chrono::duration_cast<chrono::milliseconds>(t2 - t1)).count();
    this_thread::sleep_for(
        chrono::milliseconds(max(0, (int)mspf - (int)processtime)));
  }

  imshow("random", image);
  waitKey(0);
  vid.release();
  return 0;
}
