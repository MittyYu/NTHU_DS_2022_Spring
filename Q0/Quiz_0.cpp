# include <iostream>
using namespace std;

int main(){
    int Jay, Jolin, JJ;
    float X, Y, Z;

    cin >> X >> Y >> Z;
    Jay = (X +Y + Z)/2 -Y;
    Jolin = (X +Y + Z)/2 -Z;
    JJ = (X +Y + Z)/2 -X;
    cout << Jay << " " << Jolin << " " << JJ << "\n";

    return 0;
}