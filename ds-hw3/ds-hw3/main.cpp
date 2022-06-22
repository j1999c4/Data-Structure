#include <iostream>
#include <limits.h>
#define MAX 100000
using namespace std;
//*****************************************************************************************
int MSIZE_R;
int MSIZE_C;
int maze[MAX][MAX];
enum ntype { virgin, listed, visited };     // for status field
//*****************************************************************************************
typedef struct {
    int x;
    int y;
    int value;
    int dist;                               // distance from start node
    int status;                             // enum as above
} node_t;
//*****************************************************************************************
node_t node [MAX][MAX];                     // working array
node_t *list[MAX];                    // array of current node pointers
int listlen;                                // num elements in list[]
//*****************************************************************************************
void neigh(node_t *cptr, int dx, int dy)
{
    node_t *nptr;                           // pointer to neighbour
    int dist;                               // accumulated distance from start
    int x = cptr->x + dx;                   // work out neighbour coords
    int y = cptr->y + dy;                   // work out neighbour coords
    if (x < 0 || x >= MSIZE_C || y < 0 || y >= MSIZE_R)
        return;                             // failed edge test
    nptr = &node[y][x];                     // point to neighbour
    if (nptr->value == 0)                   // no-go node
        return;
    if (nptr->status == visited)            // do no re-visit
        return;
    dist = cptr->dist + nptr->value;        // accumulate distance from start
    if (dist < nptr->dist)                  // if it's less than what was known...
        nptr->dist = dist;                  // ...update with the new distance
    if (nptr->status == virgin) {           // if it's never been seen...
        list[listlen++] = nptr;             // ... neighbour to list
        nptr->status = listed;              // and set its status
    }
}
//*****************************************************************************************
int main(void)
{
    cin >> MSIZE_R >> MSIZE_C ;
    int i, j, smallest, smallind;
    int end_j[2*MSIZE_C],end_i[2*MSIZE_R],k=0,temp=0;
    node_t *cptr, *eptr;
    int start_x,start_y;
    cin >> start_y >> start_x ;
    for (j=0; j<MSIZE_R; j++) {
        for (i=0; i<MSIZE_C; i++) {
            cin >> maze[j][i];
            if((j==0 && maze[j][i]!=0) || (j==MSIZE_R-1 && maze[j][1]!=0)){
                end_j[k]=j;
                end_i[k]=i;
                k++;
            }
            if((i==0 && maze[j][i]!=0 && j!=0 && j!=MSIZE_R-1) || (i==MSIZE_C-1 && maze[j][i]!=0 && j!=0 && j!=MSIZE_R-1)){
                end_j[k]=j;
                end_i[k]=i;
                k++;
            }
        }
    }
    for (j=0; j<MSIZE_R; j++) {
        for (i=0; i<MSIZE_C; i++) {
            
        }
    }

    for (j=0; j<MSIZE_R; j++) {
        for (i=0; i<MSIZE_C; i++) {
            cptr = &node[j][i];             // pointer to the array element
            cptr->value = maze[j][i];       // the maze definition
            cptr->x = i;                    // self's position
            cptr->y = j;                    // self's position
            cptr->dist = INT_MAX;           // distance from start (unknown)
            cptr->status = virgin;          // never examined
        }
    }
    cptr = &node[start_x][start_y];         // pointer to start node
    cptr->dist  = cptr->value;              // distance of start node from itself!
    for(int t=0;t<k;t++){
        eptr = &node[end_j[t]][end_i[t]];
        while (cptr != eptr) {                  // until we reach the target node
            cptr->status = visited;             // we've been here now
            neigh(cptr,  0, -1);                // examine node above
            neigh(cptr, -1,  0);                 // examine node on left
            neigh(cptr,  1,  0);                 // examine node on right
            neigh(cptr,  0,  1);                 // examine node below
            // find smallest distance of nodes in list[] (won't include virgins)
            smallest = INT_MAX;
            smallind = -1;                      // set invalid marker index
            for (i=0; i<listlen; i++) {
                if (smallest > list[i]->dist) { // compare distance with smallest
                    smallest = list[i]->dist;   // remembers the smallest
                    smallind = i;               // remembers the list index of smallest
                }
            }
            // take smallest for next time and remove from list
            if(smallind < 0) {                  // -1 was the "marker"
                cout << "No route found\n" ;
                return 1;
            }
            cptr = list[smallind];              // smallest becomes current node
            if (listlen)                        // replace in list with last element...
                list[smallind] = list[--listlen];// ... and reduce list length
        }                                       // now examine this node
        if(t==0) temp = eptr->dist;
        if(temp > (eptr->dist)) temp = eptr ->dist ;
    }
    cout <<temp << endl;
}
