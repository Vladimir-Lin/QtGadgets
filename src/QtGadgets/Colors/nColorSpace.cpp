#include <qtgadgets.h>

N::ColorSpace:: ColorSpace(void)
{
}

N::ColorSpace::~ColorSpace(void)
{
}

QColor N::ColorSpace::YUV(double Y,double U,double V)
{
  ColorYUV C(Y,U,V)  ;
  return C . toRgb() ;
}

QColor N::ColorSpace::YIQ(double Y,double I,double Q)
{
  ColorYIQ C(Y,I,Q)  ;
  return C . toRgb() ;
}

QColor N::ColorSpace::XYZ(double X,double Y,double Z)
{
  ColorXYZ C(X,Y,Z)  ;
  return C . toRgb() ;
}

QColor N::ColorSpace::Lab(double L,double a,double b)
{
  ColorLab C(L,a,b)  ;
  return C . toRgb() ;
}

QColor N::ColorSpace::LUV(double L,double U,double V)
{
  ColorLUV C(L,U,V)  ;
  return C . toRgb() ;
}

void N::ColorSpace::DrawHSV(QImage & image,Colors & colors,double V)
{
  int w = image . width  ( ) - 1         ;
  int h = image . height ( ) - 1         ;
  int x                                  ;
  int y                                  ;
  for (int i=0;i<colors.count();i++)     {
    QColor hsv (QColor((QRgb)colors[i])) ;
    double H = hsv.hsvHueF       ()      ;
    double S = hsv.hsvSaturationF()      ;
    QColor c                             ;
    c . setHsvF(H,S,V)                   ;
    H *= w                               ;
    S *= h                               ;
    x  = (int)H                          ;
    y  = (int)S                          ;
    if (x>w) x = w                       ;
    if (y>h) y = h                       ;
    image.setPixel(x,y,c.rgb())          ;
  }                                      ;
}

void N::ColorSpace::DrawHSL(QImage & image,Colors & colors,double L)
{
  int w = image . width  ( ) - 1         ;
  int h = image . height ( ) - 1         ;
  int x                                  ;
  int y                                  ;
  for (int i=0;i<colors.count();i++)     {
    QColor hsv (QColor((QRgb)colors[i])) ;
    double H = hsv.hslHueF       ()      ;
    double S = hsv.hslSaturationF()      ;
    QColor c                             ;
    c . setHslF(H,S,L)                   ;
    H *= w                               ;
    S *= h                               ;
    x  = (int)H                          ;
    y  = (int)S                          ;
    if (x>w) x = w                       ;
    if (y>h) y = h                       ;
    image.setPixel(x,y,c.rgb())          ;
  }                                      ;
}

// Y [  0.000000 ,  1.000000 ]
// I [ -0.595716 ,  0.595716 ] 1.191432
// Q [ -0.522591 ,  0.522591 ] 1.045182
void N::ColorSpace::DrawYIQ(QImage & image,Colors & colors,double Y)
{
  int w = image . width  ( ) - 1          ;
  int h = image . height ( ) - 1          ;
  int x                                   ;
  int y                                   ;
  for (int i=0;i<colors.count();i++)      {
    QColor   rgb((QRgb)colors[i])         ;
    ColorYIQ yiq(rgb            )         ;
    ColorYIQ hiq(Y,yiq.I,yiq.Q  )         ;
    QColor    c = hiq.toRgb()             ;
    double I = yiq.I                      ;
    double Q = yiq.Q                      ;
    I -= -0.595716                        ;
    I /= 1.191432                         ;
    I *= w                                ;
    Q -= -0.522591                        ;
    Q /= 1.045182                         ;
    Q *= h                                ;
    x  = (int)I                           ;
    y  = (int)Q                           ;
    if (x>w) x = w                        ;
    if (y>h) y = h                        ;
    image.setPixel(x,y,c.rgb())           ;
  }                                       ;
}

// Y [  0.000 ,  1.000 ]
// U [ -0.436 ,  0.436 ] 0.872
// V [ -0.615 ,  0.615 ] 1.230
void N::ColorSpace::DrawYUV(QImage & image,Colors & colors,double Y)
{
  int w = image . width  ( ) - 1          ;
  int h = image . height ( ) - 1          ;
  int x                                   ;
  int y                                   ;
  for (int i=0;i<colors.count();i++)      {
    QColor   rgb((QRgb)colors[i])         ;
    ColorYUV yuv(rgb            )         ;
    ColorYUV huv(Y,yuv.U,yuv.V  )         ;
    QColor    c = huv.toRgb()             ;
    double U = yuv.U                      ;
    double V = yuv.V                      ;
    U -= -0.436                           ;
    U /=  0.872                           ;
    U *= w                                ;
    V -= -0.615                           ;
    V /= 1.230                            ;
    V *= h                                ;
    x  = (int)U                           ;
    y  = (int)V                           ;
    if (x>w) x = w                        ;
    if (y>h) y = h                        ;
    image.setPixel(x,y,c.rgb())           ;
  }                                       ;
}

