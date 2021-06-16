#include <qtgadgets.h>

N::Screen:: Screen(void)
{
  Initialize();
}

N::Screen:: Screen(const Screen & screen)
{
  ME = screen ;
}

N::Screen::~Screen(void)
{
}

N::Screen & N::Screen::operator = (const Screen & screen)
{
  nMemberCopy ( screen , MonitorSize        ) ;
  nMemberCopy ( screen , HeightInCentimeter ) ;
  nMemberCopy ( screen , WidthInCentimeter  ) ;
  nMemberCopy ( screen , WidthPixels        ) ;
  nMemberCopy ( screen , WidthLength        ) ;
  nMemberCopy ( screen , HeightPixels       ) ;
  nMemberCopy ( screen , HeightLength       ) ;
  return ME                                   ;
}

void N::Screen::Initialize(void)
{
  #ifdef Q_OS_WIN
  if (NotNull(qApp))                                       {
    QRect rt           = qApp->desktop()->screenGeometry() ;
    MonitorSize        . setWidth  (rt.width ())           ;
    MonitorSize        . setHeight (rt.height())           ;
    WidthPixels        = rt.width()                        ;
    WidthLength        = qApp->desktop()->widthMM ()       ;
    WidthInCentimeter  = WidthLength                       ;
    WidthInCentimeter /= 10                                ;
    HeightPixels       = rt.height()                       ;
    HeightLength       = qApp->desktop()->heightMM()       ;
    HeightInCentimeter = HeightLength                      ;
    HeightInCentimeter/= 10                                ;
    MonitorFactors     = QSizeF ( 1.0 , 1.0 )              ;
  }                                                        ;
  #endif
  #ifdef Q_OS_LINUX
  if (NotNull(qApp))                                       {
    QRect rt           = qApp->desktop()->screenGeometry() ;
    MonitorSize        . setWidth  (rt.width ())           ;
    MonitorSize        . setHeight (rt.height())           ;
    WidthPixels        = rt.width()                        ;
    WidthLength        = qApp->desktop()->widthMM ()       ;
    WidthInCentimeter  = WidthLength                       ;
    WidthInCentimeter /= 10                                ;
    HeightPixels       = rt.height()                       ;
    HeightLength       = qApp->desktop()->heightMM()       ;
    HeightInCentimeter = HeightLength                      ;
    HeightInCentimeter/= 10                                ;
    MonitorFactors     = QSizeF ( 1.0 , 1.0 )              ;
  }                                                        ;
  #endif
  #ifdef Q_OS_MACX
  if (NotNull(qApp))                                       {
    QRect rt           = qApp->desktop()->screenGeometry() ;
    MonitorSize        . setWidth  (rt.width ())           ;
    MonitorSize        . setHeight (rt.height())           ;
    WidthPixels        = rt.width()                        ;
    WidthLength        = qApp->desktop()->widthMM ()       ;
    WidthInCentimeter  = WidthLength                       ;
    WidthInCentimeter /= 10                                ;
    HeightPixels       = rt.height()                       ;
    HeightLength       = qApp->desktop()->heightMM()       ;
    HeightInCentimeter = HeightLength                      ;
    HeightInCentimeter/= 10                                ;
    MonitorFactors     = QSizeF ( 1.0 , 1.0 )              ;
  }                                                        ;
  #endif
  #ifdef Q_OS_ANDROID
  if (NotNull(qApp))                                       {
    QRect rt           = qApp->desktop()->screenGeometry() ;
    MonitorSize        . setWidth  (rt.width ())           ;
    MonitorSize        . setHeight (rt.height())           ;
    WidthPixels        = rt.width()                        ;
    WidthLength        = qApp->desktop()->widthMM ()       ;
    WidthInCentimeter  = WidthLength                       ;
    WidthInCentimeter /= 10                                ;
    HeightPixels       = rt.height()                       ;
    HeightLength       = qApp->desktop()->heightMM()       ;
    HeightInCentimeter = HeightLength                      ;
    HeightInCentimeter/= 10                                ;
    MonitorFactors     = QSizeF ( 1.0 , 1.0 )              ;
  }                                                        ;
  #endif
  #ifdef Q_OS_IOS
  if (NotNull(qApp))                                       {
    QRect rt           = qApp->desktop()->screenGeometry() ;
    MonitorSize        . setWidth  (rt.width ())           ;
    MonitorSize        . setHeight (rt.height())           ;
    WidthPixels        = rt.width()                        ;
    WidthLength        = qApp->desktop()->widthMM ()       ;
    WidthInCentimeter  = WidthLength                       ;
    WidthInCentimeter /= 10                                ;
    HeightPixels       = rt.height()                       ;
    HeightLength       = qApp->desktop()->heightMM()       ;
    HeightInCentimeter = HeightLength                      ;
    HeightInCentimeter/= 10                                ;
    MonitorFactors     = QSizeF ( 1.0 , 1.0 )              ;
  }                                                        ;
  #endif
}

