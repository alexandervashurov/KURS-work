#pragma once

#include <vector>
#include <map>
#include <list>
#include <fstream>
#include <string>
typedef unsigned char byte;

using namespace std;


class node
{
public:
	int frequency;
	byte simb;
	node* left;
	node* right;
	node(){}
	~node()
	{
		
			if (left != NULL)
			{
				left->~node();
				delete left;
				left = NULL;
			}
			if (right != NULL)
			{
				right->~node();
				delete right;
				right = NULL;
			}
		

	}
	node(node* L, node* R)
	{
		left = L;
		right = R;
		frequency = L->frequency + R->frequency;
	}
	node(byte first, int second)
	{
		left = NULL;
		right = NULL;
		simb = first;
		frequency = second;
	}
};

struct CMP
{
	bool operator()(node* left, node* right)const
	{
		return left->frequency < right->frequency;
	}
};

class haffman
{
private:
	map<byte, int> inmap;
	vector<bool> symbol_code;
	map<byte, vector<bool> > table;
	list<node*> treecell;
	node* root;


	void create_table(node* root)
	{
		if (root->left != NULL)
		{
			symbol_code.push_back(0);
			create_table(root->left);
		}

		if (root->right != NULL)
		{
			symbol_code.push_back(1);
			create_table(root->right);
		}

		if (root->left == NULL && root->right == NULL)
			table[root->simb] = symbol_code;
		if (symbol_code.size())
		symbol_code.pop_back();
	}


    void read_file(std::string filename)
	{
        ifstream in;
        in.open(filename.c_str(), ios::binary);
		byte temp;
		while (!in.eof())
		{
			temp = in.get();
			inmap[temp] += 1;
		}

		in.close();
	}
	void write_file(string infilename, string filename)
	{
        ofstream out(filename.c_str(), ios::binary);
        ifstream in(infilename.c_str(), ios::binary);


		int count = 0;
		byte buff = 0;
		byte temp;
		vector<bool> x;
		while (!in.eof())
		{
			temp = in.get();
			x = table[temp];
			for (auto n :x)
			{
				buff = buff | n << (7 - count);
				count++;
				if (count == 8)
				{
					count = 0;
					out << buff;
					buff = 0;
				}
			}

		}
		out.close();
		in.close();
	}

	void razarch(string filename, string infile)
	{
        ofstream F(filename.c_str(), ios::binary);
        ifstream in(infile.c_str(), ios::binary);

		node *p = root;
		int count = 0;
		byte temp;
		temp = in.get();
		while (!in.eof())
		{
			bool b = temp & (1 << (7 - count));
			if (b)
				p = p->right;
			else
				p = p->left;
			if (p->left == NULL && p->right == NULL)
			{
				F << p->simb;
				p = root;
			}
			count++;
			if (count == 8)
			{
				count = 0;
				temp = in.get();
			}
		}

		F.close();
		in.close();
	}


	void build_tree()
	{

		map<byte, int>::iterator it;

		for (it = inmap.begin(); it != inmap.end(); it++)
		{
			
			node* p = new node(it->first, it->second);

			treecell.push_back(p);
		}

		while (treecell.size() != 1)
		{
			treecell.sort(CMP());

			node* left = treecell.front();
			treecell.pop_front();
			node* right = treecell.front();
			treecell.pop_front();
			node* result = new node(left, right);
			treecell.push_back(result);
		}

		root = treecell.front();

		create_table(root);
	}

public:

	haffman()
	{
	}

	~haffman()
	{
		root->~node();
		delete root;
	}
	
	void archivate(string infile, string outfile)
	{
		read_file(infile);
		build_tree();
		write_file(infile, outfile);

	}
	void unarchivate(string infile, string outfile)
	{
		razarch(outfile, infile);
	}

};

