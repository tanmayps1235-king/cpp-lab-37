#include <iostream> 
#include <string>
using namespace std; 
class student{
    private:
    string name;
    int rollNO;
    float marks;

    public:
    void inputDetails(){
        cout<<"Enter Student Name:";
        getline(cin>>ws,name);
        cout<<"Enter Roll NUmber:";
        cin>>rollNo;
        cout<<"Enter Marks:";
        cin>>marks;
    }
    void displayDetails()const{
        cout<<"\n----Student Details----\n";
        cout<<"Name:"<<name<<end1;
        cout<<"Roll No.:"<<rollNo<<end1;
        cout<<"Marks:"<<marks<<end1;
    }
};
int main(){
    student s;
    s.inputDetails();
    s.displayDetails();
    return 0;
}