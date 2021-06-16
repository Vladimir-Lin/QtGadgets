#include <qtgadgets.h>

N::GeogrianEdit:: GeogrianEdit     ( QWidget * parent             )
                : CalendarTimeEdit (           parent             )
                , validator        ( new GeogrianValidator (this) )
{
  setButtonSymbols ( QAbstractSpinBox::PlusMinus )                  ;
  setAccelerated   ( true                        )                  ;
  setStardate      ( StarDate::now()             )                  ;
  ///////////////////////////////////////////////////////////////////
  TimeZone    = 0                                                   ;
  ///////////////////////////////////////////////////////////////////
  Names [ 0 ] = tr ( "C.E."     )                                   ;
  Names [ 1 ] = tr ( "B.C."     )                                   ;
  Names [ 2 ] = tr ( " year "   )                                   ;
  Names [ 3 ] = tr ( " month "  )                                   ;
  Names [ 4 ] = tr ( " day"     )                                   ;
  Names [ 5 ] = tr ( " hour "   )                                   ;
  Names [ 6 ] = tr ( " minute " )                                   ;
  Names [ 7 ] = tr ( " second"  )                                   ;
  ///////////////////////////////////////////////////////////////////
  nConnect         ( lineEdit() , SIGNAL ( textChanged(QString) )   ,
                     this       , SLOT   ( textChanged(QString) ) ) ;
}

N::GeogrianEdit::~GeogrianEdit(void)
{
  if ( NotNull(validator) ) validator->deleteLater() ;
  validator = NULL                                   ;
}

QAbstractSpinBox::StepEnabled N::GeogrianEdit::stepEnabled(void) const
{
  return StepUpEnabled | StepDownEnabled ;
}

void N::GeogrianEdit::setRange(TimePeriod period)
{
  Range.L = period.L              ;
  Range.R = period.R              ;
  /////////////////////////////////
  QLineEdit * le = lineEdit ( )   ;
  if (IsNull(le)) return          ;
  int p = le->cursorPosition()    ;
  if (Range.L>0)                  {
    if (Range.L>Time.Stardate)    {
      Time.Stardate = Range.L     ;
      Time . locate         (   ) ;
      setTimeText           (   ) ;
      le->setCursorPosition ( p ) ;
    }                             ;
  }                               ;
  if (Range.R>0)                  {
    if (Range.R<Time.Stardate)    {
      Time.Stardate = Range.R     ;
      Time . locate         (   ) ;
      setTimeText           (   ) ;
      le->setCursorPosition ( p ) ;
    }                             ;
  }                               ;
}

TUID N::GeogrianEdit::currentStardate(void)
{
  return Time . Stardate ;
}

bool N::GeogrianEdit::setStardate(TUID sd)
{
  Time . assign ( sd ) ;
  Time . locate (    ) ;
  setTimeText   (    ) ;
  return true          ;
}

void N::GeogrianEdit::setTimeZone(int gmt)
{
  TimeZone = gmt ;
}

void N::GeogrianEdit::Adjustment(int year,int month,int mdays)
{
  DateTime NX                            ;
  TUID     TT                            ;
  TUID     TS                            ;
  TS   = Time . Stardate + TimeZone      ;
  TS  %= 86400                           ;
  NX   . setYMD ( year , month , mdays ) ;
  TT   = NX.Stardate                     ;
  TT  /= 86400                           ;
  TT  *= 86400                           ;
  TT  += TS                              ;
  TT  -= TimeZone                        ;
  Time . Stardate = TT                   ;
  Time . locate ( )                      ;
}

void N::GeogrianEdit::AdjustDateTime(int year,int month,int mdays,int item)
{
  FixupDateTime ( year , month , mdays , item ) ;
}

