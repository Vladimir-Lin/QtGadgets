#include <qtgadgets.h>

namespace N
{

#pragma pack(push,1)

typedef struct                       { // Total 513 KB
  qint32           total             ; // currently, this is a fixed number = 512
  qint32           processes         ; // current running processes
  char             buffer  [ 1016 ]  ;
  ProcessDetails   details [  512 ]  ; // actually, ProcessDetails details [ total ]
} ProcessesDetails                   ;

typedef struct                       { // 1024 Bytes
  qint64           Memory            ; // Device memory size
  qint32           Blocks            ; // CUDA Blocks
  qint32           Threads           ; // CUDA Threads
  char             buffer [ 496 ]    ;
  char             Name   [ 256 ]    ; // CUDA device name
  char             PciBus [ 256 ]    ; // CUDA device PCI bus
} CudaInstance                       ;

typedef struct                       { // Total 65 KB
  qint32           Version           ; // CUDA Version
  qint32           Devices           ; // CUDA Device count, max 64
  qint32           Offset            ; // offset position for internal use buffer
  char             Buffer   [ 1012 ] ; // internal use
  CudaInstance     Profiles [   64 ] ; // CUDA device profiles
} CudaDetails                        ;

typedef struct                       { // OpenGL details
  char             Version  [  64 ]  ; // OpenGL Version
  char             Vendor   [  64 ]  ; // OpenGL Vendor
  char             Renderer [  64 ]  ; // OpenGL Renderer
  char             Shading  [  64 ]  ; // OpenGL Shading Language
  qint32           Flags    [  64 ]  ; // OpenGL Flags
  char             Buffer   [ 512 ]  ; // not used now
} OpenGLdetails                      ;

typedef struct                       { // Total 8 KB
  qint32           calling           ; // caller is writing
  qint32           answering         ; // receiver is writing
  quint64          caller            ; // caller instance
  quint64          receiver          ; // receiver instance
  char             sending [ 4080 ]  ; // sender buffer
  char             answer  [ 4080 ]  ; // answer buffer
} CallHub                            ;

typedef struct                       {
  qint32           readable          ; // Read lock
  qint32           writable          ; // Write lock
  qint32           size              ;
  char             buffer  [ 1016 ]  ;
  CpuDetails       cpu               ; // CPU details
  ProcessesDetails processes         ; // Processes details
  CudaDetails      cuda              ; // CUDA details
  OpenGLdetails    opengl            ; // OpenGL details
  CallHub          hub               ; // Caller HUB
  char             friends [ 8192 ]  ;
} SystemDetails                      ;

#pragma pack(pop)

}

N::MachineProfiler:: MachineProfiler( QObject * parent )
                   : QObject        (           parent )
                   , data           ( NULL             )
                   , size           ( 0                )
                   , local          ( NULL             )
                   , personality    ( NULL             )
                   , KeyThread      ( NULL             )
{
  variables [ "Port"           ] = 0       ;
  variables [ "CpuInterval"    ] = 1200    ;
  variables [ "SystemInterval" ] =  671    ;
  variables [ "TSC"            ] = 4013500 ;
  variables [ "Running"        ] = false   ;
}

N::MachineProfiler::~MachineProfiler(void)
{
}

int N::MachineProfiler::sizeHint(void)
{
  return sizeof(N::SystemDetails) ;
}

bool N::MachineProfiler::isReadable(void)
{
  if ( NULL == data ) return false           ;
  SystemDetails * s = (SystemDetails *) data ;
  return ( 2 == s -> readable )              ;
}

bool N::MachineProfiler::isWritable(void)
{
  if ( NULL == data ) return false           ;
  SystemDetails * s = (SystemDetails *) data ;
  return ( 2 == s -> writable )              ;
}

bool N::MachineProfiler::setReading(bool reading)
{
  if ( NULL == data ) return false           ;
  SystemDetails * s = (SystemDetails *) data ;
  if ( reading )                             {
    while ( 0 == s -> readable )             {
      Time::msleep ( 2 )                     ;
    }                                        ;
    s -> readable = 0                        ;
  } else                                     {
    if    ( 0 == s -> readable )             {
      s -> readable = 2                      ;
    }                                        ;
  }                                          ;
  return true                                ;
}

