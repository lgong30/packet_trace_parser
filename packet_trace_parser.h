//
// Created by Long Gong on 10/23/16.
//

#ifndef PACKET_TRACE_PARSER_PACKET_TRACE_PARSER_H
#define PACKET_TRACE_PARSER_PACKET_TRACE_PARSER_H

#include <iostream>
#include <string>
#include <functional>  // for std::hash
#include <fstream>
#include <boost/asio.hpp> // for ip

class packet_header{
public:
    std::string src_ip;
    std::string dst_ip;
    unsigned protocol;
    unsigned src_port;
    unsigned dst_port;
    packet_header(): src_ip(""), dst_ip(""), protocol(0), src_port(0), dst_port(0){}
    std::string to_string(bool only_ip=false) const{
        if (only_ip) return src_ip + dst_ip;
        else return src_ip + std::to_string(src_port) + dst_ip + std::to_string(dst_port) + std::to_string(protocol);
    }
    bool operator==(const packet_header& other) const{
        return  (src_ip == other.src_ip &&
                 dst_ip == other.dst_ip &&
                 src_port == other.src_port &&
                 dst_port == other.dst_port &&
                 protocol == other.protocol);
    }
    bool valid(){
        bool vflag = true;
        boost::system::error_code ec1, ec2;
        boost::asio::ip::address::from_string(src_ip,ec1);
        if (ec1) {vflag = false; std::cerr << "Source IP Error: " + ec1.message() << std::endl;}
        boost::asio::ip::address::from_string(dst_ip,ec2);
        if (ec2) {vflag = false; std::cerr << "Destionation IP Error: " + ec2.message() << std::endl;}
        if (!(protocol < 256)) {vflag = false; std::cerr << "Protocol Invalid (" << protocol << ")" << std::endl;}
        if (!(src_port < 65536)) {vflag = false; std::cerr << "Source Port Invalid (" << src_port << ")" << std::endl;}
        if (!(dst_port < 65536)) {vflag = false; std::cerr << "Destination Port Invalid (" << dst_port << ")" << std::endl;}
        return vflag;
    }
};

std::istream& operator>>(std::istream& is, packet_header& obj){
    std::string ignore;
    is >> ignore
       >> ignore
       >> ignore;

    is >> obj.src_ip
       >> obj.dst_ip
       >> obj.protocol
       >> obj.src_port
       >> obj.dst_port
       >> ignore;

    return is;
}

std::ostream& operator<<(std::ostream& os, const packet_header& obj){
    os << "(" << obj.src_ip << ", "
              << obj.src_port << ", "
              << obj.dst_ip   << ", "
              << obj.dst_port << ", "
              << obj.protocol << ")";
    return os;
}

//namespace std
//{
//    template <> struct hash<packet_header>
//    {
//        typedef packet_header argument_type;
//        typedef std::size_t result_type;
//        result_type operator()(argument_type const & obj) const {
//            return std::hash<std::string>{}(obj.to_string());
//        }
//    };
//}

template <bool option>
class MyHash {
public:
    std::size_t operator()(packet_header const& obj) const
    {
        return std::hash<std::string>{}(obj.to_string(option));
    }
};

class packet_trace_parser {
public:
    std::string trace;
    std::ifstream is;
    packet_trace_parser(std::string const &trace_file): trace(trace_file), is(trace_file){

    }
    bool next(packet_header& ph){
        if (is) {is >> ph; return true;}
        else return false;
    }
    ~packet_trace_parser(){
        is.close();
    }
};


#endif //PACKET_TRACE_PARSER_PACKET_TRACE_PARSER_H
