#ifdef CHANGED
#include "pageprovider.h"
#include "bitmap.h"

PageProvider::PageProvider()
{

    pageMap = new Bitmap(numPages);
    pageMap->Mark(0);
}

PageProvider::~PageProvider()
{

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

#endif // CHANGED