bool N::MachineProfiler::setWriting(bool writing)
{
  if ( NULL == data ) return false           ;
  SystemDetails * s = (SystemDetails *) data ;
  if ( writing )                             {
    while ( 0 == s -> writable )             {
      Time::msleep ( 2 )                     ;
    }                                        ;
    s -> writable = 0                        ;
  } else                                     {
    if    ( 0 == s -> writable )             {
      s -> writable = 2                      ;
    }                                        ;
  }                                          ;
  return true                                ;
}

bool N::MachineProfiler::setData(QByteArray & d)
{
  int s = d . size ( )                 ;
  if ( s < sizeHint ( ) ) return false ;
  data = (void *) d . data ( )         ;
  size =          d . size ( )         ;
  return true                          ;
}

bool N::MachineProfiler::setData(void * d,int s)
{
  if ( s < sizeHint ( ) ) return false ;
  data = d                             ;
  size = s                             ;
  return true                          ;
}

QVariant N::MachineProfiler::value(QString key)
{
  return variables [ key ] ;
}

QVariant N::MachineProfiler::setValue(QString key,QVariant v)
{
  variables [ key ] = v    ;
  return variables [ key ] ;
}

qint32 * N::MachineProfiler::IntPointer(QString scope,QString key)
{
  if ( NULL == data ) return NULL                                 ;
  SystemDetails * d = (SystemDetails *) data                      ;
  QString         s = scope . toLower ( )                         ;
  QString         k = key   . toLower ( )                         ;
  if ( "cpu"     == s )                                           {
    if ( "initialized" == k ) return & ( d -> cpu . Initialized ) ;
    if ( "processors"  == k ) return & ( d -> cpu . Processors  ) ;
  }                                                               ;
  if ( "process" == s )                                           {
    if ( local == NULL ) return NULL                              ;
    if ( "occupied"    == k ) return & ( local -> occupied )      ;
    if ( "openmp"      == k ) return & ( local -> openmp   )      ;
    if ( "machine"     == k ) return & ( local -> machine  )      ;
    if ( "process"     == k ) return & ( local -> process  )      ;
    if ( "port"        == k ) return & ( local -> port     )      ;
    if ( "interval"    == k ) return & ( local -> interval )      ;
    if ( "load"        == k ) return & ( local -> load     )      ;
    if ( "offset"      == k ) return & ( local -> offset   )      ;
  }                                                               ;
  if ( "cuda"    == s )                                           {
    if ( "Version"     == k ) return & ( d -> cuda . Version )    ;
    if ( "Devices"     == k ) return & ( d -> cuda . Devices )    ;
    if ( "Offset"      == k ) return & ( d -> cuda . Offset  )    ;
  }                                                               ;
  if ( "opengl"  == s )                                           {
    if ( "Flags"       == k ) return d -> opengl . Flags          ;
  }                                                               ;
  return NULL                                                     ;
}

qint64 * N::MachineProfiler::TuidPointer(QString scope,QString key)
{
  if ( NULL == data ) return NULL                                            ;
  SystemDetails * d = (SystemDetails *) data                                 ;
  QString s = scope . toLower ( )                                            ;
  QString k = key   . toLower ( )                                            ;
  if   ( "cpu"              == s    )                                        {
    if ( "memory"           == k    ) return & ( d -> cpu . Memory         ) ;
    if ( "cache"            == k    ) return & ( d -> cpu . Cache          ) ;
  }                                                                          ;
  if   ( "process"          == s    )                                        {
    if ( local              == NULL ) return NULL                            ;
    if ( "peak"             == k    ) return & ( local -> peak             ) ;
    if ( "working"          == k    ) return & ( local -> working          ) ;
    if ( "page"             == k    ) return & ( local -> page             ) ;
    if ( "timestamp"        == k    ) return & ( local -> timestamp        ) ;
    if ( "registered"       == k    ) return & ( local -> registered       ) ;
    if ( "updated"          == k    ) return & ( local -> updated          ) ;
    if ( "total"            == k    ) return & ( local -> total            ) ;
    if ( "available"        == k    ) return & ( local -> available        ) ;
    if ( "virtualTotal"     == k    ) return & ( local -> virtualTotal     ) ;
    if ( "virtualAvailable" == k    ) return & ( local -> virtualAvailable ) ;
  }                                                                          ;
  if   ( "cuda"             == s    )                                        {
  }                                                                          ;
  if   ( "opengl"           == s    )                                        {
  }                                                                          ;
  return NULL                                                                ;
}

