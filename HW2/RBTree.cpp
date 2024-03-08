#include<iostream>
#include<vector>
#include<sstream> 
#include<stdlib.h>
#include<fstream>
#include<string>
using namespace std;
ofstream output("output.txt",ios::out);
struct node{
		node *parent,*leftchild,*rightchild;
		int NodeValue;
		bool color;	//0 means black and 1 means red
};


class tree{
	public:
		node *root;
		node *NIL;
		tree();
		void insert(int value);
		void insert_fixup(node *ins);
		void delet(int value);
		void delet_fixup(node *del);
		node *find(int value);
		void RightRotation(node *right);
		void LeftRotation(node *left);
		void inorder(node *current);
};

tree::tree(){
	NIL=new node;
	NIL->color=false;
	NIL->leftchild=NIL;
	NIL->rightchild=NIL;
	root=NIL;
	root->parent=NIL;
}

void tree::insert(int value){
	node *inse=new node,*tmp,*tmp1;
	tmp=root;
	inse->leftchild=NIL;
	inse->rightchild=NIL;
	inse->NodeValue=value;
	if(root==NIL){
		root=inse;
		inse->parent=NIL;
		inse->color=false;
	}
	else{
		inse->color=true;
		while(tmp!=NIL){
			tmp1=tmp;
			if(tmp->NodeValue>inse->NodeValue){
				tmp=tmp->leftchild;
			}
			else{
				tmp=tmp->rightchild;
			}
		}
		inse->parent=tmp1;
		if(tmp1->NodeValue>inse->NodeValue){
			tmp1->leftchild=inse;
		}
		else{
			tmp1->rightchild=inse;
		}
		if(inse->parent->color==true){
			insert_fixup(inse);
		}

	}
}

void tree::RightRotation(node *right){
	node *child;
	child=right->leftchild;
	right->leftchild=child->rightchild;
	if(right->leftchild!=NIL) right->leftchild->parent=right;
	child->parent=right->parent;
	if(right->parent!=NIL){
		if(right->parent->leftchild==right){
			right->parent->leftchild=child;
		}
		else{
			right->parent->rightchild=child;
		}
	}
	else root=child;
	right->parent=child;
	child->rightchild=right;
	
}

void tree::LeftRotation(node *left){
	node *child;
	child=left->rightchild;
	left->rightchild=child->leftchild;
	if(left->rightchild!=NIL) left->rightchild->parent=left;
	child->parent=left->parent;
	if(left->parent!=NIL){
		if(left->parent->rightchild==left){
			left->parent->rightchild=child;
		}
		else{
			left->parent->leftchild=child;
		}
	}
	else root=child;
	child->leftchild=left;
	left->parent=child;
	
}

void tree::insert_fixup(node *ins){
	while(ins->parent!=NIL&&ins->parent->color==true){
		if(ins->parent->parent->leftchild==ins->parent){
			if(ins->parent->parent->rightchild!=NIL&&ins->parent->parent->rightchild->color==true){
				ins->parent->parent->rightchild->color=false;
				ins->parent->color=false;
				ins->parent->parent->color=true;
				ins=ins->parent->parent;
			}
			else{
				if(ins->parent->leftchild==ins){
					ins->parent->color=false;
					ins->parent->parent->color=true;
					RightRotation(ins->parent->parent);
				}
				else{
					ins=ins->parent;
					LeftRotation(ins);
					ins->parent->color=false;
					ins->parent->parent->color=true;
					RightRotation(ins->parent->parent);
				}
			}
		}
		else{
			if(ins->parent->parent->leftchild!=NIL&&ins->parent->parent->leftchild->color==true){
				ins->parent->parent->leftchild->color=false;
				ins->parent->color=false;
				ins->parent->parent->color=true;
				ins=ins->parent->parent;
			}
			else{
				if(ins->parent->rightchild==ins){
					ins->parent->color=false;
					ins->parent->parent->color=true;
					LeftRotation(ins->parent->parent);
				}
				else{
					ins=ins->parent;
					RightRotation(ins);
					ins->parent->color=false;
					ins->parent->parent->color=true;
					LeftRotation(ins->parent->parent);
				}
			}
		}
	}
	root->color=false;
}

node *tree::find(int value){
	node *tmp;
	tmp=root;
	while(tmp!=NIL&&tmp->NodeValue!=value){
		if(tmp->NodeValue>value){
			tmp=tmp->leftchild;
		}
		else tmp=tmp->rightchild;
	}
	return tmp;
}

