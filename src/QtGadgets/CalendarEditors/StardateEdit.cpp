#include <qtgadgets.h>

N::StardateEdit:: StardateEdit     ( QWidget * parent               )
                : CalendarTimeEdit (           parent               )
                , validator        ( new StardateValidator ( this ) )
{
  setButtonSymbols    ( QAbstractSpinBox::PlusMinus                  ) ;
  setAccelerated      ( true                                         ) ;
  setKeyboardTracking ( true                                         ) ;
  setStardate         ( StarDate::now()                              ) ;
  nConnect            ( lineEdit() , SIGNAL ( textChanged(QString) )   ,
                        this       , SLOT   ( textChanged(QString) ) ) ;
}

N::StardateEdit::~StardateEdit(void)
{
}

QAbstractSpinBox::StepEnabled N::StardateEdit::stepEnabled(void) const
{
  return StepUpEnabled | StepDownEnabled ;
}

void N::StardateEdit::setRange(TimePeriod period)
{
  Range.L = period.L              ;
  Range.R = period.R              ;
  /////////////////////////////////
  QLineEdit * le = lineEdit ( )   ;
  if (IsNull(le)) return          ;
  int p = le->cursorPosition()    ;
  if (Range.L>0)                  {
    if (Range.L>Stardate)         {
      Stardate = Range.L          ;
      setTimeText           (   ) ;
      le->setCursorPosition ( p ) ;
    }                             ;
  }                               ;
  if (Range.R>0)                  {
    if (Range.R<Stardate)         {
      Stardate = Range.R          ;
      setTimeText           (   ) ;
      le->setCursorPosition ( p ) ;
    }                             ;
  }                               ;
}

TUID N::StardateEdit::currentStardate(void)
{
  return Stardate ;
}

bool N::StardateEdit::setStardate(TUID sd)
{
  Stardate  = sd  ;
  setTimeText ( ) ;
  return true     ;
}

void N::StardateEdit::setTimeZone(int gmt)
{ Q_UNUSED ( gmt ) ;
}

void N::StardateEdit::stepBy(int steps)
{
  QLineEdit * le = lineEdit ( )        ;
  if (IsNull(le)) return               ;
  QString s                            ;
  int     p                            ;
  int     c                            ;
  int     e                            ;
  int     l                            ;
  //////////////////////////////////////
  p = le -> cursorPosition (     )     ;
  s = le -> text           (     )     ;
  l = s . length           (     )     ;
  c = s . indexOf          ( ' ' )     ;
  //////////////////////////////////////
  if (p<0) return                      ;
  if (c<0) return                      ;
  if (c>p)                             {
    Stardate += ( steps * 86400 )      ;
  } else                               {
    while (c<l && s.at(c)==QChar(' ')) {
      c++                              ;
    }                                  ;
    if (c>=l) return                   ;
    if (c> p) return                   ;
    e = c                              ;
    c = s.indexOf(':',e)               ;
    if (c<0) return                    ;
    if (c>p)                           {
      Stardate += ( steps * 3600 )     ;
    } else                             {
      c++                              ;
      e = c                            ;
      c = s.indexOf(':',e)             ;
      if (c<0) return                  ;
      if (c>p)                         {
        Stardate += ( steps * 60 )     ;
      } else                           {
        c++                            ;
        e = c                          ;
        if (p>e)                       {
          Stardate += steps            ;
        }                              ;
      }                                ;
    }                                  ;
  }                                    ;
  //////////////////////////////////////
  setTimeText             (          ) ;
  le -> setCursorPosition ( p        ) ;
  emit Changed            ( Stardate ) ;
}

QValidator::State N::StardateEdit::validate (QString & input,int & pos) const
{
  return validator -> validate ( input , pos ) ;
}

void N::StardateEdit::setTimeText(void)
{
  QLineEdit * le = lineEdit ( ) ;
  if (IsNull(le)) return        ;
  QString n                     ;
  QString s                     ;
  TUID    d = Stardate / 86400  ;
  TUID    t = Stardate % 86400  ;
  int     S = t % 60            ;
  int     M = ( t / 60 ) % 60   ;
  int     H = t / 3600          ;
  n = QString::number ( d     ) ;
  s = QString ( "%1:%2:%3"      )
      . arg (H,2,10,QChar('0')  )
      . arg (M,2,10,QChar('0')  )
      . arg (S,2,10,QChar('0')) ;
  n = n + " " + s               ;
  le -> blockSignals  ( true  ) ;
  le -> setText       ( n     ) ;
  le -> blockSignals  ( false ) ;
}

bool N::StardateEdit::madeChange(const QString & text)
{
  QStringList T = text.split(' ') ;
  if (T.count()!=2) return false  ;
  QStringList D = T[1].split(':') ;
  if (D.count()!=3) return false  ;
  bool ok = false                 ;
  TUID x[4]                       ;
  TUID v                          ;
  D . prepend ( T[0] )            ;
  for (int i=0;i<D.count();i++)   {
    ok  = false                   ;
    x[i] = D[i].toLongLong(&ok)   ;
    if (!ok)   return false       ;
  }                               ;
  if (x[1]< 0) return false       ;
  if (x[1]>23) return false       ;
  if (x[2]< 0) return false       ;
  if (x[2]>59) return false       ;
  if (x[3]< 0) return false       ;
  if (x[3]>59) return false       ;
  x[1]    *= 3600                 ;
  x[2]    *=   60                 ;
  v        = x[0]                 ;
  v       *= 86400                ;
  v       += x[1]                 ;
  v       += x[2]                 ;
  v       += x[3]                 ;
  if (Range.L>0)                  {
    if (Range.L<v)                {
      v        = Range.L          ;
      Stardate = v                ;
      setTimeText ( )             ;
    }                             ;
  }                               ;
  if (Range.R>0)                  {
    if (Range.R>v)                {
      v        = Range.R          ;
      Stardate = v                ;
      setTimeText ( )             ;
    }                             ;
  }                               ;
  Stardate = v                    ;
  return true                     ;
}

void N::StardateEdit::textChanged(const QString & text)
{
  QLineEdit * le = lineEdit ( ) ;
  if (IsNull(le)) return        ;
  int p = le->cursorPosition()  ;
  if (!madeChange(text))        {
    setTimeText ( )             ;
    le->setCursorPosition ( p ) ;
    return                      ;
  }                             ;
  le -> setCursorPosition ( p ) ;
  emit Changed ( Stardate )     ;
}
