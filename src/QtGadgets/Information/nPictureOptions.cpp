#include <qtgadgets.h>

N::PictureOptions:: PictureOptions (void)
                  : dpi            (96  )
{
}

N::PictureOptions:: PictureOptions(const PictureOptions & options)
{
  ME = options ;
}

N::PictureOptions::~PictureOptions(void)
{
}

N::PictureOptions & N::PictureOptions::operator = (const PictureOptions & options)
{
  nMemberCopy ( options , dpi ) ;
  return ME                     ;
}
