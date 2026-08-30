#include <iostream>
using namespace std;

class Farm
{
private:
    int farmId;
    float farmArea;
    float farmCost;

public:
    void getData()
    {
        cout << "Enter Farm ID: ";
        cin >> farmId;

        cout << "Enter Farm Area (sq ft): ";
        cin >> farmArea;

        cout << "Enter Farm Cost: ";
        cin >> farmCost;
    }

    void putData()
    {
        cout << "\nFarm ID: " << farmId;
        cout << "\nFarm Area: " << farmArea;
        cout << "\nFarm Cost: " << farmCost;
    }

    void ratePerSquare()
    {
        float rate = farmCost / farmArea;
        cout << "\nRate Per Square Foot = " << rate << endl;
    }
};

int main()
{
    Farm f1, f2;

    cout << "Enter details of Farm 1\n";
    f1.getData();

    cout << "\nEnter details of Farm 2\n";
    f2.getData();

    cout << "\n\nDetails of Farm 1";
    f1.putData();
    f1.ratePerSquare();

    cout << "\n\nDetails of Farm 2";
    f2.putData();
    f2.ratePerSquare();

    return 0;
}