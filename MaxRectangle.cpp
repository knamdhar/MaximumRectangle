#include<stdio.h>
#include<iostream>

using namespace std;

struct info
{
	public:
	int start;
	int end;
	int height;
	int index;
	
	info(int height, int start, int end, int index)
	{
		this->height = height;
		this->start = start;
		this->end = end;
		this->index = index;
	}
};

class Stack
{
	private:
	struct node
	{
		node* next;
		info* data;
		
		node()
		{
			this->next = NULL;
			this->data = NULL;
		}
	};
	node* start;
	
	public:
	
	Stack()
	{
		start = NULL;
	}
	
	void push(info* data)
	{
		node* temp = new node();
		temp->data = data;
		temp->next = NULL;
		if(start == NULL)
			start = temp;
		else
		{
			temp->next = start;
			start = temp;
		}
	}
	
	info* pop()
	{
		info* data = start->data;
		start = start->next;
		return data;
	}
	
	info* seek()
	{
		return start->data;
	}
	
	bool isEmpty()
	{
		if(start == NULL)
			return true;
		return false;
	}
};

int main()
{
	int arr[] = {7,  100, 7, 7};						//18
	int size = sizeof(arr)/sizeof(int);
	int content[4][2]; 
	Stack* stk = new Stack();
	content[0][0] = 0;
	content[0][1] = 0;
	info* first = new info(arr[0], 0, 0, 0);
	stk->push(first);
	for(int i = 1; i < size; i++)
	{
		if(arr[i] > (stk->seek())->height)
		{
			info* pushed = new info(arr[i], i, i, i);
			stk->push(pushed);
			content[i][0] = i;
			content[i][1] = i;
		}
		else
		{
			bool fl = false;
			while((stk->seek())->height >= arr[i])
			{
				info* popped = stk->pop();
				content[popped->index][1] = i - 1;
				if(stk->isEmpty())
				{
					fl = true;
					break;
				}
			}
			if(!fl)
			{
				content[i][1] = i;
				content[i][0] = (stk->seek())->index + 1;
				content[(stk->seek())->index][1] = i;

			}
			else
			{
				content[i][1] = i;
				content[i][0] = 0;
				content[0][1] = i - 1;
			}
			info* pushed = new info(arr[i], content[i][0], content[i][1], i);
			stk->push(pushed);
		}
	}
	
	int ender = (stk->pop())->index;
	while(stk->isEmpty() == false)
	{
		content[(stk->pop())->index][1] = ender;
	}
	
	int maxarea = 0;
	int s = 0;
	int e = 0;
	for(int i = 0; i < size; i++)
	{
		if(maxarea < ((content[i][1] - content[i][0] + 1)*arr[i]))
		{
			maxarea = (content[i][1] - content[i][0] + 1)*arr[i];
			s = content[i][0];
			e = content[i][1];
		}
	}
	
	cout<<"Maxarea = "<<maxarea<<"\nStart: "<<s<<"\nEnd: "<<e<<"\n";
	
	return 0;
}
