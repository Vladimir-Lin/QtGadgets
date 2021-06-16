#include <qtgadgets.h>

N::ChartPainter:: ChartPainter(void)
{
  font    . setFamily    ( "verdana" ) ;
  font    . setPixelSize ( 15        ) ;
  ctype   = Dpie                       ;
  cltype  = Vertical                   ;
  cX      = 0                          ;
  cY      = 0                          ;
  cW      = 100                        ;
  cH      = 100                        ;
  lX      = cX + cW + 20               ;
  lY      = cY                         ;
  shadows = true                       ;
}

N::ChartPainter::~ChartPainter(void)
{
  pieces . clear ( ) ;
}

int N::ChartPainter::addPiece(QString name,Qt::GlobalColor color,float percentage)
{
  ChartPiece piece                      ;
  nPiece++                              ;
  piece  . addName       ( name       ) ;
  piece  . setColor      ( color      ) ;
  piece  . setPercentage ( percentage ) ;
  pieces . append        ( piece      ) ;
  return 0                              ;
}

int N::ChartPainter::addPiece(QString name,QColor color,float percentage)
{
  ChartPiece piece                      ;
  nPiece++                              ;
  piece  . addName       ( name       ) ;
  piece  . setColor      ( color      ) ;
  piece  . setPercentage ( percentage ) ;
  pieces . append        ( piece      ) ;
  return 0                              ;
}

int N::ChartPainter::setCords(double x, double y, double w, double h)
{
  cX = x            ;
  cY = y            ;
  cW = w            ;
  cH = h            ;
  lX = cX + cW + 20 ;
  lY = cY           ;
  return 0          ;
}

int N::ChartPainter::setLegendCords(double x, double y)
{
  lX = x   ;
  lY = y   ;
  return 0 ;
}

int N::ChartPainter::setType(N::ChartPainter::type t)
{
  ctype = t ;
  return 0  ;
}

int N::ChartPainter::setLegendType(legend t)
{
  cltype = t ;
  return 0   ;
}
int N::ChartPainter::setFont(QFont f)
{
  font = f ;
  return 0 ;
}

int N::ChartPainter::setShadows(bool ok)
{
  shadows = ok ;
  return 0     ;
}

