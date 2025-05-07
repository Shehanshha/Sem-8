#include<iostream>
#include<omp.h>
using namespace std;

int minval(int arr[],int n)
{
	cout<<"\n---Parallel execution for minimum------\n";
	double start_time = omp_get_wtime();
	
	int min_val = arr[0];
	#pragma omp parallel for reduction(min : min_val)
    for(int i=0;i<n;i++)
	{
		printf("Thread %d processing index %d (value: %d)\n",omp_get_thread_num(),i,arr[i]);
		if(arr[i] < min_val)
			min_val = arr[i];
	}
	double end_time = omp_get_wtime();
	cout<<"Minimum value:"<<min_val<<endl;
	cout<<"Time taken for parallel execution is"<<(end_time - start_time) *1000 <<" Millisecond"<<endl;
	return min_val;
}
int minval_s(int arr[],int n)
{
	double start_time = omp_get_wtime();
	int min_val = arr[0];
	for(int i=0;i<n;i++)
	{
		if(arr[i]<min_val)
			min_val = arr[i];
	}
    double end_time = omp_get_wtime();
	cout<<"Minimum value:"<<min_val<<endl;
	cout<<"Time taken for sequential processing: "<<(end_time - start_time) *1000<<" Millisecond"<<endl;
	return min_val;
}
int maxval(int arr[],int n)
{
	cout<<"\n----Parallel execution for Maximum------";
	double start_time = omp_get_wtime();
	
	int max_val = arr[0];
	#pragma omp parallel for reduction(max:max_val)
	for(int i=0;i<n;i++)
	{
		printf("Thread %d processing index %d (value:%d)\n",omp_get_thread_num(),i,arr[i]);
		if(arr[i] > max_val)
			max_val = arr[i];
	}
	double end_time = omp_get_wtime();
	cout<<"Maximum value:"<<max_val<<endl;
	cout<<"Time taken:"<<(end_time - start_time) *1000<<" Millisecond"<<endl;
	return max_val;
}	
int sum(int arr[],int n)
{
	cout<<"\n---------Parallel execution of sum----------";
	double start_time = omp_get_wtime();
	
	int total = 0;
	#pragma omp parallel for reduction(+:total)
	for(int i=0;i<n;i++)
	{
		printf("Thread %d processing index %d (value:%d)\n",omp_get_thread_num(),i,arr[i]);
		total += arr[i];
	}
	double end_time = omp_get_wtime();
	cout<<"Sum: "<<total<<endl;
	cout<<"Time taken: "<<(end_time - start_time) *1000<<" Millisecond"<<endl;
	return total;
}	
double avg(int arr[],int n)
{
	cout<<"\n---------Parallel execution of average----------";
	double start_time = omp_get_wtime();
	int total = 0;
	
	#pragma omp parallel for reduction(+:total)
	for(int i=0;i<n;i++)
	{
		printf("Thread %d processing index %d (value:%d)\n",omp_get_thread_num(),i,arr[i]);
		total += arr[i];
	}
	double end_time = omp_get_wtime();
	cout<<"Average: "<< (double)total / n;
	cout<<"Time taken:"<<(end_time - start_time) *1000<<" Millisecond"<<endl;
	return total;
}	
int main()
{
	int n;
	cout<<"Enter the number of elements:"<<endl;
	cin>>n;
	
	int arr[n];
	cout<<"Enter the array elements:"<<endl;
	for(int i=0;i<n;i++)
	{	
		cin>>arr[i];
	}
	minval(arr,n);
	minval_s(arr,n);
	maxval(arr,n);
	sum(arr,n);
	avg(arr,n);
	return 0;
}	
	