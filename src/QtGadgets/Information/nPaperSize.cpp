#include <qtgadgets.h>

N::PaperSize:: PaperSize(void)
{
}

N::PaperSize:: PaperSize (const PaperSize & paperSize)
{
  ME = paperSize ;
}

N::PaperSize::~PaperSize(void)
{
}

N::PaperSize & N::PaperSize::operator = (const PaperSize & p)
{
  nMemberCopy ( p , name      ) ;
  nMemberCopy ( p , uuid      ) ;
  nMemberCopy ( p , direction ) ;
  nMemberCopy ( p , width     ) ;
  nMemberCopy ( p , height    ) ;
  return ME                     ;
}

QRectF N::PaperSize::rect(int d)
{
  double w = width        ;
  double h = height       ;
  switch (d)              {
    case Qt::Vertical     :
      w = width           ;
      h = height          ;
    break                 ;
    case Qt::Horizontal   :
      h = width           ;
      w = height          ;
    break                 ;
  }                       ;
  w /= 10                 ;
  h /= 10                 ;
  return QRectF (0,0,w,h) ;
}
