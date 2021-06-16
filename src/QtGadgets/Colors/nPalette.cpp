#include <qtgadgets.h>

N::Palette:: Palette     (void              )
           : QByteArray  (sizeof(QRgb)*256,0)
           , TotalColors (0                 )
{
}

N::Palette:: Palette     (const Palette & palette)
           : QByteArray  (sizeof(QRgb)*256,0     )
           , TotalColors (0                      )
{
  ME = palette ;
}

N::Palette::~Palette (void)
{
}

N::Palette & N::Palette::operator = (const Palette & palette)
{
  int t = palette.size()                              ;
  resize ( t         )                                ;
  unsigned char * a = (unsigned char *)palette.data() ;
  unsigned char * b = (unsigned char *)        data() ;
  memcpy ( b , a , t )                                ;
  TotalColors = palette.TotalColors                   ;
  return ME                                           ;
}

QVector<QRgb> N::Palette::colors(void)
{
  QRgb * d = (QRgb *)data()                             ;
  QVector<QRgb> colormaps                               ;
  for (int ii=0;ii<TotalColors;ii++) colormaps << d[ii] ;
  return colormaps                                      ;
}

int N::Palette::toColors(Colors & colors)
{
  QRgb * d = (QRgb *)data()          ;
  for (int ii=0;ii<TotalColors;ii++) {
    colors << (unsigned int)d[ii]    ;
  }                                  ;
  return colors.count()              ;
}

void N::Palette::set(Colors & colors)
{
  QRgb * d = (QRgb *)data()                      ;
  int    e = colors.count()                      ;
  TotalColors  = e                               ;
  if (e>256) e = 256                             ;
  for (int ii=0;ii<256;ii++) d[ii] = qRgb(0,0,0) ;
  QList<unsigned int> CM                         ;
  for (int ii=0;ii<e;ii++) CM << colors[ii]      ;
  qSort(CM.begin(),CM.end())                     ;
  for (int ii=0;ii<e;ii++) d[ii] = CM[ii]        ;
}

void N::Palette::set(QVector<QRgb> colormaps)
{
  QRgb * d = (QRgb *)data()                      ;
  int    e = colormaps.count()                   ;
  TotalColors = e                                ;
  if (e<=0 ) return                              ;
  if (e>256) e = 256                             ;
  for (int ii=0;ii<256;ii++) d[ii] = qRgb(0,0,0) ;
  QList<unsigned int> CM                         ;
  for (int ii=0;ii<e;ii++) CM << colormaps[ii]   ;
  if (e>1) qSort(CM.begin(),CM.end())            ;
  for (int ii=0;ii<e;ii++) d[ii] = CM[ii]        ;
}

QByteArray N::Palette::Compress(void)
{
  QByteArray c        ;
  c = qCompress(ME,9) ;
  return c            ;
}

bool N::Palette::Uncompress(QByteArray & unc)
{
  QByteArray c = qUncompress(unc)               ;
  if (c.size()==size())                         {
    char * t = data()                           ;
    char * f = c.data()                         ;
    memcpy(t,f,sizeof(QRgb)*256)                ;
    TotalColors = size() / sizeof(unsigned int) ;
    return true                                 ;
  } else return false                           ;
}

void N::Palette::set(QImage & image)
{
  QImage * I = new QImage();
  *I = image.convertToFormat(QImage::Format_Indexed8,Qt::ThresholdDither);
  set(I->colorTable());
  delete I;
  I = NULL;
}

unsigned long long N::Palette::sigma(void)
{
  QRgb *             d = (QRgb *)data() ;
  unsigned long long s = 0              ;
  int                R = 0              ;
  int                G = 0              ;
  int                B = 0              ;
  int                A = 0              ;
  for (int ii=0;ii<TotalColors;ii++)    {
    A += qAlpha (d[ii])                 ;
    R += qRed   (d[ii])                 ;
    G += qGreen (d[ii])                 ;
    B += qBlue  (d[ii])                 ;
  }                                     ;
  s  = (A & 0xFFFF); s <<= 16           ;
  s |= (R & 0xFFFF); s <<= 16           ;
  s |= (G & 0xFFFF); s <<= 16           ;
  s |= (B & 0xFFFF)                     ;
  return s                              ;
}

int N::Palette::total(void) const
{
  return TotalColors;
}

void N::Palette::setTotal(int Total)
{
  TotalColors = Total ;
}

QImage N::Palette::Image(void)
{
  QRgb * d = (QRgb *)data()                      ;
  QImage I(QSize(128,128),QImage::Format_ARGB32) ;
  QPainter p                                     ;
  p . begin      ( &I                  )         ;
  p . setPen     ( QColor(255,255,255) )         ;
  p . setBrush   ( QColor(255,255,255) )         ;
  p . drawRect   ( 0,0,128,128         )         ;
  for (int ii=0;ii<TotalColors;ii++)             {
    int x = ii % 16 ; x *= 8                     ;
    int y = ii / 16 ; y *= 8                     ;
    QColor c(d[ii])                              ;
    p . setPen   ( c                   )         ;
    p . setBrush ( c                   )         ;
    p . drawRect ( x , y , 8 , 8       )         ;
  }                                              ;
  p . end        (                     )         ;
  return I                                       ;
}
