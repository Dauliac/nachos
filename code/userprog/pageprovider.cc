#ifdef CHANGED
#include "pageprovider.h"
#include "bitmap.h"
#include "system.h"
#include "machine.h"
PageProvider::PageProvider()
{
    pageMap = new BitMap(NumPhysPages);
    pageMap->Mark(0);
}

PageProvider::~PageProvider()
{
    delete pageMap;
}

int PageProvider::GetEmptyPage()
{
    //DEBUG ('a', "Allocated page: %i\n", page);
    int page = pageMap->Find();
    ASSERT(page != -1);
    DEBUG ('a', "Allocated page: %i\n", page);
    DEBUG ('a', "NumAvailPage : %i\n", this->NumAvailPage());
    memset(machine->mainMemory + page * PageSize, 0, PageSize);
    //memset(machine->mainMemory + page * PageSize, 0, PageSize);
    return page;

}

void PageProvider::ReleasePage(int numPage)
{
    pageMap->Clear(numPage);
}

int PageProvider::NumAvailPage()
{
    return pageMap->NumClear();
}

#endif // CHANGED
