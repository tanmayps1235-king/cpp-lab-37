#include <iostream>
using namespace std;
int main(){
    int a, b, optn;
    cout<<"Enter two numbers: ";
    cin>>a>>b;
    cout<<"\n1.Add\n2.Subtract\n3.Multiply\n4.Divide\n5.Modulus\n";
    cout<<"Enter choice number : ";
    cin>>optn;
    if(optn==1) cout << "Sum = " << a + b;
    else if(optn==2)  cout << "Difference = " << a - b;
    else if(optn==3) cout << "Product = " << a * b;
    else if(optn==4) cout << "Division = " << (float)a / b;
    else if(optn==5) cout << "Modulus = " << a % b;
    else cout << "Invalid Choice";
    return 0;
}