#include <stdio.h> // for printf, etc
#include <stdlib.h> // for rand(), etc
#include <math.h> // for sin(),cos(), etc
#include <iostream>// for std::cout, etc, c++の方が出力が簡単、型を指定せずに済む
#include <iomanip>//  for std::setprecision(), 桁数を指定する
#include <fstream> // for ifstream/ofstream
#include <time.h>// for time(NULL), etc
#include "MT.h"// for MT, メルセンスツイスターを参照してくる	

int main(void){
  int i, count = 0, max = 1e+8;
  double x,y,z,pi, out=1.e+2;
  char fname[128]; //charは文字列、名前を付けるための箱を用意
  std::ofstream file; //stdの中のofstreamを参照、fileを置くとoutputできる
  srand(time(NULL)); //乱数の種、時刻
  sprintf(fname,"pi-error.dat"); //fnameにpi-error.datを入れる（名前を付けただけ）
  file.open(fname); 
  for(i=0;i<max;i++){
    x = (double)rand()/RAND_MAX; //(double):変数をキャストするrand()がint型だから、rand():一様乱数、RAND_MAX:最大値 
    y = (double)rand()/RAND_MAX;
    z = x*x + y*y;
    if(z<=1.0)
      count++; //扇形の中に入ったやつを足していく
    if(i>=(int)out){    // (double)out: cast double to int
      pi=(double)count /(double)i*4.0; // 前はmaxだったけど、今はmaxの値によっての収束の変化を見たいから、全部の点の数はiにしている
      file<<std::setprecision(16)<<i<<"\t"<<pi<<"\t"<<abs(pi-M_PI)<<std::endl;; //１６桁吐きだす、i:1行目何回吐きだしたか、\t:スペース１個、abs:絶対値、理論値とのずれ
      std::cout<<std::setprecision(16)<<i<<"\t"<<pi<<"\t"<<abs(pi-M_PI)<<std::endl; //コンソールに出す
      out*=1.2; //100から1.2倍していく、等比級数で出す。細かく出しすぎると多くなりすぎちゃうから
    }
  }
  file.close();
  out=1e+2;
  count=0;

  sprintf(fname,"pi-error-MT.dat");
  file.open(fname);
  init_genrand(time(NULL));
  for(i=0;i<max;i++){
    x = genrand_res53();
    y = genrand_res53();
    z = x*x + y*y;
    if(z<=1.0)
      count++;
    if(i>=(int)out){
      pi=(double)count /(double)i*4.0;
      file<<std::setprecision(16)<<i<<"\t"<<pi<<"\t"<<abs(pi-M_PI)<<std::endl;;
      std::cout<<std::setprecision(16)<<i<<"\t"<<pi<<"\t"<<abs(pi-M_PI)<<std::endl;
      out*=1.2;
    }
  }
  file.close();
  return 0;
}
