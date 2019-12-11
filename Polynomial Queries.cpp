//Cses polynomial queries
//a_0'+a_1'*(index-mid-1)=a_0+a_1*(index-l)==>a_0'=a_0+(mid+1-l)*a_1, a_1'=a_1
#include <bits/stdc++.h>
#define lli long long int
#define pb push_back
#define mod 1000000007
#define mod2 998244353
#define MAXN 1000000000
#define v32 vector<int>
#define v64 vector<lli>
#define v1024 vector <vector <int>>
#define v4096 vector <vector <lli>>
#define vt vector
#define true 1
#define false 0
#define f(x, y, z) for (int x = y; x < z; x++)
#define fd(x, y, z) for (int x = y; x > z; x--)
#define lb lower_bound
#define ld long double
#define m64 map<lli,lli>
#define m32 map<int,int>
#define m64it map<lli,lli>::iterator
#define m32it map<int,int>::iterator
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define ist insert
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define ordered_set tree<pair<int,int>, null_type,less<pair<int,int>>, rb_tree_tag,tree_order_statistics_node_update> 
using namespace __gnu_pbds;
using namespace std;
lli tmod(lli x,lli m){return (x%m+m)%m;}
class LAZY //currently set to add 1,2,3... in a given range
{
   public:
   struct node
   {
    int l,r,lazy=0;lli lazyval=0,offset=0;
    lli sum=0;
   };	
   vt <node> st;v64 h;
   LAZY(v64 a)
   { 
   	  h=a;
   	  st.resize(4*h.size());
   	  cst(0,h.size()-1);
   }	
   void cst(int l,int r,int k=0)
   {
    st[k].l=l,st[k].r=r;
    if(l==r)
        { 
          st[k].sum=h[l];   
          return;
        }
    cst(l,(l+r)/2,2*k+1);
    cst((l+r)/2+1,r,2*k+2);
    st[k].sum=st[2*k+1].sum+st[2*k+2].sum;    
   }
   void shift(int k)
   {
   lli l=st[k].l,r=st[k].r,mid=(l+r)>>1;
   st[k].sum+=(((r-l+1)*(r-l+2))>>1)*st[k].lazyval+st[k].offset*(r-l+1);
   if(st[k].l!=st[k].r)
   {
       st[2*k+1].lazyval+=st[k].lazyval;
       st[2*k+1].offset+=st[k].offset;
       st[2*k+2].lazyval+=st[k].lazyval;
       st[2*k+2].offset+=st[k].offset+(mid+1-l)*st[k].lazyval;
       st[2*k+1].lazy=st[2*k+2].lazy=1;
   }
   st[k].offset=0;
   st[k].lazyval=0;
   st[k].lazy=0;      
   }
   lli query(int l,int r,int k=0)
   {
	if(st[k].lazy)
       shift(k);
    // cout<<k<<" "<<st[k].sum<<"\n";
   int ll=st[k].l,rr=st[k].r,mid=(ll+rr)/2;
   if(l>rr || r<ll)return 0;
   if(ll>=l && rr<=r) return st[k].sum;
    return query(l,r,2*k+1)+query(l,r,2*k+2);     
   }
   void update(int l,int r,int k=0)
   {
	if(l>r)
		return;
   lli ll=st[k].l,rr=st[k].r,mid=(ll+rr)>>1;
   if(l>rr || r<ll)return;
   if(ll>=l && rr<=r)
         {
          st[k].offset+=(ll-l);   
          st[k].lazyval++;
          st[k].lazy=1;      
          return;
         } 
         if(st[k].lazy)
           shift(k);
        //  if(st[k].l==st[k].r) return;
      update(l,r,2*k+1);
      update(l,r,2*k+2);
      if(st[2*k+1].lazy)
       shift(2*k+1);
       if(st[2*k+2].lazy)
       shift(2*k+2);
    st[k].sum=st[2*k+1].sum+st[2*k+2].sum;           
   }
};
int main()
{
  fastio;
  int n,q;cin>>n>>q;
  v64 a(n);f(i,0,n)cin>>a[i];
  LAZY ST(a);
  f(i,0,q){
      int x,a,b;
      cin>>x>>a>>b;
      a--,b--;
      if(x==1){
          ST.update(a,b);
      }
      else cout<<ST.query(a,b)<<"\n";
  }
  return 0;    	
}