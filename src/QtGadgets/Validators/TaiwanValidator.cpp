#include <qtgadgets.h>

N::TaiwanValidator:: TaiwanValidator ( QObject * parent )
                   : QValidator      (           parent )
                   , Validator       (           parent )
{
  Keywords [ 0 ] = tr ( "M.G."     ) ;
  Keywords [ 1 ] = tr ( "B.M."     ) ;
  Keywords [ 2 ] = tr ( " year "   ) ;
  Keywords [ 3 ] = tr ( " month "  ) ;
  Keywords [ 4 ] = tr ( " day"     ) ;
  Keywords [ 5 ] = tr ( " hour "   ) ;
  Keywords [ 6 ] = tr ( " minute " ) ;
  Keywords [ 7 ] = tr ( " second"  ) ;
}

N::TaiwanValidator::~TaiwanValidator (void)
{
}

int N::TaiwanValidator::Type(void) const
{
  return 10000 + Calendars::Taiwanese ;
}

void N::TaiwanValidator::Fixup(QString & input) const
{
  fixup(input) ;
}

QLocale N::TaiwanValidator::Locale(void) const
{
  return QValidator::locale() ;
}

void N::TaiwanValidator::setLocale (const QLocale & locale)
{
  QValidator::setLocale(locale) ;
}

QValidator::State N::TaiwanValidator::isValid(QString & input,int & pos) const
{
  return validate(input,pos) ;
}

void N::TaiwanValidator::fixup(QString & input) const
{ Q_UNUSED ( input ) ;
}

