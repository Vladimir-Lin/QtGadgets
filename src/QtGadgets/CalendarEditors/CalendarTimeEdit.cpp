#include <qtgadgets.h>

N::CalendarTimeEdit:: CalendarTimeEdit ( QWidget * parent )
                    : QAbstractSpinBox (           parent )
{
  Range.L = 0 ;
  Range.R = 0 ;
}

N::CalendarTimeEdit::~CalendarTimeEdit(void)
{
}

void N::CalendarTimeEdit::setRange(TimePeriod period)
{
  Range.L = period.L ;
  Range.R = period.R ;
}

void N::CalendarTimeEdit::setRange(TUID minimum,TUID maximum)
{
  TimePeriod X ( minimum , maximum ) ;
  setRange     ( X                 ) ;
}

bool N::CalendarTimeEdit::ParseText(QStringList & result,QString & text,NAMEs & names)
{
  QString T = text                ;
  UUIDs   U = names.keys()        ;
  SUID    u                       ;
  int     c                       ;
  /////////////////////////////////
  c = T.indexOf(names[1])         ;
  if (c>=0)                       {
    result << names[1]            ;
  } else                          {
    c = T.indexOf(names[0])       ;
    if (c>=0)                     {
      result << names[0]          ;
    }                             ;
  }                               ;
  /////////////////////////////////
  foreach (u,U)                   {
    if (names[u].length()>0)      {
      T = T.replace(names[u]," ") ;
    }                             ;
  }                               ;
  /////////////////////////////////
  T = T . simplified ( )          ;
  result << T.split(' ')          ;
  /////////////////////////////////
  return ( result.count() > 0 )   ;
}

int N::CalendarTimeEdit::LocateText(int cursor,QStringList & result,QString & text,NAMEs & names)
{
  return 0 ;
}

int N::CalendarTimeEdit::SkipSpace(int position,QString & text)
{
  int L = text.length()                                 ;
  while (position<L && (text.at(position)==QChar(' '))) {
    position++                                          ;
  }                                                     ;
  return position                                       ;
}

bool N::CalendarTimeEdit::isLeap(int year)
{
  bool leap   = false                               ;
  if (year>0)                                       {
    if ( ( year % 8000) == 4000 ) leap = false ; else
    if ( ( year %  400) ==    0 ) leap = true  ; else
    if ( ( year %  100) ==    0 ) leap = false ; else
    if ( ( year %    4) ==    0 ) leap = true  ; else
                                  leap = false      ;
  } else                                            {
    int ym = -year                                  ;
    ym -= 1                                         ;
    if (   ym           ==    0 ) leap = true  ; else
    if ( ( ym   % 8000) == 4000 ) leap = false ; else
    if ( ( ym   %  400) ==    0 ) leap = true  ; else
    if ( ( ym   %  100) ==    0 ) leap = false ; else
    if ( ( ym   %    4) ==    0 ) leap = true  ; else
                                  leap = false      ;
  }                                                 ;
  return leap                                       ;
}

void N::CalendarTimeEdit::FixupDateTime(int year,int month,int mdays,int item)
{
  int  ms[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31} ;
  int  yy   = year                                      ;
  int  mm   = month                                     ;
  int  dd   = mdays                                     ;
  bool leap = isLeap(year)                              ;
  if ( leap ) ms [ 2 ] = 29                             ;
  ///////////////////////////////////////////////////////
  switch ( mm )                                         {
    case  1                                             :
    case  3                                             :
    case  5                                             :
    case  7                                             :
    case  8                                             :
    case 10                                             :
    case 12                                             :
      if ( dd < 1 )                                     {
        mm--                                            ;
        if ( mm == 0 )                                  {
          yy--                                          ;
          mm = 12                                       ;
        }                                               ;
        dd = ms [ mm ]                                  ;
      } else
      if ( dd > 31 )                                    {
        mm++                                            ;
        if ( mm > 12 )                                  {
          yy++                                          ;
          mm = 1                                        ;
        }                                               ;
        dd = 1                                          ;
      }                                                 ;
    break                                               ;
    case  4                                             :
    case  6                                             :
    case  9                                             :
    case 11                                             :
      if ( dd <  1 )                                    {
        mm--                                            ;
        dd = ms [ mm ]                                  ;
      } else
      if ( dd > 30 )                                    {
        mm++                                            ;
        dd = 1                                          ;
      }                                                 ;
    break                                               ;
    case  2                                             :
      if ( dd <  1 )                                    {
        mm--                                            ;
        dd = ms [ mm ]                                  ;
      } else                                            ;
      if ( ! leap && ( dd > 28 ) )                      {
        mm++                                            ;
        dd = 1                                          ;
      } else
      if (   leap && ( dd > 29 ) )                      {
        mm++                                            ;
        dd = 1                                          ;
      }                                                 ;
    break                                               ;
    default                                             :
      if ( mm < 1 )                                     {
        mm = 12                                         ;
        if ( yy < 0 ) yy++ ; else yy--                  ;
      } else
      if ( mm > 12 )                                    {
        mm = 1                                          ;
        if ( yy < 0 ) yy-- ; else yy++                  ;
      }                                                 ;
    break                                               ;
  }                                                     ;
  ///////////////////////////////////////////////////////
  Adjustment ( yy , mm , dd )                           ;
}

void N::CalendarTimeEdit::Adjustment(int year,int month,int mdays)
{
}
