//============================================================================
// Name        : Lab10Part1.cpp
// Author      : Aaron Neidlinger
// Description : Experiment in Abstract Base Classes
//============================================================================

#include <iostream>
#include <math.h>

using namespace std;

class BaseConic{   
     protected:
          double centerX;
          double centerY;  
     public: 
          BaseConic();
          BaseConic(double x,double y);
          virtual ~BaseConic(){};
          void move(double x, double y);        //shifts the center of the shape
          virtual double area() const = 0;     //calculates area A=PIr^2 for circle and A=PIab for ellipse      
          virtual void display() const = 0;  //displays all of the shapes information
};

BaseConic::BaseConic(){
     centerX = 10;
     centerY = 10;     
}

BaseConic::BaseConic(double x, double y){
     centerX = x;
     centerY = y;     
}

void BaseConic::move(double x, double y){
     centerX += x;
     centerY += y;
}

class Circle : public BaseConic{
     private:
          double radius;
     public:
          Circle(){radius = 5;}
          Circle(double r,double x,double y):BaseConic(x,y){radius = r;}
          virtual double area() const {double a = 2*3.14*radius*radius; return a;}
          void resize(double r) {radius = r;}
          virtual void display() const;
          int position(double x, double y);    //determines if (x,y) position is in, on, or out of the circle
};

void Circle::display() const{
     cout << endl << "Circle:" << endl << "Center: ("<< centerX << " , " << centerY << ")";
     cout << endl << "Radius: " << radius << endl;
}

int Circle::position(double x, double y){
         double d = ((x - centerX)*(x - centerX)) + ((y - centerY)*(y - centerY));
         d = sqrt(d);
         
         if(d<radius)
               return 1;      //inside the circle
         if(d==radius)
               return 2;      //on the circle
         if(d>radius)
               return 3;      //outside the circle
               
         return -1;      //something went wrong
}

class Ellipse : public BaseConic{
     private:
          double a; //semi-major axis
          double b; //semi-minor axis
          double angle;  //orientation angle
          double vertex1;
          double vertex2;
     public:
          Ellipse(){   a = 5; b = 10; angle = 90;}
          Ellipse(double x, double y, double A, double B, double ang):BaseConic(x,y){a = A; b = B; angle = ang;}
          virtual double area() const {double ar = 3.14*a*b; return ar;}
          void resize(double min, double maj) {a = maj; b = min;}
          virtual void display() const; 
          void vertices();  //calculates the position of the vertices
          void rotate(double rotation){angle += rotation*90; vertices();}       //rotates the ellipse in 90 degress intervals
};

void Ellipse::vertices(){
	//checks if major axis is horizontal
	if(angle == 0 || (int)angle % 180 == 0.0){
		//left horizontally
		vertex1 = centerX - .5 * a;
		//right horizontally
		vertex2 = centerX + .5 * a;
	}
	//checks if major axis is verticall
	if((int)angle % 90 == 0.0){
		//top vertex vertically
		vertex1 = centerY + .5 * a;
		//bottom vertex vertically
		vertex2 = centerY - .5 * a;
	}
}


void Ellipse::display() const{
     //vertices();
     cout << endl << "Ellipse:" << endl << "Center: ("<< centerX << " , " << centerY << ")";
     cout << endl << "semi-major axis: " << a << endl << "semi-minor axis: " << b << endl;
     cout << "Angle of Ellipse: " << angle << " degrees" << endl;
     cout << "Vertices of the ellipse: " << vertex1 << " , " << vertex2 << endl;
}


int main() {
	Circle circle1;
	circle1.display();
	double ar = circle1.area();
	cout << "Area of circle: " << ar << endl;
	circle1.resize(2);
	circle1.move(3,4);
	circle1.display();
	int where = circle1.position(2,4);
	cout << "1 = inside the circle" << endl << "2 = on the circle" << endl << "3 = outside the circle" << endl;
	cout << "Result of (2,4): " << where << endl;
	
	Ellipse ellipse1;
	ellipse1.vertices();
	ellipse1.display();
	double are = ellipse1.area();
	cout << "Area of ellipse: " << are << endl;
	ellipse1.resize(10,20);
	ellipse1.move(3,4);
	ellipse1.display();
	ellipse1.rotate(1);
	ellipse1.display();
	
	//BaseConic base;	this generates a compile error bc it is an ABC
	
	//base abc pointer to derived classes
	BaseConic* cpointer = &circle1;
	cpointer->display();
	cpointer->move(6,2);
	cpointer->display();
	
	BaseConic* epointer = &ellipse1;
	epointer->display();
	epointer->move(-3,-4);
	epointer->display();
	
	
	
	

}