int N::ChartPainter::draw(QPainter * painter)
{
  painter -> setRenderHint ( QPainter :: Antialiasing )        ;
  painter -> setPen        ( Qt       :: NoPen        )        ;
  if (this->ctype==N::ChartPainter::Pie)                       {
    double pdegree = 0                                         ;
    pW             = 0                                         ;
    //Options
    QLinearGradient gradient(cX+0.5*cW,cY,cX+0.5*cW,cY+cH*2.5) ;
    gradient.setColorAt(1,Qt::black)                           ;
    //Draw
    //pdegree = (360/100)*pieces[i].pPerc;
    if (shadows)                                               {
      double sumangle = 0                                      ;
      for (int i=0;i<pieces.size();i++)                        {
        sumangle += 3.6*pieces[i].Percentage                   ;
      }                                                        ;
      painter->setBrush(Qt::darkGray)                          ;
      painter->drawPie (cX,cY+pW+5,cW,cH,alpha*16,sumangle*16) ;
    }                                                          ;
    ////////////////////////////////////////////////////////////
    QPen pen                                                   ;
    pen.setWidth(2)                                            ;
    for (int i=0;i<pieces.size();i++)                          {
      gradient.setColorAt(0,pieces[i].Color)                   ;
      painter->setBrush(gradient)                              ;
      pen.setColor(pieces[i].Color)                            ;
      painter->setPen(pen)                                     ;
      pdegree = 3.6*pieces[i].Percentage                       ;
      painter->drawPie(cX,cY,cW,cH,alpha*16,pdegree*16)        ;
      alpha += pdegree                                         ;
    }                                                          ;
  } else
  if (this->ctype==N::ChartPainter::Dpie)                      {
    double  pdegree = 0                                        ;
    QPointF p                                                  ;
    pW = 50                                                    ;
    ////////////////////////////////////////////////////////////
    QLinearGradient gradient(cX-0.5*cW,cY+cH/2,cX+1.5*cW,cY+cH/2);
    gradient.setColorAt(0,Qt::black)                           ;
    gradient.setColorAt(1,Qt::white)                           ;
    QLinearGradient gradient_side(cX,cY+cH,cX+cW,cY+cH)        ;
    gradient_side.setColorAt(0,Qt::black)                      ;
    ////////////////////////////////////////////////////////////
    double sumangle = 0                                        ;
    for (int i=0;i<pieces.size();i++)                          {
      sumangle += 3.6*pieces[i].Percentage                     ;
    }                                                          ;
    if (shadows)                                               {
      painter->setBrush(Qt::darkGray)                          ;
      painter->drawPie(cX,cY+pW+5,cW,cH,alpha*16,sumangle*16)  ;
    }                                                          ;
    ////////////////////////////////////////////////////////////
    int q = GetQuater(alpha+sumangle)                          ;
    if (q ==2 || q==3)                                         {
      QPointF p         = GetPoint(alpha+sumangle)             ;
      QPointF points[4] =                                      {
        QPointF ( p.x()   , p.y()      )                       ,
        QPointF ( p.x()   , p.y()+pW   )                       ,
        QPointF ( cX+cW/2 , cY+cH/2+pW )                       ,
        QPointF ( cX+cW/2 , cY+cH/2    )                     } ;
      gradient_side.setColorAt(1,pieces[pieces.size()-1].Color);
      painter->setBrush(gradient_side)                         ;
      painter->drawPolygon(points,4)                           ;
    }                                                          ;
    ////////////////////////////////////////////////////////////
    p = GetPoint  ( alpha )                                    ;
    q = GetQuater ( alpha )                                    ;
    if (q ==1 || q==4)                                         {
      QPointF points[4] =                                      {
        QPointF ( p.x()   , p.y()      )                       ,
        QPointF ( p.x()   , p.y()  +pW )                       ,
        QPointF ( cX+cW/2 , cY+cH/2+pW )                       ,
        QPointF ( cX+cW/2 , cY+cH/2    )                     } ;
      gradient_side.setColorAt(1,pieces[0].Color)              ;
      painter->setBrush(gradient_side)                         ;
      painter->drawPolygon(points,4)                           ;
    }                                                          ;
    ////////////////////////////////////////////////////////////
    for (int i=0;i<pieces.size();i++)                          {
      gradient.setColorAt(0.5,pieces[i].Color)                 ;
      painter->setBrush(gradient)                              ;
      pdegree = 3.6*pieces[i].Percentage                       ;
      painter->drawPie(cX,cY,cW,cH,alpha*16,pdegree*16)        ;
      double a_ = Angle360  ( alpha )                          ;
      int    q_ = GetQuater ( alpha )                          ;
      alpha += pdegree                                         ;
      double a  = Angle360  ( alpha )                          ;
      int    q  = GetQuater ( alpha )                          ;
      QPainterPath path                                        ;
      p = GetPoint ( alpha )                                   ;
      if ((q == 3 || q == 4) && (q_ == 3 || q_ == 4))          {
        if ( a > a_ )                                          {
          QPointF p_old = GetPoint(alpha-pdegree)              ;
          path.moveTo(p_old.x()-1,p_old.y())                   ;
          path.arcTo(cX,cY,cW,cH,alpha-pdegree,pdegree)        ;
          path.lineTo(p.x(),p.y()+pW)                          ;
          path.arcTo(cX,cY+pW,cW,cH,alpha,-pdegree)            ;
        } else                                                 {
          path.moveTo(cX,cY+cH/2)                              ;
          path.arcTo(cX,cY,cW,cH,180,Angle360(alpha)-180)      ;
          path.lineTo(p.x(),p.y()+pW)                          ;
          path.arcTo(cX,cY+pW,cW,cH,Angle360(alpha),-Angle360(alpha)+180);
          path.lineTo(cX,cY+cH/2)                              ;
          path.moveTo(p.x(),p.y())                             ;
          path.arcTo(cX,cY,cW,cH,alpha-pdegree,360-Angle360(alpha-pdegree));
          path.lineTo(cX+cW,cY+cH/2+pW)                        ;
          path.arcTo(cX,cY+pW,cW,cH,0,-360+Angle360(alpha-pdegree));
        }                                                      ;
      } else
      if ((q == 3 || q == 4) && (q_ == 1 || q_ == 2) && a>a_ ) {
        path.moveTo(cX,cY+cH/2)                                ;
        path.arcTo(cX,cY,cW,cH,180,Angle360(alpha)-180)        ;
        path.lineTo(p.x(),p.y()+pW)                            ;
        path.arcTo(cX,cY+pW,cW,cH,Angle360(alpha),-Angle360(alpha)+180);
        path.lineTo(cX,cY+cH/2)                                ;
      } else
      if ((q == 1 || q == 2) && (q_ == 3 || q_ == 4) && a<a_)  {
        p = GetPoint(alpha-pdegree)                            ;
        path.moveTo(p.x(),p.y())                               ;
        path.arcTo(cX,cY,cW,cH,alpha-pdegree,360-Angle360(alpha-pdegree));
        path.lineTo(cX+cW,cY+cH/2+pW)                          ;
        path.arcTo(cX,cY+pW,cW,cH,0,-360+Angle360(alpha-pdegree));
      } else
      if ((q ==1 || q==2) && (q_==1 || q_==2) && a<a_)         {
        path . moveTo (cX   ,cY+cH/2           )               ;
        path . arcTo  (cX   ,cY,cW,cH,180,180  )               ;
        path . lineTo (cX+cW,cY+cH/2+pW        )               ;
        path . arcTo  (cX   ,cY+pW,cW,cH,0,-180)               ;
        path . lineTo (cX   ,cY+cH/2           )               ;
      }                                                        ;
      //////////////////////////////////////////////////////////
      if (!path.isEmpty())                                     {
        gradient_side.setColorAt(1,pieces[i].Color)            ;
        painter->setBrush(gradient_side)                       ;
        painter->drawPath(path)                                ;
      }                                                        ;
    }                                                          ;
  } else
  if (this->ctype==N::ChartPainter::Histogramm)                {
    double pDist = 15                                          ;
    double pW    = (cW-(pieces.size())*pDist)/pieces.size()    ;
    ////////////////////////////////////////////////////////////
    QLinearGradient gradient(cX+cW/2,cY,cX+cW/2,cY+cH)         ;
    gradient.setColorAt(0,Qt::black)                           ;
    QPen pen                                                   ;
    pen.setWidth(3)                                            ;
    ////////////////////////////////////////////////////////////
    for (int i=0;i<pieces.size();i++)                          {
      if (shadows)                                             {
        painter->setPen  (Qt::NoPen   )                        ;
        painter->setBrush(Qt::darkGray)                        ;
        painter->drawRect(cX+pDist+i*(pW + pDist)-pDist/2,cY+cH-1,pW,-cH/100*pieces[i].Percentage+pDist/2-5) ;
      }                                                        ;
      gradient.setColorAt(1,pieces[i].Color);
      painter->setBrush(gradient);
      pen.setColor(pieces[i].Color);
      painter->setPen(pen);
      painter->drawRect(cX+pDist+i*(pW + pDist),cY+cH,pW,-cH/100*pieces[i].Percentage-5);
      QString label = QString::number(pieces[i].Percentage)+"%";
      painter->setPen(Qt::SolidLine);
      painter->drawText(cX+pDist+i*(pW + pDist)+pW/2-painter->fontMetrics().width(label)/2,cY+cH-cH/100*pieces[i].Percentage-painter->fontMetrics().height()/2,label);
    }                                                          ;
    ////////////////////////////////////////////////////////////
    painter->setPen(Qt::SolidLine)                             ;
    for (int i=1;i<10;i++)                                     {
      painter->drawLine(cX-3,cY+cH/10*i,cX+3,cY+cH/10*i)       ;
      //painter->drawText(cX-20,cY+cH/10*i,QString::number((10-i)*10)+"%");
    }                                                          ;
    painter->drawLine(cX,cY+cH,cX,cY      )                    ;
    painter->drawLine(cX,cY,cX+4,cY+10    )                    ;
    painter->drawLine(cX,cY,cX-4,cY+10    )                    ;
    painter->drawLine(cX,cY+cH,cX+cW,cY+cH)                    ;
  }                                                            ;
  return 0                                                     ;
}

