#include <qtgadgets.h>

typedef struct    {
  double position ;
  int    R        ;
  int    G        ;
  int    B        ;
  int    A        ;
} nGradientPoint  ;

typedef struct                {
  int            Type         ;
  int            Spread       ;
  int            Coordinate   ;
  double         x1           ;
  double         y1           ;
  double         z1           ;
  double         x2           ;
  double         y2           ;
  double         z2           ;
  int            Size         ;
  nGradientPoint Points [256] ;
} nGradientConfiguration      ;

N::Gradient:: Gradient (enum QGradient::Type type)
            : gradient (NULL                     )
            , uuid     (0                        )
            , step     (0                        )
            , editable (true                     )
{
  switch (type)                                      {
    case QGradient::LinearGradient                   :
      gradient = (QGradient *)new QLinearGradient () ;
    break                                            ;
    case QGradient::RadialGradient                   :
      gradient = (QGradient *)new QRadialGradient () ;
    break                                            ;
    case QGradient::ConicalGradient                  :
      gradient = (QGradient *)new QConicalGradient() ;
    break                                            ;
    case QGradient::NoGradient                       :
    break                                            ;
  }                                                  ;
}

N::Gradient::~Gradient(void)
{
}

int N::Gradient::packsize(void)
{
  return sizeof(nGradientConfiguration) ;
}

QLinearGradient * N::Gradient::linear(void)
{
  if (IsNull(gradient)) return NULL                            ;
  if (gradient->type()!=QGradient::LinearGradient) return NULL ;
  return (QLinearGradient *)gradient                           ;
}

QRadialGradient * N::Gradient::radial(void)
{
  if (IsNull(gradient)) return NULL ;
  if (gradient->type()!=QGradient::RadialGradient) return NULL ;
  return (QRadialGradient *)gradient                           ;
}

QConicalGradient * N::Gradient::conical(void)
{
  if (IsNull(gradient)) return NULL ;
  if (gradient->type()!=QGradient::ConicalGradient) return NULL ;
  return (QConicalGradient *)gradient                           ;
}

QBrush N::Gradient::Brush(void)
{
  if (IsNull(gradient)) return QBrush() ;
  return QBrush ( *gradient )           ;
}

QByteArray N::Gradient::Configure(void)
{
  QByteArray conf                                                ;
  conf.resize(sizeof(nGradientConfiguration))                    ;
  nGradientConfiguration ngc                                     ;
  QLinearGradient  * LINEAR  = (QLinearGradient  *)gradient      ;
  QRadialGradient  * RADIAL  = (QRadialGradient  *)gradient      ;
  QConicalGradient * CONICAL = (QConicalGradient *)gradient      ;
  QPointF           P                                            ;
  memset ( &ngc , 0 , sizeof(nGradientConfiguration) )           ;
  ngc.Type       = (int)gradient->type           ( )             ;
  ngc.Spread     = (int)gradient->spread         ( )             ;
  ngc.Coordinate = (int)gradient->coordinateMode ( )             ;
  switch (ngc.Type)                                              {
    case QGradient::LinearGradient                               :
      P = LINEAR  -> start     ()                                ;
      ngc.x1 = P.x             ()                                ;
      ngc.y1 = P.y             ()                                ;
      P = LINEAR  -> finalStop ()                                ;
      ngc.x2 = P.x             ()                                ;
      ngc.y2 = P.y             ()                                ;
    break                                                        ;
    case QGradient::RadialGradient                               :
      P = RADIAL  -> center        ()                            ;
      ngc.x1 = P.x                 ()                            ;
      ngc.y1 = P.y                 ()                            ;
      ngc.z1 = RADIAL->radius      ()                            ;
      P = RADIAL  -> focalPoint    ()                            ;
      ngc.x2 = P.x                 ()                            ;
      ngc.y2 = P.y                 ()                            ;
      ngc.z2 = RADIAL->focalRadius ()                            ;
    break                                                        ;
    case QGradient::ConicalGradient                              :
      P = CONICAL -> center   ()                                 ;
      ngc.x1 = P.x            ()                                 ;
      ngc.y1 = P.y            ()                                 ;
      ngc.z1 = CONICAL->angle ()                                 ;
    break                                                        ;
    case QGradient::NoGradient                                   :
    break                                                        ;
  }                                                              ;
  QGradientStops gs = gradient->stops()                          ;
  int total = gs.count()                                         ;
  if (total>256) total = 256                                     ;
  ngc.Size = total                                               ;
  for (int i=0;i<total;i++)                                      {
    QGradientStop s = gs [i]                                     ;
    double g = s.first                                           ;
    QColor c = s.second                                          ;
    ngc.Points[i].position = g                                   ;
    ngc.Points[i].R        = c . red   ()                        ;
    ngc.Points[i].G        = c . green ()                        ;
    ngc.Points[i].B        = c . blue  ()                        ;
    ngc.Points[i].A        = c . alpha ()                        ;
  }                                                              ;
  memcpy ( conf.data() , &ngc , sizeof(nGradientConfiguration) ) ;
  return     conf                                                ;
}

