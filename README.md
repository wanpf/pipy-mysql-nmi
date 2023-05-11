## 1. pipy-mysql-nmi 使用 pipy nmi 方式，探测 mysql 是主节点还是从节点

## 2. pjs 参考脚本   

### 2.1 导入变量
```bash
  .import({
    __mysqlIp: 'mysql-nmi',
    __mysqlPort: 'mysql-nmi',
    __mysqlUser: 'mysql-nmi',
    __mysqlPasswd: 'mysql-nmi',
    __mysqlSql: 'mysql-nmi',
  })
```

### 2.2 将待检测的 mysql 配置信息设置到导入的变量  
```bash
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
```

### 2.3 加载 mysql-nmi.so 模块，并获取检测结果  
```bash
  .use('./mysql-nmi.so')
  .replaceMessage(
    msg => (
      console.log('mysql-nmi message:', msg),
      msg?.head?.result == '0' && console.log('master mysql'),
      msg?.head?.result == '1' && console.log('slave mysql'),
      new Message()
    )
  )
```

### 2.4 结果说明  
如果 msg.head.result 为 0， 表示 mysql 主节点  
如果 msg.head.result 为 1， 表示 mysql 从节点  
如果是其他值，表示连接到 mysql 失败 （可能端口不通，也可能是用户名密码错误） 

### 2.5 演示图   
<img width="1192" alt="image" src="https://github.com/wanpf/pipy-mysql-nmi/assets/2276200/4f7f7355-337b-4118-87cb-636c57872e48">

## 3. 说明  
默认的 mysql-nmi.so 适用于 linux/x86-64 环境， 其他环境需要重新编译。 

