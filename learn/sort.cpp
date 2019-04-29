#include <iostream>

using namespace std;

void bubble_sort(int a[20]){
    //冒泡排序
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 20-i-1; j++){
            if(a[j] < a[j+1]){
                swap(a[j],a[j+1]);
            }
        }
    }
    for(int i = 0; i < 20; i++)
        cout<<a[i]<<" ";
    cout<<endl;
}

void select_sort(int a[20]){
    //选择排序
    for(int i = 0; i < 20; i++){
        int small = i;
        for(int j = i; j < 20; j++){
            if(a[j] < a[small])
                small = j;
        }
        swap(a[i],a[small]);
    }
    for(int i = 0; i < 20; i++)
        cout<<a[i]<<" ";
    cout<<endl;

}

void insert_sort(int a[20]){
    //插入排序
    for(int i = 1; i < 20; i++){
        int current = a[i];
        int parrent = i-1;
        while(parrent >= 0 && a[parrent] < current){
            a[parrent+1] = a[parrent];
            parrent--;
        }
        a[parrent+1] = current;
    }
    for(int i = 0; i < 20; i++)
        cout<<a[i]<<" ";
    cout<<endl;
}

void shell_sort(int a[20]){
    //希尔排序
    for(int cnt = 20/2; cnt > 0; cnt = cnt/2 ){

        for(int i = cnt; i < 20; i++){
            int parrent = i;
            int current = a[i];
            while( (parrent-cnt) >= 0 && a[parrent-cnt] > current){
                a[parrent] = a[parrent-cnt];
                parrent -= cnt;
            }
            a[parrent] = current;
        }

    }

    for(int i = 0; i < 20; i++)
        cout<<a[i]<<" ";
    cout<<endl;
}


void merge(int* a,int left,int right,int* result){
    if(left == right)
        return;
    else if(left == right-1){
        if(a[left] < a[right])
            swap(a[left],a[right]);
    }
    else{
        int mid = (left+right)/2;
        merge(a,left,mid,result);
        merge(a,mid+1,right,result);
        int k = left;
        int i = left,j = mid+1;
        for(; i <= mid && j <= right;){
            if(a[i] < a[j]){
                result[k++] = a[j++];
            }
            else{
                result[k++] = a[i++];
            }
        }
        while(i <= mid){
            result[k++] = a[i++];
        }
        while(j <= right)
            result[k++] = a[j++];

        for(int m = left; m <= right; m++){
            a[m] = result[m];
        }
    }
}

void merge_sort(int a[20]){
    //归并排序
    int result[20];
    merge(a,0,19,result);
    for(int i = 0; i < 20; i++)
        cout<<a[i]<<" ";
    cout<<endl;
}

void q_sort(int* a,int start,int end){
   //快速排序
   if(start >= end)
        return;

    int i = start+1;
    int j = end;
    while(i <= j){
        while(a[i] > a[start] && i <= j)
            i++;
        while(a[j] < a[start] && i <= j)
            j--;
        if(i < j)
            swap(a[i++],a[j--]);
           
    }
    swap(a[j],a[start]);
    q_sort(a,start,j-1);
    q_sort(a,j+1,end);
    return;
}


void adjust(int *a,int len,int index){
    int left = index*2 + 1;
    int right = index*2 + 2;
    int maxId = index;
    if(left < len && a[left] > a[maxId])
        maxId = left;
    if(right < len && a[right] > a[maxId])
        maxId = right;
    if(maxId != index){
        swap(a[index],a[maxId]);
        adjust(a,len,maxId);
    }

}

void heap_sort(int* a,int size){
    //堆排序
    for(int i = size/2 - 1; i >= 0; i--){
        adjust(a,size,i);
    }
    for(int i = size-1; i >= 1; i--){
        swap(a[0],a[i]);
        adjust(a,i,0);
    }

}

int main(){

    int a[20];
    for(int i = 0; i < 20; i++)
        a[i] = rand()%100;
    for(int i = 0; i < 20; i++)
        cout<<a[i]<<" ";
    cout<<endl;

   // bubble_sort(a);

   // select_sort(a);

    insert_sort(a);

   // shell_sort(a);

   // merge_sort(a);

  //  q_sort(a,0,19);

  heap_sort(a,20);
    for(int i = 0; i < 20; i++)
        cout<<a[i]<<" ";
    cout<<endl;
    

    return 0;
}