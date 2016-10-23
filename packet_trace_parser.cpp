//
// Created by Long Gong on 10/23/16.
//

#include "packet_trace_parser.h"
#include <unordered_map>

typedef std::unordered_map<packet_header, int, MyHash<false> > Flow_Counter;
int main()
{
    std::string trace("UNC.15");
    packet_trace_parser ptp(trace);
    packet_header ph;

    Flow_Counter flow_counters;

    while (ptp.next(ph)) {
        if (flow_counters.find(ph) == flow_counters.end()) flow_counters[ph] = 0;
        ++ flow_counters[ph];
    }

    for (Flow_Counter::iterator it = flow_counters.begin();it != flow_counters.end();++ it)
        std::cout << it->first << " --> " << it->second << std::endl;

    return 0;
}