#include<iostream>
#include<array>
#include<fstream>
#include<exception>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
using namespace std;


// The number of elements (n) should be provided as command line argument, while the
//number of threads (M) should be read from the console.
void bubbleSort(int* arr, int size)
{
  
  for (int i=0; i< size;i++)
  {
    for (int j=0; j< size-1; j++)
    {
      if (arr[j]>arr[j+1])
      {
        swap(arr[j],arr[j+1]);
        //arr[j]=arr[j+1];
      }
    }
    
  }
}

void insertionSort(int* arr, int size)
{
  
  for( int i=0;i<size;i++)
  {
    int k=i;
    while(k>0)
      if (arr[k]<arr[k-1])
      {
        swap(arr[k],arr[k-1]);
        k--;
      }else
        break;
  }
}

int partition(int* arr, int low, int high)
{
  int pivot= arr[(low+high)/2];
/*  while (low < high)
  {
    if (arr[low]>=pivot && arr[high]<pivot)
    {
      swap(arr[low],arr[high]);
      low++;
      high--;
    }else 
    {  
      if (arr[low]<pivot)
        low++;
      if (arr[high]>pivot) 
        high--;
    }
  }
  if (low>high)
    return low-1;
  else 
    return low
    */
  while(true)
  {
    while(arr[low]<pivot)
      low++;
    while(arr[high]>pivot)
      high--;
    if(low>=high)
      return high;
    swap(arr[low],arr[high]);
    low++;
    high--;
  }
}   

void quickSort(int* arr, int low,int high)
{
  int p;
  if (low<high)
  {
   p= partition(arr,low,high);
   quickSort(arr,low,p);
   quickSort(arr,p+1,high);
  }
}

int main(int argc, char* argv[])
{
  int number=0;
  if (argc!=2)
  {
    cout<<"enter only the number of elements in the list in the commmandline"<<endl;
    exit(-1);
  }
  else
  {
    try
    {
      number=atoi(argv[1]);
    }catch(const exception& e)
    {
      cout<<"enter the number only\n";
    }
  }
  
  int a[7]={3,1,2,4,5,6,8};
  int* arr;

  arr=a;
  for (int i=0; i<7;i++)
  cout<<arr[i]<<endl;
  
  
  quickSort(arr,0,6);
  
  for (int i=0; i<7;i++)
  cout<<arr[i]<<endl;
  
  
  return 0;
}
