#ifndef GIRAFFE_HH
#define GIRAFFE_HH
#include "mammal.hh"
#include "animal.hh"


class Giraffe: public Mammal
{
public:
    Giraffe();
    void make_noise(std::ostream& output);


private:
};

#endif // BIRD_HH
