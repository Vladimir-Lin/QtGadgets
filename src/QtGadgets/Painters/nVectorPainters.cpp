#include <qtgadgets.h>

int N::toPathes(Vector & vector,QPainterPath & path)
{
  int total = vector.count()                  ;
  if (total<=0) return 0                      ;
  void * aa = vector.array()                  ;
  switch  ( vector . Type ( ) )               {
    case Cpp::Char                            :
      if (total>0)                            {
        char * v = (char *)aa                 ;
        path.moveTo(0,v[0])                   ;
        for (int i=1;i<total;i++)             {
          path.lineTo(i,v[i])                 ;
        }                                     ;
      }                                       ;
    break                                     ;
    case Cpp::Byte                            :
      if (total>0)                            {
        char * v = (char *)aa                 ;
        path.moveTo(0,v[0])                   ;
        for (int i=1;i<total;i++)             {
          path.lineTo(i,v[i])                 ;
        }                                     ;
      }                                       ;
    break                                     ;
    case Cpp::Short                           :
      if (total>0)                            {
        short * v = (short *)aa               ;
        path.moveTo(0,v[0])                   ;
        for (int i=1;i<total;i++)             {
          path.lineTo(i,v[i])                 ;
        }                                     ;
      }                                       ;
    break                                     ;
    case Cpp::UShort                          :
      if (total>0)                            {
        ushort * v = (ushort *)aa             ;
        path.moveTo(0,v[0])                   ;
        for (int i=1;i<total;i++)             {
          path.lineTo(i,v[i])                 ;
        }                                     ;
      }                                       ;
    break                                     ;
    case Cpp::Integer                         :
      if (total>0)                            {
        int * v = (int *)aa                   ;
        path.moveTo(0,v[0])                   ;
        for (int i=1;i<total;i++)             {
          path.lineTo(i,v[i])                 ;
        }                                     ;
      }                                       ;
    break                                     ;
    case Cpp::UInt                            :
      if (total>0)                            {
        unsigned int * v = (unsigned int *)aa ;
        path.moveTo(0,v[0])                   ;
        for (int i=1;i<total;i++)             {
          path.lineTo(i,v[i])                 ;
        }                                     ;
      }                                       ;
    break                                     ;
    case Cpp::LongLong                        :
      if (total>0)                            {
        TUID * v = (TUID *)aa                 ;
        path.moveTo(0,v[0])                   ;
        for (int i=1;i<total;i++)             {
          path.lineTo(i,v[i])                 ;
        }                                     ;
      }                                       ;
    break                                     ;
    case Cpp::ULongLong                       :
      if (total>0)                            {
        SUID * v = (SUID *)aa                 ;
        path.moveTo(0,v[0])                   ;
        for (int i=1;i<total;i++)             {
          path.lineTo(i,v[i])                 ;
        }                                     ;
      }                                       ;
    break                                     ;
    case Cpp::Float                           :
      if (total>0)                            {
        float * v = (float *)aa               ;
        path.moveTo(0,v[0])                   ;
        for (int i=1;i<total;i++)             {
          path.lineTo(i,v[i])                 ;
        }                                     ;
      }                                       ;
    break                                     ;
    case Cpp::Double                          :
      if (total>0)                            {
        double * v = (double *)aa             ;
        path.moveTo(0,v[0])                   ;
        for (int i=1;i<total;i++)             {
          path.lineTo(i,v[i])                 ;
        }                                     ;
      }                                       ;
    break                                     ;
    case Cpp::LDouble                         :
      if (total>0)                            {
        long double * v = (long double *)aa   ;
        path.moveTo(0,v[0])                   ;
        for (int i=1;i<total;i++)             {
          path.lineTo(i,v[i])                 ;
        }                                     ;
      }                                       ;
    break                                     ;
    case Cpp::VLong                           :
    break                                     ;
    case Cpp::VDouble                         :
    break                                     ;
    case Cpp::Rational                        :
    break                                     ;
    case Cpp::Pointer                         :
    break                                     ;
  }                                           ;
  return vector . count ( )                   ;
}

