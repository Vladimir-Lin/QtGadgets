#include <qtgadgets.h>

N::RegularExpressionValidator:: RegularExpressionValidator  ( QObject * parent )
                              : QRegularExpressionValidator (           parent )
                              , Validator                   (           parent )
{
}

N::RegularExpressionValidator::~RegularExpressionValidator (void)
{
}

int N::RegularExpressionValidator::Type(void) const
{
  return 1102 ;
}

void N::RegularExpressionValidator::Fixup(QString & input) const
{
  QRegularExpressionValidator::fixup(input) ;
}

QLocale N::RegularExpressionValidator::Locale(void) const
{
  return QRegularExpressionValidator::locale() ;
}

void N::RegularExpressionValidator::setLocale (const QLocale & locale)
{
  QRegularExpressionValidator::setLocale(locale) ;
}

QValidator::State N::RegularExpressionValidator::isValid(QString & input,int & pos) const
{
  return QRegularExpressionValidator::validate(input,pos) ;
}
