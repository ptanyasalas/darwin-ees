#pragma once
namespace darwin {
struct Position { double x{0.0}; double y{0.0}; };
double wrappedDelta(double from, double to, double size);
double distance(const Position& a, const Position& b, double worldSize);
Position wrap(Position p, double worldSize);
}
