etcd-iot
========

Internet of Things using etcd

teva-c-connected: Texas Instruments Teva C Connected Launchpad using [Energia](http://energia.nu)  
spark-core: [Spark Core](http://spark.io)  

Connects to specified etcd server and advertises its service, IP adress, and port number for that service, then starts accepting HTTP connections.

## Usage Example
Suppose you have a network of sensors that when '/' is requested on a certain port, they return a temperature and coordinates.  
On the central computer, you could have a script running at intervals that checks etcd for sensors, and gets the values for all and maps them.  
More sensors could be added, with the only configuration needed being the IP of the central computer and the name of the service.