void N::Gradient::setConfigure(QByteArray & conf)
{
  if (conf.size()!=sizeof(nGradientConfiguration)) return                      ;
  nGradientConfiguration * ngc = (nGradientConfiguration *)conf.data()         ;
  QLinearGradient  * LINEAR  = NULL                                            ;
  QRadialGradient  * RADIAL  = NULL                                            ;
  QConicalGradient * CONICAL = NULL                                            ;
  switch (ngc->Type)                                                           {
    case QGradient::LinearGradient                                             :
      LINEAR   = new QLinearGradient  ()                                       ;
      LINEAR  -> setSpread        ((QGradient::Spread        )ngc->Spread    ) ;
      LINEAR  -> setCoordinateMode((QGradient::CoordinateMode)ngc->Coordinate) ;
      LINEAR  -> setStart     (ngc->x1,ngc->y1)                                ;
      LINEAR  -> setFinalStop (ngc->x2,ngc->y2)                                ;
      gradient = (QGradient *)LINEAR                                           ;
    break                                                                      ;
    case QGradient::RadialGradient                                             :
      RADIAL   = new QRadialGradient  ()                                       ;
      RADIAL  -> setSpread        ((QGradient::Spread        )ngc->Spread    ) ;
      RADIAL  -> setCoordinateMode((QGradient::CoordinateMode)ngc->Coordinate) ;
      gradient = (QGradient *)RADIAL                                           ;
      RADIAL  -> setCenter      (ngc->x1,ngc->y1)                              ;
      RADIAL  -> setRadius      (ngc->z1        )                              ;
      RADIAL  -> setFocalPoint  (ngc->x1,ngc->y1)                              ;
      RADIAL  -> setFocalRadius (ngc->z1        )                              ;
    break                                                                      ;
    case QGradient::ConicalGradient                                            :
      CONICAL  = new QConicalGradient ()                                       ;
      CONICAL -> setSpread        ((QGradient::Spread        )ngc->Spread    ) ;
      CONICAL -> setCoordinateMode((QGradient::CoordinateMode)ngc->Coordinate) ;
      CONICAL -> setCenter        (ngc->x1,ngc->y1)                            ;
      CONICAL -> setAngle         (ngc->z1        )                            ;
      gradient = (QGradient *)CONICAL                                          ;
    break                                                                      ;
    case QGradient::NoGradient                                                 :
      gradient = NULL                                                          ;
    break                                                                      ;
  }                                                                            ;
  if (IsNull(gradient)) return                                                 ;
  int total = ngc->Size                                                        ;
  for (int i=0;i<total;i++)                                                    {
    nGradientPoint GP = ngc->Points[i]                                         ;
    QColor c(GP.R,GP.G,GP.B,GP.A)                                              ;
    gradient->setColorAt(GP.position,c)                                        ;
  }                                                                            ;
}

QByteArray N::Gradient::toCpp(void)
{
  QByteArray cpp ;
  return cpp     ;
}