quint64 * N::MachineProfiler::UuidPointer(QString scope,QString key)
{
  if ( NULL == data ) return NULL                              ;
  SystemDetails * d = (SystemDetails *) data                   ;
  QString         s = scope . toLower ( )                      ;
  QString         k = key   . toLower ( )                      ;
  if   ( "cpu"      == s    )                                  {
    if ( "features" == k    ) return & ( d -> cpu . Features ) ;
  }                                                            ;
  if   ( "process"  == s    )                                  {
    if ( local      == NULL ) return NULL                      ;
    if ( "instance" == k    ) return & ( local -> instance   ) ;
  }                                                            ;
  if   ( "cuda"     == s    )                                  {
  }                                                            ;
  if   ( "opengl"   == s    )                                  {
  }                                                            ;
  return NULL                                                  ;
}

char * N::MachineProfiler::NamePointer(QString scope,QString key)
{
  if ( NULL == data ) return NULL                                    ;
  SystemDetails * d = (SystemDetails *) data                         ;
  QString         s = scope . toLower ( )                            ;
  QString         k = key   . toLower ( )                            ;
  if   ( "cpu"         == s )                                        {
    if ( "name"        == k ) return (char *) d -> cpu    . Name     ;
    if ( "buffer"      == k ) return (char *) d -> cpu    . Buffer   ;
  }                                                                  ;
  if   ( "process"     == s )                                        {
    if ( local == NULL ) return NULL                                 ;
    if ( "application" == k ) return (char *) local -> application   ;
    if ( "buffer"      == k ) return (char *) local -> buffer        ;
  }                                                                  ;
  if   ( "cuda"        == s )                                        {
    if ( "buffer"      == k ) return (char *) d -> cuda   . Buffer   ;
  }                                                                  ;
  if   ( "opengl"      == s )                                        {
    if ( "version"     == k ) return (char *) d -> opengl . Version  ;
    if ( "vendor"      == k ) return (char *) d -> opengl . Vendor   ;
    if ( "renderer"    == k ) return (char *) d -> opengl . Renderer ;
    if ( "shading"     == k ) return (char *) d -> opengl . Shading  ;
    if ( "buffer"      == k ) return (char *) d -> opengl . Buffer   ;
  }                                                                  ;
  return NULL                                                        ;
}

char * N::MachineProfiler::GetFriends(int & s)
{
  if ( NULL == data )                        {
    s = 0                                    ;
    return NULL                              ;
  }                                          ;
  SystemDetails * d = (SystemDetails *) data ;
  ////////////////////////////////////////////
  s = 8192                                   ;
  return  d -> friends                       ;
}

N::ProcessDetails * N::MachineProfiler::GetProcesses(int & total)
{
  if ( NULL == data )                        {
    total = 0                                ;
    return NULL                              ;
  }                                          ;
  SystemDetails * d = (SystemDetails *) data ;
  ////////////////////////////////////////////
  total = d -> processes . total             ;
  return  d -> processes . details           ;
}

bool N::MachineProfiler::GetApplications(QStringList & applications)
{
  if ( NULL == data ) return false                            ;
  SystemDetails * d = (SystemDetails *) data                  ;
  /////////////////////////////////////////////////////////////
  for (int i = 0 ; i < d -> processes . total ; i++ )         {
    N::ProcessDetails * pd = & d -> processes . details [ i ] ;
    if ( pd -> occupied > 0 )                                 {
      QString app = QString::fromUtf8 ( pd -> application )   ;
      if ( pd -> instance > 0 )                               {
        if ( ! applications . contains ( app ) )              {
          applications << app                                 ;
        }                                                     ;
      }                                                       ;
    }                                                         ;
  }                                                           ;
  /////////////////////////////////////////////////////////////
  return ( applications . count ( ) > 0 )                     ;
}

