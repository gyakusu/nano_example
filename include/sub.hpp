#pragma once

#include <Eigen/Dense>
#include <optional>
#include <tuple>

using Eigen::Vector3d;

class A {
 public:
  Vector3d n;
};

class B {
 public:
  A cross(const A& a, const A& b);
  std::tuple<A, A> dot_cross(const A& a, const A& b);
  std::optional<A> cross_opt(const A& a, const A& b);
};

/** reference for testing
int main() {
  A a0[100];
  for (int i = 0; i < 100; i++) {
    a0[i].n = Vector3d(1, 0, 0);
  }

  A a1[100];
  for (int i = 0; i < 100; i++) {
    a1[i].n = Vector3d(0, 1, 0);
  }

A a01[100];
  B b;
  for (int i = 0; i < 100; i++) {
    a01[i] = b.cross(a0[i], a1[i]);
  }

  std::cout << "a0 x a1 = " << a01[99].n.transpose() << std::endl;

  return 0;
}

*/
