#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

using namespace std;
using namespace boost::asio;


typedef boost::shared_ptr<ip::tcp::socket> socket_ptr;


int main()
{

    io_service service;
    ip::tcp::resolver resolver(service);
    ip::tcp::resolver::query query("google.com", "80");
    ip::tcp::resolver::iterator iter = resolver.resolve(query);
    ip::tcp::endpoint ep = *iter;

    cout << ep.address().to_string() << ":" << ep.port() << endl;

    ip::tcp::socket sock(service);
    sock.open(ip::tcp::v4());
    sock.connect(ep);
    sock.write_some(buffer("GET"));
    char buff[1024]; sock.read_some(buffer(buff,1024));
    sock.shutdown(ip::tcp::socket::shutdown_receive);
    sock.close();

    cout << buff << endl;



    return 0;
}
