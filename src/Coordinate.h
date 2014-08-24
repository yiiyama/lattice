#ifndef Coordinate_h
#define Coordinate_h

#include <string>

#include <map>
#include <set>

namespace lattice {

  unsigned const MAXDIM(4);

  struct Bounds {
    Bounds() : ndim(0) {}
    unsigned ndim;
    int max[MAXDIM];
  };

  class Coordinate {
  public:
    Coordinate(Bounds const&);
    Coordinate(Coordinate const&);
    ~Coordinate();

    Coordinate& operator=(Coordinate const&);

    bool isValid() const;

    int t() const { return coords_[0]; }
    int x() const { return coords_[1]; }
    int y() const { return coords_[2]; }
    int z() const { return coords_[3]; }
    int operator[](unsigned _i) const { return _i < MAXDIM ? coords_[_i] : 0; }

    std::string getName() const;

    Coordinate& next();
    Coordinate& prev();
    Coordinate& move(char, int);
    Coordinate& move(unsigned, int);
    Coordinate& moveTo(int, int = 0, int = 0, int = 0);

    bool atLowEdge(unsigned) const;
    bool atHighEdge(unsigned) const;

    bool operator<(Coordinate const&) const;
    bool operator==(Coordinate const&) const;
    bool operator!=(Coordinate const& _rhs) const { return !operator==(_rhs); }

  private:
    Bounds const* bounds_;
    int coords_[MAXDIM];
  };

  typedef std::map<Coordinate, double> ValueMap;
  typedef std::map<Coordinate, double>::const_iterator VMItr;
  typedef std::set<Coordinate> CoordSet;
  typedef std::set<Coordinate>::const_iterator CSIter;

}

#endif