void N::GeogrianEdit::stepBy(int steps)
{
  QLineEdit * le = lineEdit ( )             ;
  if (IsNull(le)) return                    ;
  QString s                                 ;
  QString r                                 ;
  int     p                                 ;
  int     c                                 ;
  int     e                                 ;
  int     l                                 ;
  bool    epf                               ;
  ///////////////////////////////////////////
  DateTime NX                               ;
  NX . Stardate = Time.Stardate + TimeZone  ;
  NX . locate                (            ) ;
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
    AdjustDateTime ( - NX . year  ( )       ,
                       NX . month ( )       ,
                       NX . mday  ( )       ,
                       3                  ) ;
    epf = false                             ;
  } else
  if (c>0)                                  {
    epf = false                             ;
    e = c + 1                               ;
    while (e<l && s.at(e) == QChar(' '))    {
      e++                                   ;
    }                                       ;
    c = s.indexOf(Names[2],e)               ;
    if (c>e)                                {
      epf = true                            ;
      if (e<=p && p<c)                      {
        int yy = NX . year  ( )             ;
        int mm = NX . month ( )             ;
        int dd = NX . mday  ( )             ;
        yy += steps                         ;
        if ( 0 == yy && steps < 0 )         {
          yy = -1                           ;
        } else
        if ( 0 == yy && steps > 0 )         {
          yy = 1                            ;
        }                                   ;
        AdjustDateTime ( yy,mm,dd,0 )       ;
        epf = false                         ;
      }                                     ;
    }                                       ;
    if (epf)                                {
      e = c + Names[2].length()             ;
      c = s.indexOf(Names[3],e)             ;
      if (c>e)                              {
        epf = true                          ;
        if (e<=p && p<c)                    {
          int yy = NX . year  ( )           ;
          int mm = NX . month ( )           ;
          int dd = NX . mday  ( )           ;
          mm += steps                       ;
          AdjustDateTime ( yy,mm,dd,1 )     ;
          epf = false                       ;
        }                                   ;
      }                                     ;
    }                                       ;
    if (epf)                                {
      r = Names[4]                          ;
      if (r.length()<=0) r = " "            ;
      e = c + Names[3].length()             ;
      c = s.indexOf(r,e)                    ;
      if (c>e)                              {
        epf = true                          ;
        if (e<=p && p<c)                    {
          int yy = NX . year  ( )           ;
          int mm = NX . month ( )           ;
          int dd = NX . mday  ( )           ;
          dd += steps                       ;
          AdjustDateTime ( yy,mm,dd,2 )     ;
          epf = false                       ;
        }                                   ;
      }                                     ;
      e = c + r.length()                    ;
    }                                       ;
    if (epf)                                { // at hh:mm:ss section
      while (c<l && s.at(c)==QChar(' '))    {
        c++                                 ;
      }                                     ;
      if ( c < l && c <= p )                {
        e = c                               ;
        c = s.indexOf(Names[5],e)           ;
        if (c<0) return                     ;
        if (c>p)                            {
          Time.Stardate += ( steps * 3600 ) ;
          Time.locate()                     ;
        } else                              {
          c++                               ;
          e = c                             ;
          c = s.indexOf(Names[6],e)         ;
          if (c<0) return                   ;
          if (c>p)                          {
            Time.Stardate += ( steps * 60 ) ;
            Time.locate()                   ;
          } else                            {
            c++                             ;
            e = c                           ;
            if (p>e)                        {
              Time.Stardate += steps        ;
              Time.locate()                 ;
            }                               ;
          }                                 ;
        }                                   ;
      }                                     ;
    }                                       ;
  }                                         ;
  ///////////////////////////////////////////
  setTimeText             (               ) ;
  le -> setCursorPosition ( p             ) ;
  emit Changed            ( Time.Stardate ) ;
}

QValidator::State N::GeogrianEdit::validate (QString & input,int & pos) const
{
  return validator -> validate ( input , pos ) ;
}

void N::GeogrianEdit::setTimeText(void)
{
  QLineEdit * le = lineEdit ( )           ;
  if (IsNull(le)) return                  ;
  le -> blockSignals ( true             ) ;
  le -> setText      ( GeogrianString() ) ;
  le -> blockSignals ( false            ) ;
}

QString N::GeogrianEdit::GeogrianString(void)
{
  QString  t                                           ;
  DateTime NX                                          ;
  int      Y                                           ;
  NX . Stardate = Time.Stardate + TimeZone             ;
  NX . locate ( )                                      ;
  if (NX.year()<0)                                     {
    t =  Names     [ 1 ]                               ;
    Y = -NX . year (   )                               ;
  } else                                               {
    t =  Names     [ 0 ]                               ;
    Y =  NX . year (   )                               ;
  }                                                    ;
  t += " "                                             ;
  t += QString::number( Y              )               ;
  t += Names [ 2 ]                                     ;
  t += QString::number( NX . month ( ) )               ;
  t += Names [ 3 ]                                     ;
  t += QString::number( NX . mday  ( ) )               ;
  t += Names [ 4 ]                                     ;
  if ( Names[4] != " " ) t += " "                      ;
  t += QString("%1").arg(NX.hours  (),2,10,QChar('0')) ;
  t += Names [ 5 ]                                     ;
  t += QString("%1").arg(NX.minutes(),2,10,QChar('0')) ;
  t += Names [ 6 ]                                     ;
  t += QString("%1").arg(NX.seconds(),2,10,QChar('0')) ;
  t += Names [ 7 ]                                     ;
  return t                                             ;
}

