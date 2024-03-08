#include<iostream>
#include<vector>
#include<sstream>
#include<stdlib.h>
#include<fstream>
#include<string>
using namespace std;

void initial(int **arr,int m,int n){
	int i,j;
	for(i=0;i<m;i++){
		for(j=0;j<n;j++){
			arr[i][j]=0;
		}
	}
}

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

int main(){
	stringstream con;
	int m=0,n=0,i,j,k,l,alnum=0,daymax=0;
	vector<string> tmp1;
	vector<int> day;
	string c="",ig="";
	con.clear();
	con.str("");
	ifstream input("input.txt",ios::in);
	ofstream output("output.txt",ios::out);
	m=0;
	while(1){
		alnum=0;
		while(1){
			getline(input,c);			//Get the one row of array
			if(c.length()>1){
				SplitString(c,tmp1);	//Split the row to numbers
				m++;					//Calculate how many rows in this array
				c="";					
			}
			else break;
		}
		if(m==0) {
			break;
		}
		else n=tmp1.size()/m;					//Calculate how many columns in this array
		int **arr=(int**)malloc(sizeof(int*)*(m+1));	//Allocate a m*n array
		for(i=0;i<m+1;i++) arr[i]=(int*)malloc(sizeof(int)*(n+1));
		initial(arr,m+1,n+1);
		l=0;
		for(i=0;i<=m;i++){				//Transfer string element to integer array and store to arr
			for(j=0;j<=n;j++){
				if(i==0||j==0) arr[i][j]=0;
				else{
					con<<tmp1[l];
					con>>arr[i][j];
					con.clear();
					con.str("");
					l++;	
				}
			}
		}
		
		tmp1.clear();
		while(!input.eof()){
			getline(input,c);			//Get the one row of array
			if(c.length()<=3){
				getline(input,ig);
				SplitString(c,tmp1);		//Split the row to numbers
				alnum++;				//Calculate how many rows in this array
			}
			else break;
		}
		day.assign(alnum,0);
		for(i=0;i<alnum;i++){	//Transfer string to integer
			con<<tmp1[i];
			con>>day[i];
			con.clear();
			con.str("");
		}
		tmp1.clear();
		
		
		for(l=0;l<alnum;l++){
			int **DP=(int**)malloc(sizeof(int*)*(day[l]+1));	//Allocate a m*n array
			for(i=0;i<=day[l];i++) DP[i]=(int*)malloc(sizeof(int)*(n+1));
			initial(DP,day[l]+1,n+1);
			for(i=1;i<=n;i++){
				for(j=1;j<=day[l];j++){
					if(j<i||j>day[l]-(n-i)) DP[j][i]=0;
					else if(j==i) DP[j][i]=DP[j-1][i-1]+arr[1][i];
					else {
						for(k=1;(k<=(day[l]-n+1)&& k<=(j-i+1)&&k<=m);k++){
							if(DP[j][i]<DP[j-k][i-1]+arr[k][i]){
								DP[j][i]=DP[j-k][i-1]+arr[k][i];
							}	
						}
					}
				}
			}
			if(l!=0) {
				cout<<endl<<DP[day[l]][n];
				output<<endl<<DP[day[l]][n];
			}
			else {
				cout<<DP[day[l]][n];
				output<<DP[day[l]][n];
			}
			for(i=0;i<=day[l];i++) free(DP[i]);		//Free memory
			free(DP);
		}
		m=0;
		if(c.length()>3){
			SplitString(c,tmp1);		//Split the row to numbers
			m++;
			cout<<endl;
			output<<endl;
		}
		for(i=0;i<=m;i++) free(arr[i]);		//Free memory
		free(arr);
		if(input.eof()) break;
	}
	input.close();
	output.close();
}
