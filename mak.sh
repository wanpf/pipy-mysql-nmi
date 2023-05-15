
gcc -I/root/pipy/pipy/include -I/root/pipy/pipy/src -I/usr/include/mysql /root/pipy/pipy/samples/nmi/pipy-mysql-nmi/mysql.c libmysqlclient.a libssl.a libcrypto.a -lstdc++ -lpthread -lm -ldl -fPIC -shared -o /root/pipy/pipy/samples/nmi/pipy-mysql-nmi/mysql-nmi.so 

