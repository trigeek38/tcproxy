# tcproxy #
tcproxy is a small efficient tcp proxy for linux that can be used to port forwarding or load balance.

# sample usage #
  * tcproxy "any:11212 -> 11211"
  * tcproxy -d "192.168.0.1:11212 -> 192.168.0.2:11211"
  * tcproxy "any:11212 -> rr{192.168.0.100:11211 192.168.0.101:11211 192.168.0.102:11211}"
  * tcproxy "any:11212 -> hash{192.168.0.100:11211 192.168.0.101:11211 192.168.0.102:11211}"

see https://github.com/dccmx/tcproxy for new versions