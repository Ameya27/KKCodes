#include <bits/stdc++.h>
#include <iostream>
using namespace std;
typedef long long ll;

struct Node{
    ll sum;
    ll formula;
};
typedef struct Node Node;


int get_Mid(int a,int b){
    return (a+b)/2;
}


ll sum_Interval(Node* ptr,int ind,int l,int r,int start,int end){
    if(l>end || r<start){
        return 0;
    }
    else if(l<=start & r>=end){
        return ptr[ind].formula-(l-1)*ptr[ind].sum;
    }
    else{
        int mid=get_Mid(start,end);
        return sum_Interval(ptr,2*ind+1,l,r,start,mid)+sum_Interval(ptr,2*ind+2,l,r,mid+1,end);
    }
}


ll Sum(Node* st,int left,int right,int n){
    ll val=sum_Interval(st,0,left,right,1,n);
    if((left&1)==0){
        val*=-1;
    }
    return val;
}


void update_ST(Node* ptr,int ind,int start,int end,int diff,int s_diff,int qind){
    ptr[ind].sum+=diff;
    ptr[ind].formula+=s_diff;
    int mid=get_Mid(start,end);
    if(start==end){
        return;
    }
    if(qind<=mid){
        update_ST(ptr,2*ind+1,start,mid,diff,s_diff,qind);
    }
    else{
        update_ST(ptr,2*ind+2,mid+1,end,diff,s_diff,qind);
    }
}

void Update(Node* st,int arr[],int ind,int new_val,int n){
    if((ind&1)==0){
        new_val*=-1;
    }
    int diff=new_val-arr[ind];
    int s_diff=diff*ind;
    //cout<<diff<<' '<<s_diff;
    //cout<<ind;
    arr[ind]=new_val;
    //cout<<ind<<' '<<diff<<' '<<s_diff;
    update_ST(st,0,1,n,diff,s_diff,ind);
}

int create_ST(Node *ptr,int index,int start,int end,int arr[]){
    if(start==end){
        ptr[index].sum=arr[start];
        ptr[index].formula=arr[start]*start;
        return index;
    }
    int mid=get_Mid(start,end);
    int ind1=create_ST(ptr,2*index+1,start,mid,arr);
    int ind2=create_ST(ptr,2*index+2,mid+1,end,arr);
    ptr[index].sum=ptr[ind1].sum+ptr[ind2].sum;
    ptr[index].formula=ptr[ind1].formula+ptr[ind2].formula;
    return index;
}

Node *mod_Seg_Tree(int arr[],int n){
    int expo=(int)ceil(log2(n));
    int size=(int)(pow(2,expo+1)-1);
    Node* st=new Node[size];
    create_ST(st,0,1,n,arr);
    return st;
}

void print_ST(Node* st,int i,int n){
    if(i<n){
        printf("Sum=%d Sweetness=%d \n",st[i].sum,st[i].formula);
        print_ST(st,2*i+1,n);
        print_ST(st,2*i+2,n);
    }
}


int main(){
    int t;
    cin>>t;
    int c=1;
    while(t--){
        int N,Q;
        scanf("%d%d",&N,&Q);
        int A[N+1];
        A[0]=0;
        for(int i=0;i<N;i++){
            scanf("%d",&A[i+1]);
            if(i&1){
                A[i+1]*=-1;
            }
        }
        Node* Mod_Segtree=mod_Seg_Tree(A,N);
        int expo=(int)ceil(log2(N));
        int size=(int)(pow(2,expo+1)-1);
        //print_ST(Mod_Segtree,0,size);
        ll tot=0;
        while(Q--){
            char decision;
            int a1,a2;
            scanf("\n%c%d%d",&decision,&a1,&a2);
            switch(decision){
                case 'U':
                    Update(Mod_Segtree,A,a1,a2,N);
                    break;
                case 'Q':
                    tot+=Sum(Mod_Segtree,a1,a2,N);
                    break;
            }
        }
        printf("Case #%d: %lld\n",(c),tot);
        //print_ST(Mod_Segtree,0,size);
        c+=1;
    }
}
