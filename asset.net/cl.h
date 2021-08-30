#include <vector>
#pragma once
#include <cliext/vector>

using namespace std;

template <class TBase>

class cl
{
protected:

//The Vector container that will hold the collection of Items

	vector<TBase> m_items;

	//cl();

public:
	
	int Add(TBase item) 
	{  
		//Create a new base item  
		TBase BaseItem;   
		//Add the item to the container  
		m_items.push_back(BaseItem); 
		//Return the position of the item within the container.
		//Zero Based 
		m_items[m_items.size()-1]=item;
		
		return (m_items.size()-1); 
	}   


	//Remove a specific Item from the collection 
	void Remove(int ItemKey)  
	{  
		//Remove the Item using the vectorâ €™s erase function 
		

	
		m_items.erase(m_items.begin()+ItemKey); 
	}  
	
	void Clear(void) 
		//Clear the collection 
	{  
		m_items.clear(); 
	}   //Return the number of items in collection

	int Count(void) 
	{    
		return m_items.size();
		//One Based  
	}
	//Operator Returning a reference to TBase 
	TBase& operator [](int ItemKey) 
	{   
		return m_items[ItemKey];  
	} 

};  