void N::Screen::setMonitor(qreal w,qreal h)
{
  WidthInCentimeter  = w ;
  HeightInCentimeter = h ;
}

QPoint N::Screen::position(qreal x,qreal y)
{
  QPoint pt                                                          ;
  pt.setX((int)(((qreal)MonitorSize.width ())*x/WidthInCentimeter )) ;
  pt.setY((int)(((qreal)MonitorSize.height())*y/HeightInCentimeter)) ;
  return pt                                                          ;
}

QSize N::Screen::dimension(qreal width,qreal height)
{
  QSize d                                                                     ;
  d.setWidth ((int)(((qreal)MonitorSize.width ())*width /WidthInCentimeter )) ;
  d.setHeight((int)(((qreal)MonitorSize.height())*height/HeightInCentimeter)) ;
  return d                                                                    ;
}

int N::Screen::widthPixels(int millimeters)
{
  long long w      ;
  w  = millimeters ;
  w *= WidthPixels ;
  w /= WidthLength ;
  return (int)w    ;
}

int N::Screen::heightPixels(int millimeters)
{
  long long h       ;
  h  = millimeters  ;
  h *= HeightPixels ;
  h /= HeightLength ;
  return (int)h     ;
}

qreal N::Screen::widthPixels(qreal millimeters)
{
  qreal w          ;
  w  = millimeters ;
  w *= WidthPixels ;
  w /= WidthLength ;
  return w         ;
}

qreal N::Screen::heightPixels(qreal millimeters)
{
  qreal h           ;
  h  = millimeters  ;
  h *= HeightPixels ;
  h /= HeightLength ;
  return h          ;
}

int N::Screen::widthLength(int pixels)
{
  long long w      ;
  w  = pixels      ;
  w *= WidthLength ;
  w /= WidthPixels ;
  return (int)w    ;
}

int N::Screen::heightLength(int pixels)
{
  long long h       ;
  h  = pixels       ;
  h *= HeightLength ;
  h /= HeightPixels ;
  return (int)h     ;
}

void N::Screen::Detect(void)
{
  QRect rt = qApp->desktop()->screenGeometry()              ;
  bool  wh = ( rt         .width() > rt         .height() ) ;
  bool  WH = ( MonitorSize.width() > MonitorSize.height() ) ;
  if ( wh != WH )                                           {
    Screen S                                                ;
    S . MonitorSize . setWidth  ( MonitorSize . height () ) ;
    S . MonitorSize . setHeight ( MonitorSize . width  () ) ;
    S . HeightInCentimeter = WidthInCentimeter              ;
    S . WidthInCentimeter  = HeightInCentimeter             ;
    S . WidthPixels        = HeightPixels                   ;
    S . WidthLength        = HeightLength                   ;
    S . HeightPixels       = WidthPixels                    ;
    S . HeightLength       = WidthLength                    ;
    ME = S                                                  ;
  }                                                         ;
}
