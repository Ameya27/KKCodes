#include <bits/stdc++.h>
using namespace std;


void print_ST(int *st,int i,int n){
    if(i<n){
        printf("%d",st[i]);
        print_ST(st,2*i+1,n);
        print_ST(st,2*i+2,n);
    }
}

int get_mid(int start,int end){
    return (start+end)/2;
}


int get_Sum_Util(int* ptr,int ind,int start,int end,int qs,int qe){
    if(qs>start || qe<end){
        return 0;
    }
    else if(start>=qs && qe>=end)
        return ptr[ind];
    else{
        int mid=get_mid(start,end);
        return get_Sum_Util(ptr,2*ind+1,start,mid,qs,qe)+get_Sum_Util(ptr,2*ind+2,mid+1,end,qs,qe);
    }
}


int get_Sum(int* ptr,int n,int qs,int qe){
    if(qs<0 || qe>n-1 ||qs>qe){
        cout<<"Invalid Input";
        return -1;
    }
    return get_Sum_Util(ptr,0,0,n-1,qs,qe);
}


void get_Update_Util(int* ptr,int ind,int start,int end,int qind,int diff){
    if(qind<start || qind>end){
        return;
    }
    ptr[ind]+=diff;
    int mid=get_mid(start,end);
    get_Update_Util(ptr,2*ind+1,start,mid,qind,diff);
    get_Update_Util(ptr,2*ind+2,mid+1,end,qind,diff);
}

void get_Update(int arr[],int* ptr,int n,int i,int new_val){
    if(i<0 || i>n-1){
        cout<<"Invalid Input";
        return;
    }
    int diff=arr[i]-new_val;
    arr[i]=new_val;
    get_Update_Util(ptr,0,0,n-1,i,diff);
}


int construct_Seg_Tree_Util(int* ptr,int index,int start,int end,int arr[]){
    if(start==end){
        ptr[index]=arr[start];
        return arr[start];
    }
    int mid=get_mid(start,end);
    int x=construct_Seg_Tree_Util(ptr,2*index+1,start,mid,arr)+construct_Seg_Tree_Util(ptr,2*index+2,mid+1,end,arr);
    ptr[index]=x;
    return x;
}




int *construct_Seg_Tree(int arr[],int n){
    int sizeofsegtree;
    int expo=(int)ceil(log2(n));
    sizeofsegtree=(int)(2*pow(2,expo)-1);
    int *st=new int[sizeofsegtree];
    construct_Seg_Tree_Util(st,0,0,n-1,arr);
    return st;
}



int main(){
    int n;
    cout<<"Number of elements: ";
    cin>>n;
    cout<<"Enter the elements: ";
    int arr[n];
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    int *ptr=construct_Seg_Tree(arr,n);
    //printf("%d%d%d%d%d%d%d",ptr[0],ptr[1],ptr[2],ptr[3],ptr[4],ptr[5],ptr[6]);
    int expo=(int)ceil(log2(n));
    int sizeofsegtree=(int)(2*pow(2,expo)-1);
    print_ST(ptr,0,sizeofsegtree);
}
