#include <stdio.h>
#include <stdlib.h>
#include <math.h> // for mathmatical functions
#include <iostream> // for input or output, i.e., std::cout
#include <fstream> // for  std::ofstream file 
#include <cfloat> // for DBL_EPSILON ダブル制度の一番小さいやつ, a.k.a. numerical epsilon 
//using namespace std;                                                                                                                                       

int damp(double dt){ //double dtを外から持ってくる（引数）
  char filename[128];
  std::ofstream file;
  int i=0;
  double v=10.,out=1.;
  sprintf(filename,"velo_%.4f.dat",dt); //%.4f:小数点以下４以下のdouble型に、持ってきたdtが入る
  file.open(filename);
  while(v > DBL_EPSILON){ //continue while v > 2.22044604925031e-16.  
    v-=v*dt;  // as same as v = v - v*dt 次のステップのvは前のステップvから-vdt
    i++;      // as same as i += 1 or i =i + 1;　iは試行回数
    if((double)i >= out){
      file << (double)i*dt << "\t" << v <<std::endl; //idtが時間　その時の速度
      std::cout << (double)i*dt << "\t" << v <<std::endl;
      out*=1.5;  // as same as out = out * 1.5
    }
  }
  file.close();  // should be closed when all input process has been finised.
  return 0; //ファイルに出力する関数だから、データを吐きだす必要はない
}

int main(){
  double dt;
  for(dt=1.e-4;dt<=1.e-1;dt*=10.) //dt=0.0001からはじまって、0.001,0.01,0.1まで
    damp(dt);
  return 0;
}
