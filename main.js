pipy()

// test case 1

  .task()
  .onStart(
    () => (
      new Message({
        mysqlIp: '127.0.0.1',
        mysqlPort: 3305,
        mysqlUser: 'root',
        mysqlPasswd: '123456',
        mysqlSql: 'show slave status'
      })
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

// test case 2

  .task()
  .onStart(
    () => (
      new Message({
        mysqlIp: '127.0.0.1',
        mysqlPort: 3306,
        mysqlUser: 'root',
        mysqlPasswd: '123456',
        mysqlSql: 'show slave status'
      })
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


// test case 3

  .task()
  .onStart(
    () => (
      new Message({
        mysqlIp: '127.0.0.1',
        mysqlPort: 3307,
        mysqlUser: 'root',
        mysqlPasswd: '123456',
        mysqlSql: 'show slave status'
      })
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