void tree::delet(int value){
	node *tmp,*x,*y;
	tmp=find(value);
	if(tmp->leftchild==NIL||tmp->rightchild==NIL){
		y=tmp;
	}
	else {
		y=tmp->rightchild;
		while(y->leftchild!=NIL){
			y=y->leftchild; 
		}
		tmp->NodeValue=y->NodeValue;
	}
	if(y->leftchild!=NIL){
		x=y->leftchild;
	}
	else x=y->rightchild;
	
	x->parent=y->parent;
	
	if(y->parent==NIL){
		root=x;
	}
	else if(y->parent->leftchild==y){
		y->parent->leftchild=x;
	}
	else{
		y->parent->rightchild=x;
	}
	if(y->color==false) delet_fixup(x);
}

void tree::inorder(node *current){
	if(current!=NIL){
		inorder(current->leftchild);
		cout<<"key: "<<current->NodeValue<<" "<<"parent: ";
		output<<"key: "<<current->NodeValue<<" "<<"parent: ";
		if(current->parent!=NIL){
			cout<<current->parent->NodeValue;
			output<<current->parent->NodeValue;
		}
		else {
			cout<<" ";
			output<<" ";
		}
		cout<<" color: ";
		output<<" color: ";
		if(current->color==true) {
			cout<<"red"<<endl;
			output<<"red"<<endl;
		}
		else {
			cout<<"black"<<endl;
			output<<"black"<<endl;
		}
		inorder(current->rightchild);
	}
}

void tree::delet_fixup(node *del){
	while(del!=root&&del->color==false){	 
		if(del->parent->leftchild==del){
			if(del->parent->rightchild->color){
				del->parent->rightchild->color=false;
				del->parent->color=true;
				LeftRotation(del->parent);
			}	
			if(del->parent->rightchild->leftchild->color==false&&del->parent->rightchild->rightchild->color==false){
				del->parent->rightchild->color=true;
				del=del->parent;
			}
			else {
				if (del->parent->rightchild->rightchild->color==false){
					del->parent->rightchild->leftchild->color=false;
					del->parent->rightchild->color=true;
					RightRotation(del->parent->rightchild);
				}	
				del->parent->rightchild->color=del->parent->color;
				del->parent->color=false;
				del->parent->rightchild->rightchild->color=false;
				LeftRotation(del->parent);
				del=root;	
			}
		}
		else{
			if(del->parent->leftchild->color){
				del->parent->leftchild->color=false;
				del->parent->color=true;
				RightRotation(del->parent);
			}
			if(del->parent->leftchild->leftchild->color==false&&del->parent->leftchild->rightchild->color==false){
				del->parent->leftchild->color=true;
				del=del->parent;
			}
			else{
				if(del->parent->leftchild->leftchild->color==false){
					del->parent->leftchild->color=true;
					del->parent->leftchild->rightchild->color=false;
					LeftRotation(del->parent->leftchild);
				}
				del->parent->leftchild->color=del->parent->color;
				del->parent->leftchild->leftchild->color=false;
				del->parent->color=false;
				RightRotation(del->parent);
				del=root;
			}
		}
	}
	del-> color=false;
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

int main(){
	tree use;
	stringstream con;
	vector<string> tmp;
	int insertnum=0,i,num,j,oper,del,ins,delnum;
	con.clear();
	con.str("");
	string c1,ig;
	ifstream input("input.txt",ios::in);
	input>>num;
	for(i=0;i<num;i++){
		input>>oper;	//Input the action which the user wants to execute(insert or delete) 
		c1="";
		getline(input,ig);
		if(oper==1){
			cout<<"Insert: ";
			output<<"Insert: ";
			getline(input,c1);			//Get the numbers which user inserts
			SplitString(c1,tmp);		//Split the string into numbers
			insertnum=tmp.size();		//Calculate how many numbers are inserted
			for(j=0;j<insertnum;j++){	//Transfer string to number
				con.clear();
				con.str("");	
				con<<tmp[j];
				con>>ins;
				if(j!=insertnum-1){
					cout<<ins<<", ";
					output<<ins<<", ";
				}
				else {
					cout<<ins<<endl;
					output<<ins<<endl;
				}
				use.insert(ins);
			}
			tmp.clear();
			use.inorder(use.root);
		}
		else if(oper==2){
			cout<<"Delete: ";
			output<<"Delete: ";
			getline(input,c1);			//Get the numbers which user inserts
			SplitString(c1,tmp);		//Split the string into numbers
			delnum=tmp.size();			//Calculate how many numbers are inserted
			for(j=0;j<delnum;j++){		//Transfer string to integers
				con.clear();
				con.str("");	
				con<<tmp[j];
				con>>del;
				if(j!=delnum-1){
					cout<<del<<", ";
					output<<del<<", ";
				}
				else {
					cout<<del<<endl;
					output<<del<<endl;
				}
				use.delet(del);
			}
			tmp.clear();
			use.inorder(use.root);
		}
	}
	input.close();
	output.close();
} 
