pipy()

  .import({
    __mysqlIp: 'mysql-nmi',
    __mysqlPort: 'mysql-nmi',
    __mysqlUser: 'mysql-nmi',
    __mysqlPasswd: 'mysql-nmi',
    __mysqlSql: 'mysql-nmi',
  })

  .task()
  .onStart(
    () => (
      __mysqlIp = '127.0.0.1',
      __mysqlPort = '3305',
      __mysqlUser = 'root',
      __mysqlPasswd = '123456',
      __mysqlSql = 'show slave status',
      new Message()
    )
  )
  .use('./mysql-nmi.so')
  .replaceMessage(
    msg => (
      console.log('mysql-nmi message:', msg),
      msg?.head?.result == '0' && console.log('master mysql'),
      msg?.head?.result == '1' && console.log('slave mysql'),
      new Message()
    )
  )

  .task()
  .onStart(
    () => (
      __mysqlIp = '127.0.0.1',
      __mysqlPort = '3306',
      __mysqlUser = 'root',
      __mysqlPasswd = '123456',
      __mysqlSql = 'show slave status',
      new Message()
    )
  )
  .use('./mysql-nmi.so')
  .replaceMessage(
    msg => (
      console.log('mysql-nmi message:', msg),
      msg?.head?.result == '0' && console.log('master mysql'),
      msg?.head?.result == '1' && console.log('slave mysql'),
      new Message()
    )
  )

  .task()
  .onStart(
    () => (
      __mysqlIp = '127.0.0.1',
      __mysqlPort = '3307',
      __mysqlUser = 'root',
      __mysqlPasswd = '123456',
      __mysqlSql = 'show slave status',
      new Message()
    )
  )
  .use('./mysql-nmi.so')
  .replaceMessage(
    msg => (
      console.log('mysql-nmi message:', msg),
      msg?.head?.result == '0' && console.log('master mysql'),
      msg?.head?.result == '1' && console.log('slave mysql'),
      new Message()
    )
  )
