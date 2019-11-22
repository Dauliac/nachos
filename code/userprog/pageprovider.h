#ifdef CHANGED
class PageProvider:dontcopythis
{
  public:
    PageProvider (int numPages);	
     ~PageProvider ();

    int GetEmptyPage();

  /*private:
    int numBits;		// number of bits in the bitmap
    int numWords;		// number of words of bitmap storage
    // (rounded up if numBits is not a
    //  multiple of the number of bits in
    //  a word)
    unsigned int *map;		// bit storage*/
};

#endif // CHANGED
