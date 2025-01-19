#include <Eigen/Dense>
#include <iostream>

#include "sub.hpp"
using Eigen::Vector3d;

int main() {
  const int N = 100;

  A a0[N];
  for (int i = 0; i < N; i++) {
    a0[i].n = Vector3d(1, 0, 0);
  }

  A a1[N];
  for (int i = 0; i < N; i++) {
    a1[i].n = Vector3d(0, 1, 0);
  }

  A a01[N];
  B b;
  for (int i = 0; i < N; i++) {
    a01[i] = b.cross(a0[i], a1[i]);
  }

  std::cout << "a0 x a1 = " << a01[N - 1].n.transpose() << std::endl;

  return 0;
}