#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int size[N];
int parent[N];
void make(int v)
{
	parent[v]=v;
	size[v]=1;
}
int find(int v)
{
	if(v==parent[v]) return v;
	return parent[v]=find(parent[v]);

}
void Union(int a,int b)
{
	a=find(a);
	b=find(b);
	if(a!=b)
	{
		if(size[a]<size[b])
		{
			swap(a,b);
		}
		parent[b]=a;
		size[a]+=size[b];
	}
}
int main() {
	int n;
	cin>>n;
	int k;
	vector<int> v[n];
	cin>>k;
	for(int i=1;i<=n;i++)
	{
		make(i);
	}
	for(int i=0;i<k;i++)
	{
		int x,y;
		cin>>x>>y;
		Union(x,y);
	}
	int c=0;
	for(int i=1;i<=n;i++)
	{
		if(find(i)==i)
		{
			c++;
		}
	}
	cout<<c<<endl;
}