int N::toPathes(Vector & vector,double factor,QPainterPath & path)
{
  int total = vector.count()                  ;
  if (total<=0) return 0                      ;
  void * aa = vector.array()                  ;
  switch  ( vector . Type ( ) )               {
    case Cpp::Char                            :
      if (total>0)                            {
        char * v = (char *)aa                 ;
        path.moveTo(0,v[0])                   ;
        for (int i=1;i<total;i++)             {
          double f = i                        ;
          f *= factor                         ;
          path.lineTo(f,v[i])                 ;
        }                                     ;
      }                                       ;
    break                                     ;
    case Cpp::Byte                            :
      if (total>0)                            {
        char * v = (char *)aa                 ;
        path.moveTo(0,v[0])                   ;
        for (int i=1;i<total;i++)             {
          double f = i                        ;
          f *= factor                         ;
          path.lineTo(f,v[i])                 ;
        }                                     ;
      }                                       ;
    break                                     ;
    case Cpp::Short                           :
      if (total>0)                            {
        short * v = (short *)aa               ;
        path.moveTo(0,v[0])                   ;
        for (int i=1;i<total;i++)             {
          double f = i                        ;
          f *= factor                         ;
          path.lineTo(f,v[i])                 ;
        }                                     ;
      }                                       ;
    break                                     ;
    case Cpp::UShort                          :
      if (total>0)                            {
        ushort * v = (ushort *)aa             ;
        path.moveTo(0,v[0])                   ;
        for (int i=1;i<total;i++)             {
          double f = i                        ;
          f *= factor                         ;
          path.lineTo(f,v[i])                 ;
        }                                     ;
      }                                       ;
    break                                     ;
    case Cpp::Integer                         :
      if (total>0)                            {
        int * v = (int *)aa                   ;
        path.moveTo(0,v[0])                   ;
        for (int i=1;i<total;i++)             {
          double f = i                        ;
          f *= factor                         ;
          path.lineTo(f,v[i])                 ;
        }                                     ;
      }                                       ;
    break                                     ;
    case Cpp::UInt                            :
      if (total>0)                            {
        unsigned int * v = (unsigned int *)aa ;
        path.moveTo(0,v[0])                   ;
        for (int i=1;i<total;i++)             {
          double f = i                        ;
          f *= factor                         ;
          path.lineTo(f,v[i])                 ;
        }                                     ;
      }                                       ;
    break                                     ;
    case Cpp::LongLong                        :
      if (total>0)                            {
        TUID * v = (TUID *)aa                 ;
        path.moveTo(0,v[0])                   ;
        for (int i=1;i<total;i++)             {
          double f = i                        ;
          f *= factor                         ;
          path.lineTo(f,v[i])                 ;
        }                                     ;
      }                                       ;
    break                                     ;
    case Cpp::ULongLong                       :
      if (total>0)                            {
        SUID * v = (SUID *)aa                 ;
        path.moveTo(0,v[0])                   ;
        for (int i=1;i<total;i++)             {
          double f = i                        ;
          f *= factor                         ;
          path.lineTo(f,v[i])                 ;
        }                                     ;
      }                                       ;
    break                                     ;
    case Cpp::Float                           :
      if (total>0)                            {
        float * v = (float *)aa               ;
        path.moveTo(0,v[0])                   ;
        for (int i=1;i<total;i++)             {
          double f = i                        ;
          f *= factor                         ;
          path.lineTo(f,v[i])                 ;
        }                                     ;
      }                                       ;
    break                                     ;
    case Cpp::Double                          :
      if (total>0)                            {
        double * v = (double *)aa             ;
        path.moveTo(0,v[0])                   ;
        for (int i=1;i<total;i++)             {
          double f = i                        ;
          f *= factor                         ;
          path.lineTo(f,v[i])                 ;
        }                                     ;
      }                                       ;
    break                                     ;
    case Cpp::LDouble                         :
      if (total>0)                            {
        long double * v = (long double *)aa   ;
        path.moveTo(0,v[0])                   ;
        for (int i=1;i<total;i++)             {
          double f = i                        ;
          f *= factor                         ;
          path.lineTo(f,v[i])                 ;
        }                                     ;
      }                                       ;
    break                                     ;
    case Cpp::VLong                           :
    break                                     ;
    case Cpp::VDouble                         :
    break                                     ;
    case Cpp::Rational                        :
    break                                     ;
    case Cpp::Pointer                         :
    break                                     ;
  }                                           ;
  return vector . count ( )                   ;
}

