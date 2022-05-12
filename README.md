# xmlrpc-c_example
A simple standalone XML-RPC Abyss HTTP/1.1 server with an appropriate client - written in C example programs inspired by https://sourceforge.net/p/xmlrpc-c/code/HEAD/tree/trunk/examples/

## Installing requirements

To build the programs, you first need to install the following third-party development utilities and libraries:
```
clang gcc git make libcurl4-openssl-dev libssl-dev
```
Also, you need to install XML-RPC C development libraries.

### Third-party development utilities and libraries
On Debian-based OS the required third-party development utilities and libraries can be installed with the following command:
```
sudo apt update
sudo apt install clang gcc git make libcurl4-openssl-dev libssl-dev
```

### XML-RPC C development libraries
The required XML-RPC C development libraries can be installed with the following commands:
```
cd ~/
wget -c https://sourceforge.net/projects/xmlrpc-c/files/Xmlrpc-c%20Super%20Stable/1.54.05/xmlrpc-c-1.54.05.tgz
tar -xvf xmlrpc-c-1.54.05.tgz
cd xmlrpc-c-1.54.05
./configure
make
sudo make install
sudo ldconfig
```
Now you may remove `~/xmlrpc-c-1.54.05.tgz` and `~/xmlrpc-c-1.54.05`
```
rm -rf ~/xmlrpc-c-1.54.05.tgz ~/xmlrpc-c-1.54.05
```

## Building
The programs can be built with the following commands:
```
cd ~/
git clone https://github.com/mxsleo/xmlrpc-c_example.git
cd xmlrpc-c_example
make
```
Also, the build system supports building only server or client and performing cleanup:
```
make server
make client
make clean
```

## Usage

### Server
To **start** the server, you can use the following command:
```
./unix_server <port>
```
For example,
```
./unix_server 8080
```
Also, you may execute it as a **background** task:
```
./unix_server <port> &
```
To return the process to foreground, use:
```
fg [<PID>]
```
To **stop** the server, use `Ctrl+C`

### Client
To start the client, you can use the following command:
```
./unix_client <server ip> <port>
```
For example,
```
./unix_client 192.168.0.10 8080
./unix_client localhost 8080
```

### Tracing
If you want to discover, what is being transmitted over the network during the communication between the programs, use the following command:
```
sudo tcpdump -i any -A port <port>
```
