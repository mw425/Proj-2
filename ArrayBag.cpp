//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

/** Implementation file for the class ArrayBag.
 @file ArrayBag.cpp */

#include "ArrayBag.h"
#include <cstdlib> // for rand()
#include <cassert>

template<class ItemType>
ArrayBag<ItemType>::ArrayBag()
{
  itemCount = 0;
  maxItems = DEFAULT_CAPACITY;
}  // end default constructor

template<class ItemType>
bool ArrayBag<ItemType>::add(const ItemType& newEntry)
{
  bool hasRoomToAdd = (itemCount < maxItems);
  if (hasRoomToAdd)
  {
    items[itemCount] = newEntry;
    itemCount++;
  }
  return hasRoomToAdd;
}  // end add

template<class ItemType>
std::vector<ItemType> ArrayBag<ItemType>::toVector() const
{
  std::vector<ItemType> bagContents;
  for (int i = 0; i < itemCount; i++)
    bagContents.push_back(items[i]);
  return bagContents;
}  // end toVector

template<class ItemType>
void ArrayBag<ItemType>::fillArray(ItemType arr[]) const
{
  for (int i = 0; i < itemCount; i++)
    arr[i] = items[i];
}  // end fillArray

template<class ItemType>
int ArrayBag<ItemType>::getCurrentSize() const
{
  return itemCount;
}  // end getCurrentSize

template<class ItemType>
bool ArrayBag<ItemType>::isEmpty() const
{
  return itemCount == 0;
}  // end isEmpty

template<class ItemType>
bool ArrayBag<ItemType>::isFull() const
{
  return itemCount == maxItems;
}  // end isFull

template<class ItemType>
ItemType ArrayBag<ItemType>::get(int pos) const
{
  assert(0 <= pos && pos < itemCount);
  return items[pos];
}

template<class ItemType>
int ArrayBag<ItemType>::getFrequencyOf(const ItemType &anEntry) const
{
  int frequency = 0;
  int curIndex = 0; // Current array index
  while (curIndex < itemCount)
  {
    if (items[curIndex] == anEntry)
    {
      frequency++;
    }  // end if

    curIndex++; // Increment to next entry
  }  // end while

  return frequency;
}  // end getFrequencyOf

template<class ItemType>
bool ArrayBag<ItemType>::contains(const ItemType &anEntry) const
{
  bool isFound = false;
  int curIndex = 0; // Current array index
  while (!isFound && (curIndex < itemCount))
  {
    isFound = (anEntry == items[curIndex]);
    if (!isFound)
      curIndex++; // Increment to next entry
  }  // end while

  return isFound;
}  // end contains

template<class ItemType>
int ArrayBag<ItemType>::getIndexOf(const ItemType &target) const
{
  bool isFound = false;
  int result = -1;
  int searchIndex = 0;

  // If the bag is empty, then itemCount is zero, so loop is skipped
  while (!isFound && (searchIndex < itemCount))
  {
    isFound = (items[searchIndex] == target);
    if (isFound)
    {
      result = searchIndex;
    }
    else
    {
      searchIndex++;
    }
  }  // end while

  return result;
}  // end getIndexOf

template<class ItemType>
bool ArrayBag<ItemType>::remove(const ItemType &anEntry)
{
  int locatedIndex = getIndexOf(anEntry);
  bool canRemoveItem = !isEmpty() && (locatedIndex > -1);
  if (canRemoveItem)
  {
    itemCount--;
    items[locatedIndex] = items[itemCount];
  }  // end if

  return canRemoveItem;
}  // end remove

template<class ItemType>
void ArrayBag<ItemType>::clear()
{
  itemCount = 0;
}  // end clear

template<class ItemType>
ItemType ArrayBag<ItemType>::pickRandom() const
{
  int randomIndex = rand() % itemCount;
  return items[randomIndex];
}
