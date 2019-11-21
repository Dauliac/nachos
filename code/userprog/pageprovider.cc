#ifdef CHANGED
#
#include bitmap.h

PageProvider::PageProvider()
{

    pageMap = new Bitmap(numPages);
    pageMap->Mak(0);
}

PageProvider::~PageProvider()
{

}

PageProvider::GetEmptyPage()
{
    int gettedPage = pageMap->Find();

}

#endif // CHANGED