//Name: JUSTIN CHU
//Date: 4/4/2023
//This program sorts cards based on various sorting algorithms and linked lists, including quickSort, mergeSort, bubbleSort and insertionSort, taken from Yu-Gi-Oh cards within a csv file.


#include "CardShop.hpp"
#include "Node.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>


/**
  @pre  : the input file is in csv format: "name,type,level_rank,race,attribute,atk,def"
  @param: the name of the input file
  @post:  Reads the input file and adds pointers to YGOCard objects 
          instantiated with the information read from the file. 
    */
CardShop::CardShop(std::string input_file_name) 
{
  std::ifstream fin(input_file_name);
  if (fin.fail())
  {
    std::cerr << "File cannot be opened for reading. \n";
    exit(1); // exit if failed to open the file
  }
  //we don't use the first line
  std::string ignore;
  getline(fin, ignore);

  //the columns of the csv associated with the data members
  std::string name, type, race, attribute;
  int level_rank, atk, def;

  std::string temp_string;
  int temp_int;
  int item_counter = 0;
  while (getline(fin, temp_string, ','))
  {
    name = temp_string;

    getline(fin, type, ',');
  
    getline(fin, temp_string, ',');
    std::istringstream(temp_string) >> temp_int;
    level_rank = temp_int;

    getline(fin, race, ',');

    getline(fin, attribute, ',');

    getline(fin, temp_string, ',');
    std::istringstream(temp_string) >> temp_int;
    atk = temp_int;

    getline(fin, temp_string);
    std::istringstream(temp_string) >> temp_int;
    def = temp_int;

    //create new card
    YGOCard *card_ptr = new YGOCard(name, type, level_rank, race, attribute, atk, def);

    //add to linked list and increment counter
    insert(item_counter++, card_ptr);
  }
}

//@post: removes all cards from the shop
//Deallocate and delete items
void CardShop::clear()
{
  for (int i = 0; i < item_count_; i++)
  {
    YGOCard *ptr = getItem(i);
    delete ptr;
    ptr = nullptr;
  }
  DoublyLinkedList::clear();
}

//destructor
CardShop::~CardShop()
{
  clear();
}

//@post: displays information of all cards in the shop, one per line
void CardShop::display()
{
  for (int i = 0; i < item_count_; i++)
  {
    getItem(i)->display();
  }
}

  //@param: the index of the first card to be displayed
  //@param: the index of the last card to be displayed
  //@post: displays the names of all cards in the shop with startRange and endRange, 
  //       inclusive, one per line
void CardShop::displayName(int startRange, int endRange)
{
  for (int i = startRange; i <= endRange; i++)
  {
    getItem(i)->displayName();
    if (i != endRange)
    {
      std::cout << ", ";
    }
    else
    {
      std::cout << std::endl;
    }
  }
}


//@return:  true if all the cards in rhs are equal to the cards in the shop, false otherwise
bool CardShop::operator==(const CardShop &rhs) const
{
  if (getLength() != rhs.getLength())
  {
    return false;
  }
  for (int i = 0; i < getLength(); i++)
  {
    if (*(getPointerTo(i)->getItem()) == *(rhs.getPointerTo(i)->getItem()))
    {
    }
    else
    {
      return false;
    }
  }
  return true;
}

//bubbleSort
template <typename Comparator>                              
int CardShop::bubbleSort(Comparator comp, std::string key) 
{
  
    int count = 0;
    int size = getLength();

    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            YGOCard *card1 = this->getItem(j);
            YGOCard *card2 = this->getItem(j + 1);

            if (key == "atk")
            {
                int val1 = card1->getAtk();
                int val2 = card2->getAtk();
                if (comp(val2,val1))
                {
                    swap(j+1, j); 
                    count++;
                }
              }
            else if (key == "def")
            {
                int val1 = card1->getDef();
                int val2 = card2->getDef();
                if (comp(val2,val1))
                {
                    swap(j+1, j); 
                    count++;
                }
            }
            else {
                throw std::invalid_argument("Unusable!");
            }
        }
    }
    return count;
}  

//Insertion sort
template <typename Comparator>
int CardShop::insertionSort(Comparator comp, std::string key)
{
    int count = 0;
    int size = getLength();
    for (int i = 1; i < size; i++)
    {
        YGOCard *current_card = getItem(i);
        int j = i - 1;
        YGOCard *next_card = getItem(j);
        while(j >= 0 && comp(getCardValue(current_card, key), getCardValue(next_card, key)))
        {
          
          swap(j + 1, j);
          
          
          current_card = getItem(j);
          next_card = getItem(j - 1);
          j--;
          count++;
        }
        
        
        setItem(j + 1, current_card);
    }
    return count;
}

//helps get card value
int CardShop::getCardValue(YGOCard* card, std::string key)
{
    if (key == "atk") {
        return card->getAtk();
    } else if (key == "def") {
        return card->getDef();
    } else {
        throw std::invalid_argument("Can't use");
    }
}

 //Quick sort
template <typename Comparator>
int CardShop::quickSort(Comparator comp, std::string key) 
{
    int count = 0;
    quickSortHelper(comp, 0, getLength() - 1, key, count);
    return count;
}

template <typename Comparator>
void CardShop::quickSortHelper(Comparator comp, int low, int high, std::string key, int& numSwaps)
{
    if (low < high)
    {
        int pivotIndex = partition(comp, low, high, key, numSwaps);
        quickSortHelper(comp, low, pivotIndex - 1, key, numSwaps);
        quickSortHelper(comp, pivotIndex + 1, high, key, numSwaps);
    }
}

template <typename Comparator>
int CardShop::partition(Comparator comp, int low, int high, std::string key, int& numSwaps)
{
    YGOCard *pivot = getItem(high);
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        YGOCard *card = getItem(j);
        if (key == "atk")
        {
            if (comp(card->getAtk(), pivot->getAtk()))
            {
                i++;
                swap(i, j);
                numSwaps++;
            }
        }
        else if (key == "def")
        {
            if (comp(card->getDef(), pivot->getDef()))
            {
                i++;
                swap(i, j);
                numSwaps++;
            }
        }
        else
        {
            throw std::invalid_argument("Can't use");
        }
    }
    swap(i + 1, high);
    numSwaps++;
    return i + 1;
}

//mergeSort
template<typename Comparator>
int CardShop::mergeSort(Comparator comp, std::string key) 
{
  return 0;
}