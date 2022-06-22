#include <iostream>
#include <iomanip>
#include <vector>
#include <math.h>
using namespace std;
void merge(int arr[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    int i = 0,j = 0,k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
void mergeSort(int arr[],int l,int r){
    if(l>=r){
        return;
    }
    int m =l+ (r-l)/2;
    mergeSort(arr,l,m);
    mergeSort(arr,m+1,r);
    merge(arr,l,m,r);
}
int main() {
    int round,point;
    
    cin >> round;
    while(round){
        double ans=0;
        cin >> point;
        int x[point],y[point];
        int a,b,u=0,d=0;
        int count=2*point;
        while(count){
            cin >> a >> b;
            if (a > 0) {
                x[u] = a;
                u++;
            } else if (a < 0) {
                x[u] = (-1) * a;
                u++;
            } else if (b > 0) {
                y[d] = b;
                d++;
            } else {
                y[d] = (-1) * b;
                d++;
            }
            count--;
        }
        mergeSort(x,0,point-1);
        mergeSort(y,0,point-1);
        for (int i = 0; i < point; i++)   ans += pow(pow((double) x[i], 2) + pow((double) y[i], 2), 0.5);
        cout << fixed << setprecision(8);
        cout << ans << endl;
        round--;
    }
}
