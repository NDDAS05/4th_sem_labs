#include<iostream>
#include<cstring>

class Container{
  static int count;

  public:
    virtual void volume() = 0;
    virtual ~Container(){}
};