QValidator::State N::TaiwanValidator::validate(QString & input,int & pos) const
{
  if (input.length()<=0) return Intermediate        ;
  QString m                                         ;
  QString d                                         ;
  bool    bc    = false                             ;
  bool    leap  = false                             ;
  bool    okay  = true                              ;
  int     index = 0                                 ;
  bool    done                                      ;
  int     year                                      ;
  int     month                                     ;
  int     day                                       ;
  int     hour                                      ;
  int     minute                                    ;
  int     second                                    ;
  ///////////////////////////////////////////////////
  if (input.contains(Keywords[1]))                  { // check Before Common Era
    m     = input.left(Keywords[1].length())        ;
    okay  = ( m == Keywords[1] )                    ;
    index = Keywords[1].length()                    ;
  } else
  ///////////////////////////////////////////////////
  if (input.contains(Keywords[0]))                  { // check Common Era
    m     = input.left(Keywords[0].length())        ;
    okay  = ( m == Keywords[0] )                    ;
    index = Keywords[0].length()                    ;
    bc    = true                                    ;
  } else okay = false                               ;
  if ( ! okay ) return Invalid                      ;
  ///////////////////////////////////////////////////
  while ( index < input.length()                   &&
          input.at(index) == QChar(' ')           ) { // skip space
    ++index                                         ;
  }                                                 ;
  if ( index >= input.length() ) return Invalid     ;
  ///////////////////////////////////////////////////
  d    = ""                                         ; // check year
  done = false                                      ;
  while ( ! done )                                  {
    if ( index >= input.length() ) done = true      ;
    if ( ! done )                                   {
      QChar c = input.at(index)                     ;
      if (c.isDigit())                              {
        d . append ( c )                            ;
        index++                                     ;
      } else done = true                            ;
    }                                               ;
  }                                                 ;
  if (d.length()<=0) return Invalid                 ;
  okay = false                                      ;
  year = d.toInt(&okay)                             ;
  if ( ! okay ) return Invalid                      ;
  ///////////////////////////////////////////////////
  m      = input.mid(index,Keywords[2].length())    ;
  okay   = ( m == Keywords[2] )                     ;
  if ( ! okay ) return Invalid                      ;
  index += Keywords[2].length()                     ;
  ///////////////////////////////////////////////////
  d    = ""                                         ; // check month
  done = false                                      ;
  while ( ! done )                                  {
    if ( index >= input.length() ) done = true      ;
    if ( ! done )                                   {
      QChar c = input.at(index)                     ;
      if (c.isDigit())                              {
        d . append ( c )                            ;
        index++                                     ;
      } else done = true                            ;
    }                                               ;
  }                                                 ;
  if (d.length()<=0) return Invalid                 ;
  okay  = false                                     ;
  month = d.toInt(&okay)                            ;
  if ( ! okay ) return Invalid                      ;
  ///////////////////////////////////////////////////
  m      = input.mid(index,Keywords[3].length())    ;
  okay   = ( m == Keywords[3] )                     ;
  if ( ! okay ) return Invalid                      ;
  index += Keywords[3].length()                     ;
  ///////////////////////////////////////////////////
  d    = ""                                         ; // check day
  done = false                                      ;
  while ( ! done )                                  {
    if ( index >= input.length() ) done = true      ;
    if ( ! done )                                   {
      QChar c = input.at(index)                     ;
      if (c.isDigit())                              {
        d . append ( c )                            ;
        index++                                     ;
      } else done = true                            ;
    }                                               ;
  }                                                 ;
  if (d.length()<=0) return Invalid                 ;
  okay = false                                      ;
  day  = d.toInt(&okay)                             ;
  if ( ! okay ) return Invalid                      ;
  ///////////////////////////////////////////////////
  if ( Keywords[4].length() > 0 )                   {
    m    = input.mid(index,Keywords[4].length())    ;
    okay = ( m == Keywords[4] )                     ;
    if ( ! okay ) return Invalid                    ;
    index += Keywords[4].length()                   ;
  }                                                 ;
  ///////////////////////////////////////////////////
  while ( index < input.length()                   &&
          input.at(index) == QChar(' ')           ) { // skip space
    ++index                                         ;
  }                                                 ;
  if ( index >= input.length() ) return Invalid     ;
  ///////////////////////////////////////////////////
  d    = ""                                         ; // check hour
  done = false                                      ;
  while ( ! done )                                  {
    if ( index >= input.length() ) done = true      ;
    if ( ! done )                                   {
      QChar c = input.at(index)                     ;
      if (c.isDigit())                              {
        d . append ( c )                            ;
        index++                                     ;
      } else done = true                            ;
    }                                               ;
  }                                                 ;
  if (d.length()<=0) return Invalid                 ;
  okay = false                                      ;
  hour = d.toInt(&okay)                             ;
  if ( ! okay ) return Invalid                      ;
  ///////////////////////////////////////////////////
  m      = input.mid(index,Keywords[5].length())    ;
  okay   = ( m == Keywords[5] )                     ;
  if ( ! okay ) return Invalid                      ;
  index += Keywords[5].length()                     ;
  ///////////////////////////////////////////////////
  d    = ""                                         ; // check minute
  done = false                                      ;
  while ( ! done )                                  {
    if ( index >= input.length() ) done = true      ;
    if ( ! done )                                   {
      QChar c = input.at(index)                     ;
      if (c.isDigit())                              {
        d . append ( c )                            ;
        index++                                     ;
      } else done = true                            ;
    }                                               ;
  }                                                 ;
  if (d.length()<=0) return Invalid                 ;
  okay   = false                                    ;
  minute = d.toInt(&okay)                           ;
  if ( ! okay ) return Invalid                      ;
  ///////////////////////////////////////////////////
  m      = input.mid(index,Keywords[6].length())    ;
  okay   = ( m == Keywords[6] )                     ;
  if ( ! okay ) return Invalid                      ;
  index += Keywords[6].length()                     ;
  ///////////////////////////////////////////////////
  d    = ""                                         ; // check second
  done = false                                      ;
  while ( ! done )                                  {
    if ( index >= input.length() ) done = true      ;
    if ( ! done )                                   {
      QChar c = input.at(index)                     ;
      if (c.isDigit())                              {
        d . append ( c )                            ;
        index++                                     ;
      } else done = true                            ;
    }                                               ;
  }                                                 ;
  if (d.length()<=0) return Invalid                 ;
  okay   = false                                    ;
  second = d.toInt(&okay)                           ;
  if ( ! okay ) return Invalid                      ;
  ///////////////////////////////////////////////////
  if ( second <  0 ) return Invalid                 ;
  if ( second > 59 ) return Intermediate            ;
  ///////////////////////////////////////////////////
  if ( minute <  0 ) return Invalid                 ;
  if ( minute > 59 ) return Intermediate            ;
  ///////////////////////////////////////////////////
  if ( hour   <  0 ) return Invalid                 ;
  if ( hour   > 23 ) return Intermediate            ;
  ///////////////////////////////////////////////////
  if ( day    <  1 ) return Intermediate            ;
  if ( day    > 31 ) return Intermediate            ;
  ///////////////////////////////////////////////////
  if ( month  <  1 ) return Intermediate            ;
  if ( month  > 12 ) return Intermediate            ;
  ///////////////////////////////////////////////////
  switch ( month )                                  {
    case  1                                         :
    case  3                                         :
    case  5                                         :
    case  7                                         :
    case  8                                         :
    case 10                                         :
    case 12                                         :
    return Acceptable                               ;
    case  4                                         :
    case  6                                         :
    case  9                                         :
    case 11                                         :
      if ( day > 30 ) return Intermediate           ;
    return Acceptable                               ;
  }                                                 ;
  ///////////////////////////////////////////////////
  if ( day < 28 ) return Acceptable                 ;
  if ( day > 29 ) return Intermediate               ;
  ///////////////////////////////////////////////////
  if ( bc )                                         {
    int ym = -year                                  ;
    ym -= 1                                         ;
    if (   ym           ==    0 ) leap = true  ; else
    if ( ( ym   % 8000) == 4000 ) leap = false ; else
    if ( ( ym   %  400) ==    0 ) leap = true  ; else
    if ( ( ym   %  100) ==    0 ) leap = false ; else
    if ( ( ym   %    4) ==    0 ) leap = true  ; else
                                  leap = false      ;
  } else                                            {
    if ( ( year % 8000) == 4000 ) leap = false ; else
    if ( ( year %  400) ==    0 ) leap = true  ; else
    if ( ( year %  100) ==    0 ) leap = false ; else
    if ( ( year %    4) ==    0 ) leap = true  ; else
                                  leap = false      ;
  }                                                 ;
  ///////////////////////////////////////////////////
  return leap ? Acceptable : Intermediate           ;
}
