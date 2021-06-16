/****************************************************************************
 *                                                                          *
 * Copyright (C) 2001 ~ 2016 Neutrino International Inc.                    *
 *                                                                          *
 * Author : Brian Lin <lin.foxman@gmail.com>, Skype: wolfram_lin            *
 *                                                                          *
 ****************************************************************************/

#ifndef QT_GADGETS_H
#define QT_GADGETS_H

#include <QtCore>
#include <QtGui>
#include <QtNetwork>
#include <QtSql>
#include <QtScript>
#include <QtPositioning>
#include <QtOpenGL>
#include <QtCUDA>
#include <QtOpenCV>
#include <Essentials>
#include <QtCalendar>
#include <QtGMP>
#include <QtGSL>
#include <QtAlgebra>
#include <QtDiscrete>
#include <QtFFT>
#include <Mathematics>
#include <QtFuzzy>
#include <QtFLP>
#include <QtGeometry>

QT_BEGIN_NAMESPACE

#ifndef QT_STATIC
#    if defined(QT_BUILD_QTGADGETS_LIB)
#      define Q_GADGETS_EXPORT Q_DECL_EXPORT
#    else
#      define Q_GADGETS_EXPORT Q_DECL_IMPORT
#    endif
#else
#    define Q_GADGETS_EXPORT
#endif

namespace N
{

class Q_GADGETS_EXPORT ColorYUV                   ;
class Q_GADGETS_EXPORT ColorYIQ                   ;
class Q_GADGETS_EXPORT ColorXYZ                   ;
class Q_GADGETS_EXPORT ColorLab                   ;
class Q_GADGETS_EXPORT ColorLUV                   ;
class Q_GADGETS_EXPORT ColorSpace                 ;
class Q_GADGETS_EXPORT Palette                    ;
class Q_GADGETS_EXPORT Validator                  ;
class Q_GADGETS_EXPORT Validators                 ;
class Q_GADGETS_EXPORT IntValidator               ;
class Q_GADGETS_EXPORT DoubleValidator            ;
class Q_GADGETS_EXPORT RegExpValidator            ;
class Q_GADGETS_EXPORT RegularExpressionValidator ;
class Q_GADGETS_EXPORT UuidValidator              ;
class Q_GADGETS_EXPORT GeogrianValidator          ;
class Q_GADGETS_EXPORT HoloceneValidator          ;
class Q_GADGETS_EXPORT BuddhistValidator          ;
class Q_GADGETS_EXPORT StardateValidator          ;
class Q_GADGETS_EXPORT StarTrekValidator          ;
class Q_GADGETS_EXPORT TaiwanValidator            ;
class Q_GADGETS_EXPORT CalendarTimeEdit           ;
class Q_GADGETS_EXPORT GeogrianEdit               ;
class Q_GADGETS_EXPORT HoloceneEdit               ;
class Q_GADGETS_EXPORT BuddhistEdit               ;
class Q_GADGETS_EXPORT StardateEdit               ;
class Q_GADGETS_EXPORT StarTrekEdit               ;
class Q_GADGETS_EXPORT TaiwanEdit                 ;
class Q_GADGETS_EXPORT Font                       ;
class Q_GADGETS_EXPORT Pen                        ;
class Q_GADGETS_EXPORT Brush                      ;
class Q_GADGETS_EXPORT Gradient                   ;
class Q_GADGETS_EXPORT ChartPiece                 ;
class Q_GADGETS_EXPORT ChartPainter               ;
class Q_GADGETS_EXPORT PaperSize                  ;
class Q_GADGETS_EXPORT Paper                      ;
class Q_GADGETS_EXPORT PaperOptions               ;
class Q_GADGETS_EXPORT PictureOptions             ;
class Q_GADGETS_EXPORT Screen                     ;
class Q_GADGETS_EXPORT RasterOptions              ;
class Q_GADGETS_EXPORT DockInformation            ;
class Q_GADGETS_EXPORT WidgetInformation          ;
class Q_GADGETS_EXPORT MachineProfiler            ;

typedef QMap  < SUID    , QIcon        > ICONs        ; // QIcons
typedef QMap  < int     , Font         > FONTs        ;
typedef QMap  < QString , Font         > FontMaps     ;
typedef QMap  < int     , Pen          > Pens         ;
typedef QMap  < QString , Pen          > PenMaps      ;
typedef QMap  < int     , Brush        > Brushes      ;
typedef QMap  < QString , Brush        > BrushMaps    ;
typedef QMap  < int     , Gradient     > Gradients    ;
typedef QMap  < QString , Gradient     > GradientMaps ;
typedef QMap  < int     , QPainterPath > Pathes       ;

Q_GADGETS_EXPORT int  toPathes    (Vector & vector,QPainterPath & path) ;
Q_GADGETS_EXPORT int  toPathes    (Vector & vector,double factor,QPainterPath & path) ;
Q_GADGETS_EXPORT void PaintVector (QSizeF scale,QPointF shift,Vector & vector,QPainter & painter) ;

/*****************************************************************************
 *                                                                           *
 *                                Color Models                               *
 *                                                                           *
 *****************************************************************************/

class Q_GADGETS_EXPORT ColorYUV
{
  public:

    double Y ; // [  0.000 ,  1.000 ]
    double U ; // [ -0.436 ,  0.436 ]
    double V ; // [ -0.615 ,  0.615 ]

