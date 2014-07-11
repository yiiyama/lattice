#ifndef Coordinate_h
#define Coordinate_h

#include <string>

namespace lattice {

  class Coordinate {
  public:
    static unsigned const MAXDIM = 4;

    Coordinate(unsigned, int*, int*, int*);
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

    Coordinate& operator++();
    Coordinate& operator--();
    Coordinate& move(char, int);
    Coordinate& move(unsigned, int);

    bool operator<(Coordinate const&) const;
    bool operator==(Coordinate const&) const;

  private:
    unsigned ndim_;
    int coords_[MAXDIM];
    int lows_[MAXDIM];
    int highs_[MAXDIM];
  };

}

#endif
