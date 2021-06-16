#include <qtgadgets.h>

typedef struct        {
  int  R              ;
  int  G              ;
  int  B              ;
  int  A              ;
  int  Style          ;
  int  Size           ;
  char Extra[4]       ;
} nBrushConfiguration ;

N::Brush:: Brush    (void)
         : QBrush   (    )
         , uuid     (0   )
         , editable (true)
{
}

N::Brush:: Brush  (Qt::BrushStyle style)
         : QBrush (               style)
         , uuid   (0                   )
{
}

N::Brush:: Brush  (const QColor & color, Qt::BrushStyle style)
         : QBrush (               color,                style)
         , uuid   (0                                         )
{
}

N::Brush:: Brush  (Qt::GlobalColor color,Qt::BrushStyle style)
         : QBrush (                color,               style)
         , uuid   (0                                         )
{
}

N::Brush:: Brush  (const QColor & color,const QPixmap & pixmap)
         : QBrush (               color,                pixmap)
         , uuid   (0                                          )
{
}

N::Brush:: Brush  (Qt::GlobalColor color,const QPixmap & pixmap)
         : QBrush (                color,                pixmap)
         , uuid   (0                                           )
{
}

N::Brush:: Brush  (const QPixmap & pixmap)
         : QBrush (                pixmap)
         , uuid   (0                     )
{
}

N::Brush:: Brush  (const QImage & image)
         : QBrush (               image)
         , uuid   (0                   )
{
}

N::Brush:: Brush  (const QBrush & other)
         : QBrush (               other)
         , uuid   (0                   )
{
}

N::Brush:: Brush  (const QGradient & gradient)
         : QBrush (                  gradient)
         , uuid   (0                         )
{
}

N::Brush::~Brush (void)
{
}

int N::Brush::packsize(void)
{
  return sizeof(nBrushConfiguration) ;
}

QByteArray N::Brush::Configure(void)
{
  QByteArray conf                                             ;
  conf.resize(sizeof(nBrushConfiguration))                    ;
  nBrushConfiguration nbc                                     ;
  QColor c = color()                                          ;
  memset ( &nbc , 0 , sizeof(nBrushConfiguration) )           ;
  nbc.R     = c.red      ( )                                  ;
  nbc.G     = c.green    ( )                                  ;
  nbc.B     = c.blue     ( )                                  ;
  nbc.A     = c.alpha    ( )                                  ;
  nbc.Style = (int)style ( )                                  ;
  nbc.Size  = 0                                               ;
  memcpy ( conf.data() , &nbc , sizeof(nBrushConfiguration) ) ;
  return     conf                                             ;
}

void N::Brush::setConfigure(QByteArray & conf)
{
  if (conf.size()!=sizeof(nBrushConfiguration)) return           ;
  nBrushConfiguration * nbc = (nBrushConfiguration *)conf.data() ;
  QColor c ( nbc->R,nbc->G,nbc->B,nbc->A )                       ;
  setColor ( c                           )                       ;
  setStyle ( (Qt::BrushStyle)nbc->Style  )                       ;
}

QByteArray N::Brush::toCpp(void)
{
  QByteArray     cpp                       ;
  QColor         c = color ( )             ;
  Qt::BrushStyle s = style ( )             ;
  QString        C                         ;
  C = QString ( "%1,%2,%3,%4"              )
      . arg ( c.red  ()                    )
      . arg ( c.green()                    )
      . arg ( c.blue ()                    )
      . arg ( c.alpha()                  ) ;
  cpp.append( "nBrush("                  ) ;
  cpp.append( "QColor("                  ) ;
  cpp.append( C . toUtf8 ( )             ) ;
  cpp.append( "),Qt::"                   ) ;
  switch (s)                               {
    case Qt::NoBrush                       :
      cpp.append("NoBrush")                ;
    break                                  ;
    case Qt::SolidPattern                  :
      cpp.append("SolidPattern")           ;
    break                                  ;
    case Qt::Dense1Pattern                 :
      cpp.append("Dense1Pattern")          ;
    break                                  ;
    case Qt::Dense2Pattern                 :
      cpp.append("Dense2Pattern")          ;
    break                                  ;
    case Qt::Dense3Pattern                 :
      cpp.append("Dense3Pattern")          ;
    break                                  ;
    case Qt::Dense4Pattern                 :
      cpp.append("Dense4Pattern")          ;
    break                                  ;
    case Qt::Dense5Pattern                 :
      cpp.append("Dense5Pattern")          ;
    break                                  ;
    case Qt::Dense6Pattern                 :
      cpp.append("Dense6Pattern")          ;
    break                                  ;
    case Qt::Dense7Pattern                 :
      cpp.append("Dense7Pattern")          ;
    break                                  ;
    case Qt::HorPattern                    :
      cpp.append("HorPattern")             ;
    break                                  ;
    case Qt::VerPattern                    :
      cpp.append("VerPattern")             ;
    break                                  ;
    case Qt::CrossPattern                  :
      cpp.append("CrossPattern")           ;
    break                                  ;
    case Qt::BDiagPattern                  :
      cpp.append("BDiagPattern")           ;
    break                                  ;
    case Qt::FDiagPattern                  :
      cpp.append("FDiagPattern")           ;
    break                                  ;
    case Qt::DiagCrossPattern              :
      cpp.append("DiagCrossPattern")       ;
    break                                  ;
    case Qt::LinearGradientPattern         :
      cpp.append("LinearGradientPattern" ) ;
    break                                  ;
    case Qt::ConicalGradientPattern        :
      cpp.append("ConicalGradientPattern") ;
    break                                  ;
    case Qt::RadialGradientPattern         :
      cpp.append("RadialGradientPattern" ) ;
    break                                  ;
    case Qt::TexturePattern                :
      cpp.append("TexturePattern")         ;
    break                                  ;
  }                                        ;
  cpp.append( ") ;"                      ) ;
  return cpp                               ;
}