    explicit ColorYUV     (double y,double u,double v) ;
    explicit ColorYUV     (QColor & color) ;
    explicit ColorYUV     (void) ;
             ColorYUV     (const ColorYUV & yuv) ;
    virtual ~ColorYUV     (void) ;

    ColorYUV & operator = (const ColorYUV & yuv) ;

    ColorYUV & setRgb     (QColor & color) ;
    QColor     toRgb      (void) ;

  protected:

  private:

};

class Q_GADGETS_EXPORT ColorYIQ
{
  public:

    double Y ; // [  0.000000 ,  1.000000 ]
    double I ; // [ -0.595716 ,  0.595716 ]
    double Q ; // [ -0.522591 ,  0.522591 ]

    explicit ColorYIQ     (double y,double i,double q) ;
    explicit ColorYIQ     (QColor & color) ;
    explicit ColorYIQ     (void) ;
             ColorYIQ     (const ColorYIQ & yiq) ;
    virtual ~ColorYIQ     (void) ;

    ColorYIQ & operator = (const ColorYIQ & yuv) ;

    ColorYIQ & setRgb     (QColor & color) ;
    QColor     toRgb      (void) ;

  protected:

  private:

};

// CIE XYZ Color Model
class Q_GADGETS_EXPORT ColorXYZ
{
  public:

    double X ; // [ 0.0 , 0.95047 ]
    double Y ; // [ 0.0 , 1.00000 ]
    double Z ; // [ 0.0 , 1.08883 ]

    explicit ColorXYZ     (double x,double y,double z) ;
    explicit ColorXYZ     (QColor & color) ;
    explicit ColorXYZ     (void) ;
             ColorXYZ     (const ColorXYZ & xyz) ;
    virtual ~ColorXYZ     (void) ;

    ColorXYZ & operator = (const ColorXYZ & xyz) ;

    ColorXYZ & setRgb     (QColor & color) ;
    QColor     toRgb      (void) ;

    double Gamma          (double v) ;
    double invertGamma    (double r) ;

  protected:

  private:

};

// CIE Lab
class Q_GADGETS_EXPORT ColorLab
{
  public:

    double L ; // [    0.0000 , 100.0000 ]
    double a ; // [ - 86.1846 ,  98.2542 ]
    double b ; // [ -107.8640 ,  94.4825 ]

    explicit ColorLab     (double L,double a,double b) ;
    explicit ColorLab     (ColorXYZ & XYZ) ;
    explicit ColorLab     (QColor & color) ;
    explicit ColorLab     (void) ;
             ColorLab     (const ColorLab & lab) ;
    virtual ~ColorLab     (void) ;

    ColorLab & operator = (const ColorLab & xyz) ;

    ColorLab & setXYZ     (ColorXYZ & XYZ) ;
    ColorXYZ   toXYZ      (void) ;

    ColorLab & setRgb     (QColor & color) ;
    QColor      toRgb     (void) ;

    double Forward        (double parament) ;
    double Reverse        (double parament) ;

  protected:

  private:

};

// CIE LUV
class Q_GADGETS_EXPORT ColorLUV
{
  public:

    double L ; // [   0.0000 , 100.0000 ]
    double U ; // [ -83.0798 , 175.0530 ]
    double V ; // [ -21.0972 , 435.3520 ]

    explicit ColorLUV     (double L,double U,double V) ;
    explicit ColorLUV     (ColorXYZ & XYZ) ;
    explicit ColorLUV     (QColor & color) ;
    explicit ColorLUV     (void) ;
             ColorLUV     (const ColorLUV & luv) ;
    virtual ~ColorLUV     (void) ;

    ColorLUV & operator = (const ColorLUV & luv) ;

    ColorLUV & setXYZ     (ColorXYZ & XYZ) ;
    ColorXYZ   toXYZ      (void) ;

    ColorLUV & setRgb     (QColor & color) ;
    QColor     toRgb      (void) ;

  protected:

  private:

};

class Q_GADGETS_EXPORT ColorSpace
{
  public:

    explicit ColorSpace (void) ;
    virtual ~ColorSpace (void) ;

    static QColor YUV (double Y,double U,double V) ;
    static QColor YIQ (double Y,double I,double Q) ;
    static QColor XYZ (double X,double Y,double Z) ;
    static QColor Lab (double L,double a,double b) ;
    static QColor LUV (double L,double U,double V) ;

    static void DrawHSV (QImage & image,Colors & colors,double V = 1.00000) ;
    static void DrawHSL (QImage & image,Colors & colors,double L = 1.00000) ;
    static void DrawYIQ (QImage & image,Colors & colors,double Y = 1.00000) ;
    static void DrawYUV (QImage & image,Colors & colors,double Y = 1.00000) ;
    static void DrawLab (QImage & image,Colors & colors,double L = 100.000) ;
    static void DrawLUV (QImage & image,Colors & colors,double L = 100.000) ;

    static bool  isSkin       (QColor c) ;
    static UUIDs SkinCounting (QImage & Source,QImage & Mask) ;

  protected:

  private:

};

class Q_GADGETS_EXPORT Palette : public QByteArray
{
  public:

    explicit Palette         (void);
             Palette         (const Palette & palette) ;
    virtual ~Palette         (void);

    Palette &     operator = (const Palette & palette) ;

    int           total      (void) const ;

    QImage        Image      (void) ;

