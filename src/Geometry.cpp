#include "darwin/Geometry.h"
#include <cmath>
#include <stdexcept>
namespace darwin {
double wrappedDelta(double from,double to,double size){ if(size<=0) throw std::invalid_argument("World size must be positive"); double d=to-from; if(d>size/2)d-=size; if(d< -size/2)d+=size; return d; }
double distance(const Position&a,const Position&b,double s){ return std::hypot(wrappedDelta(a.x,b.x,s),wrappedDelta(a.y,b.y,s)); }
Position wrap(Position p,double s){ if(s<=0)throw std::invalid_argument("World size must be positive"); p.x=std::fmod(p.x,s);p.y=std::fmod(p.y,s);if(p.x<0)p.x+=s;if(p.y<0)p.y+=s;return p; }
}
