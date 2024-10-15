#include <iostream>
using namespace std;
int max(int a, int b)
{
if(a>b)
{
return a;
}
else
{
return b;
}
}
int table(int weight[], int profit[],int n,int cap)
{
int arr[n+1][cap+1];
int i,w;
for(int w=0;w<=cap;w++)
{
if(weight[0]<=w)
{
arr[0][w]=profit[0];
}
else
{
arr[0][w]=0;
}
}
for(i=0;i<=n;i++)
{
for(w=0;w<=cap;w++)
{
if(i==0 || w==0)
{
arr[i][w]=0;
}
else if(weight[i-1]<=w)
{
arr[i][w]=max(profit[i-1]+arr[i-1][w-weight[i-1]],arr[i-1][w]);
}
else
{
arr[i][w]=arr[i-1][w];
}
}
}
for(i=0;i<=n;i++)
{
cout<<"\n";
for(w=0;w<=cap;w++)
{
cout<<" "<<arr[i][w]<<" ";
}
}
cout<<"\n";
return arr[n][cap];
}
int main()
{
int n;
int cap;
cout<<"Enter the number of objects to be inserted\t";
cin>>n;
cout<<"Enter capacity of knapsack\t";
cin>>cap;
int weight[n];
int profit[n];
cout<<"\neneter weight of object"<<endl;
for( int i=0;i<n;i++)
{
cin>>weight[i];
}
cout<<"\nenter profit of the object"<<endl;
for(int i=0;i<n;i++)
{
cin>>profit[i];
}
int value = table(weight,profit,n,cap);
cout<<"\nMaximum profit is "<<value;
return 0;
}
