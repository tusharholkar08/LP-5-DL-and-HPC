#include<iostream>
#include<cstdlib>
#include<omp.h>
#include<time.h>
using namespace std;

void merge(int array[],int low1, int high1,int low2,int high2, int n)
{
	int temp[n];
	int i=low1,j=low2,k=0;
	
	while(i<=high1 && j<=high2)
	{
		if(array[i]<array[j])
			temp[k++]=array[i++];
		else
			temp[k++]=array[j++];
	}
	
	while(i<=high1)
		temp[k++]=array[i++];
	
	while(j<=high2) 
		temp[k++]=array[j++];
		
	for(i=low1,j=0;i<=high2;i++,j++)
		array[i]=temp[j];
}

void mergesort(int array[], int low, int high, int n)
{
	if(low<high)
	{
		int mid=(low+high)/2;
		#pragma omp parallel sections
		{
			#pragma omp section
			{
				mergesort(array,low,mid,n);
			}
			
			#pragma omp section
			{
				mergesort(array,mid+1,high,n);
			}
			
		}
		
        merge(array,low,mid,mid+1,high,n);

	}
}




int main()
{
	int n;
	cout<<"Enter the number of elements : ";
	cin>>n;
    int arr[n] = {0};
	for(int i=0;i<n;i++)
	{
		cin>>arr[i]; 
	}
	cout<<"Original Array: ";
	for(int i=0;i<n;i++)
	{
		cout<<arr[i]<<" ";
	}	
	cout<<endl;
	mergesort(arr,0,n-1,n);
	cout<<"Final Array: ";
	for(int i=0;i<n;i++)
	{
		cout<<arr[i]<<" ";
	}
	cout<<endl;
    return 0;
}


