#include <iostream>
#include <string>
#define PI 3.1415
using namespace std;

class shape{
public:
	virtual void readInput() const = 0;
	virtual double displayArea() const = 0;
	virtual void objInfo() const = 0;
	virtual string getType() const = 0;
	virtual ~shape(){}
};

class Triangle: public shape{
	double height;
	double base;
public:
	Triangle():height(0), base(0){}
	Triangle(double height, double base):height(height),base(base){}
	
	void readInput(){
		cout << "Enter height:";
		cin >> height;

		cout << "Enter base length: ";
		cin >> base;
	}

	string getType() const { return "Triangle"; }

	double displayArea(){
		return 0.5 * base * height;
	}

	void objInfo(){
		cout<< "Shape: "<<getType()<<endl
		    << "Shape Properties:\n-----------------------"<<endl
		    << "\tHeight: "<<height<<endl
		    << "\tBase: "<<base<<endl
		    << "\t Occupied Area: "<<displayArea()<<"\n--------------------------"<<endl;
	}
};


class Rectangle: public shape{
	double height;
	double width;
public:
	Rectangle
	Rectangle(double height, double width):height(height), width(width) {}
	
	void readInput(){
		cout<<"Enter height: ";
		cin >> height;

		cout<<"Enter width: ";
		cin >> width;
		
	}

	string getType() const { return "Rectangle"; }

	double displayArea(){
		return height * width;
	}

	void objInfo(){
		cout<< "Shape: "<<getType()<<endl
		    << "Shape Properties:\n-----------------------"<<endl
		    << "\tHeight: "<<height<<endl
		    << "\tWidth: "<<base<<endl
		    << "\t Occupied Area: "<<displayArea()<<"\n--------------------------"<<endl;
	}
};


class Circle: public shape{
	double radius;
public:
	Circle(double radius): radius(radius){}

	string getType() const { return "Circle"; }

	void readInput(){
		cout << "Enter radius: ";
		cin >> radius;
	}

	double displayArea(){
		return PI * radius * radius;
	}

	void objInfo(){
		cout<< "Shape: "<<getType()<<endl
		    << "Shape Properties:\n-----------------------"<<endl
		    << "\tRadius: "<<radius<<endl
		    << "\t Occupied Area: "<<displayArea()<<"\n--------------------------"<<endl;
	}
};


class ShapeStack{
	Shape** shapeStk;
	int top;
	int currentSize;
	int maxCapacity;

	void inflate(){
		maxCapacity *= 2;
		shape** shapeStk_new = new shape*[maxCapacity];

		for(int i=0; i<size; i++){
			shapeStk_new[i] = shapeStk[i];
		}

		delete [] shapeStk;

		shapeStk = shapeStk_new;
	}
public:
	ShapeStack(int maxCapacity):top(-1), currentSize(0), maxCapacity(maxCapacity), shapeStk(nullptr){
		shapeStk = new shape*[maxCapacity];
	}

	void push()
};
