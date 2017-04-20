#include <bits/stdc++.h>
using namespace std;
set<char> inp; // for the alphabet input
set<int> followpos[10]; // kind of mapping for the followpositions eg: 1 -> {1,2,3} and so on
map<int,char> position; // this is mapping for integer to alphabets of node, the integer repersents the position of node
int pos=1; // for refering to position number of nodes
set<int> operator +(set<int> a,set<int> b) // used for doing union operation
{
	a.insert(b.begin(),b.end());
	return a;
}
struct node // single node of tree with all its properties associated with it like data, position, firstpos, lastpos; followpos is not included here
{
	int pos;
	char ch;
	bool nullable;
	set<int>firstpos,lastpos;
	node *left,*right;
};

node *Get(int pos,char ch) // creating the node declared above and initializing 2 of its properties : data and position
{
	node *temp=new node();
	temp->left=temp->right=NULL;
	temp->pos=pos;
	temp->ch=ch;
	temp->nullable = false;
	temp->firstpos.clear(),temp->lastpos.clear();
	return temp;
}
void postfix(node *root) // simply iterating over tree using postorder traversal
{
	if(root)
	{
		postfix(root->left);
		postfix(root->right);
		cout<<root->pos<<"    "<<root->ch<<setw(10)<<root->nullable<<setw(10);
		cout<<" { ";
		for(auto i:root->firstpos)
			cout<<i<<setw(2);
		cout<<"} "<<setw(20)<<" {";
		for(auto i:root->lastpos)
			cout<<i<<"  ";
		cout<<"} "<<endl;
	}
}


node* create(string str) // creating the complete tree with the help of nodes and taking the regular expression as the argument
{
	stack<node *>st; // to store the nodes
	node *rand; // store the value poped from stack
	for(int i=0;i<str.size();i++) // running the loop to iterate over each charater of string and perform required operation
	{
		if(isalpha(str[i])||str[i]=='#')// checking if alphabet and then setting firstpos, lastpos
		{
			
			rand=Get(pos,str[i]);
			rand->firstpos.insert(pos);
			rand->lastpos.insert(pos);
			if(str[i]!='#') // we don't use # in the final table so we don't need to instert into alphabet list
			{
				inp.insert(str[i]);
				position[pos]=str[i]; // position is map which stores alphabets corrosoping to integer positions
			}
			pos++;
			st.push(rand); // inserting node into stack.
		}
		else if(str[i]=='*')
		{
			rand = st.top(); // only poping one value from stack because we have only one child of *
			st.pop();
			node* temp = Get(0,str[i]);
			temp->firstpos = rand->firstpos;
			temp->lastpos = rand->lastpos;
			temp->left = rand;
			temp->nullable=true;
			st.push(temp);
			for(auto H:temp->lastpos)	
				followpos[H] = followpos[H] + temp->firstpos;
			
		}
		else if(str[i]=='|'||str[i]=='/')
		{
			node *right  = st.top();st.pop();
			node *left = st.top();st.pop();
			node *temp=Get(0,str[i]);
			temp->nullable = left->nullable|right->nullable;
			temp->firstpos = left->firstpos + right->firstpos;
			temp->lastpos = left->lastpos + right->lastpos;
			temp->left = left;
			temp->right = right;
			st.push(temp);
		}
		else
		{
			node *right  = st.top();st.pop();
			node *left = st.top();st.pop();
			node *temp=Get(0,str[i]);
			temp->nullable = left->nullable & right->nullable;
			temp->firstpos = left->nullable ? left->firstpos + right->firstpos : left->firstpos;
			temp->lastpos =  right->nullable ? left->lastpos + right->lastpos : right->lastpos;
			temp->left=left;
			temp->right=right;
			st.push(temp);
			for(auto H:left->lastpos)
				followpos[H] = followpos[H] + right->firstpos;
		}
	}
	return st.top();	
}
void dfa(node *root) // for constructing dfa
{
	set<int> Union;// used as a temporary variable to store the result obtained after union
	map<set<int>,char> redundant;
	map<set<int>,map<char,set<int> > > Final;
	int k=1,cur=1; // curr is one or more step ahead than k
	set<int>states[10];
	char ch='A';
	states[cur++] = root->firstpos;
	redundant[root->firstpos]=ch++;
	while(1)
	{
		for(auto i:inp)// here a b a a b  = i
		{
			for(auto pos:states[k]) // ab ki no honge 1(a),2(b) ,3(a),4(a)  = pos state(1 2 3)
				{
					
					if(position[pos]==i)  //change position[pos]= inp[pos-1]==i
						Union = Union + followpos[pos];
					if(Union.size()>0 && redundant[Union]==0)// check kiaa ki new stare aaai to nhi hai (redundant[Union]==0)
					{
						redundant[Union]=ch++;
						states[cur++] = Union;
						
					}
					// dought set start with 0 or not
					
				}
			Final[states[k]][i] = Union;
			Union.clear();
		}
		if(k==cur-1)
			break;
		k++;
	}
	for(auto i:Final)
	{
		cout<<"{ ";
		for(auto j:i.first)
			cout<<j<<" ";
		cout<<"} ";
		for(auto h:i.second)
		{
			cout<<h.first<<"  { ";
			for(auto m:h.second)
				cout<<m<<" "; 
				cout<<"  }  "; 
			
		}
		cout<<endl;
		
	}
	    
}
int main()
{
	string str("ab|*a.b.b.#.");
	node *tree=create(str);
	cout<<"Pos   name    nullable  firstpos   lastpos \n";
	postfix(tree);
	
	cout<<"Follow position\n";
	for(int i=1;i<pos-1;i++)
	{
		cout<<i<<"        ";
		for(auto j:followpos[i])
			cout<<j<<" ";
		cout<<endl;
	}
	dfa(tree);
}