void N::PaintVector (QSizeF s,QPointF shift,Vector & vector,QPainter & p)
{
  int total = vector.count()                  ;
  if (total<=0) return                        ;
  void * aa = vector.array()                  ;
  switch  ( vector . Type ( ) )               {
    case Cpp::Char                            :
      if (total>0)                            {
        char * v = (char *)aa                 ;
        double x                              ;
        double y                              ;
        QPointF p1                            ;
        QPointF p2                            ;
        x  = 0                                ;
        y  = v[0]                             ;
        y *= s . height()                     ;
        p1 . setX ( x )                       ;
        p1 . setY ( y )                       ;
        p1 += shift                           ;
        for (int i=1;i<total;i++)             {
          x  = i                              ;
          x *= s . width ()                   ;
          y  = v[i]                           ;
          y *= s . height()                   ;
          p2 . setX ( x )                     ;
          p2 . setY ( y )                     ;
          p2 += shift                         ;
          p  . drawLine ( p1 , p2 )           ;
          p1  = p2                            ;
        }                                     ;
      }                                       ;
    break                                     ;
    case Cpp::Byte                            :
      if (total>0)                            {
        char * v = (char *)aa                 ;
        double x                              ;
        double y                              ;
        QPointF p1                            ;
        QPointF p2                            ;
        x  = 0                                ;
        y  = v[0]                             ;
        y *= s . height()                     ;
        p1 . setX ( x )                       ;
        p1 . setY ( y )                       ;
        p1 += shift                           ;
        for (int i=1;i<total;i++)             {
          x  = i                              ;
          x *= s . width ()                   ;
          y  = v[i]                           ;
          y *= s . height()                   ;
          p2 . setX ( x )                     ;
          p2 . setY ( y )                     ;
          p2 += shift                         ;
          p  . drawLine ( p1 , p2 )           ;
          p1  = p2                            ;
        }                                     ;
      }                                       ;
    break                                     ;
    case Cpp::Short                           :
      if (total>0)                            {
        short * v = (short *)aa               ;
        double x                              ;
        double y                              ;
        QPointF p1                            ;
        QPointF p2                            ;
        x  = 0                                ;
        y  = v[0]                             ;
        y *= s . height()                     ;
        p1 . setX ( x )                       ;
        p1 . setY ( y )                       ;
        p1 += shift                           ;
        for (int i=1;i<total;i++)             {
          x  = i                              ;
          x *= s . width ()                   ;
          y  = v[i]                           ;
          y *= s . height()                   ;
          p2 . setX ( x )                     ;
          p2 . setY ( y )                     ;
          p2 += shift                         ;
          p  . drawLine ( p1 , p2 )           ;
          p1  = p2                            ;
        }                                     ;
      }                                       ;
    break                                     ;
    case Cpp::UShort                          :
      if (total>0)                            {
        ushort * v = (ushort *)aa             ;
        double x                              ;
        double y                              ;
        QPointF p1                            ;
        QPointF p2                            ;
        x  = 0                                ;
        y  = v[0]                             ;
        y *= s . height()                     ;
        p1 . setX ( x )                       ;
        p1 . setY ( y )                       ;
        p1 += shift                           ;
        for (int i=1;i<total;i++)             {
          x  = i                              ;
          x *= s . width ()                   ;
          y  = v[i]                           ;
          y *= s . height()                   ;
          p2 . setX ( x )                     ;
          p2 . setY ( y )                     ;
          p2 += shift                         ;
          p  . drawLine ( p1 , p2 )           ;
          p1  = p2                            ;
        }                                     ;
      }                                       ;
    break                                     ;
    case Cpp::Integer                         :
      if (total>0)                            {
        int * v = (int *)aa                   ;
        double x                              ;
        double y                              ;
        QPointF p1                            ;
        QPointF p2                            ;
        x  = 0                                ;
        y  = v[0]                             ;
        y *= s . height()                     ;
        p1 . setX ( x )                       ;
        p1 . setY ( y )                       ;
        p1 += shift                           ;
        for (int i=1;i<total;i++)             {
          x  = i                              ;
          x *= s . width ()                   ;
          y  = v[i]                           ;
          y *= s . height()                   ;
          p2 . setX ( x )                     ;
          p2 . setY ( y )                     ;
          p2 += shift                         ;
          p  . drawLine ( p1 , p2 )           ;
          p1  = p2                            ;
        }                                     ;
      }                                       ;
    break                                     ;
    case Cpp::UInt                            :
      if (total>0)                            {
        unsigned int * v = (unsigned int *)aa ;
        double x                              ;
        double y                              ;
        QPointF p1                            ;
        QPointF p2                            ;
        x  = 0                                ;
        y  = v[0]                             ;
        y *= s . height()                     ;
        p1 . setX ( x )                       ;
        p1 . setY ( y )                       ;
        p1 += shift                           ;
        for (int i=1;i<total;i++)             {
          x  = i                              ;
          x *= s . width ()                   ;
          y  = v[i]                           ;
          y *= s . height()                   ;
          p2 . setX ( x )                     ;
          p2 . setY ( y )                     ;
          p2 += shift                         ;
          p  . drawLine ( p1 , p2 )           ;
          p1  = p2                            ;
        }                                     ;
      }                                       ;
    break                                     ;
    case Cpp::LongLong                        :
      if (total>0)                            {
        TUID * v = (TUID *)aa                 ;
        double x                              ;
        double y                              ;
        QPointF p1                            ;
        QPointF p2                            ;
        x  = 0                                ;
        y  = v[0]                             ;
        y *= s . height()                     ;
        p1 . setX ( x )                       ;
        p1 . setY ( y )                       ;
        p1 += shift                           ;
        for (int i=1;i<total;i++)             {
          x  = i                              ;
          x *= s . width ()                   ;
          y  = v[i]                           ;
          y *= s . height()                   ;
          p2 . setX ( x )                     ;
          p2 . setY ( y )                     ;
          p2 += shift                         ;
          p  . drawLine ( p1 , p2 )           ;
          p1  = p2                            ;
        }                                     ;
      }                                       ;
    break                                     ;
    case Cpp::ULongLong                       :
      if (total>0)                            {
        SUID * v = (SUID *)aa                 ;
        double x                              ;
        double y                              ;
        QPointF p1                            ;
        QPointF p2                            ;
        x  = 0                                ;
        y  = v[0]                             ;
        y *= s . height()                     ;
        p1 . setX ( x )                       ;
        p1 . setY ( y )                       ;
        p1 += shift                           ;
        for (int i=1;i<total;i++)             {
          x  = i                              ;
          x *= s . width ()                   ;
          y  = v[i]                           ;
          y *= s . height()                   ;
          p2 . setX ( x )                     ;
          p2 . setY ( y )                     ;
          p2 += shift                         ;
          p  . drawLine ( p1 , p2 )           ;
          p1  = p2                            ;
        }                                     ;
      }                                       ;
    break                                     ;
    case Cpp::Float                           :
      if (total>0)                            {
        float * v = (float *)aa               ;
        double x                              ;
        double y                              ;
        QPointF p1                            ;
        QPointF p2                            ;
        x  = 0                                ;
        y  = v[0]                             ;
        y *= s . height()                     ;
        p1 . setX ( x )                       ;
        p1 . setY ( y )                       ;
        p1 += shift                           ;
        for (int i=1;i<total;i++)             {
          x  = i                              ;
          x *= s . width ()                   ;
          y  = v[i]                           ;
          y *= s . height()                   ;
          p2 . setX ( x )                     ;
          p2 . setY ( y )                     ;
          p2 += shift                         ;
          p  . drawLine ( p1 , p2 )           ;
          p1  = p2                            ;
        }                                     ;
      }                                       ;
    break                                     ;
    case Cpp::Double                          :
      if (total>0)                            {
        double * v = (double *)aa             ;
        double x                              ;
        double y                              ;
        QPointF p1                            ;
        QPointF p2                            ;
        x  = 0                                ;
        y  = v[0]                             ;
        y *= s . height()                     ;
        p1 . setX ( x )                       ;
        p1 . setY ( y )                       ;
        p1 += shift                           ;
        for (int i=1;i<total;i++)             {
          x  = i                              ;
          x *= s . width ()                   ;
          y  = v[i]                           ;
          y *= s . height()                   ;
          p2 . setX ( x )                     ;
          p2 . setY ( y )                     ;
          p2 += shift                         ;
          p  . drawLine ( p1 , p2 )           ;
          p1  = p2                            ;
        }                                     ;
      }                                       ;
    break                                     ;
    case Cpp::LDouble                         :
      if (total>0)                            {
        long double * v = (long double *)aa   ;
        double x                              ;
        double y                              ;
        QPointF p1                            ;
        QPointF p2                            ;
        x  = 0                                ;
        y  = v[0]                             ;
        y *= s . height()                     ;
        p1 . setX ( x )                       ;
        p1 . setY ( y )                       ;
        p1 += shift                           ;
        for (int i=1;i<total;i++)             {
          x  = i                              ;
          x *= s . width ()                   ;
          y  = v[i]                           ;
          y *= s . height()                   ;
          p2 . setX ( x )                     ;
          p2 . setY ( y )                     ;
          p2 += shift                         ;
          p  . drawLine ( p1 , p2 )           ;
          p1  = p2                            ;
        }                                     ;
      }                                       ;
    break                                     ;
    case Cpp::VLong                           :
    break                                     ;
    case Cpp::VDouble                         :
    break                                     ;
    case Cpp::Rational                        :
    break                                     ;
    case Cpp::Pointer                         :
    break                                     ;
  }                                           ;
}
