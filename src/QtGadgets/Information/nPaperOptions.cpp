#include <qtgadgets.h>

N::PaperOptions:: PaperOptions (void        )
                : current      (-1          )
                , direction    (Qt::Vertical)
{
}

N::PaperOptions:: PaperOptions(const PaperOptions & options)
{
  ME = options ;
}

N::PaperOptions::~PaperOptions(void)
{
}

N::PaperOptions & N::PaperOptions::operator = (const PaperOptions & options)
{
  nMemberCopy ( options , current   ) ;
  nMemberCopy ( options , direction ) ;
  nMemberCopy ( options , papers    ) ;
  return ME                           ;
}
