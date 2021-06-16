#include <qtgadgets.h>

N::DoubleValidator:: DoubleValidator  ( QObject * parent )
                   : QDoubleValidator (           parent )
                   , Validator        (           parent )
{
}

N::DoubleValidator::~DoubleValidator (void)
{
}

int N::DoubleValidator::Type(void) const
{
  return 1002 ;
}

void N::DoubleValidator::Fixup(QString & input) const
{
  QDoubleValidator::fixup(input) ;
}

QLocale N::DoubleValidator::Locale(void) const
{
  return QDoubleValidator::locale() ;
}

void N::DoubleValidator::setLocale (const QLocale & locale)
{
  QDoubleValidator::setLocale(locale) ;
}

QValidator::State N::DoubleValidator::isValid(QString & input,int & pos) const
{
  return QDoubleValidator::validate(input,pos) ;
}
