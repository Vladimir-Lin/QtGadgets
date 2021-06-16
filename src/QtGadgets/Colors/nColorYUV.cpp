#include <qtgadgets.h>

N::ColorYUV:: ColorYUV (double y,double u,double v)
            : Y        (y                         )
            , U        (u                         )
            , V        (v                         )
{
}

N::ColorYUV:: ColorYUV (QColor & color)
            : Y        (0             )
            , U        (0             )
            , V        (0             )
{
  setRgb ( color ) ;
}

N::ColorYUV:: ColorYUV (void)
            : Y        (0   )
            , U        (0   )
            , V        (0   )
{
}

N::ColorYUV::ColorYUV (const ColorYUV & yuv)
{
  ME = yuv ;
}

N::ColorYUV::~ColorYUV (void)
{
}

N::ColorYUV & N::ColorYUV::operator = (const ColorYUV & yuv)
{
  Y = yuv.Y ;
  U = yuv.U ;
  V = yuv.V ;
  return ME ;
}

N::ColorYUV & N::ColorYUV::setRgb(QColor & color)
{
  double R = color . redF   ()                               ;
  double G = color . greenF ()                               ;
  double B = color . blueF  ()                               ;
  Y = (  0.29900 * R ) + (  0.58700 * G ) + (  0.11400 * B ) ;
  U = ( -0.14713 * R ) + ( -0.28886 * G ) + (  0.43600 * B ) ;
  V = (  0.61500 * R ) + ( -0.51499 * G ) + ( -0.10001 * B ) ;
  return (*this)                                             ;
}

QColor N::ColorYUV::toRgb(void)
{
  QColor C                                    ;
  double R                                    ;
  double G                                    ;
  double B                                    ;
  R = Y                    + (  1.13983 * V ) ; // R = Y + 1.13983 * V
  G = Y + ( -0.39465 * U ) + ( -0.58060 * V ) ; // G = Y - 0.39465 * U - 0.58060 * V
  B = Y + (  2.03211 * U )                    ; // B = Y + 2.03211 * U
  C . setRedF   ( R )                         ;
  C . setGreenF ( G )                         ;
  C . setBlueF  ( B )                         ;
  return C                                    ;
}