quint64 N::MachineProfiler::GetInstance(QString name)
{
  if ( NULL == data ) return 0                                ;
  SystemDetails * d = (SystemDetails *) data                  ;
  /////////////////////////////////////////////////////////////
  for (int i = 0 ; i < d -> processes . total ; i++ )         {
    N::ProcessDetails * pd = & d -> processes . details [ i ] ;
    if ( pd -> occupied > 0 )                                 {
      QString app = QString::fromUtf8 ( pd -> application )   ;
      if ( pd -> instance > 0 )                               {
        if ( app == name ) return pd -> instance              ;
      }                                                       ;
    }                                                         ;
  }                                                           ;
  /////////////////////////////////////////////////////////////
  return 0                                                    ;
}

qint64 N::MachineProfiler::BootUpTime(void)
{
  qint64 t = machine . Timestamp ( )              ;
  qint64 d = variables [ "TSC" ] . toLongLong ( ) ;
  if ( d <= 0 ) return 0                          ;
  return t / d                                    ;
}

qint64 N::MachineProfiler::ApplicationTime(void)
{
  if ( NULL == local ) return 0                   ;
  qint64 r = local -> registered                  ;
  qint64 t = machine . Timestamp ( )              ;
  qint64 d = variables [ "TSC" ] . toLongLong ( ) ;
  if ( d <= 0 ) return 0                          ;
  return ( t - r ) / d                            ;
}

void N::MachineProfiler::run(int T,ThreadData * d)
{
  if ( ! IsContinue ( d ) ) return ;
  switch ( T )                     {
    case 10001                     :
      System ( d )                 ;
    break                          ;
    case 10002                     :
      Cpu    ( d )                 ;
    break                          ;
    case 10003                     :
      Caller ( d )                 ;
    break                          ;
  }                                ;
}

bool N::MachineProfiler::startup(void)
{
  isContinue = true ;
  start ( 10001 )   ;
  start ( 10002 )   ;
  return true       ;
}

bool N::MachineProfiler::startup(VarArgs & args)
{
  isContinue = true      ;
  start ( 10001 , args ) ;
  start ( 10002        ) ;
  return true            ;
}

bool N::MachineProfiler::stop(void)
{
  isContinue = false ;
  return true        ;
}

int N::MachineProfiler::Locate(quint64 instance)
{
  if ( NULL == data ) return -1                                  ;
  SystemDetails * s  = (SystemDetails *) data                    ;
  int             t  = s -> processes . total                    ;
  qint64          dt = variables [ "TSC" ] . toLongLong ( )      ;
  qint64          t1                                             ;
  qint64          t2                                             ;
  ////////////////////////////////////////////////////////////////
  if ( dt > 10000 )                                              {
    t2 = machine . Timestamp ( )                                 ;
    for (int i=0;i<t;i++)                                        {
      qint64 tx                                                  ;
      t1  = s -> processes . details [ i ] . timestamp           ;
      tx  = t2 - t1                                              ;
      tx /= dt                                                   ;
      if ( tx > 3000 )                                           {
        s -> processes . details [ i ] . occupied = 0            ;
        s -> processes . details [ i ] . instance = 0            ;
        ::memset ( s->processes.details[i].application,0,256 )   ;
      }                                                          ;
    }                                                            ;
  }                                                              ;
  ////////////////////////////////////////////////////////////////
  for (int i=0;i<t;i++)                                          {
    if ( instance == s -> processes . details [ i ] . instance ) {
      return i                                                   ;
    }                                                            ;
  }                                                              ;
  ////////////////////////////////////////////////////////////////
  for (int i=0;i<t;i++)                                          {
    if ( s -> processes . details [ i ] . occupied <= 0        ) {
      return i                                                   ;
    }                                                            ;
  }                                                              ;
  ////////////////////////////////////////////////////////////////
  return -1                                                      ;
}

