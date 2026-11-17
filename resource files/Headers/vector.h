//simple 3D vector class
#include <math.h>
class Vector3{
    public:  //public representations
    float x,y,z;

    //constructors 
    Vector3(){} //default constructor leaves vector in an indeterminate state

    //copy constructor 
    Vector3(const Vector3 &a) : x(a.x), y(a.y), z(a.z){}

    //construct given 3 values 

    Vector3(float nx, float ny , float nz) :x(nx) , y(ny) ,z(nz){}

    //standard object maintenance

      //Assignment.We adhere to C convention and return referenece to the lvalue
    
      Vector3 &operator = (const Vector3 &a){
        x = a.x; y =a.y; z= a.z;

        return *this;
      }

      //check for equality
      
      bool operator ==(const Vector3 &a)const {
        return x==a.x &&y ==a.y && z==a.z;
      }

      bool operator !=(const Vector3 &a) const{
        return x!=a.x || y!=a.y || z!=a.z;
      }


        //Vector operations 
        //Set the vector to zero 


        void zero(){ x= y=z =0.0f;}

        //unary minus returns the negative vector 

        Vector3 operator -() const {return Vector3(-x,-y,-z);}

        //Binary + & - add and subtract vectors 

        Vector3 operator +(const Vector3 &a) const {
            return Vector3(x + a.x, y+a.y ,z+a.z);
        }
        Vector3 operator -(const Vector3 &a) const {
            return Vector3(x-a.x,y-a.y,z-a.z);
        }

       //Multiplication and division by scalar 

       Vector3 operator *(float a) const {
        return Vector3(x*a,y*a,z*a);
       }
       Vector3 operator /(float a)const {
        float oneOverA = 1.0f/a; // no check for divide for zero here
        return Vector3(x*oneOverA,y*oneOverA,z*oneOverA);
       }

       //combined assignment operators to confirm to C notation convention 

       Vector3 &operator +=(const Vector3 &a) {
        x+= a.x; y+=a.y; z+=a.z;
        return *this;
       }

       Vector3 &operator -=(const Vector3 &a){
        x-=a.x;y-=a.y;z-=a.z;
        return *this;
       }

       Vector3 &operator *=(float a) {
        x*=a;y*=a;z*=a;
        return *this;
       }

       Vector3 &operator /=(float a){
        float oneOverA =1.0f/a;
        x*=oneOverA; y*= oneOverA; z*=oneOverA;
        return *this;
       }

        //Normalize the vector 

        void normalize(){
          float magSq = x*x + y*y +z*z;
          if (magSq>0.0f){// check for divide by zero 
            float oneOverMag = 1.0f/sqrt(magSq);
            x*= oneOverMag;
            y*= oneOverMag;
            z*= oneOverMag;

          }
        }
        //Vector dot product. We overload the standard multiplication symbol to do this 

        float operator *(const Vector3 &a) const{
          return x*a.x+y*a.y+z*a.z;
        }

      };


    ////Nonmember functions 

    // Compute the magnitude of a vector 

    inline float vectorMag(const Vector3 &a){
      return sqrt(a.x*a.x+ a.y*a.y + a.z*a.z );

    }

    //Compute the cross products of two vectors 

    inline Vector3 crossProduct(const Vector3 &a, const Vector3 &b){
      return Vector3(a.y*b.z - a.z*b.y,
                     a.z*b.x - a.x*b.z,
                     a.x*b.y - a.y*b.x);

    }

    //Scalar on the left multiplication for the symmetry 

    inline Vector3 operator *(float k, const Vector3 &v){
      return Vector3(k*v.x,k*v.y,k*v.z);
    }

    // compute distance between two points

    inline float distance(const Vector3 &a, const Vector3 &b){
      float dx = a.x - b.x;
      float dy = a.y - b.y;
      float dz = a.z - b.z ;
      return sqrt(dx*dx + dy*dy +dz*dz);
    }


    ////Global variables 

    // we provide global zero vector constant 

    extern const Vector3 kZeroVector;
