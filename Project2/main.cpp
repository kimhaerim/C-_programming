#include <iostream>
#include <cmath>
using namespace std;

class NComplex {
public:
    NComplex();
    NComplex(double aValue);
    NComplex(double aValue, double bValue);
    //생성자
    friend const NComplex operator + (const NComplex& n1, NComplex& n2);
    friend const NComplex operator - (const NComplex& n1, NComplex& n2);
    friend const NComplex operator * (const NComplex& n1, NComplex& n2);
    friend const NComplex operator / (const NComplex& n1, NComplex& n2);
    friend ostream& operator << (ostream& outputStream, const NComplex& n);

private:
    double a;
    double b;
};

NComplex::NComplex() {
    a = 0;
    b = 0;
}

NComplex::NComplex(double aValue) {
    a = aValue;
    b = 0;
}

NComplex::NComplex(double aValue, double bValue) {
    a = aValue;
    b = bValue;
}

ostream& operator <<(ostream& outputStream, const NComplex& n) {
    outputStream << n.a << " + " << n.b << "i" << endl;
    return outputStream;
}


const NComplex operator + (const NComplex& n1, NComplex& n2){
    double x = n1.a + n2.a;
    double y = n1.b + n2.b;
    return NComplex(x,y);
}
const NComplex operator - (const NComplex& n1, NComplex& n2){
    double x = n1.a - n2.a;
    double y = n1.b - n2.b;
    return NComplex(x,y);
}
const NComplex operator * (const NComplex& n1, NComplex& n2){
    double x = (n1.a * n2.a) - (n1.b * n2.b);
    double y = (n1.a * n2.b) + (n1.b * n2.a);
    return NComplex(x,y);
}
const NComplex operator / (const NComplex& n1, NComplex& n2){
    if (n2.a == 0 || n2.b == 0){
        cout << "Error: divide by zero";
        exit(0);
    }
    else{
        double x = n1.a * n2.a + n1.b * n2.b;
        double y = n1.b * n2.a - n1.a * n2.b;
        double z = pow(n2.a,2) + pow(n2.b,2);
        return NComplex(x/z, y/z);
    }
}

const NComplex NComplex::operator-(NComplex &n1, double &b) {
    double x = n1.a - b;
    double y = n1.b - 0;
    return NComplex(x,y);
}

int main()
{
    NComplex n1 (5.1, 2.2), n2(2.0, 2.0), n3;
    double d1 = 3.0;

    cout << "n1+n2: " << n1+n2 << endl;
    cout << "n1*n2: " << n1*n2 << endl;
    cout << "n1-d1: " << n1-d1 << endl;
    cout << "d1*n2: " << d1*n2 << endl;
    cout << "n1/n3: " << n1/n3 << endl;
    return 0;
}

