#include <iostream>
#include <vector>
#include <time.h>
#include <chrono>
#include <stdio.h>
#include <unistd.h>
#include <set>
#include <cmath>
using namespace std;

template <typename T>
class CartesianCoord{
public:
  typedef T value_t;
  value_t x;
  value_t y;
  CartesianCoord(value_t _x = 0, value_t _y = 0):x(_x),y(_y){}
  ~CartesianCoord(void){}
  friend ostream& operator<<(ostream &out, const CartesianCoord<T> c){
    out << "(" << c.x << "," << c.y << ")";
    return out;
  }
};

typedef CartesianCoord<int> coord_t;
typedef pair<double,int> index_coord;
vector<coord_t> knn (int k, vector<coord_t> &points, const coord_t &q){
  set<index_coord> distanceSet;
  double distance;
  for(int i = 0; i < points.size();i++){
    distance = ((points[i].x-q.x)*(points[i].x-q.x));
    distance += ((points[i].y-q.y)*(points[i].y-q.y));
    distance = sqrt(abs(distance));
    distanceSet.insert({distance,i});
  }

  vector<coord_t> nearestPoints;
  auto it = distanceSet.begin();
  for(int j = 0; j < k; j++){
    nearestPoints.push_back(points[(*it).second]);
    it++;
  }
  return nearestPoints;
}

int main(int argc, char const *argv[]) {
  srand(time(NULL));

  vector<coord_t> points;
  for (size_t i = 0; i < 1000; i++) {
    points.push_back(coord_t(rand()%1000,rand()%1000));
  }
  vector<coord_t>::iterator it = points.begin();
  for(; it != points.end(); it++){
    fflush(stdout);
    cout<<"\r"<<*it;
    usleep(2000);
  }
  cout << endl;

  vector<coord_t> knns;
  auto start = chrono::high_resolution_clock::now();
  knns = knn(3,points,coord_t(100,200));
  auto stop = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::microseconds>(stop-start);
  cout << "Time: "<< endl;
  cout << duration.count() << endl;
  cout << "knns"<< endl;
  vector<coord_t>::iterator kit = knns.begin();
  for(; kit != knns.end(); kit++){
    cout << *kit << endl;
  }
  return 0;
}