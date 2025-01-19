#include "sub.hpp"

A B::cross(const A& a, const A& b) {
  auto an = a.n;
  auto bn = b.n;
  auto cn = an.cross(bn);
  A c;
  c.n = cn;
  return c;
}

std::tuple<A, A> B::dot_cross(const A& a, const A& b) {
  auto an = a.n;
  auto bn = b.n;
  A c;
  c.n = an.cross(bn);
  A d;
  d.n = bn.cross(an);
  return std::make_tuple(c, d);
}

