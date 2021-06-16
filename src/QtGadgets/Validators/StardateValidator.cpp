#include <qtgadgets.h>

N::StardateValidator:: StardateValidator ( QObject * parent )
                     : QValidator        (           parent )
                     , Validator         (           parent )
{
}

N::StardateValidator::~StardateValidator (void)
{
}

int N::StardateValidator::Type(void) const
{
  return 10000 + Calendars::StarDate ;
}

void N::StardateValidator::Fixup(QString & input) const
{
  fixup(input) ;
}

QLocale N::StardateValidator::Locale(void) const
{
  return QValidator::locale() ;
}

void N::StardateValidator::setLocale (const QLocale & locale)
{
  QValidator::setLocale(locale) ;
}

QValidator::State N::StardateValidator::isValid(QString & input,int & pos) const
{
  return validate(input,pos) ;
}

void N::StardateValidator::fixup(QString & input) const
{ Q_UNUSED ( input ) ;
}

QValidator::State N::StardateValidator::validate(QString & input,int & pos) const
{ Q_UNUSED ( pos )                                  ;
  if (input.length()<=0) return Intermediate        ;
  QStringList T = input.split(' ')                  ;
  if (T.count()!=2) return QValidator::Intermediate ;
  QStringList D = T[1].split(':')                   ;
  if (D.count()!=3) return QValidator::Intermediate ;
  bool ok = false                                   ;
  TUID v                                            ;
  D . prepend ( T[0] )                              ;
  for (int i=0;i<D.count();i++)                     {
    ok  = false                                     ;
    v = D[i].toLongLong(&ok)                        ;
    if (!ok) return QValidator::Invalid             ;
    switch (i)                                      {
      case 1                                        :
        if (v< 0) return QValidator::Invalid        ;
        if (v>23) return QValidator::Invalid        ;
      break                                         ;
      case 2                                        :
      case 3                                        :
        if (v< 0) return QValidator::Invalid        ;
        if (v>59) return QValidator::Invalid        ;
      break                                         ;
    }                                               ;
  }                                                 ;
  return QValidator::Acceptable                     ;
}
