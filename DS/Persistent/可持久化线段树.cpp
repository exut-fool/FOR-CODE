#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int n,tot,a[N],root[N];
struct sgt{
	int lc,rc,v;
}tr[N*24];
int nn(int p){
	tr[++tot]=tr[p];
	return tot;
}
int build(int p,int l,int r){
	p=++tot;
	if(l==r){
		tr[p].v=a[l];
		return p;
	} 
	int mid=(l+r)>>1;
	tr[p].lc=build(tr[p].lc,l,mid);
	tr[p].rc=build(tr[p].rc,mid+1,r);
	return p;
}
int upd(int p,int l,int r,int x,int val){
	p=nn(p);
	if(l==r){
		tr[p].v=val;
	}
	else{
		int mid=(l+r)>>1;
		if(x<=mid){
			tr[p].lc=upd(tr[p].lc,l,mid,x,val);
		}
		else{
			tr[p].rc=upd(tr[p].rc,mid+1,r,x,val);
		}
	}
	return p;
}
int ask(int p,int l,int r,int x){
	if(l==r){
		return tr[p].v;
	}
	int mid=(l+r)>>1;
	if(x<=mid) return ask(tr[p].lc,l,mid,x);
	else return ask(tr[p].rc,mid+1,r,x);
}
int m;
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	root[0]=build(0,1,n);
	for(int i=1;i<=m;i++){
		int rt,opt,x,y;
		cin>>rt>>opt>>x;
		if(opt==1){
			cin>>y;
			root[i]=upd(root[rt],1,n,x,y);
		}
		else{
			cout<<ask(root[rt],1,n,x)<<endl;
			root[i]=root[rt];
		}
	}
}
