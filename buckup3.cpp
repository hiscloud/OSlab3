#include<iostream>
#include<array>
#include<fstream>
#include<exception>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
using namespace std;
//g++ Lu_lab4 -lpthread

//global variables
pthread_mutex_t myMutex;
ofstream out;
//ifstream in;
int number=0;
string filename="log.txt";

// The number of elements (n) should be provided as command line argument, while the
//number of threads (M) should be read from the console.
void bubbleSort(int* arr, int low,int high)
{
  for (int i=low; i< high;i++)
  {
    for (int j=low; j< high-1; j++)
    {
      if (arr[j]>arr[j+1])
      {
        swap(arr[j],arr[j+1]);
        //arr[j]=arr[j+1];
      }
    }
    
  }
}

void insertionSort(int* arr, int low, int high)
{
  
  for( int i=low;i<high;i++)
  {
    int k=i;
    while(k>low)
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
void partialSort()
{
  int sortMethodN;
  int i,j;
  i=rand()%number;
  j=rand()%number;
  if (i>j)
    swap(i,j);
  cout<<"i="<<i<<", j="<<j;
  sortMethodN=rand()%3;
  if(sortMethodN==0)
  {
    cout<<"\tusing bubble sort"<<endl;
  }else if(sortMethodN==1)
  {
    cout<<"\tusing insertion sort"<<endl;
  }else
  {
    cout<<"\tusing quick sort"<<endl;
  }
}   
////////////////////////////////////////////////
void printArr(int* arr)
{
  
}
int* readArr()
{
  int* arr=new int[number];
  ifstream in;
  string dummy1;
  string dummy2;
  string lastLine;
  string element;
  int j;
  
  in.open(filename);
  while(in.good()){
    getline(in,dummy1);
    getline(in,dummy2);
  }
  in.close();
  if(dummy2=="")
    lastLine=dummy1;
  else
    lastLine=dummy2;
  cout<<lastLine<<endl;
  //cout<<lastLine.length()<<endl;
  element="";
  j=0;
  for (int i=0;i<lastLine.length();i++)
  {
    if (lastLine.at(i)!='\t')
      element+=lastLine.at(i);
    else
    {
      arr[j]=stoi(element);
      element="";
      j++;
    }
  }

  return arr;
}
void *threadSort(void *threadid)
{
   long tid;
   tid = (long)threadid;
   while ( true)
   {
 //   sortMethodN=rand()%3;
     pthread_mutex_lock(&myMutex);
     printf(" thread #%ld sorting!     ", tid);
     partialSort();
     pthread_mutex_unlock(&myMutex);
     break;
   }
  fflush(stdout);
    pthread_exit(NULL);
}


int main(int argc, char* argv[])
{
//  int number=0;
  char SNThreads[5];
  int NThreads;
// ofstream out;
  string filename="log.txt";
  int range=100;
  
  srand(time(0)); 
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
   
  
   pthread_t threads[NThreads];
   int rc;
   long t;
   for(t=0;t<NThreads;t++){
     rc = pthread_create(&threads[t], NULL, threadSort, (void *)t);
     pthread_join(threads[t],NULL);
   }
   int *array=readArr();
   quickSort(array,1,number-1);
  for (int i=0; i<number;i++)
    cout<<array[i]<<endl;
  out.close();
 
  
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
