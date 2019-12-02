#ifdef CHANGED
#ifndef PAGEPROVIDER_H
#define PAGEPROVIDER_H
#include "copyright.h"
#include "utility.h"
#include "bitmap.h"
class PageProvider:dontcopythis
{
  public:
    PageProvider();	
     ~PageProvider ();

    int GetEmptyPage();
    void ReleasePage(int numPage);
    int NumAvailPage();

  private:
    BitMap *pageMap;
};

#endif // PAGEPROVIDER_H
#endif // CHANGED
