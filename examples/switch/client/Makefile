CXX=c++

client:
	$(CXX) Client.cc OFClient.cc base/BaseOFClient.cc -Ibase -lfluid_base -lfluid_msg -lpthread -levent -levent_pthreads -o client

clean:
	rm client
