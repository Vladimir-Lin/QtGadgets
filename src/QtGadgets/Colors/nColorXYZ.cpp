#include <qtgadgets.h>

N::ColorXYZ:: ColorXYZ (double x,double y,double z)
            : X        (x                         )
            , Y        (y                         )
            , Z        (z                         )
{
}

N::ColorXYZ:: ColorXYZ (QColor & color)
            : X        (0             )
            , Y        (0             )
            , Z        (0             )
{
  setRgb ( color ) ;
}

N::ColorXYZ:: ColorXYZ (void)
            : X        (0   )
            , Y        (0   )
            , Z        (0   )
{
}

N::ColorXYZ::ColorXYZ (const ColorXYZ & xyz)
{
  ME = xyz ;
}

N::ColorXYZ::~ColorXYZ (void)
{
}

N::ColorXYZ & N::ColorXYZ::operator = (const ColorXYZ & xyz)
{
  X = xyz.X ;
  Y = xyz.Y ;
  Z = xyz.Z ;
  return ME ;
}

double N::ColorXYZ::Gamma(double v)
{
  double g                                                 ;
  if ( v > 0.04045 ) g = pow ( (v + 0.055) / 1.055 , 2.4 ) ;
                else g = v / 12.92                         ;
  return g                                                 ;
}

double N::ColorXYZ::invertGamma(double r)
{
  double g                                                        ;
  if ( r > 0.0031308) g = ( 1.055 * pow ( r , 1.0/2.4 ) ) - 0.055 ;
                 else g = 12.92 * r                               ;
  return g                                                        ;
}

N::ColorXYZ & N::ColorXYZ::setRgb(QColor & color)
{
  double R = Gamma( color . redF   () )                ;
  double G = Gamma( color . greenF () )                ;
  double B = Gamma( color . blueF  () )                ;
  X = ( 0.4124 * R ) + ( 0.3576 * G ) + ( 0.1805 * B ) ;
  Y = ( 0.2126 * R ) + ( 0.7152 * G ) + ( 0.0722 * B ) ;
  Z = ( 0.0193 * R ) + ( 0.1192 * G ) + ( 0.9505 * B ) ;
  return (*this)                                       ;
}

QColor N::ColorXYZ::toRgb(void)
{
  QColor C                                                ;
  double R                                                ;
  double G                                                ;
  double B                                                ;
  R = (  3.2406 * X ) + ( -1.5372 * Y ) + ( -0.4986 * Z ) ;
  G = ( -0.9689 * X ) + (  1.8758 * Y ) + (  0.0415 * Z ) ;
  B = (  0.0557 * X ) + ( -0.2040 * Y ) + (  1.0570 * Z ) ;
  C . setRedF   ( invertGamma ( R ) )                     ;
  C . setGreenF ( invertGamma ( G ) )                     ;
  C . setBlueF  ( invertGamma ( B ) )                     ;
  return C                                                ;
}
