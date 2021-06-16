#include <qtgadgets.h>

N::IntValidator:: IntValidator  ( QObject * parent )
                : QIntValidator (           parent )
                , Validator     (           parent )
{
}

N::IntValidator::~IntValidator (void)
{
}

int N::IntValidator::Type(void) const
{
  return 1001 ;
}

void N::IntValidator::Fixup(QString & input) const
{
  QIntValidator::fixup(input) ;
}

QLocale N::IntValidator::Locale(void) const
{
  return QIntValidator::locale() ;
}

void N::IntValidator::setLocale (const QLocale & locale)
{
  QIntValidator::setLocale(locale) ;
}

QValidator::State N::IntValidator::isValid(QString & input,int & pos) const
{
  return QIntValidator::validate(input,pos) ;
}
