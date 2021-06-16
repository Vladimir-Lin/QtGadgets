#include <qtgadgets.h>

N::ColorLUV:: ColorLUV (double l,double u,double v)
            : L        (l                         )
            , U        (u                         )
            , V        (v                         )
{
}

N::ColorLUV:: ColorLUV (ColorXYZ & XYZ)
            : L        (0             )
            , U        (0             )
            , V        (0             )
{
  setXYZ ( XYZ ) ;
}

N::ColorLUV:: ColorLUV (QColor & color)
            : L        (0             )
            , U        (0             )
            , V        (0             )
{
  setRgb ( color ) ;
}

N::ColorLUV:: ColorLUV (void)
            : L        (0   )
            , U        (0   )
            , V        (0   )
{
}

N::ColorLUV:: ColorLUV (const ColorLUV & luv)
{
  ME = luv ;
}

N::ColorLUV::~ColorLUV (void)
{
}

N::ColorLUV & N::ColorLUV::operator = (const ColorLUV & luv)
{
  L = luv.L ;
  U = luv.U ;
  V = luv.V ;
  return ME ;
}

N::ColorLUV & N::ColorLUV::setXYZ(ColorXYZ & XYZ)
{
  double X = XYZ.X                               ; // 0.95047
  double Y = XYZ.Y                               ; // 1.00000 , Yd = Y / Yn
  double Z = XYZ.Z                               ; // 1.08883
  double S                                       ;
  double u                                       ;
  double v                                       ;
  double un                                      ;
  double vn                                      ;
  if ( Y > 0.008856 )                            { // ( 116 * ( Yd ^ (1/3) ) ) - 16
    L = ( 116.0 * pow ( Y , 1.0 / 3.0 ) ) - 16.0 ;
  } else                                         {
    L = ( 24389.0 / 27.0 ) * Y                   ; // Yd * ( ( 29 / 3 ) ^ 3 )
  }                                              ;
  S  = X + ( 15.0 * Y ) + ( 3 * Z )              ;
  if (nEqual(S,0))                               {
    U = 0.0                                      ;
    V = 0.0                                      ;
  } else                                         {
    u  = ( 4 * X ) / S                           ; // u = 4X / ( X + 15Y + 3Z)
    v  = ( 9 * Y ) / S                           ; // v = 9Y / ( X + 15Y + 3Z)
    S  = 0.95047 + 15.0 + ( 3 * 1.08883 )        ;
    un = ( 4 * 0.95047 ) / S                     ;
    vn =   4             / S                     ;
    S  = 13.0 * L                                ;
    U  = S    * ( u - un )                       ;
    V  = S    * ( v - vn )                       ;
  }                                              ;
  return (*this)                                 ;
}

N::ColorXYZ N::ColorLUV::toXYZ(void)
{
  ColorXYZ XYZ                                                       ;
  double S = 13 * L                                                  ;
  double u = ( U / S )                                               ;
  double v = ( V / S )                                               ;
  double un                                                          ;
  double vn                                                          ;
  S  = 0.95047 + 15.0 + ( 3 * 1.08883 )                              ;
  un = ( 4 * 0.95047 ) / S                                           ;
  vn =   4             / S                                           ;
  u += un                                                            ;
  v += vn                                                            ;
  if ( L > 8.0 ) XYZ.Y = pow ( (L + 16.0) / 116.0 , 3.0 )            ;
            else XYZ.Y = L * ( 27.0 / 24389.0           )            ;
  XYZ.X = XYZ.Y * 2.25 * u / v                                       ;
  XYZ.Z = XYZ.Y * (12.0 - ( 3.0 * u ) - ( 20.0 * v ) ) / ( 4.0 * v ) ;
  return XYZ                                                         ;
}

N::ColorLUV & N::ColorLUV::setRgb(QColor & color)
{
  ColorXYZ XYZ  ( color ) ;
  return setXYZ ( XYZ   ) ;
}

QColor N::ColorLUV::toRgb(void)
{
  ColorXYZ XYZ = toXYZ ( ) ;
  return XYZ.toRgb     ( ) ;
}
