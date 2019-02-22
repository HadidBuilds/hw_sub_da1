#include<iostream>
using namespace std;

int main()
{
  int arr1[99]; //set array with size 9
  int j = 0; 
  //fill in array with num 11-109
  for(int i = 11; i<= 109;i++)
    {
      arr1[j] = i;
      j++;
    }
  int rem;
  int num;
  int val1=0;
  int val2=0;
  for(int i = 0; i <= 98;i++)
    {
      num = arr1[i];
      //calculate remainder
      rem = num    %3;
      //if rem == 0 then is divisible
      if(rem == 0)
	{
	  //if divisible by 3 then add
	  val1 = val1 + arr1[i];
	}
      else
	{
	  //else not divisible so add
	  val2 = val2 + arr1[i];
	}
    }
  cout<<"VALUE1:"<<val1<<endl; //addition of num divisible by three 
  cout<<"VALUE2:"<<val2<<endl; //addition of num not divisible by three
    return 0;
}
