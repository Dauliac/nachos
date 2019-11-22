#ifdef CHANGED
class PageProvider:dontcopythis
{
  public:
    PageProvider (int numPages);	
     ~PageProvider ();

    int GetEmptyPage();
    void ReleasePage(int numPage);
    int NumAvailPage();

  private:
    int pagesNumber;
};

#endif // CHANGED
