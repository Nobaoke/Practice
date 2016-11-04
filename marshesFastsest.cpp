/*
    Not my code, but faster than my solution
*/

#include <iostream>
using namespace std;
    
int main() { 
    int m, n;
    cin >> m >> n;          
    int best = 0;    
    int R[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            R[i][j] = -1;
        }
    }    
    for (int y = 0; y < m; y++) {
        int A[n];        
        for (int j = 0; j < n; j++) {
            char c;
            cin >> c;                
            if (c == '.') {
                A[j] = 1;
            } else {
                A[j] = 0;
            }
        }
        for (int a = 0; a < n; a++) { 
            bool visible = true;
            for (int b = a+1; b<n; b++) {
                // is b visible from a?
                if (A[b] == 0) {
                    visible = false;
                }
                if (A[a] == 1 && A[b] == 1) {
                    // the shape can extend thru this row too
                    if (R[a][b] >= 0) {
                        R[a][b] += 1;
                    }
                    if (visible && R[a][b] < 0) {
                        R[a][b] = 0;
                    }
                    if (visible && R[a][b] > 0) {
                        // consider the rect formed, by closing off the shape here.
                        int v = 2*R[a][b] + 2*(b-a);
                        if (v > best) {
                            best = v;
                            if (best == 126) {
                                cout << endl;
                                cout << a << ", " << b << endl;
                                cout << y << ", " << R[a][b] << endl;
                            }
                        }
                    }
                }
                else {
                    R[a][b] = -1;
                }
            }
        }
    }
    if (best > 0) {        
        cout << best << endl;
    }
    else {
        cout <<  "impossible"<< endl;
    }    
    return best;
}