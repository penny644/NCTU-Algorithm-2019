#include<iostream>
#include<vector>
#include<sstream> 
#include<stdlib.h>
#include<fstream>
#include<string>
#define MAX 2147483647
using namespace std;

//Compare whether the element at the specific position in vector<string> is equal to c
bool comvtoc(vector<string>& v,string c,int i){
	string a;
	a=v[i];
	if(a==c) return true;
	else return false;
}

//Initialize array
void initial(int **arr,int m,int n){
	int i,j;
	for(i=0;i<m;i++){
		for(j=0;j<n;j++){
			arr[i][j]=0;
		}
	}
}

//Split string: use a space as the separation mark
void SplitString(string a, vector<string>& b)
{
    int p1, p2;
    string c=" ";
    p2 = a.find(c);
    p1 = 0;
    while(p2!=-1)
    {
        b.push_back(a.substr(p1, p2-p1));
        p1 = p2 + c.size();
        p2 = a.find(c, p1);
    }
    if(p1 != a.length()) b.push_back(a.substr(p1));
}



//Swap two numbers
void swap(int &a, int &b){
	int tmp;
	tmp=a;
	a=b;
	b=tmp;
}

//Insert the element to young tableau 
void insert(int m,int n,int **arr){
	while(1){
		if(m!=0){
			if(n!=0){
				if(arr[m-1][n]>=arr[m][n]&&arr[m][n-1]>=arr[m][n]){
					if(arr[m-1][n]>=arr[m][n-1]) {
						swap(arr[m][n],arr[m-1][n]);
						m--;
					}
					else{
						swap(arr[m][n],arr[m][n-1]);
							n--;
					}
				}
				else if(arr[m-1][n]<=arr[m][n]&&arr[m][n-1]>=arr[m][n]){
					swap(arr[m][n],arr[m][n-1]);
				}
				else if(arr[m-1][n]>=arr[m][n]&&arr[m][n-1]<=arr[m][n]){
					swap(arr[m][n],arr[m-1][n]);
				}
				else break;
			}
			else{
				if(arr[m-1][n]>=arr[m][n]) {
					swap(arr[m][n],arr[m-1][n]);
						m--;
				}
				else break;
			}
		}
		else{
			if(n!=0){
				if(arr[m][n-1]>=arr[m][n]) {
					swap(arr[m][n],arr[m][n-1]);
					n--;
				}
				else break;
			}
			else break;
		}
	}	
}

//Extract element from young tableau 
void extract_min(int **arr,int m,int n){
	int	lastm=0,lastn=0;
	while(1){
		if(lastm<m-1){
			if(lastn<n-1){
				if(arr[lastm+1][lastn]<=arr[lastm][lastn]&&arr[lastm][lastn+1]<=arr[lastm][lastn]){
					if(arr[lastm+1][lastn]<=arr[lastm][lastn+1]) {
						swap(arr[lastm][lastn],arr[lastm+1][lastn]);
						lastm++;
					}
					else{
						swap(arr[lastm][lastn],arr[lastm][lastn+1]);
						lastn++;
					}
				}
				else if(arr[lastm+1][lastn]>=arr[lastm][lastn]&&arr[lastm][lastn+1]<=arr[lastm][lastn]){
					swap(arr[lastm][lastn],arr[lastm][lastn+1]);
				}
				else if(arr[lastm+1][lastn]<=arr[lastm][lastn]&&arr[lastm][lastn+1]>=arr[lastm][lastn]){
					swap(arr[lastm][lastn],arr[lastm+1][lastn]);
				}
				else break;
			}
			else{
				if(arr[lastm+1][lastn]<=arr[lastm][lastn]) {
					swap(arr[lastm][lastn],arr[lastm+1][lastn]);
					lastm++;
				}
				else break;
			}
		}
		else{
			if(lastn<n-1){
				if(arr[lastm][lastn+1]<=arr[lastm][lastn]) {
					swap(arr[lastm][lastn],arr[lastm][lastn+1]);
					lastn++;
				}
				else break;
			}
			else break;
		} 
	}
}

int main(){
	stringstream con;
	int num,oper,m=0,n=0,i,j=0,k=0,insertnum=0,**arr,l=0,lastm=-1,lastn=-1,extract;
	vector<string> tmp;
	vector<int> ins;
	string c,c1,ig; 
	con.clear();
	con.str("");
	ifstream input("input.txt",ios::in);
	ofstream output("output.txt",ios::out);
	input>>num;
	for(i=0;i<num;i++){
		input>>oper;	//Input the action which the user wants to execute(insert or extract) 
		m=0;			//Initialize the row index
		c1="";
		getline(input,ig);
		if(oper==1){
			getline(input,c1);			//Get the numbers which user inserts
			SplitString(c1,tmp);		//Split the string into numbers
			insertnum=tmp.size();		//Calculate how many numbers are inserted
			ins.assign(insertnum,0);	
			
			for(j=0;j<insertnum;j++){	//Transfer string to integer
				con<<tmp[j];
				con>>ins[j];
				con.clear();
				con.str("");
			}
			tmp.clear();
			
			cout<<"Insert ";			 
			output<<"Insert ";
			for(j=0;j<insertnum;j++){
				cout<<ins[j]<<" ";
				output<<ins[j]<<" ";
			}
			cout<<endl;
			output<<endl;
		}
		while(1){
			getline(input,c);			//Get the array which user inputs
			if(c.size()!=0){
				SplitString(c,tmp);		//Split the string into numbers
				m++;					//Calculate how many rows in this array
			}
			else break;
		}
		n=tmp.size()/m;					//Calculate how many columns in this array
		 
		arr=(int**)malloc(sizeof(int*)*m);	//Allocate a m*n array
		for(j=0;j<m;j++) arr[j]=(int*)malloc(sizeof(int)*n);
		initial(arr,m,n);
		
		l=0;
		for(j=0;j<m;j++){				//Transfer string element to integer array and store to arr
			for(k=0;k<n;k++){
				if(comvtoc(tmp,"x",l)) arr[j][k]=MAX;
				else{
					con<<tmp[l];
					con>>arr[j][k];
				}
				con.clear();
				con.str("");
				l++;
			}
		}
		tmp.clear();
		
		if(oper==1){						//insert element
			for(l=0;l<insertnum;l++){
				lastn=-1;
				lastm=-1;
				for(j=0;j<m;j++){
					for(k=0;k<n;k++){
						if(arr[j][k]==MAX){
							lastn=k;
							lastm=j;
							break;
						}
					}
					if(lastm!=-1) break;
				}
				arr[lastm][lastn]=ins[l];
				insert(lastm,lastn,arr);
			}
		}
		else if(oper==2){					//extract the minimum value
			extract=arr[0][0];
			cout<<"Extract-min "<<extract<<endl;
			output<<"Extract-min "<<extract<<endl;
			arr[0][0]=MAX;
			extract_min(arr,m,n);
		}
		
		for(k=0;k<m;k++){
			for(j=0;j<n;j++){
				if(arr[k][j]==MAX){
					cout<<"x ";
					output<<"x ";
				}
				else{
					cout<<arr[k][j]<<" ";
					output<<arr[k][j]<<" ";
				}
				
			}
			cout<<endl;
			output<<endl;
		}
		if(i<=num-1){
			cout<<endl;
			output<<endl;
		} 
		
		for(j=0;j<m;j++) free(arr[j]);		//free memory
		free(arr);
		
	}
	input.close();
	output.close();
}