bool N::MachineProfiler::Initialize(void)
{
  if ( NULL == data ) return false                                       ;
  SystemDetails * s = (SystemDetails *) data                             ;
  if ( s -> processes . total == 512 ) return true                       ;
  ////////////////////////////////////////////////////////////////////////
  s -> readable              = 0                                         ;
  s -> writable              = 0                                         ;
  ////////////////////////////////////////////////////////////////////////
  ::memset (     s -> buffer   , 0 , 1016                  )             ;
  ::memset (     s -> friends  , 0 , 8192                  )             ;
  ::memset ( & ( s -> cpu    ) , 0 , sizeof(CpuDetails)    )             ;
  ::memset ( & ( s -> cuda   ) , 0 , sizeof(CudaDetails)   )             ;
  ::memset ( & ( s -> opengl ) , 0 , sizeof(OpenGLdetails) )             ;
  ::memset ( & ( s -> hub    ) , 0 , sizeof(CallHub)       )             ;
  ////////////////////////////////////////////////////////////////////////
  s -> size                  = size                                      ;
  s -> processes . total     = 512                                       ;
  s -> processes . processes = 0                                         ;
  ////////////////////////////////////////////////////////////////////////
  machine . Tell ( & ( s -> cpu ) )                                      ;
  ////////////////////////////////////////////////////////////////////////
  s -> cuda . Version = QtCUDA::Version ( )                              ;
  s -> cuda . Devices = QtCUDA::Devices ( )                              ;
  s -> cuda . Offset  = 1024                                             ;
  ////////////////////////////////////////////////////////////////////////
  CudaInstance * cid                                                     ;
  int            ttt = s -> cuda . Devices                               ;
  cid = (CudaInstance *) ( ( (char *)&(s->cuda) ) + s -> cuda . Offset ) ;
  if ( ttt > 64 ) ttt = 64                                               ;
  for (int i = 0 ; i < ttt ; i++ )                                       {
    cudaHandle cuda = QtCUDA::Handle ( i    )                            ;
    QString    n    = QtCUDA::Name   ( cuda )                            ;
    QString    pci  = QtCUDA::PciBus ( cuda )                            ;
    size_t     v    = QtCUDA::Memory ( cuda )                            ;
    //////////////////////////////////////////////////////////////////////
    cid [ i ] . Memory  = v                                              ;
    cid [ i ] . Blocks  = 0                                              ;
    cid [ i ] . Threads = 0                                              ;
    CopyToArray ( cid [ i ] . Name   , 256 , n   )                       ;
    CopyToArray ( cid [ i ] . PciBus , 256 , pci )                       ;
  }                                                                      ;
  ////////////////////////////////////////////////////////////////////////
  QMap<int,QString> GLI                                                  ;
  if ( QtGL :: Details ( GLI ) )                                         {
    #define COGL(item,length,tag)                                        \
                CopyToArray ( s -> opengl . item  , length , GLI [ tag ] )
    COGL ( Version  , 64 , GL_VERSION                  )                 ;
    COGL ( Vendor   , 64 , GL_VENDOR                   )                 ;
    COGL ( Renderer , 64 , GL_RENDERER                 )                 ;
    COGL ( Shading  , 64 , GL_SHADING_LANGUAGE_VERSION )                 ;
    #undef  COGL
  }                                                                      ;
  ////////////////////////////////////////////////////////////////////////
  s -> readable              = 2                                         ;
  s -> writable              = 2                                         ;
  return true                                                            ;
}

