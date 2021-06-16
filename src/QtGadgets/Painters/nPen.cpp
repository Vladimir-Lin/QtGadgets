#include <qtgadgets.h>

N::Pen:: Pen      (void)
       : QPen     (    )
       , uuid     (0   )
       , editable (true)
{
}

N::Pen:: Pen  (Qt::PenStyle style)
       : QPen (             style)
       , uuid (0                 )
{
}

N::Pen:: Pen  (const QColor & color)
       : QPen (               color)
       , uuid (0                   )
{
}

N::Pen:: Pen  (const QBrush & brush,qreal width,Qt::PenStyle style,Qt::PenCapStyle cap,Qt::PenJoinStyle join)
       : QPen (               brush,      width,             style,                cap,                 join)
       , uuid (0                                                                                            )
{
}

N::Pen:: Pen  (const QPen & pen)
       : QPen (             pen)
       , uuid (0               )
{
}

N::Pen::~Pen (void)
{
}

typedef struct      {
  double MiterLimit ;
  double WidthF     ;
  int    CapStyle   ;
  int    PenStyle   ;
  int    JoinStyle  ;
  int    Cosmetic   ;
  int    R          ;
  int    G          ;
  int    B          ;
  int    A          ;
  int    Size       ;
  char   Extra[4]   ;
} nPenConfiguration ;

int N::Pen::packsize(void)
{
  return sizeof(nPenConfiguration) ;
}

QByteArray N::Pen::Configure(void)
{
  QByteArray conf                                           ;
  conf.resize(sizeof(nPenConfiguration))                    ;
  nPenConfiguration npc                                     ;
  QColor c = color()                                        ;
  memset ( &npc , 0 , sizeof(nPenConfiguration) )           ;
  npc.MiterLimit = miterLimit    ()                         ;
  npc.WidthF     = widthF        ()                         ;
  npc.CapStyle   = (int)capStyle ()                         ;
  npc.PenStyle   = (int)style    ()                         ;
  npc.JoinStyle  = (int)joinStyle()                         ;
  npc.Cosmetic   = isCosmetic    () ? 1 : 0                 ;
  npc.R          = c.red         ()                         ;
  npc.G          = c.green       ()                         ;
  npc.B          = c.blue        ()                         ;
  npc.A          = c.alpha       ()                         ;
  npc.Size       = 0                                        ;
  memcpy ( conf.data() , &npc , sizeof(nPenConfiguration) ) ;
  return     conf                                           ;
}

void N::Pen::setConfigure(QByteArray & conf)
{
  if (conf.size()!=sizeof(nPenConfiguration)) return         ;
  nPenConfiguration * npc = (nPenConfiguration *)conf.data() ;
  QColor c(npc->R,npc->G,npc->B,npc->A)                      ;
  setColor      ( c                                )         ;
  setMiterLimit ( npc->MiterLimit                  )         ;
  setWidthF     ( npc->WidthF                      )         ;
  setCapStyle   ( (Qt::PenCapStyle )npc->CapStyle  )         ;
  setStyle      ( (Qt::PenStyle    )npc->PenStyle  )         ;
  setJoinStyle  ( (Qt::PenJoinStyle)npc->JoinStyle )         ;
  setCosmetic   ( npc->Cosmetic == 1               )         ;
}

QString N::Pen::Export(QString function)
{
  return "" ;
}
