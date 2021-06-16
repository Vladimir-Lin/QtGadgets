#include <qtgadgets.h>

N::ColorLab:: ColorLab (double l,double A,double B)
            : L        (l                         )
            , a        (A                         )
            , b        (B                         )
{
}

N::ColorLab:: ColorLab (ColorXYZ & XYZ)
            : L        (0             )
            , a        (0             )
            , b        (0             )
{
  setXYZ ( XYZ ) ;
}

N::ColorLab:: ColorLab (QColor & color)
            : L        (0             )
            , a        (0             )
            , b        (0             )
{
  setRgb ( color ) ;
}

N::ColorLab:: ColorLab (void)
            : L        (0   )
            , a        (0   )
            , b        (0   )
{
}

N::ColorLab:: ColorLab (const ColorLab & lab)
{
  ME = lab ;
}

N::ColorLab::~ColorLab (void)
{
}

N::ColorLab & N::ColorLab::operator = (const ColorLab & lab)
{
  L = lab.L ;
  a = lab.a ;
  b = lab.b ;
  return ME ;
}

double N::ColorLab::Forward(double p)
{ // ( 6 / 29 ) ^ 3 ~ 0.008856
  if ( p > 0.008856 ) return pow     ( p , 1.0 /  3.0 ) ;
  return ( p * ( 841.0 / 108.0 ) ) + (     4.0 / 29.0 ) ;
}

double N::ColorLab::Reverse(double p)
{ // 3 * ( 6 / 29 ) * ( 6 / 29 ) = 3 * 36 / 841 = 108 / 841
  if ( p > ( 6.0 / 29.0 ) ) return p * p * p        ;
  return ( p - ( 4.0 / 29.0 ) ) * ( 108.0 / 841.0 ) ;
}

N::ColorLab & N::ColorLab::setXYZ(ColorXYZ & XYZ)
{
  // L = ( 116 * Forward(Y) ) - 16
  // a = 500 * [ Forward(X) - Forward(Y) ]
  // b = 200 * [ Forward(Y) - Forward(Z) ]
  double X = Forward(XYZ.X/0.95047) ; // 0.95047
  double Y = Forward(XYZ.Y        ) ; // 1.00000
  double Z = Forward(XYZ.Z/1.08883) ; // 1.08883
  L = ( 116 * Y ) - 16              ;
  a = 500 * ( X - Y )               ;
  b = 200 * ( Y - Z )               ;
  return ME                         ;
}

N::ColorXYZ N::ColorLab::toXYZ(void)
{
  ColorXYZ XYZ                    ;
  double Y = ( L + 16.0 ) / 116.0 ;
  double X = Y + ( a / 500.0 )    ;
  double Z = Y - ( b / 200.0 )    ;
  XYZ.X = Reverse(X) * 0.95047    ;
  XYZ.Y = Reverse(Y)              ;
  XYZ.Z = Reverse(Z) * 1.08883    ;
  return XYZ                      ;
}

N::ColorLab & N::ColorLab::setRgb(QColor & color)
{
  ColorXYZ XYZ  ( color ) ;
  return setXYZ ( XYZ   ) ;
}

QColor N::ColorLab::toRgb(void)
{
  ColorXYZ XYZ = toXYZ ( ) ;
  return XYZ.toRgb     ( ) ;
}
