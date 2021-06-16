#include <qtgadgets.h>

N::ColorYIQ:: ColorYIQ (double y,double i,double q)
            : Y        (y                         )
            , I        (i                         )
            , Q        (q                         )
{
}

N::ColorYIQ:: ColorYIQ (QColor & color)
            : Y        (0             )
            , I        (0             )
            , Q        (0             )
{
  setRgb ( color ) ;
}

N::ColorYIQ:: ColorYIQ (void)
            : Y        (0   )
            , I        (0   )
            , Q        (0   )
{
}

N::ColorYIQ::ColorYIQ (const ColorYIQ & yiq)
{
  ME = yiq ;
}

N::ColorYIQ::~ColorYIQ (void)
{
}

N::ColorYIQ & N::ColorYIQ::operator = (const ColorYIQ & yiq)
{
  Y = yiq.Y ;
  I = yiq.I ;
  Q = yiq.Q ;
  return ME ;
}

N::ColorYIQ & N::ColorYIQ::setRgb(QColor & color)
{
  double R = color . redF   ()                                  ;
  double G = color . greenF ()                                  ;
  double B = color . blueF  ()                                  ;
  Y = (  0.299000 * R ) + (  0.587000 * G ) + (  0.114000 * B ) ;
  I = (  0.595716 * R ) + ( -0.274453 * G ) + ( -0.321263 * B ) ;
  Q = (  0.211456 * R ) + ( -0.522591 * G ) + (  0.311135 * B ) ;
  return (*this)                                                ;
}

QColor N::ColorYIQ::toRgb(void)
{
  QColor C                                  ;
  double R                                  ;
  double G                                  ;
  double B                                  ;
  R = Y + (  0.9563 * I ) + (  0.6210 * Q ) ;
  G = Y + ( -0.2721 * I ) + ( -0.6474 * Q ) ;
  B = Y + ( -1.1070 * I ) + (  1.7046 * Q ) ;
  C . setRedF   ( R )                       ;
  C . setGreenF ( G )                       ;
  C . setBlueF  ( B )                       ;
  return C                                  ;
}