    QVector<QRgb> colors     (void) ;
    void          set        (QVector<QRgb> colormaps);
    void          set        (QImage & image) ;
    int           toColors   (Colors & colors) ;
    void          set        (Colors & colors) ;

    QByteArray    Compress   (void) ;
    bool          Uncompress (QByteArray & data) ;

    SUID          sigma      (void) ;
    void          setTotal   (int Total) ;

  protected:

    int TotalColors ;

  private:

};

/*****************************************************************************
 *                                                                           *
 *                                  Validators                               *
 *                                                                           *
 *****************************************************************************/

class Q_GADGETS_EXPORT Validator
{
  public:

    Validator (QObject * parent = NULL)
    {
    }

    virtual ~ Validator ( void )
    {
    }

    virtual int               Type      (void                     ) const = 0 ;
    virtual void              Fixup     (QString & input          ) const = 0 ;
    virtual QLocale           Locale    (void                     ) const = 0 ;
    virtual void              setLocale (const QLocale & locale   )       = 0 ;
    virtual QValidator::State isValid   (QString & input,int & pos) const = 0 ;

};

class Q_GADGETS_EXPORT Validators : public QList<Validator *>
{
  public:

    explicit           Validators (void) ;
    virtual           ~Validators (void) ;

    static Validator * validator  (int type,QObject * parent = NULL) ;

  protected:

  private:

};

class Q_GADGETS_EXPORT IntValidator : public QIntValidator
                                    , public  Validator
{
  Q_OBJECT
  public:

             IntValidator               (QObject * parent) ;
    virtual ~IntValidator               (void) ;

    virtual int               Type      (void                     ) const ;
    virtual void              Fixup     (QString & input          ) const ;
    virtual QLocale           Locale    (void                     ) const ;
    virtual void              setLocale (const QLocale & locale   )       ;
    virtual QValidator::State isValid   (QString & input,int & pos) const ;

  protected:

  private:

} ;

class Q_GADGETS_EXPORT DoubleValidator : public QDoubleValidator
                                       , public  Validator
{
  Q_OBJECT
  public:

             DoubleValidator            (QObject * parent) ;
    virtual ~DoubleValidator            (void) ;

    virtual int               Type      (void                     ) const ;
    virtual void              Fixup     (QString & input          ) const ;
    virtual QLocale           Locale    (void                     ) const ;
    virtual void              setLocale (const QLocale & locale   )       ;
    virtual QValidator::State isValid   (QString & input,int & pos) const ;

  protected:

  private:

} ;

class Q_GADGETS_EXPORT RegExpValidator : public QRegExpValidator
                                       , public  Validator
{
  Q_OBJECT
  public:

             RegExpValidator            (QObject * parent) ;
    virtual ~RegExpValidator            (void) ;

    virtual int               Type      (void                     ) const ;
    virtual void              Fixup     (QString & input          ) const ;
    virtual QLocale           Locale    (void                     ) const ;
    virtual void              setLocale (const QLocale & locale   )       ;
    virtual QValidator::State isValid   (QString & input,int & pos) const ;

  protected:

  private:

} ;

class Q_GADGETS_EXPORT RegularExpressionValidator : public QRegularExpressionValidator
                                                  , public  Validator
{
  Q_OBJECT
  public:

             RegularExpressionValidator (QObject * parent) ;
    virtual ~RegularExpressionValidator (void) ;

    virtual int               Type      (void                     ) const ;
    virtual void              Fixup     (QString & input          ) const ;
    virtual QLocale           Locale    (void                     ) const ;
    virtual void              setLocale (const QLocale & locale   )       ;
    virtual QValidator::State isValid   (QString & input,int & pos) const ;

  protected:

  private:

} ;

class Q_GADGETS_EXPORT UuidValidator  : public QValidator
                                      , public Validator
{
  Q_OBJECT
  public:

             UuidValidator              (QObject * parent) ;
    virtual ~UuidValidator              (void) ;

    virtual int               Type      (void                     ) const ;
    virtual void              Fixup     (QString & input          ) const ;
    virtual QLocale           Locale    (void                     ) const ;
    virtual void              setLocale (const QLocale & locale   )       ;
    virtual QValidator::State isValid   (QString & input,int & pos) const ;
    virtual void              fixup     (QString & input          ) const ;
    virtual QValidator::State validate  (QString & input,int & pos) const ;

  protected:

  private:

} ;

class Q_GADGETS_EXPORT GeogrianValidator : public QValidator
                                         , public  Validator
{
  Q_OBJECT
  public:

             GeogrianValidator          (QObject * parent) ;
    virtual ~GeogrianValidator          (void) ;

    virtual int               Type      (void                     ) const ;
    virtual void              Fixup     (QString & input          ) const ;
    virtual QLocale           Locale    (void                     ) const ;
    virtual void              setLocale (const QLocale & locale   )       ;
    virtual QValidator::State isValid   (QString & input,int & pos) const ;
    virtual void              fixup     (QString & input          ) const ;
    virtual QValidator::State validate  (QString & input,int & pos) const ;

  protected:

    NAMEs Keywords ;

  private:

} ;

class Q_GADGETS_EXPORT HoloceneValidator : public QValidator
                                         , public  Validator
{
  Q_OBJECT
  public:

             HoloceneValidator          (QObject * parent) ;
    virtual ~HoloceneValidator          (void) ;

    virtual int               Type      (void                     ) const ;
    virtual void              Fixup     (QString & input          ) const ;
    virtual QLocale           Locale    (void                     ) const ;
    virtual void              setLocale (const QLocale & locale   )       ;
    virtual QValidator::State isValid   (QString & input,int & pos) const ;
    virtual void              fixup     (QString & input          ) const ;
    virtual QValidator::State validate  (QString & input,int & pos) const ;

  protected:

    NAMEs Keywords ;

  private:

} ;

class Q_GADGETS_EXPORT StardateValidator : public QValidator
                                         , public  Validator
{
  Q_OBJECT
  public:

             StardateValidator          (QObject * parent) ;
    virtual ~StardateValidator          (void) ;

    virtual int               Type      (void                     ) const ;
    virtual void              Fixup     (QString & input          ) const ;
    virtual QLocale           Locale    (void                     ) const ;
    virtual void              setLocale (const QLocale & locale   )       ;
    virtual QValidator::State isValid   (QString & input,int & pos) const ;
    virtual void              fixup     (QString & input          ) const ;
    virtual QValidator::State validate  (QString & input,int & pos) const ;

  protected:

    NAMEs Keywords ;

  private:

} ;

class Q_GADGETS_EXPORT BuddhistValidator : public QValidator
                                         , public  Validator
{
  Q_OBJECT
  public:

             BuddhistValidator          (QObject * parent) ;
    virtual ~BuddhistValidator          (void) ;

    virtual int               Type      (void                     ) const ;
    virtual void              Fixup     (QString & input          ) const ;
    virtual QLocale           Locale    (void                     ) const ;
    virtual void              setLocale (const QLocale & locale   )       ;
    virtual QValidator::State isValid   (QString & input,int & pos) const ;
    virtual void              fixup     (QString & input          ) const ;
    virtual QValidator::State validate  (QString & input,int & pos) const ;

  protected:

    NAMEs Keywords ;

  private:

} ;

class Q_GADGETS_EXPORT StarTrekValidator : public QValidator
                                         , public  Validator
{
  Q_OBJECT
  public:

             StarTrekValidator          (QObject * parent) ;
    virtual ~StarTrekValidator          (void) ;

    virtual int               Type      (void                     ) const ;
    virtual void              Fixup     (QString & input          ) const ;
    virtual QLocale           Locale    (void                     ) const ;
    virtual void              setLocale (const QLocale & locale   )       ;
    virtual QValidator::State isValid   (QString & input,int & pos) const ;
    virtual void              fixup     (QString & input          ) const ;
    virtual QValidator::State validate  (QString & input,int & pos) const ;

  protected:

    NAMEs Keywords ;

  private:

} ;

class Q_GADGETS_EXPORT TaiwanValidator  : public QValidator
                                        , public  Validator
{
  Q_OBJECT
  public:

             TaiwanValidator            (QObject * parent) ;
    virtual ~TaiwanValidator            (void) ;

    virtual int               Type      (void                     ) const ;
    virtual void              Fixup     (QString & input          ) const ;
    virtual QLocale           Locale    (void                     ) const ;
    virtual void              setLocale (const QLocale & locale   )       ;
    virtual QValidator::State isValid   (QString & input,int & pos) const ;
    virtual void              fixup     (QString & input          ) const ;
    virtual QValidator::State validate  (QString & input,int & pos) const ;

  protected:

    NAMEs Keywords ;

  private:

} ;

/*****************************************************************************
 *                                                                           *
 *                              Calendar Editors                             *
 *                                                                           *
 *****************************************************************************/

class Q_GADGETS_EXPORT CalendarTimeEdit : public QAbstractSpinBox
{
  Q_OBJECT
  Q_PROPERTY(long long stardate READ currentStardate WRITE setStardate DESIGNABLE true)
  public:

    explicit CalendarTimeEdit    (QWidget * parent) ;
    virtual ~CalendarTimeEdit    (void) ;

    virtual TUID currentStardate (void) = 0 ;
    virtual bool setStardate     (TUID sd) = 0 ;
    virtual void setTimeZone     (int gmt) = 0 ;
    virtual void setRange        (TimePeriod period) ;
    virtual void setRange        (TUID minimum,TUID maximum) ;

  protected:

    TimePeriod Range ;

    virtual bool ParseText       (QStringList & result,QString & text,NAMEs & names) ;
    virtual int  LocateText      (int cursor,QStringList & result,QString & text,NAMEs & names) ;

    virtual void FixupDateTime   (int year,int month,int mdays,int item) ;
    virtual void Adjustment      (int year,int month,int mdays) ;
    virtual int  SkipSpace       (int position,QString & text) ;
    virtual bool isLeap          (int year) ;

  private:

  public slots:

  protected slots:

  private slots:

  signals:

    void Changed                 (TUID time) ;

};

class Q_GADGETS_EXPORT GeogrianEdit : public CalendarTimeEdit
{
  Q_OBJECT
  public:

    explicit GeogrianEdit              (QWidget * parent) ;
    virtual ~GeogrianEdit              (void) ;

    virtual TUID currentStardate       (void) ;
    virtual bool setStardate           (TUID sd) ;
    virtual void setTimeZone           (int gmt) ;
    virtual void stepBy                (int steps) ;
    virtual QValidator::State validate (QString & input,int & pos) const ;
    virtual void setRange              (TimePeriod period) ;

  protected:

    DateTime            Time      ;
    int                 TimeZone  ;
    NAMEs               Names     ;
    GeogrianValidator * validator ;

    void   setTimeText                 (void) ;

    virtual void Adjustment            (int year,int month,int mdays) ;
    virtual StepEnabled stepEnabled    (void) const ;
    bool                madeChange     (const QString & text) ;

  private:

    QString GeogrianString             (void) ;
    void    AdjustDateTime             (int year,int month,int mdays,int item) ;

  public slots:

  protected slots:

    void   textChanged                 (const QString & text) ;

  private slots:

  signals:

};

class Q_GADGETS_EXPORT HoloceneEdit : public CalendarTimeEdit
{
  Q_OBJECT
  public:

    explicit HoloceneEdit              (QWidget * parent) ;
    virtual ~HoloceneEdit              (void) ;

    virtual TUID currentStardate       (void) ;
    virtual bool setStardate           (TUID sd) ;
    virtual void setTimeZone           (int gmt) ;
    virtual void stepBy                (int steps) ;
    virtual QValidator::State validate (QString & input,int & pos) const ;
    virtual void setRange              (TimePeriod period) ;

  protected:

    HoloceneCalendar    Time      ;
    int                 TimeZone  ;
    NAMEs               Names     ;
    HoloceneValidator * validator ;

    void                setTimeText    (void) ;

    virtual void        Adjustment     (int year,int month,int mdays) ;
    virtual bool        isLeap         (int year) ;
    virtual StepEnabled stepEnabled    (void) const ;
    bool                madeChange     (const QString & text) ;

  private:

    QString HoloceneString             (void) ;
    void    AdjustDateTime             (int year,int month,int mdays,int item) ;

  public slots:

  protected slots:

    void   textChanged                 (const QString & text) ;

  private slots:

  signals:

};

class Q_GADGETS_EXPORT BuddhistEdit : public CalendarTimeEdit
{
  Q_OBJECT
  public:

    explicit BuddhistEdit              (QWidget * parent) ;
    virtual ~BuddhistEdit              (void) ;

    virtual TUID currentStardate       (void) ;
    virtual bool setStardate           (TUID sd) ;
    virtual void setTimeZone           (int gmt) ;
    virtual void stepBy                (int steps) ;
    virtual QValidator::State validate (QString & input,int & pos) const ;
    virtual void setRange              (TimePeriod period) ;

  protected:

    BuddhistCalendar    Time      ;
    int                 TimeZone  ;
    NAMEs               Names     ;
    BuddhistValidator * validator ;

    void                setTimeText    (void) ;

    virtual void        Adjustment     (int year,int month,int mdays) ;
    virtual bool        isLeap         (int year) ;
    virtual StepEnabled stepEnabled    (void) const ;
    bool                madeChange     (const QString & text) ;

  private:

    QString BuddhistString             (void) ;
    void    AdjustDateTime             (int year,int month,int mdays,int item) ;

  public slots:

  protected slots:

    void   textChanged                 (const QString & text) ;

  private slots:

  signals:

};

class Q_GADGETS_EXPORT StardateEdit : public CalendarTimeEdit
{
  Q_OBJECT
  public:

    explicit StardateEdit              (QWidget * parent) ;
    virtual ~StardateEdit              (void) ;

    virtual TUID currentStardate       (void) ;
    virtual bool setStardate           (TUID sd) ;
    virtual void setTimeZone           (int gmt) ;
    virtual void stepBy                (int steps) ;
    virtual QValidator::State validate (QString & input,int & pos) const ;
    virtual void setRange              (TimePeriod period) ;

  protected:

    TUID                Stardate  ;
    StardateValidator * validator ;

    void                setTimeText    (void) ;

    virtual StepEnabled stepEnabled    (void) const ;
    bool                madeChange     (const QString & text) ;

  private:

  public slots:

  protected slots:

    void   textChanged                 (const QString & text) ;

  private slots:

  signals:

};

class Q_GADGETS_EXPORT StarTrekEdit : public CalendarTimeEdit
{
  Q_OBJECT
  public:

    explicit StarTrekEdit              (QWidget * parent) ;
    virtual ~StarTrekEdit              (void) ;

    virtual TUID currentStardate       (void) ;
    virtual bool setStardate           (TUID sd) ;
    virtual void setTimeZone           (int gmt) ;
    virtual void stepBy                (int steps) ;
    virtual QValidator::State validate (QString & input,int & pos) const ;
    virtual void setRange              (TimePeriod period) ;

  protected:

    StarTrek            Time      ;
    int                 TimeZone  ;
    NAMEs               Names     ;
    StarTrekValidator * validator ;

    void                setTimeText    (void) ;

    virtual StepEnabled stepEnabled    (void) const ;
    bool                madeChange     (const QString & text) ;

  private:

    QString StarTrekString             (void) ;

  public slots:

  protected slots:

    void   textChanged                 (const QString & text) ;

  private slots:

  signals:

};

class Q_GADGETS_EXPORT TaiwanEdit : public CalendarTimeEdit
{
  Q_OBJECT
  public:

    explicit TaiwanEdit                (QWidget * parent) ;
    virtual ~TaiwanEdit                (void) ;

    virtual TUID currentStardate       (void) ;
    virtual bool setStardate           (TUID sd) ;
    virtual void setTimeZone           (int gmt) ;
    virtual void stepBy                (int steps) ;
    virtual QValidator::State validate (QString & input,int & pos) const ;
    virtual void setRange              (TimePeriod period) ;

