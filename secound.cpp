#include <bits/stdc++.h>
#include <math.h>

using namespace std;

int main(){
    ///for(int cycl=0; cycl<100;cycl++){
    ios_base::sync_with_stdio(0);
    setlocale(LC_ALL, "rus");
    int cnt;
    cout << "Введите № задания" << endl;
    cin >> cnt;
    if (cnt==1){
        double h, R, r, L;
        double p;
        p = 3.1415;
        cout << "h, R, r" << endl;
        cin >> h >> R >> r;
        if (R <= 0 or r <= 0 or R==r){cout<<"Wrong input"<<endl;}
        else{ L = sqrt((R-r)*(R-r) + h*h);
            double V, S;
            if (h <= 0){cout << "error - H not hiegher 0, no V"; }
            else{V = (p * h * (R*R + R*r + r*r))/3; cout << V << endl;}
            S = p * (R*R+(R+r)*L+r*r);
            cout << S << endl;
        }
    }
    else if(cnt==2){
        float a, x;
        cin >> a >> x;
        if(x==0){cout << "Error, wrong input" << endl;}
        else{   
            if(abs(x)<1){cout << a * log(abs(x)) << endl;}
            else{
                if((a - x*x) >= 0){cout << sqrt(a-x*x) << endl;}
                else{cout << "Wrong input" << endl;}
            }
        }   
    }
    else if(cnt==3){
        float x, y, b;
        cin >> x >> y >> b;
        if((b-x)>=0 and (b-y)>0){
            cout << log(b-y)*sqrt(b-x) << endl;
        }
        else{cout <<"error"<<endl;}
    }
    else if(cnt==4){
        double n;
        cin >> n;
        if(n > 0 and (n == (long long)n)){
            for(int i=0; i<10; i++){
                cout << n+i << endl;
            }
        }
        else{ cout << "error" << endl; }
    }
    else if(cnt==5){
        for(float x= -4; x<=4; x=x+0.5){
            if (x==1){cout << x << "       error" << endl;}
            else{cout << x <<"      " << (x*x-2*x+2)/(x-1) << endl;}
        }
    }
}
///}