int N::ChartPainter::drawLegend(QPainter * painter)
{
  //double ptext = 25;
  double angle = alpha ;
  painter->setPen(Qt::SolidLine)                           ;
  //////////////////////////////////////////////////////////
  switch ( cltype )                                        {
    /*case N::ChartPainter::Horizontal:
    {
        int dist = 5;
        painter->setBrush(Qt::white);
        float x = cX;
        float y = cY+cH+20+dist;
        //painter->drawRoundRect(cX+cW+20,cY,dist*2+200,pieces.size()*(fontmetr.height()+2*dist)+dist,15,15);
        for (int i=0;i<pieces.size();i++)
        {
            painter->setBrush(pieces[i].rgbColor);
            x += fontmetr.height()+2*dist;
            if (i%3 == 0)
            {
                x = cX;
                y += dist+fontmetr.height();
            }
            painter->drawRect(x,y,fontmetr.height(),fontmetr.height());
            QString label = pieces[i].pname + " - " + QString::number(pieces[i].pPerc)+"%";
            painter->drawText(x+fontmetr.height()+dist,y+fontmetr.height()/2+dist,label);
            x += fontmetr.width(label);
        }
        break;
    }*/
    case N::ChartPainter::Vertical:
      {
        int dist = 5;
        painter->setBrush(Qt::white);
        //painter->drawRoundRect(cX+cW+20,cY,dist*2+200,pieces.size()*(painter->fontMetrics().height()+2*dist)+dist,15,15);
        for (int i=pieces.size()-1;i>=0;i--)      {
          painter->setBrush(pieces[i].Color);
          float x = lX+dist;
          float y = lY+dist+i*(painter->fontMetrics().height()+2*dist);
          painter->drawRect(x,y,painter->fontMetrics().height(),painter->fontMetrics().height());
          painter->drawText(x+painter->fontMetrics().height()+dist,y+painter->fontMetrics().height()/2+dist,pieces[i].Name + " - " + QString::number(pieces[i].Percentage)+"%") ;
        }
      }
    break;
    case N::ChartPainter::Round:
        for (int i=pieces.size()-1;i>=0;i--)
        {
            float len = 100;
            double pdegree = 3.6*pieces[i].Percentage;
            angle -= pdegree/2;
            QPointF p = GetPoint(angle);
            QPointF p_ = GetPoint(angle, cW+len,cH+len);
            int q = GetQuater(angle);
            if (q == 3 || q == 4)
            {
                p.setY(p.y()+pW/2);
                p_.setY(p_.y()+pW/2);
            }
            painter->drawLine(p.x(),p.y(),p_.x(),p_.y());
            QString label = pieces[i].Name + " - " + QString::number(pieces[i].Percentage)+"%";
            float recW = painter->fontMetrics().width(label)+10;
            float recH = painter->fontMetrics().height()+10;
            p_.setX(p_.x()-recW/2 + recW/2*cos(angle*M_PI/180));
            p_.setY(p_.y()+recH/2 + recH/2*sin(angle*M_PI/180));
            painter->setBrush(Qt::white);
            painter->drawRoundRect(p_.x() ,p_.y(), recW, -recH);
            painter->drawText(p_.x()+5, p_.y()-recH/2+5, label);
            angle -= pdegree/2;
         }
        break;
  }                      ;
  return cltype ;
}

QPointF N::ChartPainter::GetPoint(double angle, double R1, double R2)
{
  if (R1 == 0 && R2 == 0)                          {
    R1 = cW                                        ;
    R2 = cH                                        ;
  }                                                ;
  QPointF point                                    ;
  double x =  R1/2*cos(angle*M_PI/180); x+=cW/2+cX ;
  double y = -R2/2*sin(angle*M_PI/180); y+=cH/2+cY ;
  point . setX ( x )                               ;
  point . setY ( y )                               ;
  return point                                     ;
}

int N::ChartPainter::GetQuater(double angle)
{
  angle = Angle360(angle)               ;
  if (angle>=  0 && angle< 90) return 1 ;
  if (angle>= 90 && angle<180) return 2 ;
  if (angle>=180 && angle<270) return 3 ;
  if (angle>=270 && angle<360) return 4 ;
  return 0                              ;
}

double N::ChartPainter::Angle360(double angle)
{
  int    i     = (int)angle ;
  double delta = angle - i  ;
  return (i%360 + delta)    ;
}