  protected:

    TaiwanCalendar    Time      ;
    int               TimeZone  ;
    NAMEs             Names     ;
    TaiwanValidator * validator ;

    void                setTimeText    (void) ;

    virtual void        Adjustment     (int year,int month,int mdays) ;
    virtual bool        isLeap         (int year) ;
    virtual StepEnabled stepEnabled    (void) const ;
    bool                madeChange     (const QString & text) ;

  private:

    QString TaiwanString               (void) ;
    void    AdjustDateTime             (int year,int month,int mdays,int item) ;

  public slots:

  protected slots:

    void   textChanged                 (const QString & text) ;

  private slots:

  signals:

};

/*****************************************************************************
 *                                                                           *
 *                                Painters                                   *
 *                                                                           *
 *****************************************************************************/

class Q_GADGETS_EXPORT Font : public QFont
{
  public:

    SUID    uuid     ;
    QString name     ;
    double  cm       ;
    bool    editable ;

    explicit    Font         (void) ;
    explicit    Font         (const QString & family              ,
                              int             pointSize = -1      ,
                              int             weight    = -1      ,
                              bool            italic    = false ) ;
    explicit    Font         (const QFont & font, QPaintDevice * pd) ;
    explicit    Font         (const QFont & font) ;
                Font         (const Font  & font) ;

    virtual int packsize     (void) ;
    void        setScreen    (Screen & screen) ;
    void        setDPI       (int DPI) ;

    QByteArray  Configure    (void) ;
    void        setConfigure (QByteArray & conf) ;

    QByteArray  toCpp        (QString variableName,int tabSize = 2) ;
    QFont       toQFont      (void) ;

  protected:

  private:

};

class Q_GADGETS_EXPORT Pen : public QPen
{
  public:

    SUID    uuid     ;
    QString name     ;
    bool    editable ;

    explicit Pen             (void) ;
    explicit Pen             (Qt::PenStyle style) ;
    explicit Pen             (const QColor   & color) ;
    explicit Pen             (const QBrush   & brush                   ,
                              qreal            width                   ,
                              Qt::PenStyle     style = Qt::SolidLine   ,
                              Qt::PenCapStyle  cap   = Qt::SquareCap   ,
                              Qt::PenJoinStyle join  = Qt::BevelJoin ) ;
    explicit Pen             (const QPen & pen) ;
    virtual ~Pen             (void) ;

    virtual int packsize     (void) ;
    QByteArray  Configure    (void) ;
    void        setConfigure (QByteArray & conf) ;

    QString     Export       (QString function) ;

  protected:

  private:

};

class Q_GADGETS_EXPORT Brush : public QBrush
{
  public:

    SUID    uuid     ;
    QString name     ;
    bool    editable ;

    explicit Brush (void);
    explicit Brush (Qt::BrushStyle    style);
    explicit Brush (const QColor    & color,Qt::BrushStyle style = Qt::SolidPattern);
    explicit Brush (Qt::GlobalColor   color,Qt::BrushStyle style = Qt::SolidPattern);
    explicit Brush (const QColor    & color,const QPixmap & pixmap);
    explicit Brush (Qt::GlobalColor   color,const QPixmap & pixmap);
    explicit Brush (const QPixmap   & pixmap);
    explicit Brush (const QImage    & image);
    explicit Brush (const QBrush    & other);
    explicit Brush (const QGradient & gradient);
    virtual ~Brush (void);

    virtual int packsize     (void) ;
    QByteArray  Configure    (void) ;
    void        setConfigure (QByteArray & conf) ;

    QByteArray  toCpp        (void) ;

  protected:

  private:

};

class Q_GADGETS_EXPORT Gradient
{
  public:

    SUID        uuid     ;
    QString     name     ;
    QGradient * gradient ;
    int         step     ;
    QColor      color    ;
    bool        editable ;

    explicit Gradient          (enum QGradient::Type type = QGradient::NoGradient) ;
    virtual ~Gradient          (void) ;

    virtual int packsize       (void) ;
    QByteArray  Configure      (void) ;
    void        setConfigure   (QByteArray & conf) ;

    QLinearGradient  * linear  (void) ;
    QRadialGradient  * radial  (void) ;
    QConicalGradient * conical (void) ;

    QBrush             Brush   (void) ;

    QByteArray         toCpp   (void) ;

  protected:

  private:

};

class Q_GADGETS_EXPORT ChartPiece
{
  public:

    QString Name       ;
    QColor  Color      ;
    float   Percentage ;

    explicit ChartPiece     (void) ;
             ChartPiece     (const ChartPiece & piece) ;
    virtual ~ChartPiece     (void) ;

    void addName            (QString name);
    void setColor           (Qt::GlobalColor color);
    void setColor           (QColor color);
    void setPercentage      (float percentage);

    ChartPiece & operator = (const ChartPiece & piece) ;

  protected:

  private:

};

class Q_GADGETS_EXPORT ChartPainter
{
  public:

    typedef enum  {
      Histogramm  ,
      Pie         ,
      Dpie        }
      type        ;
    typedef enum  {
      Horizontal  ,
      Vertical    ,
      Round       }
      legend      ;

    double alpha  ;

    explicit ChartPainter (void) ;
    virtual ~ChartPainter (void) ;