void N::MachineProfiler::FlushPersonality (void)
{
  if ( NULL == data        ) return                                          ;
  if ( NULL == personality ) return                                          ;
  ////////////////////////////////////////////////////////////////////////////
  SystemDetails * s  = (SystemDetails *) data                                ;
  Thread        * kt = KeyThread                                             ;
  int             sc = qApp -> desktop ( ) -> screenCount ( )                ;
  int             kc = 0                                                     ;
  ////////////////////////////////////////////////////////////////////////////
  if ( NULL != kt ) kc = kt -> AllThreads . count ( )                        ;
  ////////////////////////////////////////////////////////////////////////////
  personality -> lock   ( )                                                  ;
  ////////////////////////////////////////////////////////////////////////////
  personality -> Information [ "Processors"   ] = s -> cpu . Processors      ;
  personality -> Information [ "Memory"       ] = s -> cpu . Memory          ;
  personality -> Information [ "CpuName"      ] = s -> cpu . Name            ;
  ////////////////////////////////////////////////////////////////////////////
  personality -> Information [ "MemoryLoad"   ] = local -> load              ;
  personality -> Information [ "MemoryTotal"  ] = local -> total             ;
  personality -> Information [ "MemoryAvail"  ] = local -> available         ;
  personality -> Information [ "VirtualTotal" ] = local -> virtualTotal      ;
  personality -> Information [ "VirtualAvail" ] = local -> virtualAvailable  ;
  personality -> Information [ "PeakMemory"   ] = local -> peak              ;
  personality -> Information [ "WorkMemory"   ] = local -> working           ;
  personality -> Information [ "Instance"     ] = local -> instance          ;
  personality -> Information [ "MachineCpu"   ] = local -> machine           ;
  personality -> Information [ "ProcessCpu"   ] = local -> process           ;
  personality -> Information [ "RDTSC"        ] = local -> timestamp         ;
  personality -> Information [ "AppTime"      ] = ApplicationTime ( )        ;
  personality -> Information [ "BootUp"       ] = BootUpTime      ( )        ;
  ////////////////////////////////////////////////////////////////////////////
  personality -> Information [ "CudaDevices"  ] = s -> cuda . Devices        ;
  ////////////////////////////////////////////////////////////////////////////
  personality -> Information [ "Monitors"     ] = sc                         ;
  personality -> Information [ "KeyThreads"   ] = kc                         ;
  ////////////////////////////////////////////////////////////////////////////
  personality -> Information [ "ProbeTime" ] = QDateTime::currentDateTime () ;
  ////////////////////////////////////////////////////////////////////////////
  personality -> unlock ( )                                                  ;
}

void N::MachineProfiler::Update(void)
{
  if ( NULL == local ) return                                  ;
  machine  . Tell                         ( local            ) ;
  local   -> machine = machine . GetUsage ( true             ) ;
  local   -> process = process . GetUsage ( false            ) ;
  profiler . setComsumption               ( local -> machine ) ;
  self     . setComsumption               ( local -> process ) ;
  FlushPersonality                        (                  ) ;
}

void N::MachineProfiler::Creator(void)
{
  if ( NULL == data  ) return                         ;
  if ( NULL == local ) return                         ;
  /////////////////////////////////////////////////////
  bool master =  ( 1 == ( local -> flags & 1 ) )      ;
  if ( master        ) return                         ;
  /////////////////////////////////////////////////////
  SystemDetails  * s  = (SystemDetails *) data        ;
  int              t  = s -> processes . total        ;
  ProcessDetails * p  = NULL                          ;
  ProcessDetails * l  = NULL                          ;
  /////////////////////////////////////////////////////
  for (int i = 0 ; ( NULL == l ) && ( i < t ) ; i++ ) {
    p = & ( s -> processes . details [ i ] )          ;
    if ( p -> occupied > 0 )                          {
      master = ( 1 == ( p -> flags & 1 ) )            ;
      if ( master ) l = p                             ;
    }                                                 ;
  }                                                   ;
  if ( NULL != l ) return                             ;
  /////////////////////////////////////////////////////
  for (int i = 0 ; i < t ; i++ )                      {
    p = & ( s -> processes . details [ i ] )          ;
    if ( p -> occupied > 0 )                          {
      if ( local -> instance == p -> instance )       {
        p -> flags |= 1                               ;
        profiler . setValue ( "Record" , true )       ;
        profiler . setValue ( "Flush"  , true )       ;
      }                                               ;
      return                                          ;
    }                                                 ;
  }                                                   ;
}

void N::MachineProfiler::Cpu(ThreadData * d)
{
  VarArgs V = d -> Arguments                                 ;
  if ( V . count ( ) > 0 )                                   {
    variables [ "CpuInterval" ] = V [ 0 ]                    ;
  }                                                          ;
  if ( profiler . Load ( ) ) profiler . index = 86400        ;
  if ( self     . Load ( ) ) self     . index = 86400        ;
  while ( IsContinue ( d ) )                                 {
    profiler . Flush ( )                                     ;
    self     . Flush ( )                                     ;
    Creator          ( )                                     ;
    Time::msleep ( variables [ "CpuInterval" ] . toInt ( ) ) ;
  }                                                          ;
  profiler . Store ( )                                       ;
  self     . Store ( )                                       ;
}