// L [    0.0000 , 100.0000 ]
// a [ - 86.1846 ,  98.2542 ] 184.4388
// b [ -107.8640 ,  94.4825 ] 202.3465
void N::ColorSpace::DrawLab(QImage & image,Colors & colors,double L)
{
  int w = image . width  ( ) - 1          ;
  int h = image . height ( ) - 1          ;
  int x                                   ;
  int y                                   ;
  for (int i=0;i<colors.count();i++)      {
    QColor   rgb((QRgb)colors[i])         ;
    ColorLab lab(rgb            )         ;
    ColorLab hab(L,lab.a,lab.a  )         ;
    QColor    c = hab.toRgb()             ;
    double a = lab.a                      ;
    double b = lab.b                      ;
    a -= - 86.1846                        ;
    a /=  184.4388                        ;
    a *= w                                ;
    b -= -107.8640                        ;
    b /=  202.3465                        ;
    b *= h                                ;
    x  = (int)a                           ;
    y  = (int)b                           ;
    if (x>w) x = w                        ;
    if (y>h) y = h                        ;
    image.setPixel(x,y,c.rgb())           ;
  }                                       ;
}

// L [   0.0000 , 100.0000 ]
// U [ -83.0798 , 175.0530 ] 258.1328
// V [ -21.0972 , 435.3520 ] 456.4492
void N::ColorSpace::DrawLUV(QImage & image,Colors & colors,double L)
{
  int w = image . width  ( ) - 1          ;
  int h = image . height ( ) - 1          ;
  int x                                   ;
  int y                                   ;
  for (int i=0;i<colors.count();i++)      {
    QColor   rgb((QRgb)colors[i])         ;
    ColorLUV luv(rgb            )         ;
    ColorLUV huv(L,luv.U,luv.V  )         ;
    QColor    c = huv.toRgb()             ;
    double U = luv.U                      ;
    double V = luv.V                      ;
    U -= - 83.0798                        ;
    U /=  258.1328                        ;
    U *= w                                ;
    V -= - 21.0972                        ;
    V /=  456.4492                        ;
    V *= h                                ;
    x  = (int)U                           ;
    y  = (int)V                           ;
    if (x>w) x = w                        ;
    if (y>h) y = h                        ;
    image.setPixel(x,y,c.rgb())           ;
  }                                       ;
}

bool N::ColorSpace::isSkin(QColor c)
{
  SkinColorI   ( I )                       ;
  SkinColorQ   ( Q )                       ;
  ColorYIQ yiq ( c )                       ;
  if (   yiq.Y < SkinColorY ) return false ;
  if ( ! I.Between(yiq.I)   ) return false ;
  if ( ! Q.Between(yiq.Q)   ) return false ;
  return true                              ;
}

UUIDs N::ColorSpace::SkinCounting(QImage & S,QImage & M)
{
  UUIDs U                                          ;
  if ( S . width  ( ) != M . width  ( ) ) return U ;
  if ( S . height ( ) != M . height ( ) ) return U ;
  SkinColorI ( I )                                 ;
  SkinColorQ ( Q )                                 ;
  SUID        colors = 0                           ;
  SUID        skins  = 0                           ;
  int         w      = M . width  ( )              ;
  int         h      = M . height ( )              ;
  for (int y=0;y<h;y++) for (int x=0;x<w;x++)      {
    QRgb rgb = M . pixel ( x, y )                  ;
    if ( rgb != 0 )                                {
      rgb = S . pixel ( x , y )                    ;
      colors ++                                    ;
      QColor   cyiq ( rgb  )                       ;
      ColorYIQ yiq  ( cyiq )                       ;
      if (   yiq. Y < SkinColorY ) continue        ;
      if ( ! I.Between(yiq.I)    ) continue        ;
      if ( ! Q.Between(yiq.Q)    ) continue        ;
      skins++                                      ;
    }                                              ;
  }                                                ;
  U << colors                                      ;
  U << skins                                       ;
  return U                                         ;
}
