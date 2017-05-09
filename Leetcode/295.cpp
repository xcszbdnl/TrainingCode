#include <cstdio>
#include <cstring>
#include <priority_queue>

class MedianFinder {
public:
    /** initialize your data structure here. */
    int odd;
    priority_queue<int> small, large;
    MedianFinder() {
        odd = 0;
    }

    void addNum(int num) {
        if (odd) {
            small.push(num);
            large.push(-small.top());
            small.pop();
        }
        else {
            large.push(-num);
            small.push(-large.top());
            large.pop();
        }
        odd ^= 1;
    }

    double findMedian() {
        if (odd) {
            return small.top();
        }
        else {
            return (small.top() - large.top()) / 2.0;
        }
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder obj = new MedianFinder();
 * obj.addNum(num);
 * double param_2 = obj.findMedian();
 */
