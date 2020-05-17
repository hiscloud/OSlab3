#include<iostream>
#include<array>

using namespace std;

void bubbleSort(double* arr)
{
cout<<sizeof(*arr)<<endl;
  for (int i=0; i< sizeof(*arr);i++)
  {
    for (int j=0; j< sizeof(*arr)-1; j++)
    {
      if (arr[j]>arr[j+1])
      {
        swap(arr[j],arr[j+1]);
      }
    }
    
  }
  
}

void insertionSort(double* arr)
{
  for( int i=0;i<sizeof(arr);i++)
  {
    int k=i;
    if(k>0)
      while(arr[k]<arr[k-1])
      {
        swap(arr[k],arr[k-1]);
        k--;
      }
  }
}
int main()
{
  double a[3]={105,110.2,2354.2};
  double* arr;
  arr=a;
  cout<<sizeof(a)<<endl;
  cout<<arr[0]<<endl;
  cout<<arr[1]<<endl;
  cout<<arr[2]<<endl;
  
  bubbleSort(arr);
  
  cout<<arr[0]<<endl;
  cout<<arr[1]<<endl;
  cout<<arr[2]<<endl;
 insertionSort(arr);
  
  cout<<arr[0]<<endl;
  cout<<arr[1]<<endl;
  cout<<arr[2]<<endl;
  
  
  return 0;
}