void N::MachineProfiler::System(ThreadData * d)
{
  variables [ "Running" ] = true                                             ;
  VarArgs V = d -> Arguments                                                 ;
  if ( V . count ( ) > 0 )                                                   {
    variables [ "SystemInterval" ] = V [ 0 ]                                 ;
  }                                                                          ;
  QDateTime T1                                                               ;
  QDateTime T2                                                               ;
  qint64    t1                                                               ;
  qint64    t2                                                               ;
  qint64    dt                                                               ;
  qint64    ms                                                               ;
  T1 = nTimeNow                                                              ;
  t1 = machine . Timestamp ( )                                               ;
  while ( IsContinue ( d ) )                                                 {
    if ( NULL != data )                                                      {
      SystemDetails * s = (SystemDetails *) data                             ;
      ////////////////////////////////////////////////////////////////////////
      if ( s -> processes . total <= 0 )                                     {
        Initialize ( )                                                       ;
      }                                                                      ;
      ////////////////////////////////////////////////////////////////////////
      while ( IsContinue ( d ) && ( 0 == s -> readable ) )                   {
        Time::msleep ( 2 )                                                   ;
      }                                                                      ;
      if ( ! IsContinue ( d ) ) break                                        ;
      ////////////////////////////////////////////////////////////////////////
      if ( NULL == local )                                                   {
        ProcessDetails pd                                                    ;
        ::memset ( &pd , 0 , sizeof(ProcessDetails) )                        ;
        if ( ( machine . Tell ( &pd ) ) && ( pd . instance > 0 ) )           {
          while ( IsContinue ( d ) && ( 0 == s -> readable ) )               {
            Time::msleep ( 2 )                                               ;
          }                                                                  ;
          int pos = Locate ( pd . instance )                                 ;
          if ( pos >= 0 )                                                    {
            local  = & ( s -> processes . details [ pos ] )                  ;
            s -> readable = 0                                                ;
            s -> writable = 0                                                ;
            s -> processes . processes ++                                    ;
            local -> occupied = 1                                            ;
            local -> port     = variables [ "Port" ] . toInt ( )             ;
            local -> flags    = 0                                            ;
            if ( profiler  . value ( "Flush" ) . toBool ( ) )                {
              local -> flags |= 1                                            ;
            }                                                                ;
            if ( variables . contains ( "Name" ) )                           {
              QString as = variables [ "Name" ] . toString ( )               ;
              CopyToArray ( local -> application , 256 , as )                ;
            }                                                                ;
            if ( local -> interval <= 0 )                                    {
              local -> interval = variables [ "SystemInterval" ] . toInt ( ) ;
            } else                                                           {
              if ( V . count ( ) <= 0 )                                      {
                variables [ "SystemInterval" ] = local -> interval           ;
              }                                                              ;
            }                                                                ;
            Update ( )                                                       ;
            s -> readable = 2                                                ;
            s -> writable = 2                                                ;
          }                                                                  ;
        }                                                                    ;
      } else                                                                 {
        s -> readable = 0                                                    ;
        s -> writable = 0                                                    ;
        Update ( )                                                           ;
        s -> readable = 2                                                    ;
        s -> writable = 2                                                    ;
      }                                                                      ;
    }                                                                        ;
    //////////////////////////////////////////////////////////////////////////
    T2  = nTimeNow                                                           ;
    ms  = T1 . msecsTo ( T2 )                                                ;
    t2  = machine . Timestamp ( )                                            ;
    dt  = t2 - t1                                                            ;
    if ( ms > 0 )                                                            {
      dt /= ms                                                               ;
      variables [ "TSC" ] = dt                                               ;
    }                                                                        ;
    Time::msleep ( variables [ "SystemInterval" ] . toInt ( ) )              ;
  }                                                                          ;
  ////////////////////////////////////////////////////////////////////////////
  SystemDetails * x = (SystemDetails *) data                                 ;
  if ( NULL != local )                                                       {
    local -> occupied = 0                                                    ;
    ::memset ( local , 0 , sizeof(ProcessDetails) )                          ;
  }                                                                          ;
  if ( NULL != x ) x -> processes . processes --                             ;
  variables [ "Running" ] = false                                            ;
}

void N::MachineProfiler::Caller(ThreadData * d)
{
}
