#include<iostream>
#include<cstdlib>

using namespace std;

int main(int argc, char* argv[]){
    int num = argc - 1;
    double sum = 0;
    if (num == 0)
    {
        cout <<"Please input numbers to find average.";
    }else{
        for (int i = 1; i <= num; i++)
        {
            sum += atof(argv[i]);
        }
        cout<<"---------------------------------\n";
        cout <<"Average of "<<num<<" numbers = "<<sum/num;
        cout<<"\n---------------------------------";
    }
    

}