    int addPiece          (QString name,Qt::GlobalColor,float Percentage) ;
    int addPiece          (QString name,QColor, float Percentage) ;
    int setCords          (double x, double y, double w, double h) ;
    int setLegendCords    (double x, double y) ;
    int setType           (type t) ;
    int setLegendType     (legend t) ;
    int setShadows        (bool ok = true) ;
    int setFont           (QFont f) ;
    int draw              (QPainter * painter) ;
    int drawLegend        (QPainter * painter) ;

  protected:

    double            cX,cY,cW,cH,pW,lX,lY ;
    int               nPiece               ;
    int               ctype                ;
    int               cltype               ;
    bool              shadows              ;
    QFont             font                 ;
    QList<ChartPiece> pieces               ;

    QPointF GetPoint  (double angle,double R1 = 0,double R2 = 0) ;
    int     GetQuater (double angle) ;
    double  Angle360  (double angle) ;

  private:

};

/*****************************************************************************
 *                                                                           *
 *                             Paper Operations                              *
 *                                                                           *
 *****************************************************************************/

class Q_GADGETS_EXPORT PaperSize
{
  public:

    QString name      ;
    SUID    uuid      ;
    int     direction ;
    int     width     ;
    int     height    ;

    explicit    PaperSize  (void) ;
                PaperSize  (const PaperSize & paperSize) ;
    virtual ~   PaperSize  (void) ;

    PaperSize & operator = (const PaperSize & paperSize) ;

    QRectF      rect       (int direction) ;

};

class Q_GADGETS_EXPORT Paper
{
  public:

    QList<PaperSize> papers ;

    explicit     Paper       (void);
    virtual ~    Paper       (void);

    bool        load         (Sql & sql,QString table);
    bool        isValid      (PaperSize & paper);
    PaperSize & indexOf      (QString name);
    PaperSize & operator[]   (QString name);
    int         WidthPixels  (QString paper,int DPI);
    int         HeightPixels (QString paper,int DPI);
    static int  Pixels       (int DPI,int mm);
    QStringList Sizes        (void);

};

class Q_GADGETS_EXPORT PaperOptions
{
  public:

    int                 current   ;
    int                 direction ;
    QMap<int,PaperSize> papers    ;

    explicit PaperOptions     (void) ;
             PaperOptions     (const PaperOptions & options) ;
    virtual ~PaperOptions     (void) ;

    PaperOptions & operator = (const PaperOptions & options) ;

  protected:

  private:

};

class Q_GADGETS_EXPORT PictureOptions
{
  public:

    int dpi ;

    explicit PictureOptions     (void) ;
             PictureOptions     (const PictureOptions & options) ;
    virtual ~PictureOptions     (void) ;

    PictureOptions & operator = (const PictureOptions & options) ;

  protected:

  private:

};

/*****************************************************************************
 *                                                                           *
 *                             Widget Information                            *
 *                                                                           *
 *****************************************************************************/

class Q_GADGETS_EXPORT Screen
{
  public:

    QSize  MonitorSize        ;
    qreal  HeightInCentimeter ;
    qreal  WidthInCentimeter  ;
    int    WidthPixels        ;
    int    WidthLength        ;
    int    HeightPixels       ;
    int    HeightLength       ;
    QSizeF MonitorFactors     ;

    explicit Screen       (void);
             Screen       (const Screen & screen) ;
    virtual ~Screen       (void);

    Screen & operator =   (const Screen & screen) ;

    void     setMonitor   (qreal w,qreal h);
    QPoint   position     (qreal x,qreal y);
    QSize    dimension    (qreal width,qreal height);

    int      widthPixels  (int millimeters);
    int      heightPixels (int millimeters);
    qreal    widthPixels  (qreal millimeters);
    qreal    heightPixels (qreal millimeters);
    int      widthLength  (int pixels);
    int      heightLength (int pixels);

    void     Initialize   (void) ;
    void     Detect       (void) ;

  protected:

  private:

};

class Q_GADGETS_EXPORT RasterOptions
{
  public:

    int            raster      ;
    int            numerator   ;
    int            denominator ;
    Screen         screen      ;
    PaperOptions   paper       ;
    PictureOptions picture     ;

    explicit RasterOptions     (void) ;
             RasterOptions     (const RasterOptions & options) ;
    virtual ~RasterOptions     (void) ;

    RasterOptions & operator = (const RasterOptions & options) ;

  protected:

  private:

};

class Q_GADGETS_EXPORT DockInformation
{
  public:

    bool       floating ;
    bool       show     ;
    int        area     ;
    int        width    ;
    int        height   ;
    QByteArray geometry ;

    explicit DockInformation     (void) ;
             DockInformation     (const DockInformation & dock) ;
    virtual ~DockInformation     (void) ;

    DockInformation & operator = (const DockInformation & dock) ;

};

class Q_GADGETS_EXPORT WidgetInformation
{
  public:

    bool    visible  ;
    bool    minimize ;
    bool    maximize ;
    QRect   geometry ;

    explicit WidgetInformation (QWidget * widget);
    explicit WidgetInformation (void);
    virtual ~WidgetInformation (void);

    void setWidget             (QWidget * widget);
    void restoreWidget         (QWidget * widget);

    bool Load                  (QString scope,Settings & settings);
    bool Save                  (QString scope,Settings & settings);

  protected:

