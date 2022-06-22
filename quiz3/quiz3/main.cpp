#include <iostream>
using namespace std;
//*******************************************************************
int MSize_R, MSize_C;
int **maze;
//*******************************************************************
class Node {
public:
    int value, dist;
    int x,y;
    bool visited;
    Node *up, *down, *left, *right;
};
//*******************************************************************
Node *makenode (int value,int start_y,int start_x) {
    Node* new_node = new Node();
    new_node->value = value;
    new_node->dist = value;
    new_node->up = NULL;
    new_node->down = NULL;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->visited = 0;
    new_node->y=start_y;
    new_node->x=start_x;
    return new_node;
}
//*******************************************************************
void Create(Node* root, int start_x, int start_y) {
    maze[start_y][start_x] = 0;
    if(start_y+1 > MSize_R-1){
        goto stop1;
    }else {
        if (maze[start_y+1][start_x] != 0){ //down
            Node* p = makenode(maze[start_y+1][start_x],start_y+1,start_x);
            maze[start_y+1][start_x] = 0;
            root->down = p;
            Create(p, start_x, start_y+1);
        }
    }
    //
stop1:    if (start_y-1 < 0){
    goto stop2;
}else {
    if (maze[start_y-1][start_x] != 0){ //up
        Node* p = makenode(maze[start_y-1][start_x],start_y-1,start_x);
        maze[start_y-1][start_x] = 0;
        root->up = p;
        Create(p, start_x, start_y-1);
    }
}
    //
stop2:    if(start_x-1 < 0){
    goto stop3;
}else {
    if (maze[start_y][start_x-1] != 0){ //left
        Node* p = makenode(maze[start_y][start_x-1],start_y,start_x-1);
        maze[start_y][start_x-1] = 0;
        root->left = p;
        Create(p, start_x-1, start_y);
    }
}
    //
stop3:    if (start_x+1 > MSize_C-1){
    return;
}else {
    if (maze[start_y][start_x+1] != 0){ //right
        Node* p = makenode(maze[start_y][start_x+1],start_y,start_x+1);
        maze[start_y][start_x+1] = 0;
        root->right = p;
        Create(p, start_x+1, start_y);
    }
}
}
//*******************************************************************
int temp=0, path=0;
void trav(Node* root)
{
    //check up
    if (root->up != NULL) {
        if(root->up->value == -1){
            root->visited = 1;
        }else{
            root->up->dist = root->dist + root->up->value;
            root->visited = 1;
            trav(root->up);
        }
    }
    //check left
    if (root->left != NULL){
        if(root->left->value == -1){
            root->visited = 1;
        }else{
            root->left->dist = root->dist + root->left->value;
            root->visited = 1;
            trav(root->left);
        }
    }
    //check down
    if (root->down != NULL){
        if(root->down->value == -1){
            root->visited = 1;
        }else{
            root->down->dist = root->dist +root->down->value;
            root->visited = 1;
            trav(root->down);
        }
    }
    //check right
    if (root->right != NULL){
        if(root->right->value == -1){
            root->visited = 1;
        }else{
            root->right->dist = root->dist + root->right->value;
            root->visited = 1;
            trav(root->right);
        }
    }
    //check ending node
    if(root->x == MSize_C-1 && root->y == MSize_R-1){
        //record the first path
        if(path==0){
            temp=root->dist;
            path++;
        }
        //compare the shortest path
        else{
            if(temp > root->dist) temp=root->dist;
        }
    }
}
//*******************************************************************
int main(void)
{
    int start_x=0,start_y=0;
    cin >> MSize_R >> MSize_C;
    int i, j;
    maze = new int*[MSize_R];
    //create a space for 2-D array dynamically
    for(i = 0; i < MSize_R; i++)
        maze[i] = new int[MSize_C];
    //input the elements in matrix
    for (i=0; i<MSize_R; i++) {
        for (j=0; j<MSize_C; j++) {
            cin >> maze[i][j];
        }
    }
    Node* root = makenode(maze[start_y][start_x],start_y,start_x);
    Create(root, start_x, start_y);
    trav(root);
    cout << temp << endl;
    return 0;
}
//*******************************************************************
