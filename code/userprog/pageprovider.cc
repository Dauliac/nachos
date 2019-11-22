#ifdef CHANGED
#include "pageprovider.h"
#include "bitmap.h"

PageProvider::PageProvider(int pagesNumber)
{
    pageMap = new Bitmap(pagesNumber);
    pageMap->Mark(0);
}

PageProvider::~PageProvider()
{
    delete pageMap;
}

int PageProvider::GetEmptyPage()
{
    int page = pageMap->Find();
    ASSERT(page != -1);
    memset(machine->mainMemory + page * PageSize, 0, PageSize);
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