  private:

};

class Q_GADGETS_EXPORT MachineProfiler : public QObject
                                       , public Thread
{
  Q_OBJECT
  public:

    // CpuInterval    => CPU Profiler update interval
    // SystemInterval => Process usage probe interval
    // TSC            => TSC interval for ms (millisecond)
    WMAPs            variables   ;
    CPU::Usage       machine     ;
    CPU::Usage       process     ;
    CPU::Profiler    profiler    ;
    CPU::Profiler    self        ;
    ProcessDetails * local       ;
    Personality    * personality ;
    Thread         * KeyThread   ;

    explicit             MachineProfiler  (QObject * parent = NULL) ;
    virtual             ~MachineProfiler  (void) ;

    static int           sizeHint         (void) ;

    virtual bool         setData          (QByteArray & data) ;
    virtual bool         setData          (void * data,int size) ;

    qint32            *  IntPointer       (QString scope,QString key) ;
    qint64            *  TuidPointer      (QString scope,QString key) ;
    quint64           *  UuidPointer      (QString scope,QString key) ;
    char              *  NamePointer      (QString scope,QString key) ;
    char              *  GetFriends       (int & size ) ;
    N::ProcessDetails *  GetProcesses     (int & total) ;

    virtual bool         isReadable       (void) ;
    virtual bool         isWritable       (void) ;

  protected:

    void * data ;
    int    size ;

    virtual void         run              (int Type,ThreadData * data) ;

    virtual void         Cpu              (ThreadData * data) ;
    virtual void         System           (ThreadData * data) ;
    virtual void         Caller           (ThreadData * data) ;

    virtual void         Update           (void) ;
    virtual void         Creator          (void) ;

  private:

    virtual int          Locate           (quint64 instance) ;

  public slots:

    virtual bool         Initialize       (void) ;
    virtual bool         startup          (void) ;
    virtual bool         startup          (VarArgs & args) ;
    virtual bool         stop             (void) ;

    virtual QVariant     setValue         (QString key,QVariant value) ;
    virtual QVariant     value            (QString key) ;

    virtual bool         setReading       (bool reading) ;
    virtual bool         setWriting       (bool writing) ;

    virtual bool         GetApplications  (QStringList & applications) ;
    virtual quint64      GetInstance      (QString app) ;

    qint64               BootUpTime       (void) ;
    qint64               ApplicationTime  (void) ;

    virtual void         FlushPersonality (void) ;

  protected slots:

  private slots:

  signals:

} ;

}

Q_DECLARE_METATYPE ( N::ColorYUV                   )
Q_DECLARE_METATYPE ( N::ColorYIQ                   )
Q_DECLARE_METATYPE ( N::ColorXYZ                   )
Q_DECLARE_METATYPE ( N::ColorLab                   )
Q_DECLARE_METATYPE ( N::ColorLUV                   )
Q_DECLARE_METATYPE ( N::ColorSpace                 )
Q_DECLARE_METATYPE ( N::Palette                    )
// Q_DECLARE_METATYPE ( N::IntValidator               )
// Q_DECLARE_METATYPE ( N::DoubleValidator            )
// Q_DECLARE_METATYPE ( N::RegExpValidator            )
// Q_DECLARE_METATYPE ( N::RegularExpressionValidator )
// Q_DECLARE_METATYPE ( N::UuidValidator              )
// Q_DECLARE_METATYPE ( N::GeogrianValidator          )
// Q_DECLARE_METATYPE ( N::HoloceneValidator          )
// Q_DECLARE_METATYPE ( N::BuddhistValidator          )
// Q_DECLARE_METATYPE ( N::StardateValidator          )
// Q_DECLARE_METATYPE ( N::StarTrekValidator          )
// Q_DECLARE_METATYPE ( N::TaiwanValidator            )
// Q_DECLARE_METATYPE ( N::GeogrianEdit               )
// Q_DECLARE_METATYPE ( N::HoloceneEdit               )
// Q_DECLARE_METATYPE ( N::BuddhistEdit               )
// Q_DECLARE_METATYPE ( N::StardateEdit               )
// Q_DECLARE_METATYPE ( N::StarTrekEdit               )
// Q_DECLARE_METATYPE ( N::TaiwanEdit                 )
Q_DECLARE_METATYPE ( N::Font                       )
Q_DECLARE_METATYPE ( N::Pen                        )
Q_DECLARE_METATYPE ( N::Brush                      )
Q_DECLARE_METATYPE ( N::Gradient                   )
Q_DECLARE_METATYPE ( N::ChartPiece                 )
Q_DECLARE_METATYPE ( N::ChartPainter               )
Q_DECLARE_METATYPE ( N::PaperSize                  )
Q_DECLARE_METATYPE ( N::Paper                      )
Q_DECLARE_METATYPE ( N::PaperOptions               )
Q_DECLARE_METATYPE ( N::PictureOptions             )
Q_DECLARE_METATYPE ( N::Screen                     )
Q_DECLARE_METATYPE ( N::RasterOptions              )
Q_DECLARE_METATYPE ( N::DockInformation            )
Q_DECLARE_METATYPE ( N::WidgetInformation          )

Q_DECLARE_INTERFACE( N::Validator        , "com.neutrino.gui.validator"   )
Q_DECLARE_INTERFACE( N::CalendarTimeEdit , "com.neutrino.calendar.editor" )

QT_END_NAMESPACE

#endif
