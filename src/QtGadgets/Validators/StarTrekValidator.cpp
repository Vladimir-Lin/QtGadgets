#include <qtgadgets.h>

N::StarTrekValidator:: StarTrekValidator ( QObject * parent )
                     : QValidator        (           parent )
                     , Validator         (           parent )
{
  Keywords [ 0 ] = tr ( "S.D." ) ;
  Keywords [ 1 ] = tr ( "B.F." ) ;
}

N::StarTrekValidator::~StarTrekValidator (void)
{
}

int N::StarTrekValidator::Type(void) const
{
  return 10000 + Calendars::StarTrek ;
}

void N::StarTrekValidator::Fixup(QString & input) const
{
  fixup(input) ;
}

QLocale N::StarTrekValidator::Locale(void) const
{
  return QValidator::locale() ;
}

void N::StarTrekValidator::setLocale (const QLocale & locale)
{
  QValidator::setLocale(locale) ;
}

QValidator::State N::StarTrekValidator::isValid(QString & input,int & pos) const
{
  return validate(input,pos) ;
}

void N::StarTrekValidator::fixup(QString & input) const
{ Q_UNUSED ( input ) ;
}

QValidator::State N::StarTrekValidator::validate(QString & input,int & pos) const
{
  if (input.length()<=0) return Intermediate        ;
  QString m                                         ;
  bool    okay  = true                              ;
  int     index = 0                                 ;
  ///////////////////////////////////////////////////
  if (input.contains(Keywords[1]))                  { // check Before StarTrek Star Date
    m     = input.left(Keywords[1].length())        ;
    okay  = ( m == Keywords[1] )                    ;
    index = Keywords[1].length()                    ;
  } else
  ///////////////////////////////////////////////////
  if (input.contains(Keywords[0]))                  { // check StarTrek Star Date
    m     = input.left(Keywords[0].length())        ;
    okay  = ( m == Keywords[0] )                    ;
    index = Keywords[0].length()                    ;
  } else okay = false                               ;
  if ( ! okay ) return Invalid                      ;
  ///////////////////////////////////////////////////
  while ( index < input.length()                   &&
          input.at(index) == QChar(' ')           ) { // skip space
    ++index                                         ;
  }                                                 ;
  if ( index >= input.length() ) return Invalid     ;
  ///////////////////////////////////////////////////
  int         L = input.length()                    ;
  m = input.mid(index,L-index)                      ;
  if ( m.length() <= 0 ) return Invalid             ;
  ///////////////////////////////////////////////////
  QStringList S = m.split('.')                      ;
  if ( S . count ( ) < 2 ) return Invalid           ;
  ///////////////////////////////////////////////////
  for (int i=0;i<2;i++)                             {
    okay = false                                    ;
    S[i].toInt(&okay)                               ;
    if ( ! okay )  return Invalid                   ;
  }                                                 ;
  ///////////////////////////////////////////////////
  return Acceptable                                 ;
}
