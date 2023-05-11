
clang -I/var/root/cncf/wpf/pipy/include -I/var/root/cncf/wpf/pipy/src -I/usr/include/mysql /var/root/cncf/wpf/pipy/samples/nmi/pipy-mysql-nmi//mysql.c -L/usr/lib/x86_64-linux-gnu -l mysqlclient -lssl -lcrypto -lpthread -lstdc++ -ldl -fPIC -shared -o /var/root/cncf/wpf/pipy/samples/nmi/pipy-mysql-nmi//mysql-nmi.so

