#include <qtgadgets.h>

N::StarTrekEdit:: StarTrekEdit     ( QWidget * parent             )
                : CalendarTimeEdit (           parent             )
                , validator        ( new StarTrekValidator (this) )
{
  setButtonSymbols ( QAbstractSpinBox::PlusMinus )                  ;
  setAccelerated   ( true                        )                  ;
  setStardate      ( StarDate::now()             )                  ;
  ///////////////////////////////////////////////////////////////////
  TimeZone    = 0                                                   ;
  ///////////////////////////////////////////////////////////////////
  Names [ 0 ] = tr("S.D."  )                                        ;
  Names [ 1 ] = tr("B.F."  )                                        ;
  ///////////////////////////////////////////////////////////////////
  nConnect         ( lineEdit() , SIGNAL ( textChanged(QString) )   ,
                     this       , SLOT   ( textChanged(QString) ) ) ;
}

N::StarTrekEdit::~StarTrekEdit(void)
{
}

QAbstractSpinBox::StepEnabled N::StarTrekEdit::stepEnabled(void) const
{
  return StepUpEnabled | StepDownEnabled ;
}

void N::StarTrekEdit::setRange(TimePeriod period)
{
  Range.L = period.L              ;
  Range.R = period.R              ;
  /////////////////////////////////
  QLineEdit * le = lineEdit ( )   ;
  if (IsNull(le)) return          ;
  int p = le->cursorPosition()    ;
  if (Range.L>0)                  {
    if (Range.L>Time.standard())  {
      Time . assign ( Range.L )   ;
      Time . locate (         )   ;
      setTimeText           (   ) ;
      le->setCursorPosition ( p ) ;
    }                             ;
  }                               ;
  if (Range.R>0)                  {
    if (Range.R<Time.standard())  {
      Time . assign ( Range.R )   ;
      Time . locate (         )   ;
      setTimeText           (   ) ;
      le->setCursorPosition ( p ) ;
    }                             ;
  }                               ;
}
TUID N::StarTrekEdit::currentStardate(void)
{
  return Time . standard ( ) ;
}

bool N::StarTrekEdit::setStardate(TUID sd)
{
  Time . assign ( sd ) ;
  Time . locate (    ) ;
  setTimeText   (    ) ;
  return true          ;
}

void N::StarTrekEdit::setTimeZone(int gmt)
{
  TimeZone = gmt ;
}

void N::StarTrekEdit::stepBy(int steps)
{
  QLineEdit * le = lineEdit ( )             ;
  if (IsNull(le)) return                    ;
  QString s                                 ;
  int     p                                 ;
  int     c                                 ;
  int     e                                 ;
  int     l                                 ;
  bool    epf                               ;
  ///////////////////////////////////////////
  p   = le -> cursorPosition (            ) ;
  s   = le -> text           (            ) ;
  l   = s   . length         (            ) ;
  ///////////////////////////////////////////
  epf = false                               ;
  e   = s . indexOf          ( Names[1]   ) ;
  if (e>=0)                                 {
    c = e + Names[1].length()               ;
    if (e<=p && p<c) epf = true             ;
  } else                                    {
    e = s . indexOf          ( Names[0]   ) ;
    if (e>=0)                               {
      c = e + Names[0].length()             ;
      if (e<=p && p<c) epf = true           ;
    }                                       ;
  }                                         ;
  if (epf && ( 0 == steps ) ) epf = false   ;
  if (epf)                                  {
    double sd = Time.Stardate()             ;
    Time . setStardate ( -sd )              ;
    Time . locate      (     )              ;
    epf = false                             ;
  } else
  if (c>0)                                  {
    epf = false                             ;
    e = c + 1                               ;
    while (e<l && s.at(e) == QChar(' '))    {
      e++                                   ;
    }                                       ;
    /////////////////////////////////////////
    c = s.indexOf(".",e)                    ;
    if (c>e)                                {
      epf = true                            ;
      if (e<=p && p<c)                      {
        double sd = Time.Stardate()         ;
        sd += steps                         ;
        Time . setStardate ( sd )           ;
        Time . locate      (    )           ;
        epf = false                         ;
      }                                     ;
    }                                       ;
    if (epf)                                {
      double sd = Time.Stardate()           ;
      double dt = steps                     ;
      dt /= 1000                            ;
      sd += dt                              ;
      Time . setStardate ( sd )             ;
      Time . locate      (    )             ;
      epf = false                           ;
    }                                       ;
    /////////////////////////////////////////
  }                                         ;
  ///////////////////////////////////////////
  setTimeText             (               ) ;
  le -> setCursorPosition ( p             ) ;
  emit Changed          ( Time.standard() ) ;
}

