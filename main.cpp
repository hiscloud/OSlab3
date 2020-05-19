#include<iostream>
#include<array>
#include<fstream>
#include<exception>
using namespace std;


// The number of elements (n) should be provided as command line argument, while the
//number of threads (M) should be read from the console.
void bubbleSort(double* arr, int size)
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

void insertionSort(double* arr, int size)
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

void partition(double* arr, int size)
{
  if

void quickSort(double* arr, int size)
{
  
int main(int argc, char* argv)
{
  int number=0;
  if (argc!=1)
  {
    cout<<"enter only the number of elements in the list in the commmandline"<<endl;
    exit;
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
  
  double a[3]={1050,110.2,2354.2};
  double* arr;

  arr=a;
  
  cout<<arr[0]<<endl;
  cout<<arr[1]<<endl;
  cout<<arr[2]<<endl;
  
  bubbleSort(arr,3);
  
  cout<<arr[0]<<endl;
  cout<<arr[1]<<endl;
  cout<<arr[2]<<endl;
 insertionSort(arr,3);
  
  cout<<arr[0]<<endl;
  cout<<arr[1]<<endl;
  cout<<arr[2]<<endl;
  
  
  return 0;
}