bool N::GeogrianEdit::madeChange(const QString & input)
{
  if (input.length()<=0) return false                   ;
  QString m                                             ;
  QString d                                             ;
  bool    bc    = false                                 ;
  bool    leap  = false                                 ;
  bool    okay  = true                                  ;
  int     index = 0                                     ;
  bool    done                                          ;
  int     year                                          ;
  int     month                                         ;
  int     day                                           ;
  int     hour                                          ;
  int     minute                                        ;
  int     second                                        ;
  ///////////////////////////////////////////////////////
  if (input.contains(Names[1]))                         { // check Before Common Era
    m     = input.left(Names[1].length())               ;
    okay  = ( m == Names[1] )                           ;
    index = Names[1].length()                           ;
    bc    = true                                        ;
  } else
  ///////////////////////////////////////////////////////
  if (input.contains(Names[0]))                         { // check Common Era
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
  d    = ""                                             ; // check year
  done = false                                          ;
  while ( ! done )                                      {
    if ( index >= input.length() ) done = true          ;
    if ( ! done )                                       {
      QChar c = input.at(index)                         ;
      if (c.isDigit())                                  {
        d . append ( c )                                ;
        index++                                         ;
      } else done = true                                ;
    }                                                   ;
  }                                                     ;
  if (d.length()<=0) return false                       ;
  okay = false                                          ;
  year = d.toInt(&okay)                                 ;
  if ( ! okay ) return false                            ;
  ///////////////////////////////////////////////////////
  m      = input.mid(index,Names[2].length())           ;
  okay   = ( m == Names[2] )                            ;
  if ( ! okay ) return false                            ;
  index += Names[2].length()                            ;
  ///////////////////////////////////////////////////////
  d    = ""                                             ; // check month
  done = false                                          ;
  while ( ! done )                                      {
    if ( index >= input.length() ) done = true          ;
    if ( ! done )                                       {
      QChar c = input.at(index)                         ;
      if (c.isDigit())                                  {
        d . append ( c )                                ;
        index++                                         ;
      } else done = true                                ;
    }                                                   ;
  }                                                     ;
  if (d.length()<=0) return false                       ;
  okay  = false                                         ;
  month = d.toInt(&okay)                                ;
  if ( ! okay ) return false                            ;
  ///////////////////////////////////////////////////////
  m      = input.mid(index,Names[3].length())           ;
  okay   = ( m == Names[3] )                            ;
  if ( ! okay ) return false                            ;
  index += Names[3].length()                            ;
  ///////////////////////////////////////////////////////
  d    = ""                                             ; // check day
  done = false                                          ;
  while ( ! done )                                      {
    if ( index >= input.length() ) done = true          ;
    if ( ! done )                                       {
      QChar c = input.at(index)                         ;
      if (c.isDigit())                                  {
        d . append ( c )                                ;
        index++                                         ;
      } else done = true                                ;
    }                                                   ;
  }                                                     ;
  if (d.length()<=0) return false                       ;
  okay = false                                          ;
  day  = d.toInt(&okay)                                 ;
  if ( ! okay ) return false                            ;
  ///////////////////////////////////////////////////////
  if ( Names[4].length() > 0 )                          {
    m    = input.mid(index,Names[4].length())           ;
    okay = ( m == Names[4] )                            ;
    if ( ! okay ) return false                          ;
    index += Names[4].length()                          ;
  }                                                     ;
  ///////////////////////////////////////////////////////
  while ( index < input.length()                       &&
          input.at(index) == QChar(' ')               ) { // skip space
    ++index                                             ;
  }                                                     ;
  if ( index >= input.length() ) return false           ;
  ///////////////////////////////////////////////////////
  d    = ""                                             ; // check hour
  done = false                                          ;
  while ( ! done )                                      {
    if ( index >= input.length() ) done = true          ;
    if ( ! done )                                       {
      QChar c = input.at(index)                         ;
      if (c.isDigit())                                  {
        d . append ( c )                                ;
        index++                                         ;
      } else done = true                                ;
    }                                                   ;
  }                                                     ;
  if (d.length()<=0) return false                       ;
  okay = false                                          ;
  hour = d.toInt(&okay)                                 ;
  if ( ! okay ) return false                            ;
  ///////////////////////////////////////////////////////
  m      = input.mid(index,Names[5].length())           ;
  okay   = ( m == Names[5] )                            ;
  if ( ! okay ) return false                            ;
  index += Names[5].length()                            ;
  ///////////////////////////////////////////////////////
  d    = ""                                             ; // check minute
  done = false                                          ;
  while ( ! done )                                      {
    if ( index >= input.length() ) done = true          ;
    if ( ! done )                                       {
      QChar c = input.at(index)                         ;
      if (c.isDigit())                                  {
        d . append ( c )                                ;
        index++                                         ;
      } else done = true                                ;
    }                                                   ;
  }                                                     ;
  if (d.length()<=0) return false                       ;
  okay   = false                                        ;
  minute = d.toInt(&okay)                               ;
  if ( ! okay ) return false                            ;
  ///////////////////////////////////////////////////////
  m      = input.mid(index,Names[6].length())           ;
  okay   = ( m == Names[6] )                            ;
  if ( ! okay ) return false                            ;
  index += Names[6].length()                            ;
  ///////////////////////////////////////////////////////
  d    = ""                                             ; // check second
  done = false                                          ;
  while ( ! done )                                      {
    if ( index >= input.length() ) done = true          ;
    if ( ! done )                                       {
      QChar c = input.at(index)                         ;
      if (c.isDigit())                                  {
        d . append ( c )                                ;
        index++                                         ;
      } else done = true                                ;
    }                                                   ;
  }                                                     ;
  if (d.length()<=0) return false                       ;
  okay   = false                                        ;
  second = d.toInt(&okay)                               ;
  if ( ! okay ) return false                            ;
  ///////////////////////////////////////////////////////
  if ( second <  0 ) return false                       ;
  if ( second > 59 ) return false                       ;
  ///////////////////////////////////////////////////////
  if ( minute <  0 ) return false                       ;
  if ( minute > 59 ) return false                       ;
  ///////////////////////////////////////////////////////
  if ( hour   <  0 ) return false                       ;
  if ( hour   > 23 ) return false                       ;
  ///////////////////////////////////////////////////////
  if ( day    <  1 ) return false                       ;
  if ( day    > 31 ) return false                       ;
  ///////////////////////////////////////////////////////
  if ( month  <  1 ) return false                       ;
  if ( month  > 12 ) return false                       ;
  ///////////////////////////////////////////////////////
  switch ( month )                                      {
    case  1                                             :
    case  3                                             :
    case  5                                             :
    case  7                                             :
    case  8                                             :
    case 10                                             :
    case 12                                             :
    break                                               ;
    case  4                                             :
    case  6                                             :
    case  9                                             :
    case 11                                             :
      if ( day > 30 ) return false                      ;
    break                                               ;
    case  2                                             :
      if ( day > 29 ) return false                      ;
      if ( bc ) leap = isLeap( -year )                  ;
           else leap = isLeap(  year )                  ;
      if ( ( ! leap ) && ( 29 == day ) ) return false   ;
    break                                               ;
  }                                                     ;
  ///////////////////////////////////////////////////////
  TUID TT                                               ;
  if ( bc ) Time . setYMD ( -year , month , day )       ;
       else Time . setYMD (  year , month , day )       ;
  TT              = Time.Stardate                       ;
  TT             /= 86400                               ;
  TT             *= 86400                               ;
  TT             += ( hour   * 3600 )                   ;
  TT             += ( minute *   60 )                   ;
  TT             +=   second                            ;
  TT             -= TimeZone                            ;
  Time . Stardate = TT                                  ;
  Time . locate ( )                                     ;
  ///////////////////////////////////////////////////////
  return true                                           ;
}

void N::GeogrianEdit::textChanged(const QString & text)
{
  QLineEdit * le = lineEdit ( )  ;
  if (IsNull(le)) return         ;
  int p = le->cursorPosition()   ;
  if (!madeChange(text))         {
    setTimeText ( )              ;
    le->setCursorPosition ( p )  ;
    return                       ;
  }                              ;
  le -> setCursorPosition ( p )  ;
  emit Changed ( Time.Stardate ) ;
}
