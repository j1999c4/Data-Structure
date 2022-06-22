#include <iostream>
#include <iomanip>
#include <stack>
#include <queue>
#define MAX 101
#define MAXNUM 1000000
using namespace std;
int **adjmx; // Adjacency Matrix
int mx[MAX][MAX],test,xx,yy;
int *dist;
int Choose (int n, int* dist, bool* s){
    int i = 0;
    int j = 0;
    int u = 0;
    int temp;
    while (i < n){
        if (!s[i]) {
            temp = dist[i];
            u=i;
            break;
        }
        i++;
    }
    while (j < n){
        if(!s[j] && dist[j] < temp) {
            temp = dist[j];
            u = j;
        }
        j++;
    }
    return u;
}

// using Dijkstra's algorithm to find the shortest path
void diff(int n, int a){
    bool s[n];
    int pi[n];
    stack <int> stack;
    queue <int> nodeQ[n];
    queue <int> temp1, temp2;
    queue <int> num;
    for (int i = 0 ; i < n ; i++) {
        s[i] = false;
        dist[i] = adjmx[a][i];
        //nodeQ[i].push(0);
        pi[i] = -1;
    }
    //stack.push(a);
    
    s[a] = true;
    dist[a] = 0;
    // find n-1 path starting from a
    for(int i = 0 ; i < n-1 ; i++){
        //choose a vertex u, such that dist[u]
        //is munimum and s[u] = false
        int u = Choose(n, dist, s);
        s[u] = true;
        
        for (int w=0 ; w<n ; w++){
            if (!s[w]){
                if(dist[u]+adjmx[u][w] < dist[w]){
                    dist[w] = dist[u] + adjmx[u][w];
                    pi[w] = u;
                    nodeQ[w] = nodeQ[u];
                    nodeQ[w].push(u);
                } else if (dist[u] + adjmx[u][w] == dist[w]) {
                    temp1 = nodeQ[w];
                    temp2 = nodeQ[u]; // 1
                    if (temp1.empty() && temp2.empty()) {
                        if (w < u) {
                            //because dist[w]    should remain the same, so it does't change the path
                            break;
                        }
                        else if (w > u){
                            dist[w] = dist[u] + adjmx[u][w];
                            pi[w] = u;
                            nodeQ[w].push(u);
                            
                        }
                    }
                    else while (!temp1.empty() || !temp2.empty()) {
                        if (temp2.empty()) {
                            if (temp1.front() < u) {
                                //because dist[w]    should remain the same, so it does't change the path
                                break;
                            }
                            else if (temp1.front() > u){
                                dist[w] = dist[u] + adjmx[u][w];
                                pi[w] = u;
                                nodeQ[w].push(u);
                                break;
                            }else {
                                //cout << 3 << endl;
                                temp1.pop();
                            }
                        } else {
                            if (temp1.front() < temp2.front()) {
                                //because dist[w]    should remain the same, so it does't change the path
                                break;
                            }
                            else if (temp1.front() > temp2.front()){
                                dist[w] = dist[u] + adjmx[u][w];
                                pi[w] = u;
                                nodeQ[w] = nodeQ[u];
                                nodeQ[w].push(u);
                                break;
                            }else {
                                //cout << 3 << endl;
                                temp1.pop();
                                temp2.pop();
                            }
                        }
                        
                    }
                }
            }
            
        }
    }
}
int main(void){
    int num,r;
    cin >> r ;
    
    for(int g=0;g<r;g++){
        cin >>num >> test;
        adjmx = new int*[num];
        dist = new int[num];
        for (int i = 0; i < num ; i++)
            adjmx[i] = new int[num];
        for (int i = 0; i < num ; i++){
            for (int j = 0 ; j < num ; j++){
                cin >> adjmx[i][j];
                if (adjmx[i][j]==0) adjmx[i][j] = MAXNUM;
            }
        }
        for (int i = 0 ; i < num ; i++) diff(num, i);
        for(int tt=0;tt<test;tt++){
            cin>>xx>>yy;
            if (dist[yy] != 0 && dist[yy]!=MAXNUM){
                cout << "Cost(" << xx <<','<<  yy << "):";
                cout << dist[xx] << endl;
            }else{
                cout<<"Cost("<<xx<<","<<yy<<"):";
                cout<<"No Service"<<endl;
            }
        }
        
    }
}