QValidator::State N::StarTrekEdit::validate (QString & input,int & pos) const
{
  return validator -> validate ( input , pos ) ;
}

void N::StarTrekEdit::setTimeText(void)
{
  QLineEdit * le = lineEdit ( )           ;
  if (IsNull(le)) return                  ;
  le -> blockSignals ( true             ) ;
  le -> setText      ( StarTrekString() ) ;
  le -> blockSignals ( false            ) ;
}

QString N::StarTrekEdit::StarTrekString(void)
{
  QString  t                                           ;
  double   sd                                          ;
  int      Y                                           ;
  int      M                                           ;
  sd = Time.Stardate()                                 ;
  if ( sd < 0 )                                        {
    t  =  Names [ 1 ]                                  ;
    sd = -sd                                           ;
  } else                                               {
    t  =  Names [ 0 ]                                  ;
  }                                                    ;
  Y   = (int)sd                                        ;
  sd -= Y                                              ;
  M   = (int)( sd * 100000 )                           ;
  t += " "                                             ;
  t += QString("%1.%2").arg(Y).arg(M,6,10,QChar('0') ) ;
  return t                                             ;
}

bool N::StarTrekEdit::madeChange(const QString & input)
{
  if (input.length()<=0) return false                   ;
  QString m                                             ;
  bool    bf    = false                                 ;
  bool    okay  = true                                  ;
  int     index = 0                                     ;
  ///////////////////////////////////////////////////////
  if (input.contains(Names[1]))                         { // check Before StarTrek Star Date
    m     = input.left(Names[1].length())               ;
    okay  = ( m == Names[1] )                           ;
    index = Names[1].length()                           ;
    bf    = true                                        ;
  } else
  ///////////////////////////////////////////////////////
  if (input.contains(Names[0]))                         { // check StarTrek Star Date
    m     = input.left(Names[0].length())               ;
    okay  = ( m == Names[0] )                           ;
    index = Names[0].length()                           ;
  } else okay = false                                   ;
  if ( ! okay ) return false                            ;
  ///////////////////////////////////////////////////////
  while ( index < input.length()                       &&
          input.at(index) == QChar(' ')               ) { // skip space
    ++index                                             ;
  }                                                     ;
  if ( index >= input.length() ) return false           ;
  ///////////////////////////////////////////////////////
  int         L = input.length()                        ;
  m = input.mid(index,L-index)                          ;
  if ( m.length() <= 0 ) return false                   ;
  ///////////////////////////////////////////////////////
  QStringList S = m.split('.')                          ;
  if ( S . count ( ) < 2 ) return false                 ;
  ///////////////////////////////////////////////////////
  for (int i=0;i<2;i++)                                 {
    okay = false                                        ;
    S[i].toInt(&okay)                                   ;
    if ( ! okay )  return false                         ;
  }                                                     ;
  ///////////////////////////////////////////////////////
  int    Y  = S[0].toInt()                              ;
  int    M  = S[1].toInt()                              ;
  double dt = M                                         ;
  dt /= 100000                                          ;
  dt += Y                                               ;
  if ( bf ) dt = -dt                                    ;
  Time . setStardate ( dt )                             ;
  Time . locate      (    )                             ;
  ///////////////////////////////////////////////////////
  return true                                           ;
}

void N::StarTrekEdit::textChanged(const QString & text)
{
  QLineEdit * le = lineEdit ( )    ;
  if (IsNull(le)) return           ;
  int p = le->cursorPosition()     ;
  if (!madeChange(text))           {
    setTimeText ( )                ;
    le->setCursorPosition ( p )    ;
    return                         ;
  }                                ;
  le -> setCursorPosition ( p )    ;
  emit Changed ( Time.standard() ) ;
}
