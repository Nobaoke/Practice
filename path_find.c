#include "stdio.h"

int m[10][10] = 
{   0,    1,    1,    0,    1,    1,    1,    1,    0,    1,
    0,    1,    0,    0,    0,    0,    1,    1,    1,    1,
    0,    1,    0,    0,    1,    0,    1,    1,    1,    1,
    0,    0,    0,    1,    1,    0,    1,    1,    1,    1,
    0,    1,    1,    1,    0,    0,    1,    0,    0,    1,
    0,    1,    1,    1,    0,    1,    1,    0,    0,    1,
    0,    1,    0,    1,    0,    0,    0,    0,    0,    1,
    0,    1,    0,    0,    1,    1,    1,    1,    0,    1,
    0,    1,    1,    0,    1,    1,    1,    1,    0,    1,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0
};

// 0: can be pass
// 1: can not pass
// 2: way passed

int find_path_direction(int start_i, int start_j, int end_i,int end_j)
{
    if (start_i > 9 || start_i < 0 || 
        start_j > 9 || start_j < 0 ||
        end_i > 9 || end_i < 0 || 
        end_j > 9 || end_j < 0 ||
        m[end_i][end_j] != 0 ||
        m[start_i][start_j] != 0){
        return 0;
    }
    m[end_i][end_j] = 3;

    if (end_i == start_i && end_j == start_j) {
        printf("Start Point\n");
        return 1;
    }

    if (find_path_direction(start_i, start_j, end_i, end_j-1)) { // left
        printf("Right\n");
        return 1;
    } else if (find_path_direction(start_i, start_j, end_i-1, end_j)){ // up
        printf("Down\n");
        return 1;
    } else if (find_path_direction(start_i, start_j, end_i+1, end_j)) { // down
        printf("Up\n");
        return 1;
    } else if (find_path_direction(start_i, start_j, end_i, end_j+1)) { // right
        printf("Left\n");
        return 1;
    } else {
        m[end_i][end_j] = 0;
        return 0;
    }
}

// 1 means yes, 0 means false
int find_path(int start_i, int start_j, int end_i,int end_j)
{
	if (start_i > 9 || start_i < 0 || 
        start_j > 9 || start_j < 0 ||
        end_i > 9 || end_i < 0 || 
        end_j > 9 || end_j < 0 ||
        m[end_i][end_j] != 0 ||
        m[start_i][start_j] != 0){
		return 0;
	}
    m[end_i][end_j] = 3;

    if (end_i == start_i && end_j == start_j) {
        printf("(%d, %d)\n", end_i, end_j);
        return 1;
    }

    if (find_path(start_i, start_j, end_i-1, end_j) || //up
        find_path(start_i, start_j, end_i, end_j-1) || //left
        find_path(start_i, start_j, end_i+1, end_j) || //down
        find_path(start_i, start_j, end_i, end_j+1)){  //right
        printf("(%d, %d)\n", end_i, end_j);
        return 1;
    } else {
        m[end_i][end_j] = 0;
        return 0;
    }
}

int get_val(int i, int j){
    if (i<0||i>9||j<0||j>9){
        return -1;
    }
    return m[i][j];
}

void print_path(int start_i, int start_j, int end_i,int end_j) 
{
    int i, j = 0;
    if (start_i > 9 || start_i < 0 || 
        start_j > 9 || start_j < 0 ||
        end_i > 9 || end_i < 0 || 
        end_j > 9 || end_j < 0 ||
        m[end_i][end_j] != 2 ||
        m[start_i][start_j] != 2){
        printf("No paths availiable\n");
        return;
    }
    i = start_i;
    j = start_j;

    while(!(i == end_i && j == end_j)) {
        printf("(%d, %d)\n", i, j);
        m[i][j] = -1;

        if (get_val(i+1,j) == 2) {
            i++;
        } else if (get_val(i,j+1) == 2) {
            j++;
        } else if (get_val(i-1,j) == 2) {
            i--;
        } else if (get_val(i,j-1) == 2) {
            j--;
        }
    }
    printf("(%d, %d)\n", end_i, end_j);

    return;
}

void path_find(int start_i, int start_j, int end_i, int end_j){
    find_path(start_i,start_j,end_i,end_j);
    printf("End Point\n");
    //print_path(start_i,start_j,end_i,end_j);
}

void main (void)
{
    int i,j;

    path_find(0, 0, 9, 9);
    // printf("maze route\n");
    // for (i=0; i<10; i++)
    // {
    //         for(j=0; j<10; j++)
    //             printf("%d ", m[i][j]);
    //         printf("\n");
    // }
}