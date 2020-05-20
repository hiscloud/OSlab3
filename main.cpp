#include<iostream>
#include<array>
#include<fstream>
#include<exception>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
using namespace std;
//g++ Lu_lab4 -lpthread
void *PrintHello(void *threadid)
{
   long tid;
   tid = (long)threadid;
   printf("Hello World! It's me, thread #%ld!\n", tid);
   fflush(stdout);
   pthread_exit(NULL);
}
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
  char SNThreads[5];
  int NThreads;
  ofstream out;
  string filename="log.txt";
  int range=100;
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
      cout<<"Enter the number of elements only！\n";
    }
  }
  cout<<"There are "<<number<<" elements in the file."<<endl;
  out.open(filename);
   for( int i=0; i< number; i++)
    out<<rand()%range<<"\t";
  out<<endl;
  while(true){
    cout<<"Enter the number of threads:\n";
    cin>>SNThreads;
    if (NThreads = atoi(SNThreads))
    {
      break;
    }else
    {
      cout<<"Invalid input!"<<endl;
    }
  }
  cout<<"There're "<<NThreads<<" threads initilized!"<<endl;
   srand(time(0)); 
  
   pthread_t threads[NThreads];
   int rc;
   long t;
   for(t=0;t<NThreads;t++){
     rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
     pthread_join(threads[t],NULL);
   }
   

  
  
/*  
  int a[7]={3,1,2,4,5,6,8};
  int* arr;
  arr=a;
  for (int i=0; i<7;i++)
  cout<<arr[i]<<endl;
  
  
  quickSort(arr,0,6);
  
  for (int i=0; i<7;i++)
  cout<<arr[i]<<endl;
  
 */ 
  return 0;
}
