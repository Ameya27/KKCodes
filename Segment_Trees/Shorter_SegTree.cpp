#include <bits/stdc++.h>
#include <iostream>
using namespace std;
#define mod (1e9)+7
typedef long long ll;
int n;
const int N=1e5;
ll t[2*N];

void print_Array(ll arr[],int start,int end){
    for(int i=start;i<end;i++){
        printf("%lld ",arr[i]);
    }
    printf("\n");
}

void build(){
    for(int i=n-1;i>0;i--) t[i]=t[i<<1]+t[i<<1|1];
}

//p is 1-indexed
void modify(int p,ll val){
    p--;
    for(t[p+=n]=val;p>1;p>>=1) t[p>>1]=t[p]+t[p^1];
}

//l and r are 1-indexed
//query is inclusive of l and r
ll query(int l,int r){
    ll sum=0;
    l--,r--;
    for(l+=n,r+=n;l<=r;l>>=1,r>>=1){
        if(l&1) sum+=t[l++];
        if((r&1)==0) sum+=t[r--];
    }
    return sum;
}

int main(){
    int p,q,x,s,l,r,m;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%lld",t+n+i);
    }
    build();
    //print_Array(t,0,n<<1);
    //modify(2,3);
    //print_Array(t,0,n<<1);
    //printf("%lld",query(1,2));
    return 0;
}
