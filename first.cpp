#include <bits/stdc++.h>
#include <math.h>

using namespace std;

int main(){
    setlocale(LC_ALL, "rus");
    int cnt;
    cout << "Введите № задания" << endl;
    cin >> cnt;
    if (cnt==1){cout << "Алексей" << endl << endl;}
    else if (cnt==2){
        float x, y;
        cin >> x >> y;
        cout << x+y << endl; cout << x-y << endl;
        cout << x*y << endl; 
        if(y!=0){cout << x/y << endl;}
        else{cout << "error";}
    }
    else if(cnt==3){
        float b, c;
        cin >> b >> c;
        if(b==0 and c == 0){cout<< "x = R";}
        else if(b==0 and c!=0){cout<< "no answers";}
        else{ 
            if(c==0){cout << 0<< endl;}
            else{cout << -(c/b) << endl;}
        }
    }
    else if(cnt==4){
        int a, b, c;
        cin >> a >> b >> c;
        if (a==0){
            if(b==0 and c == 0){cout<< "x = R";}
            else if(b==0 and c!=0){cout<< "no answers";}
            else{ cout << -(c/b) << endl;}
        }
        else {
            int d;
            d = b*b - 4*a*c;
            if(d<0){cout << "no answ" << endl;}
            else{
                float x1, x2;
                x1 = (-b+sqrt(d))/(2*a);
                x2 = (-b-sqrt(d))/(2*a);
                if(x1==x2){cout << x1 << endl;}
                else {cout << x1 << endl << x2 << endl;}
            }
        }
    }
    else if (cnt==5){
        int lamp, curt, dl;
        cout << "Lamp turned on - 1, and turned off - 0."<< endl << "Curtains are opened - 1, closed - 0." << endl << "If its day outside - 1, or night - 0." << endl;
        cin >> lamp >> curt >> dl;
        if(lamp == 1 or (curt == 1 and dl == 1)){cout << "There is some light in room"<< endl;}
        else{cout << "It is dark in a room"<< endl;}
    }
}