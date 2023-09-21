#ifndef CARD_SHOP_HPP_
#define CARD_SHOP_HPP_
#include "DoublyLinkedList.hpp"
#include "YGOCard.hpp"
#include <iostream>
#include <fstream>
#include <sstream>


class CardShop : public DoublyLinkedList<YGOCard *>
{
public:
  CardShop() = default; //default constructor
  ~CardShop();          //destructor calls clear

  /**
  @pre  : the input file is in csv format: "name,type,level_rank,race,attribute,atk,def"
  @param: the name of the input file
  @post:  Reads the input file and adds pointers to YGOCard objects 
          instantiated with the information read from the file. 
    */
  CardShop(std::string input_file_name); //parameterized constructor

  //@post: displays information of all cards in the shop, one per line
  void display();

  //@param: the index of the first card to be displayed
  //@param: the index of the last card to be displayed
  //@post: displays the names of all cards in the shop with startRange and endRange, 
  //       inclusive, one per line
  void displayName(int startRange, int endRange);

  //@post: removes all cards from the shop
  void clear();                               

  //@return:  true if all the cards in rhs are equal to the cards in the shop, false otherwise
  bool operator==(const CardShop &rhs) const; 

 //@post: arranges all the cards in the correct order
 template<typename Comparator>
 int bubbleSort(Comparator comp, std::string key);

//@post: places an unsorted card in the correct position
 template<typename Comparator>
 int insertionSort(Comparator comp, std::string key);

//@post: divides the cards into smaller, organized portions
 template<typename Comparator>
 int quickSort(Comparator comp, std::string key);

//@post: cuts down the number of cards into various sublists; in which it then organizes them into a sorted list
template<typename Comparator>
 int mergeSort(Comparator comp, std::string key);

//@post: gets the card value using pointer so it can sort them
int getCardValue(YGOCard* card, std::string key);

//@post: helper function to hold elements less than and/or greater than pivot value
template<typename Comparator>
void quickSortHelper(Comparator comp, int low, int high, std::string key, int& numSwaps);

//@post: helper function that checks to make sure that all items less than pivot come before, while also returning position of pivot and number of swaps
template <typename Comparator>
int partition(Comparator comp, int low, int high, std::string key, int& numSwaps);
 
};



#endif