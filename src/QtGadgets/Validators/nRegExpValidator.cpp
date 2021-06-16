#include <qtgadgets.h>

N::RegExpValidator:: RegExpValidator  ( QObject * parent )
                   : QRegExpValidator (           parent )
                   , Validator        (           parent )
{
}

N::RegExpValidator::~RegExpValidator (void)
{
}

int N::RegExpValidator::Type(void) const
{
  return 1102 ;
}

void N::RegExpValidator::Fixup(QString & input) const
{
  QRegExpValidator::fixup(input) ;
}

QLocale N::RegExpValidator::Locale(void) const
{
  return QRegExpValidator::locale() ;
}

void N::RegExpValidator::setLocale (const QLocale & locale)
{
  QRegExpValidator::setLocale(locale) ;
}

QValidator::State N::RegExpValidator::isValid(QString & input,int & pos) const
{
  return QRegExpValidator::validate(input,pos) ;
}
