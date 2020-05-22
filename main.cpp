#include<iostream>
#include<array>
#include<fstream>
#include<exception>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>

using namespace std;

//global variables
pthread_mutex_t myMutex;
ofstream out;
bool stop;
bool check;
bool* canRun;
int number=0;
string filename="log.txt";
int NThreads=0;

// The number of elements (n) should be provided as command line argument, while the
//number of threads (M) should be read from the console.
void bubbleSort(int* arr, int low,int high1)
{
  int high=high1+1;
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

void insertionSort(int* arr, int low, int high1)
{
  int high=high1+1;
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
  //int high=high1-1;
  int p;
  if (low<high)
  {
   p= partition(arr,low,high);
   quickSort(arr,low,p);
   quickSort(arr,p+1,high);
  }
}
////////////////////////////////////////////////



void printArr(int* arr, int low, int high)
{
  //out.open(filename);
  for (int i=low; i<=high;i++)
  {
    cout<<arr[i]<<"\t";
    out<<arr[i]<<"\t";
  }
  cout<<endl;
  out<<endl;
 // out.close();
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
  //cout<<lastLine<<endl;
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
void partialSort()
{
  int sortMethodN;
  int i,j;
  
  int *array=readArr();
  i=rand()%number;
  j=rand()%number;
  if (i>j)
    swap(i,j);
  cout<<"i="<<i<<", j="<<j;
  sortMethodN=rand()%3;
  if(sortMethodN==0)
  {
    cout<<"\tusing bubble sort"<<endl;
    bubbleSort(array,i,j);
  }else if(sortMethodN==1)
  {
    cout<<"\tusing insertion sort"<<endl;
    insertionSort(array,i,j);
  }else
  {
    cout<<"\tusing quick sort"<<endl;
    quickSort(array,i,j);
  }
    printArr(array,0, number-1);
}   
void *threadSort(void *threadid)
{
   long tid;
   tid = (long)threadid;
   while ( !stop)
   {
     while(!canRun[tid]||check);
     pthread_mutex_lock(&myMutex);
     printf(" thread #%ld sorting!     ", tid);
     partialSort();
     pthread_mutex_unlock(&myMutex);
     check=true;
     canRun[tid]=false;
     if (tid<NThreads-1)
       canRun[tid+1]=true;
     else
       canRun[0]=true;
//     break;
   }
  fflush(stdout);
    pthread_exit(NULL);
}
void *watch(void *threadid)
{ long tid;
  tid=(long)threadid;
  bool couldStop;
  
  while(!stop)
  {while(!check);
   pthread_mutex_lock(&myMutex);
   int *array=readArr();
   couldStop=true;
   for (int i=0;i<number-1;i++)
   {if (array[i]>array[i+1])
    {
      couldStop=false;
      break;
    }
   }
   if (couldStop)
   {
     stop=true;
     out.close();
     cout<<"sorting complete, element list of each update can be found in "<<filename<<endl;
     exit(-1);
   }
   pthread_mutex_unlock(&myMutex);
   check=false;
  }
   

}

int main(int argc, char* argv[])
{
//  int number=0;
  char SNThreads[5];
  string filename="log.txt";
  int range=100;
  pthread_mutex_init(&myMutex,NULL);

  srand(time(0)); 
  if (argc!=2)
  {
    cout<<"enter the number of elements in the list in the commmandline"<<endl;
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
  int element;
   for( int i=0; i< number; i++)
   {
    int element=rand()%range; 
    cout<<element<<"\t";
    out<<element<<"\t";
   }
  cout<<endl;
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
   cout<<"There're "<<NThreads<<" sorting threads initilized!"<<endl;
   stop=false;
   pthread_t threads[NThreads];
   int rc;
   long t;
   bool run[NThreads];
   canRun=run;
   for(int i=0;i<NThreads;i++)
     canRun[i]=false;
   canRun[0]=true;
   for(t=0;t<NThreads;t++){
     rc = pthread_create(&threads[t], NULL, threadSort, (void *)t);
    // pthread_join(threads[t],NULL);
   }
   t++;
   pthread_t watcher;
   rc=pthread_create(&watcher,NULL, watch,(void*)t);
   for(t=0;t<NThreads;t++){
     pthread_join(threads[t],NULL);
   }
   pthread_join(watcher,NULL);
  out.close();

 
 
  return 0;
}
