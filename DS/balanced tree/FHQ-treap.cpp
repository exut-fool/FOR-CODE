#include<bits/stdc++.h>
using namespace std;

int cnt,n,m,x,y,z,root,opt;

struct fhq{
	int l,r,val,key,size;	
}t[114514];

int nn(int val){
	t[++cnt].val=val;
	t[cnt].size=1;
	t[cnt].key=rand();
	return cnt;
}

void upd(int p){t[p].size=t[t[p].l].size+t[t[p].r].size+1;}

void split(int now,int val,int &x,int &y){
	if(!now){x=y=0;return;}
	if(t[now].val<=val){
		x=now;
		split(t[now].r,val,t[now].r,y);
	}
	else{
		y=now;
		split(t[now].l,val,x,t[now].l);
	}
	upd(now);
} 

int merge(int x,int y){
	if(!x or !y) return x+y;
	if(t[x].key<=t[y].key){
		t[x].r=merge(t[x].r,y);
		upd(x);
		return x;
	}
	else{
		t[y].l=merge(x,t[y].l);
		upd(y);
		return y;
	}
}

void ins(int val){
	split(root,val-1,x,y);
	root=merge(merge(x,nn(val)),y);
}

void del(int val){
	split(root,val,x,z);
	split(x,val-1,x,y);
	y=merge(t[y].l,t[y].r);
	root=merge(merge(x,y),z);
}

int getrank(int val){
	split(root,val-1,x,y);
	int ret=t[x].size+1;
	root=merge(x,y);
	return ret;
}

int getnum(int rk){
	int now=root;
	while(now){
		if(t[t[now].l].size+1==rk) return t[now].val;
		else if(t[t[now].l].size+1>rk) now=t[now].l;
		else rk-=t[t[now].l].size+1,now=t[now].r;
	}
	return 0;
}

int pre(int val){
	split(root,val-1,x,y);
	int now=x;
	while(t[now].r){
		now=t[now].r;
	}
	root=merge(x,y);
	return t[now].val;
}

int nxt(int val){
	split(root,val,x,y);
	int now=y;
	while(t[now].l){
		now=t[now].l;
	}
	root=merge(x,y);
	return t[now].val;
}

int main(){
	int kk;
	cin>>n;
	while(n--){
		cin>>opt>>kk;
		if(opt==1)
			ins(kk);
		else if(opt==2)
			del(kk);
		else if(opt==3)
			cout<<getrank(kk)<<endl;
		else if(opt==4)
			cout<<getnum(kk)<<endl;
		else if(opt==5)
			cout<<pre(kk)<<endl;
		else
			cout<<nxt(kk)<<endl;
	}
	return 0;
} 
