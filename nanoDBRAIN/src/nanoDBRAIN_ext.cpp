#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>

#include <Eigen/Dense>
#include <algorithm>
#include <iostream>

#include "sub.hpp"

using Eigen::Vector3d;
namespace nb = nanobind;

using RGBImage = nb::ndarray<uint8_t, nb::shape<-1, -1, 3>, nb::device::cpu>;

NB_MODULE(nanoDBRAIN_ext, m) {
  m.def("process", [](RGBImage data) {
    // Double brightness of the MxNx3 RGB image
    for (size_t y = 0; y < data.shape(0); ++y)
      for (size_t x = 0; x < data.shape(1); ++x)
        for (size_t ch = 0; ch < 3; ++ch)
          data(y, x, ch) = (uint8_t)std::min(255, data(y, x, ch) * 2);

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
  });
}
