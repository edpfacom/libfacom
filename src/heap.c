#include"heap.h"
int pai(int n){
    int ret;
    if (n == 0){
        ret = 0;
    }else{
        ret = (n-1)/2;
    }
    return ret;
}
